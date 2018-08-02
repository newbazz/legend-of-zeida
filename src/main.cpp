#include "main.h"
#include "timer.h"
#include "ball.h"
#include "c.h"
#include "stones.h"
#include "monster.h"
#include "missile.h"
#include "island.h"
#include "make_pointer.h"
#include "cylinder.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int shooted=0;
int view_mode=1;
Ball ball1;
bool changed=false;
Sea sea;
Cylinder canon;
float eyey=-2;
//Make_Pointer pointer;
Island island;
Monster monster[5],boss;
Stones stones[100000];
Missile missile;
int counts=100;
int jumped=0;
int countJ=0;
float screen_zoom = .2, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int color =0;
int reused=0;
int countR=0;
int draw_missile=0;
double xold=0,zold=0,x_heli,z_heli;
color_t COLOR_GOLD={255,215,0};
Timer t60(1.0 / 60);

void drag(GLFWwindow* window, double xcoord, double ycoord){
    double xn,zn;
    xn=(double)xcoord;
    zn=(double)ycoord;
    x_heli+=xn-xold;
    z_heli+=zn-zold;
    xold=xn;
    zold=zn;
}
void draw() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    //glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    //glm::vec3 up (0, 1, 0);
    /* TOP VIEW */

    glm::vec3 eye ( ball1.position.x, ball1.position.y, 5+5*sin(camera_rotation_angle*M_PI/180.0f));
    glm::vec3 target (ball1.position.x,ball1.position.y,0);
    glm::vec3 up (0,1, 0);


    /*HELICOPTER VIEW*/
        /*glm::vec3 eye ( ball1.position.x-1-x_heli/2, 20+0*ball1.position.y, ball1.position.z - z_heli);
        glm::vec3 target (ball1.position.x,ball1.position.y,ball1.position.z);
        glm::vec3 up (0,0,1);*/

    /*BOAT VIEW*/

    /*glm::vec3 eye (ball1.position.x, ball1.position.y, ball1.position.z+2+0*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 target (ball1.position.x+2*cos(ball1.rotation*M_PI/180.0f), ball1.position.y+2*sin(ball1.rotation*M_PI/180.0f),2);
    glm::vec3 up (0,0, 5);*/

    /*FOLLOW-CAM VIEW*/

    /*glm::vec3 eye (ball1.position.x-3, ball1.position.y, 3+0*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 target (ball1.position.x+2*cos(ball1.rotation*M_PI/180.0f), ball1.position.y+2*sin(ball1.rotation*M_PI/180.0f),2);
    glm::vec3 up (0,0, 5);*/


    /*TOWER VIEW*/

    /*glm::vec3 eye (4, 8, 3+0*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 target (ball1.position.x+2, 0,ball1.position.y+2);
    glm::vec3 up (0,0, 5);*/


    /*glm::vec3 eye (4, eyey, 3+0*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 target (ball1.position.x+2, 0,ball1.position.y+2);
    glm::vec3 up (0,0, 5);*/
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i=0;i<counts;i++){
        stones[i].draw(VP);
    }
    ball1.draw(VP);
    sea.draw(VP);
    if(!boss.invisible)boss.draw(VP);
    for(int i=0;i<5;i++)
        if(monster[i].invisible==0)monster[i].draw(VP);
    if (draw_missile)missile.draw(VP);
    island.draw(VP);
    canon.draw(VP);
//    pointer.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int I  = glfwGetKey(window, GLFW_KEY_I);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int BOOST =glfwGetKey(window, GLFW_KEY_B);
    int REV_BOOST =glfwGetKey(window, GLFW_KEY_D);
    int SHOOT =glfwGetKey(window, GLFW_KEY_S);
    int one =glfwGetKey(window, GLFW_KEY_1);
    int two =glfwGetKey(window, GLFW_KEY_2);
    int three =glfwGetKey(window, GLFW_KEY_3);
    int four =glfwGetKey(window, GLFW_KEY_4);
    int JUMP =glfwGetKey(window, GLFW_KEY_SPACE);

    if (left&&!ball1.on_island) {
        ball1.rotation-=1;
    }
    if (right&&!ball1.on_island) {
        ball1.rotation+=1;
    }
    if (up&&!ball1.on_island) {
        ball1.position.x+=.1*cos(ball1.rotation*M_PI/180.0f);
        ball1.position.y+=.1*sin(ball1.rotation*M_PI/180.0f);
    }
    if (down&&!ball1.on_island) {
        ball1.position.x-=.1*cos(ball1.rotation*M_PI/180.0f);
        ball1.position.y-=.1*sin(ball1.rotation*M_PI/180.0f);
    }
    if (BOOST&&!ball1.on_island) {
        ball1.position.x+=.5*cos(ball1.rotation*M_PI/180.0f);
        ball1.position.y+=.5*sin(ball1.rotation*M_PI/180.0f);
    }
    if (REV_BOOST&&!ball1.on_island) {
        ball1.position.x-=.5*cos(ball1.rotation*M_PI/180.0f);
        ball1.position.y-=.5*sin(ball1.rotation*M_PI/180.0f);
    }
    if(SHOOT&&!ball1.on_island){
        draw_missile=1;
        shooted=1;
        missile=Missile(ball1.position.x,ball1.position.y,COLOR_GOLD);
        draw_missile=1;
    }
    if(JUMP&&!jumped&&!ball1.on_island){
        jumped=1;
        fprintf(stderr,"I have jumped\n");
        ball1.set_position(ball1.position.x,ball1.position.y);
    }
    if(one)view_mode=1;
    if(two)view_mode=2;
    if(three)view_mode=3;
    if(four)view_mode=4;
    if(ball1.on_island&&I){
        fprintf(stderr,"The treasure is yours and it is full of gems and jewellers\n\n");
        fprintf(stderr,"Doesn't make sense to play further\n\n");
        quit(window);

    }
}

void tick_elements() {
//    double xxx2,yyy2;
//    glfwGetCursorPos(window,&xxx2,&yyy2);
//    xxx2=(xxx2*8.0f)/600.0f - 4.0f;
//    yyy2=(yyy2*8.0f)/600.0f - 4.0f;
//    pointer.set_position(ball1.position.z,xxx2+ball1.position.x,yyy2+ball1.position.y);
    if(draw_missile){
        missile.position.x+=.1*cos(ball1.rotation*M_PI/180.0f);
        missile.position.y+=.1*sin(ball1.rotation*M_PI/180.0f);
    }
    if(draw_missile){countR++;}
    if(countR==5*110){
        draw_missile=0;
        countR=0;
    }
    if(jumped)countJ++;
    if(countJ==3*10){
        jumped=0;
        countJ=0;
        ball1.reset_position(ball1.position.x,ball1.position.y);
    }
    if(!ball1.on_island){ball1.position.x+=.005*cos(ball1.rotation*M_PI/180.0f);
    ball1.position.y+=.005*sin(ball1.rotation*M_PI/180.0f);}
    canon.set_position(ball1.position.x+2*cos(ball1.rotation*M_PI/180.0f),sin(ball1.rotation*M_PI/180.0f)*2+ball1.position.y);
    canon.z_rot = ball1.rotation;
}
void initGL(GLFWwindow *window, int width, int height) {

    ball1 = Ball(0,0, COLOR_RED);
    canon = Cylinder(ball1.position.x+2,ball1.position.y+2,{50,0,90});
    sea =Sea(0,0,{0,0,165});
    island =Island(200,-10,{222,184,135});
//    pointer=Make_Pointer(ball1.position.x,ball1.position.y,{0,0,0});
    missile=Missile(ball1.position.x,ball1.position.y,COLOR_GOLD);
    for(int i=0;i<5;i++){
        monster[i]=Monster(rand()%19+4,rand()%19+4,COLOR_BLACK);
    }
    boss=Monster(20, 20,{101,67,33});
    srand (time(NULL));
    for(int i=0;i<250;i++){
        if(i%2)stones[i]=Stones(rand()%100,rand()%100,{255,0,0},0);
        else stones[i]=Stones(rand()%100,rand()%100,{255,20,147},1);
    }
    for(int i=250;i<500;i++){
        if(i%2)stones[i]=Stones(rand()%100,rand()%100,{255,0,0},0);
        else stones[i]=Stones(rand()%100,rand()%100,{255,20,147},1);
    }
    for(int i=500;i<750;i++){
        if(i%2)stones[i]=Stones(rand()%100,rand()%100,{255,0,0},0);
        else stones[i]=Stones(rand()%100,rand()%100,{255,20,147},1);
    }
    for(int i=750;i<1000;i++){
        if(i%2)stones[i]=Stones(rand()%100,rand()%100,{255,0,0},0);
        else stones[i]=Stones(rand()%100,rand()%100,{255,20,147},1);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}
void check_collission(){
    for(int i=0;i<counts;i++){
        if(detect_collision(ball1.bounding_box(),stones[i].bounding_box())) {
            if(!ball1.life){printf("\n\n\n\n\nYOU ARE OUT AND YOUR FINAL SCORE IS:: %d\n\n\n\n\n",ball1.score );quit(window);}
            else if(stones[i].good !=0 ){
                ball1.score+=rand()%49;
                stones[i].set_delete();
                int zz=rand()%3;
                if((zz)==0){
                    fprintf(stderr,"You Got A Change In Boat Color\n");
                    int xxx=ball1.position.x;
                    int yyy=ball1.position.y;
                    ball1=Ball(xxx,yyy,{rand()%256,rand()%256,rand()%256});
                }
                else if((zz)==1){
                    fprintf(stderr,"You Got A Life Here At IIIT\n");
                    ball1.life++;
                }
                else{
                    fprintf(stderr,"You reduced time between successive bullet fires\n");
                }
            }
            else {ball1.life--;fprintf(stderr,"Life gone\n");stones[i].set_delete();}
        }
    }
    for(int i=0;i<5;i++){
        if(detect_collision(ball1.bounding_box(),monster[i].bounding_box())&&monster[i].invisible==0) {
            printf("\n\n\n\n\n\nNO LIFE LEFT\nMONSTER ATTACKED YOU\n\n");
            printf("%d\n",ball1.score);
            quit(window);
        }
    }
    for(int i=0;i<5;i++){
        if(detect_collision(monster[i].bounding_box(),missile.bounding_box())&&monster[i].invisible==0){
            ball1.score+=rand()%101;
            monster[i].invisible=1;
            draw_missile=0;
        }
    }
    if(detect_collision(boss.bounding_box(),missile.bounding_box())&&!boss.invisible){
        ball1.score+=10000;
        boss.invisible=1;
        draw_missile=0;
        fprintf(stderr,"BOSS DEAD YOU WON THE GAME\n");
        quit(window);
    }
    if(detect_collision(ball1.bounding_box(),island.bounding_box())){
        ball1.on_island=1;
    }
    else ball1.on_island=0;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
     // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            check_collission();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT))glfwSetCursorPosCallback(window, drag);
        }
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height))&&
           (abs(a.z - b.z) * 2 < (a.length + b.length));
}


void Height(int pos){
    if(pos==-1){
        if(eyey<0.5)
            eyey+=0.5;
    }
    else
        eyey+=0.5;
    changed=true;
    return;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
}
