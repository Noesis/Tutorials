////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsGui/IntegrationAPI.h>
#include <NsGui/IRenderer.h>
#include <NsGui/IView.h>
#include <NsGui/Page.h>
#include <NsCore/HighResTimer.h>
#include <NsMath/Matrix.h>
#include <NsRender/D3D11Factory.h>
#include <NsApp/ThemeProviders.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>

#include "MainWindow.xaml.bin.h"
#include "Inconsolata-Bold.ttf.bin.h"

#include "Win32_DirectXAppUtil.h"
#include "OVR_CAPI_D3D.h"


// ovrSwapTextureSet wrapper class that also maintains the render target views needed for D3D11
struct OculusTexture
{
    ovrSession  session = nullptr;
    ovrTextureSwapChain textureChain = nullptr;
    ovrTextureSwapChain depthTextureChain = nullptr;
    Noesis::Vector<ID3D11RenderTargetView*, 4> texRtv;
    Noesis::Vector<ID3D11DepthStencilView*, 4> texDsv;

    bool Init(ovrSession session_, int sizeW, int sizeH, int sampleCount, bool createDepth)
    {
        session = session_;

        // create color texture swap chain first
        {
            ovrTextureSwapChainDesc desc = {};
            desc.Type = ovrTexture_2D;
            desc.ArraySize = 1;
            desc.Width = sizeW;
            desc.Height = sizeH;
            desc.MipLevels = 1;
            desc.SampleCount = sampleCount;
            desc.Format = OVR_FORMAT_R8G8B8A8_UNORM_SRGB;
            desc.MiscFlags = ovrTextureMisc_DX_Typeless | ovrTextureMisc_AutoGenerateMips;
            desc.BindFlags = ovrTextureBind_DX_RenderTarget;
            desc.StaticImage = ovrFalse;

            ovrResult result = ovr_CreateTextureSwapChainDX(session, DIRECTX.Device, &desc, &textureChain);
            if (!OVR_SUCCESS(result))
                return false;

            int textureCount = 0;
            ovr_GetTextureSwapChainLength(session, textureChain, &textureCount);
            for (int i = 0; i < textureCount; ++i)
            {
                ID3D11Texture2D* tex = nullptr;
                ovr_GetTextureSwapChainBufferDX(session, textureChain, i, IID_PPV_ARGS(&tex));

                D3D11_RENDER_TARGET_VIEW_DESC rtvd = {};
                rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                rtvd.ViewDimension = (sampleCount > 1) ? D3D11_RTV_DIMENSION_TEXTURE2DMS
                                                       : D3D11_RTV_DIMENSION_TEXTURE2D;
                ID3D11RenderTargetView* rtv;
                HRESULT hr = DIRECTX.Device->CreateRenderTargetView(tex, &rtvd, &rtv);
                VALIDATE((hr == ERROR_SUCCESS), "Error creating render target view");
                texRtv.PushBack(rtv);
                tex->Release();
            }
        }

        // if requested, then create depth swap chain
        if (createDepth)
        {
            ovrTextureSwapChainDesc desc = {};
            desc.Type = ovrTexture_2D;
            desc.ArraySize = 1;
            desc.Width = sizeW;
            desc.Height = sizeH;
            desc.MipLevels = 1;
            desc.SampleCount = sampleCount;
            desc.Format = OVR_FORMAT_D32_FLOAT_S8X24_UINT;
            desc.MiscFlags = ovrTextureMisc_None;
            desc.BindFlags = ovrTextureBind_DX_DepthStencil;
            desc.StaticImage = ovrFalse;

            ovrResult result = ovr_CreateTextureSwapChainDX(session, DIRECTX.Device, &desc, &depthTextureChain);
            if (!OVR_SUCCESS(result))
                return false;

            int textureCount = 0;
            ovr_GetTextureSwapChainLength(session, depthTextureChain, &textureCount);
            for (int i = 0; i < textureCount; ++i)
            {
                ID3D11Texture2D* tex = nullptr;
                ovr_GetTextureSwapChainBufferDX(session, depthTextureChain, i, IID_PPV_ARGS(&tex));

                D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
                dsvDesc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
                dsvDesc.ViewDimension = (sampleCount > 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS
                                                          : D3D11_DSV_DIMENSION_TEXTURE2D;
                dsvDesc.Texture2D.MipSlice = 0;

                ID3D11DepthStencilView* dsv;
                HRESULT hr = DIRECTX.Device->CreateDepthStencilView(tex, &dsvDesc, &dsv);
                VALIDATE((hr == ERROR_SUCCESS), "Error creating depth stencil view");
                texDsv.PushBack(dsv);
                tex->Release();
            }
        }

        return true;
    }

    ~OculusTexture()
    {
        for (int i = 0; i < (int)texRtv.Size(); ++i)
        {
            Release(texRtv[i]);
        }

        for (int i = 0; i < (int)texDsv.Size(); ++i)
        {
          Release(texDsv[i]);
        }

        if (textureChain)
        {
            ovr_DestroyTextureSwapChain(session, textureChain);
        }

        if (depthTextureChain)
        {
            ovr_DestroyTextureSwapChain(session, depthTextureChain);
        }
    }

    ID3D11RenderTargetView* GetRTV()
    {
        int index = 0;
        ovr_GetTextureSwapChainCurrentIndex(session, textureChain, &index);
        return texRtv[index];
    }

    ID3D11DepthStencilView* GetDSV()
    {
      int index = 0;
      ovr_GetTextureSwapChainCurrentIndex(session, depthTextureChain, &index);
      return texDsv[index];
    }

    void Commit()
    {
        ovr_CommitTextureSwapChain(session, textureChain);
        ovr_CommitTextureSwapChain(session, depthTextureChain);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
static bool MainLoop(bool retryCreate)
{
    // Initialize these to nullptr here to handle device lost failures cleanly
    ovrMirrorTexture mirrorTexture = nullptr;
    OculusTexture  * pEyeRenderTexture[2] = { nullptr, nullptr };
    Scene          * roomScene = nullptr; 
    Camera         * mainCam = nullptr;
    ovrMirrorTextureDesc mirrorDesc = {};
    long long frameIndex = 0;
    int msaaRate = 4;

    ovrSession session;
    ovrGraphicsLuid luid;
    ovrResult result = ovr_Create(&session, &luid);
    if (!OVR_SUCCESS(result))
        return retryCreate;

    ovrHmdDesc hmdDesc = ovr_GetHmdDesc(session);

    // Setup Device and Graphics
    // Note: the mirror window can be any size, for this sample we use 1/2 the HMD resolution
    DIRECTX.InitDevice(hmdDesc.Resolution.w / 2, hmdDesc.Resolution.h / 2, reinterpret_cast<LUID*>(&luid));

    // Make the eye render buffers (caution if actual size < requested due to HW limits). 
    ovrRecti         eyeRenderViewport[2];

    for (int eye = 0; eye < 2; ++eye)
    {
        ovrSizei idealSize = ovr_GetFovTextureSize(session, (ovrEyeType)eye, hmdDesc.DefaultEyeFov[eye], 1.0f);
        pEyeRenderTexture[eye] = new OculusTexture();
        if (!pEyeRenderTexture[eye]->Init(session, idealSize.w, idealSize.h, msaaRate, true))
        {
            FATALERROR("Failed to create eye texture.");
        }
        eyeRenderViewport[eye].Pos.x = 0;
        eyeRenderViewport[eye].Pos.y = 0;
        eyeRenderViewport[eye].Size = idealSize;
        if (!pEyeRenderTexture[eye]->textureChain || !pEyeRenderTexture[eye]->depthTextureChain)
        {
            FATALERROR("Failed to create texture.");
        }
    }

    // Create a mirror to see on the monitor.
    mirrorDesc.Format = OVR_FORMAT_R8G8B8A8_UNORM_SRGB;
    mirrorDesc.Width = DIRECTX.WinSizeW;
    mirrorDesc.Height = DIRECTX.WinSizeH;
    mirrorDesc.MirrorOptions = ovrMirrorOption_Default;
    result = ovr_CreateMirrorTextureWithOptionsDX(session, DIRECTX.Device, &mirrorDesc, &mirrorTexture);
    
    if (!OVR_SUCCESS(result))
    {
        FATALERROR("Failed to create mirror texture.");
    }

    // Create the room model
    roomScene = new Scene(false);

    // Create camera
    mainCam = new Camera(XMVectorSet(0.0f, 0.0f, 5.0f, 0), XMQuaternionIdentity());

    // FloorLevel will give tracking poses where the floor height is 0
    ovr_SetTrackingOriginType(session, ovrTrackingOrigin_FloorLevel);

    // Noesis initialization
    Noesis::GUI::SetLogHandler([](const char*, uint32_t, uint32_t level, const char*, const char* msg)
    {
        char out[512];
        const char* prefixes[] = { "T", "D", "I", "W", "E" };
        snprintf(out, sizeof(out), "[NOESIS/%s] %s\n", prefixes[level], msg);
        OutputDebugStringA(out);
    });

    NoesisApp::EmbeddedXaml xamls[] = 
    {
        { "MainWindow.xaml", MainWindow_xaml },
    };

    NoesisApp::EmbeddedFont fonts[] = 
    {
        { "Fonts", Inconsolata_Bold_ttf }
    };

    Noesis::Ptr<Noesis::XamlProvider> xamlProvider = Noesis::MakePtr<NoesisApp::EmbeddedXamlProvider>(xamls);
    Noesis::Ptr<Noesis::FontProvider> fontProvider = Noesis::MakePtr<NoesisApp::EmbeddedFontProvider>(fonts);

    Noesis::GUI::SetLicense(NS_LICENSE_NAME, NS_LICENSE_KEY);

    Noesis::GUI::Init();
    NoesisApp::SetThemeProviders(xamlProvider, fontProvider);
    Noesis::GUI::LoadApplicationResources("Theme/NoesisTheme.DarkBlue.xaml");

    Noesis::Ptr<Noesis::IView> uiView = Noesis::GUI::CreateView(Noesis::GUI::LoadXaml<Noesis::Page>("MainWindow.xaml"));
    uiView->SetTessellationMaxPixelError(Noesis::TessellationMaxPixelError::HighQuality());
    uiView->GetRenderer()->Init(NoesisApp::D3D11Factory::CreateDevice(DIRECTX.Context, false));
    uiView->SetSize(eyeRenderViewport[0].Size.w, eyeRenderViewport[0].Size.h);

    uint64_t t0 = Noesis::HighResTimer::Ticks();

    // Main loop
    while (DIRECTX.HandleMessages())
    {
        ovrSessionStatus sessionStatus;
        result = ovr_GetSessionStatus(session, &sessionStatus);
        if(OVR_FAILURE(result))
          FATALERROR("Connection failed.");

        if (sessionStatus.ShouldQuit)
        {
            // Because the application is requested to quit, should not request retry
            retryCreate = false;
            break;
        }
        if (sessionStatus.ShouldRecenter)
            ovr_RecenterTrackingOrigin(session);

        if (sessionStatus.IsVisible)
        {
            uiView->Update(Noesis::HighResTimer::Seconds(Noesis::HighResTimer::Ticks() - t0));
            uiView->GetRenderer()->UpdateRenderTree();

            XMVECTOR forward = XMVector3Rotate(XMVectorSet(0, 0, -0.05f, 0), mainCam->Rot);
            XMVECTOR right   = XMVector3Rotate(XMVectorSet(0.05f, 0, 0, 0),  mainCam->Rot);
            if (DIRECTX.Key['W'] || DIRECTX.Key[VK_UP])      mainCam->Pos = XMVectorAdd(mainCam->Pos, forward);
            if (DIRECTX.Key['S'] || DIRECTX.Key[VK_DOWN])    mainCam->Pos = XMVectorSubtract(mainCam->Pos, forward);
            if (DIRECTX.Key['D'])                            mainCam->Pos = XMVectorAdd(mainCam->Pos, right);
            if (DIRECTX.Key['A'])                            mainCam->Pos = XMVectorSubtract(mainCam->Pos, right);
            static float Yaw = 0;
            if (DIRECTX.Key[VK_LEFT])  mainCam->Rot = XMQuaternionRotationRollPitchYaw(0, Yaw += 0.02f, 0);
            if (DIRECTX.Key[VK_RIGHT]) mainCam->Rot = XMQuaternionRotationRollPitchYaw(0, Yaw -= 0.02f, 0);

            // Animate the cube
            static float cubePositionClock = 0;
            if (sessionStatus.HasInputFocus) // Pause the application if we are not supposed to have input.
                roomScene->Models[0]->Pos = XMFLOAT3(9 * sinf(cubePositionClock), 3, 9 * cosf(cubePositionClock += 0.015f));
            
            // Call ovr_GetRenderDesc each frame to get the ovrEyeRenderDesc, as the returned values (e.g. HmdToEyePose) may change at runtime.
            ovrEyeRenderDesc eyeRenderDesc[2];
            eyeRenderDesc[0] = ovr_GetRenderDesc(session, ovrEye_Left, hmdDesc.DefaultEyeFov[0]);
            eyeRenderDesc[1] = ovr_GetRenderDesc(session, ovrEye_Right, hmdDesc.DefaultEyeFov[1]);

            // Get both eye poses simultaneously, with IPD offset already included. 
            ovrPosef EyeRenderPose[2];
            ovrPosef HmdToEyePose[2] = { eyeRenderDesc[0].HmdToEyePose,
                                         eyeRenderDesc[1].HmdToEyePose};

            double sensorSampleTime;    // sensorSampleTime is fed into the layer later
            ovr_GetEyePoses(session, frameIndex, ovrTrue, HmdToEyePose, EyeRenderPose, &sensorSampleTime);

            ovrTimewarpProjectionDesc posTimewarpProjectionDesc = {};

            // Render Scene to Eye Buffers
            for (int eye = 0; eye < 2; ++eye)
            {
                float eyeX = (float)eyeRenderViewport[eye].Pos.x;
                float eyeY = (float)eyeRenderViewport[eye].Pos.y;
                float eyeWidth = (float)eyeRenderViewport[eye].Size.w;
                float eyeHeight = (float)eyeRenderViewport[eye].Size.h;

                //Get the pose information in XM format
                XMVECTOR eyeQuat = XMVectorSet(EyeRenderPose[eye].Orientation.x, EyeRenderPose[eye].Orientation.y,
                                               EyeRenderPose[eye].Orientation.z, EyeRenderPose[eye].Orientation.w);
                XMVECTOR eyePos = XMVectorSet(EyeRenderPose[eye].Position.x, EyeRenderPose[eye].Position.y, EyeRenderPose[eye].Position.z, 0);

                // Get view and projection matrices for the Rift camera
                XMVECTOR CombinedPos = XMVectorAdd(mainCam->Pos, XMVector3Rotate(eyePos, mainCam->Rot));
                Camera finalCam(CombinedPos, XMQuaternionMultiply(eyeQuat,mainCam->Rot));
                XMMATRIX view = finalCam.GetViewMatrix();
                ovrMatrix4f p = ovrMatrix4f_Projection(eyeRenderDesc[eye].Fov, 0.2f, 1000.0f, ovrProjection_None);
                posTimewarpProjectionDesc = ovrTimewarpProjectionDesc_FromProjection(p, ovrProjection_None);
                XMMATRIX proj = XMMatrixSet(p.M[0][0], p.M[1][0], p.M[2][0], p.M[3][0],
                                            p.M[0][1], p.M[1][1], p.M[2][1], p.M[3][1],
                                            p.M[0][2], p.M[1][2], p.M[2][2], p.M[3][2],
                                            p.M[0][3], p.M[1][3], p.M[2][3], p.M[3][3]);
                XMMATRIX prod = XMMatrixMultiply(view, proj);


#if 1
                // UI location attached to the cameta
                XMMATRIX prod_ = XMMatrixMultiply(Camera(eyePos,  eyeQuat).GetViewMatrix(), proj);
                Noesis::Matrix4 viewport = Noesis::Matrix4::Viewport(eyeWidth, eyeHeight);
                Noesis::Matrix4 offset = Noesis::Transform3::Trans(-1.4f, -0.2f, -1.25f).ToMatrix4();
                Noesis::Matrix4 scale = Noesis::Transform3::Scale(0.002f, 0.002f, -0.002f).ToMatrix4();
                Noesis::Matrix4 eyeMtx = scale * offset * (*(Noesis::Matrix4*)&prod_) * viewport;
#else
                // UI location fixed in the world
                Noesis::Matrix4 viewport = Noesis::Matrix4::Viewport(eyeWidth, eyeHeight);
                Noesis::Matrix4 offset = Noesis::Transform3::Trans(-0.5f, -0.25f, -0.5f).ToMatrix4();
                Noesis::Matrix4 scale = Noesis::Transform3::Scale(0.002f, 0.002f, -0.002f).ToMatrix4();
                Noesis::Matrix4 eyeMtx = scale * offset * (*(Noesis::Matrix4*)&prod) * viewport;
#endif

                // UI Offscreen textures
                uiView->GetRenderer()->RenderOffscreen(eyeMtx);
                DIRECTX.Context->VSSetConstantBuffers(0, 1, &DIRECTX.UniformBufferGen->D3DBuffer);

                // Clear and set up rendertarget
                DIRECTX.SetAndClearRenderTarget(pEyeRenderTexture[eye]->GetRTV(), pEyeRenderTexture[eye]->GetDSV());
                DIRECTX.SetViewport(eyeX, eyeY, eyeWidth, eyeHeight);

                // Render scene
                roomScene->Render(&prod, 1, 1, 1, 1, true);

                // Render UI
                uiView->GetRenderer()->Render(eyeMtx);

                // Commit rendering to the swap chain
                pEyeRenderTexture[eye]->Commit();
            }

            // Initialize our single full screen Fov layer.
            ovrLayerEyeFovDepth ld = {};
            ld.Header.Type = ovrLayerType_EyeFovDepth;
            ld.Header.Flags = 0;
            ld.ProjectionDesc = posTimewarpProjectionDesc;
            ld.SensorSampleTime = sensorSampleTime;

            for (int eye = 0; eye < 2; ++eye)
            {
                ld.ColorTexture[eye] = pEyeRenderTexture[eye]->textureChain;
                ld.DepthTexture[eye] = pEyeRenderTexture[eye]->depthTextureChain;
                ld.Viewport[eye] = eyeRenderViewport[eye];
                ld.Fov[eye] = hmdDesc.DefaultEyeFov[eye];
                ld.RenderPose[eye] = EyeRenderPose[eye];
            }
            
            ovrLayerHeader* layers = &ld.Header;
            result = ovr_SubmitFrame(session, frameIndex, nullptr, &layers, 1);
            // exit the rendering loop if submit returns an error, will retry on ovrError_DisplayLost
            if (!OVR_SUCCESS(result))
                break;

            frameIndex++;
        }

        // Render mirror
        ID3D11Texture2D* tex = nullptr;
        ovr_GetMirrorTextureBufferDX(session, mirrorTexture, IID_PPV_ARGS(&tex));

        DIRECTX.Context->CopyResource(DIRECTX.BackBuffer, tex);
        tex->Release();
        DIRECTX.SwapChain->Present(0, 0);
    }

    // Release resources
    uiView->GetRenderer()->Shutdown();

    delete mainCam;
    delete roomScene;

    if (mirrorTexture)
        ovr_DestroyMirrorTexture(session, mirrorTexture);

    for (int eye = 0; eye < 2; ++eye)
    {
        delete pEyeRenderTexture[eye];
    }

    DIRECTX.ReleaseDevice();
    ovr_Destroy(session);

    // Retry on ovrError_DisplayLost
    return retryCreate || (result == ovrError_DisplayLost);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int)
{
    // Initializes LibOVR, and the Rift
    ovrInitParams initParams = { ovrInit_RequestVersion | ovrInit_FocusAware, OVR_MINOR_VERSION, NULL, 0, 0 };
    ovrResult result = ovr_Initialize(&initParams);
    VALIDATE(OVR_SUCCESS(result), "Failed to initialize libOVR.");

    VALIDATE(DIRECTX.InitWindow(hinst, L"Oculus NoesisGUI"), "Failed to open window.");

    DIRECTX.Run(MainLoop);

    ovr_Shutdown();
    return(0);
}