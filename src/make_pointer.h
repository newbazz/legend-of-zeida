#include "main.h"

#ifndef Make_Pointer_H
#define Make_Pointer_H


class Make_Pointer {
public:
    Make_Pointer() {}
    Make_Pointer(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float z,float x, float y);
private:
    VAO *object;
};

#endif // Make_Pointer_H
