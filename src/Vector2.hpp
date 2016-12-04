//
//  Vector2.hpp
//  Flocking Spaceships
//
//  Created by Kelvin Hu on 11/10/16.
//  Copyright © 2016 Kelvin HuKelvin. All rights reserved.
//

#ifndef Vector2_hpp
#define Vector2_hpp

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <algorithm>

class Vector2 {
public:
    float x;
    float y;
    
    // CONSTRUCTORS
    Vector2() : x(0), y(0) {}
    Vector2(float xValue, float yValue) : x(xValue), y(yValue) {}
    

    // ASSINGMENT AND EQUALITY OPERATIONS
    inline Vector2& operator = (const Vector2& v) { x = v.x; y = v.y; return *this; }
    inline Vector2& operator = (const float& f) { x = f; y = f; return *this; }
    inline Vector2& operator - (void) { x = -x; y = -y; return *this; }
    inline bool operator == (const Vector2& v) const { return (x == v.x) && (y == v.y); }
    inline bool operator != (const Vector2& v) const { return (x != v.x) || (y != v.y); }

    // VECTOR2 TO VECTOR2 OPERATIONS
    inline const Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
    inline const Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
    inline const Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
    inline const Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

    // VECTOR2 TO THIS OPERATIONS
    inline Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
    inline Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
    inline Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
    inline Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

    // SCALAR TO VECTOR2 OPERATIONS
    inline const Vector2 operator + (float v) const { return Vector2(x + v, y + v); }
    inline const Vector2 operator - (float v) const { return Vector2(x - v, y - v); }
    inline const Vector2 operator * (float v) const { return Vector2(x * v, y * v); }
    inline const Vector2 operator / (float v) const { return Vector2(x / v, y / v); }

    // SCALAR TO THIS OPERATIONS
    inline Vector2& operator += (float v) { x += v; y += v; return *this; }
    inline Vector2& operator -= (float v) { x -= v; y -= v; return *this; }
    inline Vector2& operator *= (float v) { x *= v; y *= v; return *this; }
    inline Vector2& operator /= (float v) { x /= v; y /= v; return *this; }

    void Set(float xValue, float yValue) { this->x = xValue; this->y = yValue; }
    
    float Length() const { return sqrt(x * x + y * y); }
    float LengthSquared() const { return x * x + y * y; }
    float Distance(const Vector2& v) const { return sqrt(((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y))); }
    float DistanceSquared(const Vector2& v) const { return ((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y)); }
    float Dot(const Vector2& v) const { return x * v.x + y * v.y; }
    float Cross(const Vector2& v) const { return x * v.y + y * v.x; }

    Vector2& Normal() { Set(-y, x); return *this; }

    
    Vector2& Normalize()
    {
        if(LengthSquared() != 0)
        {
            float length = Length();
            x /= length;
            y /= length;
            return *this;
        }
        x = y = 0;
        return *this;
    }
    
    void Limit(float maxSpeed)
    {
        if (x > maxSpeed)
            x = maxSpeed;
        if (y > maxSpeed)
            y = maxSpeed;
    }
    
    static Vector2 Max(Vector2& vec1, Vector2& vec2)
    {
        Vector2 vec_temp;
        vec_temp.x = std::min(vec1.x, vec2.y);
        vec_temp.y = std::min(vec1.y, vec2.y);
        return vec_temp;
    }

};

#endif /* Vector2_hpp */
