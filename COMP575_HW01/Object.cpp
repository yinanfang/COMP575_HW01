//
//  Object.cpp
//  Test02
//
//  Created by Golden Compass on 9/17/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#include "Object.h"

Sphere::Sphere(vec3 _center, float _radius)
{
    center = _center;
    radius = _radius;
}
//bool Sphere::isIntersectByRay(const vec3& ray)
//{
//    
//    return false;
//}





Plane::Plane(float _a, float _b, float _c, float _d)
{
    a = _a;
    b = _b;
    c = _c;
    d = _d;
}

// ax + by + cz + d = 0
Plane::Plane(vec3 point, vec3 normal)
{
    a = normal.x;
    b = normal.y;
    c = normal.z;
    d = -(a*point.x) - (b*point.y) - (c*point.z);
}