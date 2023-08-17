#pragma once
#include <vector>
#include "Vectors.h"

int w = 1000;
int h = 1000;
GLfloat ww = w;
GLfloat hh = h;

static GrainDraw UploadMesh(Vector2D center, GLfloat radius){

	int sp = 27;

	Vector2D rad_v = Vector2D(0, radius);
	std::vector<Vector2D> verts;
	std::vector<uint32_t> elem;


	Matrix2x2 rotation = Matrix2x2(cos(3.141519 * 2 / sp), sin(3.141519 * 2 / sp), -1 * sin(3.141519 * 2 / sp), cos(3.141519 * 2 / sp));
	verts.emplace_back(center);
	verts.emplace_back(center + rad_v.n_ratio_norm(ww, hh));
	
	for (int itr = 1; itr <= sp; itr++) {
		rad_v = rotation * rad_v;
		verts.emplace_back(center + rad_v.n_ratio_norm(ww, hh));
		elem.emplace_back(0);
		elem.emplace_back(itr);
		elem.emplace_back(itr+1);
	}


	uint32_t VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vector2D), verts.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector2D), (const void*)offsetof(Vector2D, Pos));
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size() * sizeof(uint32_t), elem.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return GrainDraw(VAO, static_cast<uint32_t>(elem.size()));
}


static void UnloadMesh(std::vector<GrainDraw>& details)
{
	for (auto& d : details)
	{
		glDeleteBuffers(1, &d.vao);
	}

	details.clear();
}