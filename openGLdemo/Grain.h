#pragma once
#include <vector>
#include "Vectors.h"
#include "Matrix.h"

class Grain {
private:

    Vector2D shadow = Vector2D(0, 0);
    Vector2D center = Vector2D(0, 0);
    Vector2D velocity = Vector2D(0, 0);
    GLfloat radius = 0.5;
    float mass = 0.5;


    void force_influence();
    void frame_muve();

public:
    static std::vector<Grain*> dust;
    Grain();
    Grain(Vector2D center);
    Grain(Vector2D center, GLfloat radius);
    Grain(Vector2D velosity, Vector2D center);
    Grain(Vector2D velosity, Vector2D center, GLfloat radius);
    Grain(Vector2D velosity, Vector2D center, GLfloat radius, float mass);

    Vector2D get_shadow() { return shadow; }
    GLfloat get_radius() { return radius; }
    Vector2D get_center() { return center; }
    float get_mass() { return mass; }

    void update();
};


