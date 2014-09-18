//
//  RayTracer.cpp
//  Test02
//
//  Created by Golden Compass on 9/17/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#include "RayTracer.h"

Sphere sphere01, sphere02, sphere03;
Plane HorozonPlane;

float* RayTracer::traceImage()
{
    RayTracer::initVariables();

    // Offset on the View Plane
    float co_u = -0.1, co_v = -0.1;
    float u_LimitLeft = View_Plane.LimitLeft;
    float v_LimitBottom = View_Plane.LimitBottom;
    float increment = 0.1/(512/2);
    vec3 dotOnViewPlane  = co_u*WorldDirection_u + co_v*WorldDirection_v - View_Plane.distance*WorldDirection_w - CameraPositionPoint;
    for (int i = 0; i < 512; i++) {
        co_v = v_LimitBottom + increment*i;
        for (int j = 0; j < 512; j++) {
            co_u = u_LimitLeft + increment*j;
            
            dotOnViewPlane = co_u*WorldDirection_u + co_v*WorldDirection_v - View_Plane.distance*WorldDirection_w - CameraPositionPoint;
            vec3 eyeToDotOnViewPlane = dotOnViewPlane - CameraPositionPoint;
//            cout << "eyeToDotOnViewPlane: " << eyeToDotOnViewPlane;
            
            vec3 p = CameraPositionPoint;
            vec3 d = eyeToDotOnViewPlane;
            vec3 c = sphere01.center;
            float r = sphere01.radius;
            
            float delta_a = dot(d,d);
            float delta_b = 2.0*(dot(p,d)-dot(d, c));
            float delta_c = dot(p,p)-2.0*(dot(c,p))+dot(c,c)-pow(r, 2);
            
            float determinant = pow(delta_b, 2)-4.0*(delta_a*delta_c);
//            cout << "Result: " << determinant << "\n";
            
            if (determinant > 0) {
                cout << "Result: " << determinant << "\n";
                pixels[(i*512+j)*4]=0.5;
            }
        }
    }
    cout << "Finished! ";
    
    
    
    
    
//    // Draw pixels
//    for(int i=0;i<size*4;i+=4) {
//        pixels[i]   = 0.5;  // R
//        pixels[i+1] = 1;    // G
//        pixels[i+2] = 0.5;  // B
//        pixels[i+3] = 1;    // A
//    }
    return pixels;
}


void RayTracer::initVariables()
{
    // Camera
    CameraPositionPoint = vec3(0, 0, 0);
    CameraDirection = vec3(0, 0, -1);
    View_Plane = ViewPlane(-0.1, 0.1, -0.1, 0.1, 0.1);
    
    // World
    WorldDirection_u = vec3(1, 0, 0);
    WorldDirection_v = vec3(0, 1, 0);
    WorldDirection_w = vec3(0, 0, 1);
    
    // Object
    sphere01 = Sphere(vec3(-4, 0, -7), 1);
    sphere02 = Sphere(vec3(0, 0, -7), 2);
    sphere03 = Sphere(vec3(4, 0, -7), 1);
//    HorozonPlane = pla
    

}





//    // Calculation
//    vec3 dotOnViewPlane = co_u*WorldDirection_u + co_v*WorldDirection_v - View_Plane.distance*WorldDirection_w - CameraPositionPoint;
//    vec3 eyeToDotOnViewPlane = dotOnViewPlane - CameraPositionPoint;
//    cout << "eyeToDotOnViewPlane: " << eyeToDotOnViewPlane;
//
//    vec3 p = CameraPositionPoint;
//    vec3 d = eyeToDotOnViewPlane;
//    vec3 c = sphere01.center;
//    float r = sphere01.radius;
////    cout << "CameraPositionPoint: " << CameraPositionPoint;
////    cout << "sphere01.center: " << sphere01.center;
////    cout << "sphere01.radius: " << sphere01.radius;
//
//    // \Delta = \,b^2-4ac.
//    float delta_a = dot(d,d);
//    float delta_b = 2.0*(dot(p,d)-dot(d, c));
//    float delta_c = dot(p,p)-2.0*(dot(c,p))+dot(c,c)-pow(r, 2);
//
//    float determinant = pow(delta_b, 2)-4.0*(delta_a*delta_c);
//    cout << "Result: " << determinant << "\n";



//    float delta_a = dot(d,d);
//    float delta_b = 2.0*dot(d, (CameraPositionPoint-sphere01.center));
//    float delta_c = dot((CameraPositionPoint-sphere01.center), (CameraPositionPoint-sphere01.center))-pow(r, 2);