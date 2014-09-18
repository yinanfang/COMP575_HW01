//
//  Object.h
//  Test02
//
//  Created by Golden Compass on 9/17/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#ifndef __Test02__Object__
#define __Test02__Object__

#include <iostream>
#include "Config.h"

using namespace glm;

class Sphere
{
private:
    
public:
    vec3 center;
    float radius;
    
    Sphere(){}
    Sphere(vec3 center, float radius);
    
//    bool intersectByEyeRay(vec3 eyeRay);
};

class Plane
{
private:
    
public:
    float a;
    float b;
    float c;
    float d;
    
    Plane(){}
    Plane(float a, float b, float c, float d);
    Plane(vec3 point, vec3 normal);
};



#endif /* defined(__Test02__Object__) */
