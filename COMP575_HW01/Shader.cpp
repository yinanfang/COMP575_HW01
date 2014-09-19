//
//  Shader.cpp
//  COMP575_HW01
//
//  Created by Golden Compass on 9/18/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#include "Shader.h"

float SpecularPower;
float GammaValue = 2.2;

vec3 Shader::shadePixel(const HitRecord& hitRecord)
{
    vec3 intersectPoint = hitRecord.hitPoint;
    vec3 eyeRay = hitRecord.eyeRay.vectorDirection;
    vec3 normal = hitRecord.normal;
    if (hitRecord.eyeRay.multiple == Infinity) {
        return vec3 (0,0,0);
    }
    
    
    vec3 colorRGB, L_a, L_d, L_s;
    vec3 incomingLightInverse = -normalize(intersectPoint-LightSourcePoint);
    vec3 eyeRayInverse = -normalize(eyeRay);
    
    // Ambient
    L_a = hitRecord.object->k_a;
    
    // Difuse
    float n_dot_l = dot(normal, incomingLightInverse);
    L_d = hitRecord.object->k_d * LightIllumination * std::max(0.0f, n_dot_l);
    
    // Blinn-Phong Specular
    vec3 v = eyeRayInverse;
    vec3 l = incomingLightInverse;
    vec3 h = normalize(v+l);
    float normal_dot_h = dot(normal, h);
    L_s = hitRecord.object->k_s * LightIllumination * pow(std::max(0.0f, normal_dot_h),SpecularPower);
    
    colorRGB = L_a + L_d + L_s;
    return colorRGB;
}


//vec3 Shader::shadePixel(const vec3& intersectPoint, const vec3& normal, const vec3& eyeRay)
//{
//    vec3 colorRGB, L_a, L_d, L_s;
//    vec3 incomingLightInverse = -normalize(intersectPoint-LightSourcePoint);
//    vec3 eyeRayInverse = -normalize(eyeRay);
//    
//    // Ambient
//    L_a = k_a;
//    
//    // Difuse
//    float n_dot_l = dot(normal, incomingLightInverse);
//    L_d = k_d * LightIllumination * std::max(0.0f, n_dot_l);
//    
//    // Blinn-Phong Specular
//    vec3 v = eyeRayInverse;
//    vec3 l = incomingLightInverse;
//    vec3 h = normalize(v+l);
//    float normal_dot_h = dot(normal, h);
//    L_s = k_s * LightIllumination * pow(std::max(0.0f, normal_dot_h),SpecularPower);
//    
//    colorRGB = L_a + L_d + L_s;
//    return colorRGB;
//}