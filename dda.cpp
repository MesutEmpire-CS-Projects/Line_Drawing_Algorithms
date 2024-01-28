//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include <cmath>
//#include <vector>
//using namespace std;
//
//float x_1,x_2,y_1,y_2,m;
//float dx,dy;
//int current_steps,steps;
//vector<float> coordinates;
//
//
//const char *vertexShaderSource = "#version 330 core\n"
//                                 "layout (location = 0) in vec2 aPos;\n"
//                                 "void main()\n"
//                                 "{\n"
//                                 "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
//                                 "}\0";
//
//const char *fragmentShaderSource = "#version 330 core\n"
//                                   "out vec4 FragColor;\n"
//                                   "void main()\n"
//                                   "{\n"
//                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                   "}\n\0";
//
//GLuint shaderProgram;
//
//void dda_algorithm(){
//    if (abs(dx) > abs(dy)){
//        steps = abs(dx);
//    }else{
//        steps = abs(dy);
//    }
//    coordinates.resize(2 * steps);
//    while(current_steps<=steps && x_1<=x_2 && y_1<=y_2){
//        if ( m < 1 ){
//            x_1 = 1+x_1;
//            y_1 = m+y_1;
//        } else if ( m > 1 ){
//            x_1 = (1/m)+x_1;
//            y_1 = 1+y_1;
//        }
//        else {
//            x_1 = 1+x_1;
//            y_1 = 1+y_1;
//        }
//
//        coordinates[2*current_steps] = round(x_1)/15;
//        coordinates[2*current_steps + 1] = round(y_1)/15;
//        current_steps +=1;
//    }
//
//  for(float i:coordinates){
//      cout << "element: " << i << endl;
//  }
//}
//
//void drawLine (){
//    GLuint VAO, VBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER,coordinates.size() * sizeof(float), coordinates.data(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
//    glEnableVertexAttribArray(0);
//
//    glUseProgram(shaderProgram);
//    glBindVertexArray(VAO);
//
//    glDrawArrays(GL_LINE_STRIP, 0, coordinates.size()/2);
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//}
//
//
//void drawAxes() {
//    float axes[] = {
//            -1.0f, 0.0f,
//            1.0f, 0.0f,
//            0.0f, -1.0f,
//            0.0f,  1.0f
//    };
//
//    GLuint VAO, VBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
//    glEnableVertexAttribArray(0);
//
//    glUseProgram(shaderProgram);
//    glBindVertexArray(VAO);
//
//    glDrawArrays(GL_LINES, 0, 4);
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//}
//
//void input(){
//    printf("Enter value of X1 :");
//    cin >> x_1;
//    printf("Enter value of y1 :");
//    cin >> y_1;
//    printf("Enter value of X2 :");
//    cin >> x_2;
//    printf("Enter value of Y2 :");
//    cin >> y_2;
//    dx=x_2-x_1;
//    dy=y_2-y_1;
//    m=dy/dx;
//    dda_algorithm();
//}
//
//
//int main() {
//
//    input();
//
//    glfwInit();
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
//
//    GLFWwindow *window = glfwCreateWindow(800, 800, "DDA", NULL, NULL);
//
//    if (window == NULL) {
//        cout << "Failed to create a window" << endl;
//
//        glfwTerminate();
//
//        return 1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    gladLoadGL();
//    glViewport(0, 0, 800, 800);
//
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        cout << "Failed to initialize GLAD" << endl;
//        return -1;
//    }
//
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    while(!glfwWindowShouldClose(window)){
//
//
//        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        drawAxes();
//
//        drawLine();
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//
//
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//
//    return 0;
//}
//


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "display.h"
using namespace std;

float x_1,x_2,y_1,y_2,m;
float dx,dy;
int current_steps,steps;
vector<float> coordinates;

void dda_algorithm(){
    if (abs(dx) > abs(dy)){
        steps = abs(dx);
    }else{
        steps = abs(dy);
    }
    coordinates.resize(2 * steps);
    while(current_steps<=steps && x_1<=x_2 && y_1<=y_2){
        if ( m < 1 ){
            x_1 = 1+x_1;
            y_1 = m+y_1;
        } else if ( m > 1 ){
            x_1 = (1/m)+x_1;
            y_1 = 1+y_1;
        }
        else {
            x_1 = 1+x_1;
            y_1 = 1+y_1;
        }

        coordinates[2*current_steps] = round(x_1)/15;
        coordinates[2*current_steps + 1] = round(y_1)/15;
        current_steps +=1;
    }

    for(float i:coordinates){
        cout << "element: " << i << endl;
    }
}
void input(){
    printf("Enter value of X1 :");
    cin >> x_1;
    printf("Enter value of y1 :");
    cin >> y_1;
    printf("Enter value of X2 :");
    cin >> x_2;
    printf("Enter value of Y2 :");
    cin >> y_2;
    dx=x_2-x_1;
    dy=y_2-y_1;
    m=dy/dx;
    dda_algorithm();
}


int main() {
    input();
    Display display_board = Display(coordinates);
    display_board.draw();
}


