//
// Effect File Workshop Exercise 9
// Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//

vector lhtR;    // Light direction

matrix mWld;    // World
matrix mTot;    // Total

texture tDif;   // Diffuse texture of object
texture tDf3;   // Normal map for earth

texture tL10;   // Light lookup texture for spec
texture tL80;
texture tL64;
texture tL32;
texture tL16;

vector vCPS;    // Camera Position

// Background color
DWORD  BCLR = 0xFF0000FF;

pixelshader pNIL;

string XFile = "sphere.x";

// Technique names for display in viewer window
string tec0 = "Exercise 9a: Dot 3 Bump Mapping";
string tec1 = "Exercise 9b: Dot 3 Specular Bump Mapping";
string tec2 = "Exercise 9c: Table Lookup Specular Bump Mapping";

technique tec0
{ 
    pass p0
    {
        // Load matrices
        VertexShaderConstant[0] = (mWld); // World Matrix
        VertexShaderConstant[4] = (mTot); // World*View*Proj Matrix
 
        VertexShaderConstant[16] = (lhtR); //Light Direction

        // Camera information
        VertexShaderConstant[24] = (vCPS);	

        Texture[0]   = (tDif);
        Texture[1]   = (tDf3);
        wrap0        = U | V;
        wrap1        = U | V;
	
        AddressU[0] = wrap;
        AddressV[0] = wrap;
        AddressU[1] = wrap;
        AddressV[1] = wrap;

        MinFilter[0] = Linear;
        MagFilter[0] = Linear;
        MinFilter[1] = Linear;
        MagFilter[1] = Linear;

        VertexShader = 
        asm 
        {
            vs_1_1

            dcl_position   v0
            dcl_normal     v3
            dcl_texcoord0  v7
            dcl_texcoord1  v8


            // Material properties of object
            def c9, 0.8f,0.8f,0.8f,0.8f // Diffuse
            def c10, 0,0,0,0            // Specular
            def c11, 0,0,0,0            // Ambient
	
            // Properties of light	
            def c13, 0.7f,0.7f,0.7f,0.7f // Diffuse
            def c14, 0,0,0,0             // Specular
            def c15, 0,0,0,0             // Ambient
            def c20, 0.5f,0.5f,0.5f,0.5f 
	
            // Transform position
            m4x4 oPos,v0,c4
            
            // Transform normal and tangent
            m3x3 r7,v8,c0
            m3x3 r8,v3,c0
            
            // Cross product
            mul r0,-r7.zxy,r8.yzx;
            mad r5,-r7.yzx,r8.zxy,-r0;
            
            // Transform the light vector
            dp3 r6.x,r7,-c16
            dp3 r6.y,r5,-c16
            dp3 r6.z,r8,-c16
            
            // Multiply by a half to bias, then add half
            mad r6.xyz,r6.xyz,c20,c20
            
            mov oT0.xy,v7.xy
            mov oT1.xy,v7.xy
            mov oD0.xyz,r6.xyz
        };    
	
        PixelShader = 
        asm
        {
            ps_1_1
            tex t0	 // Sample texture
            tex t1	 // Sample normal
            mov r0,t1
            dp3	r0,t1_bx2,v0_bx2; // Dot(light,normal) 
            mul r0,t0,r0          // Modulate against base color
        }; 	
    }
}



technique tec1
{ 
    pass p0
    {
        // Load matrices
        VertexShaderConstant[0] = (mWld); // World Matrix
        VertexShaderConstant[4] = (mTot); // World*View*Proj Matrix
 
        VertexShaderConstant[16] = (lhtR); // Light Direction

        // Camera information
        VertexShaderConstant[24] = (vCPS);	

        Texture[0]   = (tDif);
        Texture[1]   = (tDf3);
        wrap0        = U | V;
        wrap1        = U | V;
        
        AddressU[0] = wrap;
        AddressV[0] = wrap;
        AddressU[1] = wrap;
        AddressV[1] = wrap;
        
        MinFilter[0] = Linear;
        MagFilter[0] = Linear;
        MinFilter[1] = Linear;
        MagFilter[1] = Linear;

        VertexShader = 
        asm 
        {
            vs_1_1

            dcl_position   v0
            dcl_normal     v3
            dcl_texcoord0  v7
            dcl_texcoord1  v8


            // Material properties of object
            def c9, 0.8f,0.8f,0.8f,0.8f // Diffuse
            def c10, 0,0,0,0            // Specular
            def c11, 0,0,0,0            // Ambient
	
            // Properties of light	
            def c13, 0.7f,0.7f,0.7f,0.7f // Diffuse
            def c14, 0,0,0,0             // Specular
            def c15, 0,0,0,0             // Ambient
            def c20, 0.5f,0.5f,0.5f,0.5f 

            // Transform position
            m4x4 oPos,v0,c4
            
            // Transform normal and tangent
            m3x3 r7,v8,c0
            m3x3 r8,v3,c0
            
            // Cross product
            mul r0,-r7.zxy,r8.yzx;
            mad r5,-r7.yzx,r8.zxy,-r0;
            
            // Transform position
            m4x4 r2,v0,c0
            
            // Get a vector toward the camera
            add r2,-r2,c24
            
            dp3 r11.x,r2.xyz,r2.xyz   // Load the square into r11
            rsq r11.xyz,r11.x         // Get the inverse of the square
            mul r2.xyz,r2.xyz,r11.xyz // Multiply, r0 = -(camera vector)
            
            add r2.xyz,r2.xyz,-c16    // Get half angle
            
            // Normalize
            dp3 r11.x,r2.xyz,r2.xyz   // Load the square into r1
            rsq r11.xyz,r11.x         // Get the inverse of the square
            mul r2.xyz,r2.xyz,r11.xyz // Multiply, r2 = HalfAngle
            
            
            // Transform the half angle vector
            dp3 r6.x,r7,r2
            dp3 r6.y,r5,r2
            dp3 r6.z,r8,r2
            
            // Multiply by a half to bias, then add half
            mad r6.xyz,r6.xyz,c20,c20
            
            mov oT0.xy,v7.xy
            mov oT1.xy,v7.xy
            mov oD0.xyz,r6.xyz
        };    
	
        PixelShader = 
        asm
        {
            ps_1_1
            tex t0                // Sample base map
            tex t1                // Sample normal
            dp3	r0,t1_bx2,v0_bx2; // Dot(normal,half)
            
            mul r1,r0,r0;         // Raise it to 32nd power
            mul r0,r1,r1; 
            mul r1,r0,r0;
            mul r0,r1,r1;
            mul r0,t0,r0
        }; 	
    }
}



technique tec2
{ 
    pass p0
    {
        // Load matrices
        VertexShaderConstant[0] = (mWld); // World Matrix
        VertexShaderConstant[4] = (mTot); // World*View*Proj Matrix
 
        VertexShaderConstant[16] = (lhtR); //Light Direction

        // Camera information
        VertexShaderConstant[24] = (vCPS);	

        Texture[0]   = (tDif);
        Texture[1]   = (tDf3);
 

        Texture[0]   = (tDif);
        Texture[1]   = (tDf3);
//        Texture[0]   = ;
//        Texture[2]   = ;
//        Texture[3]   = ;
        wrap0        = U | V;
        wrap1        = 0;
        wrap2        = 0;
        wrap3        = U | V;
	
        AddressU[0] = wrap;
        AddressV[0] = wrap;
        AddressU[1] = clamp;
        AddressV[1] = clamp;
        AddressU[2] = clamp;
        AddressV[2] = clamp;

        MinFilter[0] = Linear;
        MagFilter[0] = Linear;
        MinFilter[1] = Linear;
        MagFilter[1] = Linear;

        VertexShader = 
        asm 
        {
            vs_1_1

            dcl_position   v0
            dcl_normal     v3
            dcl_texcoord0  v7
            dcl_texcoord1  v8

            // Material properties of object
            def c9, 0.8f,0.8f,0.8f,0.8f // Diffuse
            def c10, 0,0,0,0            // Specular
            def c11, 0,0,0,0            // Ambient
	
            // Properties of light	
            def c13, 0.7f,0.7f,0.7f,0.7f // Diffuse
            def c14, 0,0,0,0             // Specular
            def c15, 0,0,0,0             // Ambient
            def c20, 0.5f,0.5f,0.5f,0.5f 

            // Transform position
            m4x4 oPos,v0,c4
            
            // Transform normal and tangent
            m3x3 r7,v8,c0
            m3x3 r8,v3,c0
            
            // Cross product
            mul r0,-r7.zxy,r8.yzx;
            mad r5,-r7.yzx,r8.zxy,-r0;
            
            // Transform position
            m4x4 r2,v0,c0
            
            // Get a vector toward the camera
            add r2,-r2,c24
            
            dp3 r11.x,r2.xyz,r2.xyz   // Load the square into r11
            rsq r11.xyz,r11.x         // Get the inverse of the square
            mul r2.xyz,r2.xyz,r11.xyz // Multiply, r0 = -(camera vector)
            
            add r2.xyz,r2.xyz,-c16    // Get half angle
            
            // Normalize
            dp3 r11.x,r2.xyz,r2.xyz   // Load the square into r1
            rsq r11.xyz,r11.x         // Get the inverse of the square
            mul r2.xyz,r2.xyz,r11.xyz // Multiply, r2 = HalfAngle
            
            // Transform the half angle vector
            dp3 r6.x,r7,r2
            dp3 r6.y,r5,r2
            dp3 r6.z,r8,r2
            
            mov oT0.xy,v7.xy         // Coordinate to samp normal from
            mov oT1.xyz,r6           // Not a tex coordinate, but half
            mov oT2.xyz,r6           // Angle
            mov oT3.xy,v7.xy
        };    
	
        PixelShader = 
        asm
        {
            ps_1_1
            tex t0	                // Sample normal
            texm3x2pad t1, t0_bx2   // Look it up in a table
            texm3x2tex t2, t0_bx2   
            tex t3                  // Sample base color
            
            mov r0,t2
            mul r0,r0,t3            // Blend terms
        }; 	
    }
}