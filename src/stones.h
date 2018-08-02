#include "main.h"

#ifndef Stones_H
#define Stones_H


class Stones {
public:
    Stones() {}
    Stones(float x, float y, color_t color, int is_power);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_delete();
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    double speed;
    int good;
private:
    VAO *object;
};

#endif // Stones_H
