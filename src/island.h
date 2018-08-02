#include "main.h"

#ifndef Island_H
#define Island_H


class Island {
public:
    Island() {}
    Island(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Island_H
