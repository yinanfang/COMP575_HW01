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
    
    
    
//    RayTracer::tracePlaneForHW01(HorozonPlane, vec4(1,1,1,1), vec3(1,1,1));
//    RayTracer::traceSphereForHW01(sphere01, vec3(1,0,0));
//    RayTracer::traceSphereForHW01(sphere02, vec3(0,0.5,0));
//    RayTracer::traceSphereForHW01(sphere03, vec3(0,0,1));

    return pixels;
}

void RayTracer::renderImage()
{
    // Offset on the View Plane
    float co_u = View_Plane.LimitLeft, co_v = View_Plane.LimitBottom;
    
    float u_LimitLeft = View_Plane.LimitLeft;
    float v_LimitBottom = View_Plane.LimitBottom;
    float increment = 0.1/(512/2);
    for (int i = 0; i < 512; i++) {
        co_v = v_LimitBottom + increment*i;
        for (int j = 0; j < 512; j++) {
            co_u = u_LimitLeft + increment*j;
            
            HitRecord hitRecord = RayTracer::trace(co_u, co_v);
            
            vec3 ColorShade = Shader::shadePixel(hitRecord);
            
            pixels[(i*512+j)*4+0]=pow(ColorShade.r, (1/GammaValue));
            pixels[(i*512+j)*4+1]=pow(ColorShade.g, (1/GammaValue));
            pixels[(i*512+j)*4+2]=pow(ColorShade.b, (1/GammaValue));
            pixels[(i*512+j)*4+3]=1.0f;
        }
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

//void RayTracer::traceSphereForHW01(const Sphere& sphere, const vec3& k_d)
//{
//    // Offset on the View Plane
//    float co_u = View_Plane.LimitLeft, co_v = View_Plane.LimitBottom;
//    
//    float u_LimitLeft = View_Plane.LimitLeft;
//    float v_LimitBottom = View_Plane.LimitBottom;
//    float increment = 0.1/(512/2);
//    for (int i = 0; i < 512; i++) {
//        co_v = v_LimitBottom + increment*i;
//        for (int j = 0; j < 512; j++) {
//            co_u = u_LimitLeft + increment*j;
//   
//            
//            
//            vec3 eyeRay = EyeRay::getEyeRay(co_u, co_v, -View_Plane.distance);
//            
//            vec3 p = CameraPositionPoint;
//            vec3 d = eyeRay;
//            vec3 c = sphere.center;
//            float r = sphere.radius;
//            
//            float delta_a = dot(d,d);
//            float delta_b = 2.0*(dot(p,d)-dot(d, c));
//            float delta_c = dot(p,p)-2.0*(dot(c,p))+dot(c,c)-pow(r, 2);
//            float determinant = pow(delta_b, 2)-4.0*(delta_a*delta_c);
//
//            if (determinant > 0) {
//                // (-b - delta)/2a
//                float closerT = (-delta_b - glm::sqrt(determinant))/(2*delta_a);
//                vec3 intersectionPoint = p+closerT*d;
//                vec3 intersectionNormal = normalize(intersectionPoint-sphere.center);
//                
//                vec3 ColorShade = Shader::shadePixel(intersectionPoint, intersectionNormal, eyeRay);
//
//                pixels[(i*512+j)*4+0]=pow(ColorShade.r, (1/GammaValue));
//                pixels[(i*512+j)*4+1]=pow(ColorShade.g, (1/GammaValue));
//                pixels[(i*512+j)*4+2]=pow(ColorShade.b, (1/GammaValue));
//                pixels[(i*512+j)*4+3]=1.0f;
//            }
//        }
//    }
//    cout << "Finished! ";
//}
//
//
//
//void RayTracer::tracePlaneForHW01(const Plane& plane, const vec4& colorRGBA, const vec3& k_d)
//{
//    // Offset on the View Plane
//    float co_u = View_Plane.LimitLeft, co_v = View_Plane.LimitBottom;
//    
//    float u_LimitLeft = View_Plane.LimitLeft;
//    float v_LimitBottom = View_Plane.LimitBottom;
//    float increment = 0.1/(512/2);
//    for (int i = 0; i < 512; i++) {
//        co_v = v_LimitBottom + increment*i;
//        for (int j = 0; j < 512; j++) {
//            co_u = u_LimitLeft + increment*j;
//            
//            vec3 eyeRay = EyeRay::getEyeRay(co_u, co_v, -View_Plane.distance);
//            
//            float p_a = plane.a;
//            float p_b = plane.b;
//            float p_c = plane.c;
//            float p_d = plane.d;
//            vec3 p = CameraPositionPoint;
//            vec3 d = eyeRay;
//
//            float intersectT = -(p_a*p.x+p_b*p.y+p_c*p.z+p_d) / (p_a*d.x+p_b*d.y+p_c*d.z);
//            
//            if (intersectT>0) {
//                vec3 intersectionPoint = p+intersectT*d;
//                vec3 intersectionNormal = plane.normal;
//                
//                vec3 ColorShade = Shader::shadePixel(intersectionPoint, intersectionNormal, eyeRay);
//                
//                pixels[(i*512+j)*4+0]=pow(ColorShade.r, (1/GammaValue));
//                pixels[(i*512+j)*4+1]=pow(ColorShade.g, (1/GammaValue));
//                pixels[(i*512+j)*4+2]=pow(ColorShade.b, (1/GammaValue));
//                pixels[(i*512+j)*4+3]=1.0f;
//            }
//        }
//    }
//    cout << "Finished! ";
//}


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



//                vec3 incomingLight = normalize(intersectionPoint-LightSourcePoint);
//                float n_dot_l = dot(intersectionNormal, incomingLight);
//                float larger_one = (n_dot_l>0.0)?n_dot_l:0.0;
//                vec3 L_d = k_d * 10.0f * (larger_one);
//
//                pixels[(i*512+j)*4+0]=L_d.r;
//                pixels[(i*512+j)*4+1]=L_d.g;
//                pixels[(i*512+j)*4+2]=L_d.b;
//                pixels[(i*512+j)*4+3]=colorRGBA.a;
//
//                pixels[(i*512+j)*4+0]=colorRGBA.r;
//                pixels[(i*512+j)*4+1]=colorRGBA.g;
//                pixels[(i*512+j)*4+2]=colorRGBA.b;
//                pixels[(i*512+j)*4+3]=colorRGBA.a;

//                pixels[(i*512+j)*4+0]=colorRGBA.r;
//                pixels[(i*512+j)*4+1]=colorRGBA.g;
//                pixels[(i*512+j)*4+2]=colorRGBA.b;
//                pixels[(i*512+j)*4+3]=colorRGBA.a;

//    // Draw pixels
//    for(int i=0;i<size*4;i+=4) {
//        pixels[i]   = 0.5;  // R
//        pixels[i+1] = 1;    // G
//        pixels[i+2] = 0.5;  // B
//        pixels[i+3] = 1;    // A
//    }


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