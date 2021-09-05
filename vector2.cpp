
#include "pch.h"
#include "vector2.h"
#include <cmath>

Vector2 Vector2::create(float x, float y) {
    Vector2 v;
    return v.set(x, y);
}

Vector2 Vector2::zero = Vector2::create(0.f, 0.f);
Vector2 Vector2::one = Vector2::create(1.f, 1.f);

float Vector2::length() const {
    return (float)sqrt((float)((_x * _x) + (_y * _y)));
}

Vector2& Vector2::normalize() {
    const auto len = length();
    if (len == 0.f) {
        //if (process.env.NODE_ENV == = "development") {
        //    console.assert(false, "Normalizing a zero Vector3");
        //}
        return *this;
    } else {
        *this = *this / len;
        return *this;
    }
}
