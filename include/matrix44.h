#pragma once

#include "quaternion.h"
#include "vector3.h"
#include "vector4.h"

namespace zmath {

    class Matrix44 {        
    public:
            
        static Matrix44 identity;
        float data[16];

        Matrix44& setRotation(const Quaternion& rotation);
        Matrix44& scale(const Vector3& _scale);
        Matrix44& setPosition(const Vector3& position);        

        static Matrix44 compose(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
        static Matrix44 makePerspective(float fovRadians, float aspectRatio, float zNear, float zFar);

        Matrix44 operator * (const Matrix44& other) const;
        Vector3 operator * (const Vector3& v) const;
        Vector4 operator * (const Vector4& v) const;

        bool getInverse(Matrix44& out) const;
    };
}
