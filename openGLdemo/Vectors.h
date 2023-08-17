#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ostream>
#include <iostream>

class  Vector2D 
{
public:
	Vector2D(GLfloat x, GLfloat y);

    GLfloat getX() const { return this->Pos[0]; }
    GLfloat getY() const { return this->Pos[1]; }
    GLfloat getZ() const { return this->Pos[2]; }

    GLfloat length();

	void normaization();
	void ratio_norm(GLfloat h, GLfloat w);
	Vector2D n_ratio_norm(GLfloat h, GLfloat w);

    Vector2D operator+(const Vector2D& other);
    Vector2D operator-(const Vector2D& other);
	Vector2D operator*(float scalar);
	Vector2D operator/(float scalar);

	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);

	GLfloat Pos[3] = {0.f, 0.f, 0.f};
private:
	
};

struct GrainDraw
{
	GrainDraw(uint32_t v, uint32_t e)
	{
		vao = v;
		numElements = e;
	}
	uint32_t vao = 0;
	uint32_t numElements = 0;
};
