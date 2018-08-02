#include "island.h"
#include "main.h"

Island::Island(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, -5);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[1176139];
    float k,r=10;
    int idx=0;
    for(int i=0;i<=360;++i){
        for(int j=0;j<=180;j++){
                float c=r*cos(M_PI*j/180),a=r*sin(M_PI*j/180)*cos(M_PI*i/180),b=r*sin(M_PI*j/180)*sin(M_PI*i/180);
                vertex_buffer_data[idx++]=r*sin(M_PI*j/180)*cos(M_PI*(i+1)/180),vertex_buffer_data[idx++]=r*sin(M_PI*j/180)*sin(M_PI*(i+1)/180),vertex_buffer_data[idx++]=r*cos(M_PI*j/180);
                vertex_buffer_data[idx++]=a,vertex_buffer_data[idx++]=b,vertex_buffer_data[idx++]=c;
                k=j+1;
                c=r*cos(M_PI*k/180),a=r*sin(M_PI*k/180)*cos(M_PI*i/180),b=r*sin(M_PI*k/180)*sin(M_PI*i/180);
                vertex_buffer_data[idx++]=a,vertex_buffer_data[idx++]=b,vertex_buffer_data[idx++]=c;
            }
        }
        for(int i=0;i<=360;i++){
            for(int j=0;j<=180;j++){
                float c=r*cos(M_PI*(j+1)/180),a=r*sin(M_PI*(j+1)/180)*cos(M_PI*(i+1)/180),b=r*sin(M_PI*(j+1)/180)*sin(M_PI*(i+1)/180);
                vertex_buffer_data[idx++]=r*sin(M_PI*j/180)*cos(M_PI*(i+1)/180),vertex_buffer_data[idx++]=r*sin(M_PI*j/180)*sin(M_PI*(i+1)/180),vertex_buffer_data[idx++]=r*cos(M_PI*j/180);
                vertex_buffer_data[idx++]=a,vertex_buffer_data[idx++]=b,vertex_buffer_data[idx++]=c;
                k=j+1;
                c=r*cos(M_PI*k/180),a=r*sin(M_PI*k/180)*cos(M_PI*i/180),b=r*sin(M_PI*k/180)*sin(M_PI*i/180);
                vertex_buffer_data[idx++]=a,vertex_buffer_data[idx++]=b,vertex_buffer_data[idx++]=c;
            }
        }
         this->object = create3DObject(GL_TRIANGLES, 130682*3, vertex_buffer_data, color, GL_FILL);
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 2));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
     rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
bounding_box_t Island::bounding_box() {
    float x = this->position.x, y = this->position.y,z = this->position.z;
    bounding_box_t bbox = { x, y, z, 20,10,10};
    return bbox;
}
