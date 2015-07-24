#include "pch.h"


using namespace Noesis;


class MyTouch: public Grid
{
public:
    void OnManipulationStarting(const ManipulationStartingEventArgs& e)
    {
        e.mode = ManipulationModes_All;
        e.manipulationContainer = (Visual*)FindName("root");
        e.handled = true;
    }

    void OnManipulationInertiaStarting(const ManipulationInertiaStartingEventArgs& e)
    {
        e.translationBehavior.desiredDeceleration = 100.0f / (1000.0f * 1000.0f);
        e.rotationBehavior.desiredDeceleration = 360.0f / (1000.0f * 1000.0f);
        e.expansionBehavior.desiredDeceleration = 300.0f / (1000.0f * 1000.0f);
        e.handled = true;
    }

    void OnManipulationDelta(const ManipulationDeltaEventArgs& e)
    {
        UIElement* rectangle = (UIElement*)e.source;
        MatrixTransform* tr = (MatrixTransform*)rectangle->GetRenderTransform();
        Transform2f mtx = tr->GetMatrix();

        mtx.RotateAt(e.deltaManipulation.rotation * DegToRad_f, e.manipulationOrigin.x,
            e.manipulationOrigin.y);
        mtx.ScaleAt(e.deltaManipulation.scale, e.deltaManipulation.scale,
            e.manipulationOrigin.x, e.manipulationOrigin.y);
        mtx.Translate(e.deltaManipulation.translation.x, e.deltaManipulation.translation.y);

        tr->SetMatrix(mtx);
        e.handled = true;
    }

private:
     NS_IMPLEMENT_INLINE_REFLECTION(MyTouch, Grid)
     {
        NsMeta<TypeId>("MyTouch");
     }
};

extern "C" NS_DLL_EXPORT void NsRegisterReflection(ComponentFactory* factory, NsBool registerComponents)
{
    NS_REGISTER_COMPONENT(MyTouch)
}
