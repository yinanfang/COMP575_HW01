//
//  Camera.cpp
//  Test02
//
//  Created by Golden Compass on 9/17/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#include "Camera.h"


vec3 CameraPositionPoint;
vec3 CameraDirection;
ViewPlane View_Plane;


ViewPlane::ViewPlane(float _LimitLeft, float _LimitRight, float _LimitBottom, float _LimitTop, float _distance)
{
    LimitLeft = _LimitLeft;
    LimitRight = _LimitRight;
    LimitBottom = _LimitBottom;
    LimitTop = _LimitTop;
    distance = _distance;
}



EyeRay::EyeRay(vec3 _eyePosition, vec3 _rayDirection)
{
    eyePosition = _eyePosition;
    rayDirection = _rayDirection;
}
ostream& operator<<(ostream& os, const EyeRay& eyeRay)
{
    os << "eyeRay(" << eyeRay.eyePosition.x << ", " << eyeRay.eyePosition.y << ", " << eyeRay.eyePosition.z << ")";
    os << "eyeRay(" << eyeRay.rayDirection.x << ", " << eyeRay.rayDirection.y << ", " << eyeRay.rayDirection.z << ")";
    return os;
}