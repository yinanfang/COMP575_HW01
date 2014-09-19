//
//  Shader.h
//  COMP575_HW01
//
//  Created by Golden Compass on 9/18/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#ifndef __COMP575_HW01__Shader__
#define __COMP575_HW01__Shader__

#include <iostream>
#include "Config.h"

using namespace std;

extern vec3 k_a, k_d, k_s;
extern float SpecularPower;
extern float GammaValue;



class Shader
{
private:
    
public:
    static vec3 shadePixel(const vec3& intersectPoint, const vec3& normal, const vec3& eyeRay);
};










#endif /* defined(__COMP575_HW01__Shader__) */
