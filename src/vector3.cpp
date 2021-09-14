
#include "pch.h"
#include "vector3.h"
#include "matrix44.h"
#include <cmath>

namespace zmath {

    Vector3 Vector3::zero(0.f, 0.f, 0.f);
    Vector3 Vector3::one(1.f, 1.f, 1.f);
    Vector3 Vector3::right(1.f, 0.f, 0.f);
    Vector3 Vector3::up(0.f, 1.f, 0.f);
    Vector3 Vector3::forward(0.f, 0.f, 1.f);

    Vector3::Vector3(const Matrix44& matrix) {
        x = matrix.data[12];
        y = matrix.data[13];
        z = matrix.data[14];
    }

    float Vector3::length() const {
        return (float)sqrt((float)((x * x) + (y * y) + (z * z)));
    }

    Vector3& Vector3::normalize() {
        *this = normalized();
        return *this;
    }

    Vector3 Vector3::normalized() const {
        const auto len = length();
        if (len == 0.f) {
            //if (process.env.NODE_ENV == = "development") {
            //    console.assert(false, "Normalizing a zero Vector3");
            //}
            return *this;
        } else {
            return this->operator/(len);
        }
    }

    Vector3 Vector3::cross(const Vector3& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }
}

