// myclass.h
#ifndef DISPLAY_H
#define DISPLAY_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Display {
public:
    Display(const vector<float>& data){
        this->data = data;
    }
    void draw(){
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);

        GLFWwindow *window = glfwCreateWindow(800, 800, "DDA", NULL, NULL);

        if (window == NULL) {
            cout << "Failed to create a window" << endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);

        gladLoadGL();
        glViewport(0, 0, 800, 800);

        glfwSetFramebufferSizeCallback(window, Display::framebuffer_size_callback);


        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            cout << "Failed to initialize GLAD" << endl;
            exit(EXIT_FAILURE);
        }

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        while(!glfwWindowShouldClose(window)){


            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            this->drawAxes();
            this->drawLine();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    vector<float> data;
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec2 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                                     "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    GLuint shaderProgram;
    void drawLine (){
        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,this->data.size() * sizeof(float), this->data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawArrays(GL_LINE_STRIP, 0, this->data.size()/2);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void drawAxes() {
        float axes[] = {
                -1.0f, 0.0f,
                1.0f, 0.0f,
                0.0f, -1.0f,
                0.0f,  1.0f
        };

        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawArrays(GL_LINES, 0, 4);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }
};

#endif

