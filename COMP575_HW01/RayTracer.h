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
using namespace std;
using namespace glm;
class Sphere;

class RayTracer
{
private:
    int test;
public:
    RayTracer(){}
    float* traceImage();
    void initVariables();
    void traceSphereForHW01(const Sphere& sphere, const vec4& colorRGBA);
};






#endif /* defined(__Test02__RayTracer__) */
