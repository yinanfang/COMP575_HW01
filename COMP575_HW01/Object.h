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
class HitRecord;


class Object
{
public:
    vec3 k_a;
    vec3 k_d;
    vec3 k_s;
    float SpecularPower;
    virtual bool isIntersectedByRay(const vec3& start, const vec3& vectorDirection) const=0;
    virtual HitRecord getHitRecord(const vec3& start, const vec3& vectorDirection) const=0;
};

class Ray
{
public:
    vec3 start;
    vec3 vectorDirection;
    float multiple;
    Ray(){}
    Ray(vec3 start, vec3 vectorDirection, float multiple);
};

class HitRecord
{
public:
    Ray eyeRay;
    Object *object;
    vec3 normal;
    vec3 hitPoint;
    
};

class Sphere:public Object
{
private:
    
public:
    vec3 center;
    float radius;
    
    Sphere(){}
    Sphere(vec3 center, float radius);
    virtual bool isIntersectedByRay(const vec3& start, const vec3& vectorDirection)const;
    float getDeterminantForSphereIntersectedByLine(const vec3& eyeRay)const;
    virtual HitRecord getHitRecord(const vec3& start, const vec3& vectorDirection) const;
    
//    bool intersectByEyeRay(vec3 eyeRay);
};

class Plane:public Object
{
private:
    
public:
    float a;
    float b;
    float c;
    float d;
    vec3 normal;
    
    Plane(){}
    Plane(float a, float b, float c, float d);
    Plane(vec3 point, vec3 normal);
    virtual bool isIntersectedByRay(const vec3& start, const vec3& vectorDirection)const;
    virtual HitRecord getHitRecord(const vec3& start, const vec3& vectorDirection) const;
    
};



#endif /* defined(__Test02__Object__) */
