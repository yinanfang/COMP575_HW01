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
float Sphere::getDeterminantForSphereIntersectedByLine(const vec3& eyeRay)const
{
    vec3 p = CameraPositionPoint;
    vec3 d = eyeRay;
    vec3 c = center;
    float r = radius;
    
    float delta_a = dot(d,d);
    float delta_b = 2.0*(dot(p,d)-dot(d, c));
    float delta_c = dot(p,p)-2.0*(dot(c,p))+dot(c,c)-pow(r, 2);
    float determinant = pow(delta_b, 2)-4.0*(delta_a*delta_c);
    
    return determinant;
}
bool Sphere::isIntersectedByRay(const vec3& start, const vec3& vectorDirection)const
{
    vec3 p = start;
    vec3 d = vectorDirection;
    vec3 c = center;
    float r = radius;
    
    float delta_a = dot(d,d);
    float delta_b = 2.0*(dot(p,d)-dot(d, c));
    float delta_c = dot(p,p)-2.0*(dot(c,p))+dot(c,c)-pow(r, 2);
    float determinant = pow(delta_b, 2)-4.0*(delta_a*delta_c);
    
    return determinant>0?true:false;
}

Plane::Plane(float _a, float _b, float _c, float _d)
{
    a = _a;
    b = _b;
    c = _c;
    d = _d;
}

// ax + by + cz + d = 0
Plane::Plane(vec3 point, vec3 _normal)
{
    a = _normal.x;
    b = _normal.y;
    c = _normal.z;
    d = -(a*point.x) - (b*point.y) - (c*point.z);
    normal = normalize(_normal);
}

bool Plane::isIntersectedByRay(const vec3& start, const vec3& vectorDirection)const
{
    float p_a = a;
    float p_b = b;
    float p_c = c;
    float p_d = d;
    vec3 p = start;
    vec3 d = vectorDirection;
    
    float intersectT = -(p_a*p.x+p_b*p.y+p_c*p.z+p_d) / (p_a*d.x+p_b*d.y+p_c*d.z);
    
    return intersectT>0?true:false;
}