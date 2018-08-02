#include "main.h"

#ifndef Sea_H
#define Sea_H


class Sea{
public:
    Sea() {}
    Sea(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
};

#endif // Sea_H
