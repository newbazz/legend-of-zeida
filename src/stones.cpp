#include "stones.h"
#include "main.h"

Stones::Stones(float x, float y, color_t color, int is_power) {
    this->position = glm::vec3(x, y,-0.75);
    this->rotation = 0;
    speed = 1;
    good = is_power;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.25f,-0.25f,-0.25f, // triangle 1 : begin
        -0.25f,-0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f, // triangle 1 : end
        0.25f, 0.25f,-0.25f, // triangle 2 : begin
        -0.25f,-0.25f,-0.25f,
        -0.25f, 0.25f,-0.25f, // triangle 2 : end
        0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,
        -0.25f,-0.25f,-0.25f,
        -0.25f,-0.25f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.25f,
        0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        -0.25f,-0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f, 0.25f,-0.25f,
        -0.25f, 0.25f,-0.25f,
        0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f,
        0.25f,-0.25f, 0.25f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Stones::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 2));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Stones::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Stones::set_delete(){
    this->position = glm::vec3(-800, -800, 0);
}

void Stones::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
bounding_box_t Stones::bounding_box() {
    float x = this->position.x, y = this->position.y,z = this->position.z;
    bounding_box_t bbox = { x, y,z, 0.25, 0.25 ,0.25};
    return bbox;
}
