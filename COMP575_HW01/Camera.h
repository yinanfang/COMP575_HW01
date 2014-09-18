//
//  Camera.h
//  Test02
//
//  Created by Golden Compass on 9/17/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#ifndef __Test02__Camera__
#define __Test02__Camera__

#include <iostream>
#include "Config.h"
class ViewPlane;
class EyeRay;


using namespace glm;

extern vec3 CameraPositionPoint;
extern vec3 CameraDirection;
extern ViewPlane View_Plane;


class ViewPlane
{
private:
    
public:
    float LimitLeft;
    float LimitRight;
    float LimitBottom;
    float LimitTop;
    float distance;
    ViewPlane(){}
    ViewPlane(float _LimitLeft, float _LimitRight, float _LimitBottom, float _LimitTop, float _distance);
};



class EyeRay
{
private:
    vec3 eyePosition;
    vec3 rayDirection;
public:
    EyeRay(){}
    EyeRay(vec3 _eyePosition, vec3 _rayDirection);
    
    friend ostream& operator<<(ostream& os, const EyeRay& eyeRay);
};




#endif /* defined(__Test02__Camera__) */
