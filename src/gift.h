#include "main.h"

#ifndef Gift_H
#define Gift_H


class Gift {
public:
    Gift() {}
    Gift(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
    int score;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object2;
};

#endif // Gift_H
