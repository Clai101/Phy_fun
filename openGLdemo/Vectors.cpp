#include "Vectors.h"


Vector2D::Vector2D(GLfloat x, GLfloat y) {
    this->Pos[0] = x;
    this->Pos[1] = y;
}

void Vector2D::ratio_norm(GLfloat h, GLfloat w) {
    this->Pos[0] = this->Pos[0] * h / w;
    this->Pos[1] = this->Pos[1] * w / h;
}

Vector2D Vector2D::n_ratio_norm(GLfloat h, GLfloat w) {
    return Vector2D(this->Pos[0] * h / w, this->Pos[1] * w / h);
}

GLfloat Vector2D::length() {
    return sqrt(this->Pos[0] * this->Pos[0] + this->Pos[1] * this->Pos[1]);
}

void Vector2D::normaization() {
    GLfloat len = this->length();
    Pos[0] = Pos[0] / len;
    Pos[1] = Pos[1] / len;
}

Vector2D Vector2D::operator+(const Vector2D& other) {
    return Vector2D(this->Pos[0] + other.Pos[0], this->Pos[1] + other.Pos[1]);
}

Vector2D Vector2D::operator-(const Vector2D& other) {
    return Vector2D(this->Pos[0] - other.Pos[0], this->Pos[1] - other.Pos[1]);
}

Vector2D Vector2D::operator*(float scalar) {
    return Vector2D(this->Pos[0] * scalar, this->Pos[1] * scalar);
}

Vector2D Vector2D::operator/(float scalar) {
    return Vector2D(this->Pos[0] / scalar, this->Pos[1] / scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
{
    os << "(" << vec.Pos[0] << ", " << vec.Pos[1] << ")";
    return os;
}

