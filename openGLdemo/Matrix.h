#pragma once
#include "Vectors.h"


class Matrix2x2 {
private:
    GLfloat data[2][2];

public:
    Matrix2x2(GLfloat a, GLfloat b, GLfloat c, GLfloat d);

    Matrix2x2 operator+(Matrix2x2& other);

    Matrix2x2 operator-(Matrix2x2& other);

    Matrix2x2 operator*(Matrix2x2& other);

    Matrix2x2 operator*(GLfloat scalar);

    Vector2D operator*(Vector2D vec);

    friend std::ostream& operator<<(std::ostream& os, const Matrix2x2& matrix);
};