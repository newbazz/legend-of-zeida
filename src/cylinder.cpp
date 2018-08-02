#include "cylinder.h"
#include "main.h"
Cylinder::Cylinder(float x, float y,color_t color) {
    this->position = glm::vec3(x+3, y+3, 2);
    this->rotation = -90;
    this->z_rot = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     float i,j;
    GLfloat vertex_buffer_data[200000];
     
     int k=0;
     float r=.25f,h=3;
     float pi = M_PI/180.0f;
     for(i=-3;i<3;++i){
        for(j=0;j<=360-1;j+=1){
            vertex_buffer_data[k++]=.25f*cos(pi*j);
            vertex_buffer_data[k++]=.25f*sin(pi*j);
            vertex_buffer_data[k++]=i;
            vertex_buffer_data[k++]=.25f*cos(pi*j);
            vertex_buffer_data[k++]=.25f*sin(pi*j);
            vertex_buffer_data[k++]=.25f+1;
            vertex_buffer_data[k++]=.25f*cos(pi*(j+1));
            vertex_buffer_data[k++]=.25f*sin(pi*(j+1));
            vertex_buffer_data[k++]=i;
            vertex_buffer_data[k++]=.25f*cos(pi*j);
            vertex_buffer_data[k++]=.25f*sin(pi*j);
            vertex_buffer_data[k++]=.25f+1;
            vertex_buffer_data[k++]=.25f*cos(pi*(j+1));
            vertex_buffer_data[k++]=.25f*sin(pi*(j+1));
            vertex_buffer_data[k++]=i;
            vertex_buffer_data[k++]=.25f*cos(pi*(j+1));
            vertex_buffer_data[k++]=.25f*sin(pi*(j+1));
            vertex_buffer_data[k++]=i+1;
        }

     }
    this->object = create3DObject(GL_TRIANGLES, 2*h*360*2*3, vertex_buffer_data, color, GL_FILL);
}

void Cylinder::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 01, 0));
    glm::mat4 rotate1    = glm::rotate((float) (this->z_rot* M_PI / 180.0f), glm::vec3(0,0,1));
    rotate1*=rotate;
    Matrices.model *= (translate * rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Cylinder::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

