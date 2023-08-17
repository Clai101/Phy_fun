#include "Matrix.h"

Matrix2x2::Matrix2x2(GLfloat a, GLfloat b, GLfloat c, GLfloat d) {
    data[0][0] = a;
    data[1][0] = b;
    data[0][1] = c;
    data[1][1] = d;
}

Matrix2x2 Matrix2x2::operator+(Matrix2x2& other) {
    return Matrix2x2(data[0][0] + other.data[0][0], data[0][1] + other.data[0][1],
        data[1][0] + other.data[1][0], data[1][1] + other.data[1][1]);
}

Matrix2x2 Matrix2x2::operator-(Matrix2x2& other) {
    return Matrix2x2::Matrix2x2(data[0][0] - other.data[0][0], data[0][1] - other.data[0][1],
        data[1][0] - other.data[1][0], data[1][1] - other.data[1][1]);
}

Matrix2x2 Matrix2x2::operator*(Matrix2x2& other) {
    Matrix2x2 result(0.0f, 0.0f, 0.0f, 0.0f);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    return result;
}

Matrix2x2 Matrix2x2::operator*(GLfloat scalar) {
    return Matrix2x2(data[0][0] * scalar, data[0][1] * scalar,
        data[1][0] * scalar, data[1][1] * scalar);
}

Vector2D Matrix2x2::operator*(Vector2D vec) {
    return Vector2D(data[0][0] * vec.getX() + data[1][0] * vec.getY(),
        data[0][1] * vec.getX() + data[1][1] * vec.getY());
}

std::ostream& operator<<(std::ostream& os, const Matrix2x2& matrix) {
    os << "[" << matrix.data[0][0] << ", " << matrix.data[0][1] << "]" << std::endl;
    os << "[" << matrix.data[1][0] << ", " << matrix.data[1][1] << "]";
    return os;
}