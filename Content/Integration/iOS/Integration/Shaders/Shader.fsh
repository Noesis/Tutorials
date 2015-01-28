//
//  Shader.fsh
//  Integration
//
//  Created by Jesus on 13/05/13.
//  Copyright (c) 2013 Noesis. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
