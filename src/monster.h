#include "main.h"

#ifndef Monster_H
#define Monster_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int score;
    int invisible;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object2;
};

#endif // Monster_H
