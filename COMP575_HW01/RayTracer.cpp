//
//  RayTracer.cpp
//  Test02
//
//  Created by Golden Compass on 9/17/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#include "RayTracer.h"

std::vector<Object*> objectsList;
Sphere *sphere01, *sphere02, *sphere03;
Plane *HorizontalPlane;

float* RayTracer::runRayTracer()
{
    RayTracer::initVariables();

    RayTracer::renderImage();

    return pixels;
}

void RayTracer::renderImage()
{
    // Offset on the View Plane
    float co_u = View_Plane.LimitLeft, co_v = View_Plane.LimitBottom;
    
    // First loop for locating each pixel
    float u_LimitLeft = View_Plane.LimitLeft;
    float v_LimitBottom = View_Plane.LimitBottom;
    float increment = 0.1/(512/2);
    for (int i = 0; i < 512; i++) {
        co_v = v_LimitBottom + increment*i;
        for (int j = 0; j < 512; j++) {
            co_u = u_LimitLeft + increment*j;
            // Second loop for Antialiasing
            vec3 ColorShade;
            vec3 colorSum = vec3(0,0,0);
            float co_v_rand, co_u_rand;
            int anti_Num = 64;
            float AntialiasingInterval = increment/anti_Num;
            for (int m = 0; m < anti_Num; m++) {
                co_v_rand = co_v + AntialiasingInterval*(rand()%anti_Num);
                co_u_rand = co_u + AntialiasingInterval*(rand()%anti_Num);
                
                HitRecord hitRecord = RayTracer::trace(co_u_rand, co_v_rand);
                ColorShade = Shader::shadePixel(hitRecord);
                colorSum += ColorShade;
            }
            ColorShade = vec3(colorSum.r/anti_Num, colorSum.g/anti_Num, colorSum.b/anti_Num);
            
            
            pixels[(i*512+j)*4+0]=pow(ColorShade.r, (1/GammaValue));
            pixels[(i*512+j)*4+1]=pow(ColorShade.g, (1/GammaValue));
            pixels[(i*512+j)*4+2]=pow(ColorShade.b, (1/GammaValue));
            pixels[(i*512+j)*4+3]=1.0f;
        }
        cout << "Finished line from bottome: " << i << "\n";
    }
}

HitRecord RayTracer::trace(float co_u, float co_v)
{
    vec3 eyeRay = EyeRay::getEyeRay(co_u, co_v, -View_Plane.distance);
    HitRecord current, best;
    best.eyeRay.multiple = Infinity;
    
    for (int i=0; i<objectsList.size(); i++) {
        Object *object = objectsList[i];
        if (object->isIntersectedByRay(CameraPositionPoint, eyeRay)) {
            current = object->getHitRecord(CameraPositionPoint, eyeRay);
            if (current.eyeRay.multiple<best.eyeRay.multiple) {
                best = current;
                best.object = object;
            }
        }
    }
    return best;
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
    LightSourcePoint = vec3(-4, 4, -3);
    LightIllumination = vec3(1, 1, 1);
    
    // Object
    HorizontalPlane = new Plane(vec3(0,-2,0), vec3(0,1,0));
    objectsList.push_back(HorizontalPlane);
    HorizontalPlane->k_a = vec3(0.2,0.2,0.2);
    HorizontalPlane->k_d = vec3(1,1,1);
    HorizontalPlane->k_s = vec3(0,0,0);
    HorizontalPlane->SpecularPower = 0.0;
    
    sphere01 = new Sphere(vec3(-4, 0, -7), 1);
    objectsList.push_back(sphere01);
    sphere01->k_a = vec3(0.2,0,0);
    sphere01->k_d = vec3(1,0,0);
    sphere01->k_s = vec3(0,0,0);
    sphere01->SpecularPower = 0.0;
    
    sphere02 = new Sphere(vec3(0, 0, -7), 2);
    objectsList.push_back(sphere02);
    sphere02->k_a = vec3(0,0.2,0);
    sphere02->k_d = vec3(0,0.5,0);
    sphere02->k_s = vec3(0.5,0.5,0.5);
    sphere02->SpecularPower = 32.0;
    
    sphere03 = new Sphere(vec3(4, 0, -7), 1);
    objectsList.push_back(sphere03);
    sphere03->k_a = vec3(0,0,0.2);
    sphere03->k_d = vec3(0,0,1);
    sphere03->k_s = vec3(0,0,0);
    sphere03->SpecularPower = 0.0;
}