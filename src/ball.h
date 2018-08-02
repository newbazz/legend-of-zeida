#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void reset_position(float x, float y);
    void tick();
    double speed;
    int score;
    int life;
    int on_island;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif // BALL_H
