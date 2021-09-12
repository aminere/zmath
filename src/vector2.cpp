
#include "pch.h"
#include "vector2.h"
#include <cmath>

namespace zmath {

    Vector2 Vector2::zero(0.f, 0.f);
    Vector2 Vector2::one(1.f, 1.f);

    float Vector2::length() const {
        return (float)sqrt((float)((x * x) + (y * y)));
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
}
