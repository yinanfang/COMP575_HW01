//
//  RayTracer.h
//  Test02
//
//  Created by Golden Compass on 9/17/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#ifndef __Test02__RayTracer__
#define __Test02__RayTracer__

#include <iostream>
#include "Config.h"
#include "Object.h"
#include <vector>
using namespace std;
using namespace glm;
class Sphere;
class Plane;
class HitRecord;

class RayTracer
{
private:
    int test;
public:
    RayTracer(){}
    float* runRayTracer();
    void initVariables();
    void renderImage();
    HitRecord trace(float co_u, float co_v);
};






#endif /* defined(__Test02__RayTracer__) */
