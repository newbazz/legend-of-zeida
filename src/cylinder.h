#include "main.h"

#ifndef Cylinder_H
#define Cylinder_H


class Cylinder {
public:
    Cylinder() {}
    Cylinder(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float z_rot;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void reset_position(float x, float y);
    double speed;
    int score;
    int life;
    int on_island;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Cylinder_H
