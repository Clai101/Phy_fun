#include "Grain.h"

std::vector<Grain*> Grain::dust;

Grain::Grain() {
    dust.push_back(this);
}

Grain::Grain(Vector2D center) {
    this->center = center;
    this->shadow = center;
    dust.push_back(this);
}

Grain::Grain(Vector2D velocity, Vector2D center) {
    this->shadow = center;
    this->velocity = velocity;
    this->center = center;
    dust.push_back(this);

}

Grain::Grain(Vector2D center, GLfloat radius) {
    this->shadow = center;
    this->center = center;
    this->radius = radius;
    dust.push_back(this);

}

Grain::Grain(Vector2D velocity, Vector2D center, GLfloat radius) {
    this->shadow = center;
    this->center = center;
    this->velocity = velocity;
    this->radius = radius;
    dust.push_back(this);

}

Grain::Grain(Vector2D velocity, Vector2D center, GLfloat radius, float mass) {
    this->shadow = center;
    this->center = center;
    this->velocity = velocity;
    this->radius = radius;
    this->mass = mass;
    dust.push_back(this);

}


void Grain::frame_muve() {
    shadow = center;
    center = center + velocity / 60;
}

void Grain::force_influence() {
    Vector2D super_force = Vector2D(0, 0);
    std::cout << "centet this" << this->get_shadow() << '\n';
    for (auto  grain : dust){
        std::cout << '[' << grain << "]   [" << this << "]\n";
        if (grain == this) continue;
        Vector2D center1 = grain->get_shadow();
        float mass1 = grain->get_mass();
        center1 = center1 - this->get_shadow();
        std::cout << "center1" << center1 << abs(center1.length()) << '\n';
        super_force = super_force + center1 * (mass * mass1 / (center1.length() * center1.length() * center1.length()));
        std::cout << "super_force" << super_force << '\n';
    }
    this->velocity = this->velocity + super_force  / 600;
    std::cout << "velocity" << velocity << '\n' << '\n';
}

void Grain::update() {
    this->frame_muve();
    this->force_influence();
}
