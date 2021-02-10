#include <glad/glad.h>
#include <shader.hpp>

#include <GLFW/glfw3.h>
#include <iostream>

unsigned int screenWidth = 1280;
unsigned int screenHeight = 720;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void scrool_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  //====================//
  // GLFW window Create //
  //====================//
  GLFWwindow *window =
      glfwCreateWindow(screenWidth, screenHeight, "OpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "[ERROR] Failed to create GLFW window!" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  //=================//
  // Initialize GLAD //
  //========================================================
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "[ERROR] Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  //====================//
  // Vertex Information //
  //====================//
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f};

  unsigned VBO, VAO;

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  //========//
  // Shader //
  //==============================================
  Shader shader("./shader/a.vs", "./shader/a.fs");

  //============//
  // Randr Loop //
  //===================================
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  float currentTime;
  float lastSec = glfwGetTime();
  int fps = 0;

  while (!glfwWindowShouldClose(window)) {
    currentTime = glfwGetTime();
    processInput(window);

    glClear(GL_COLOR_BUFFER_BIT);

    // Draw
    //===========
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    fps++;
    glfwSwapBuffers(window);
    glfwPollEvents();

    if (currentTime - lastSec >= 1.0) {
      std::cout << "[DEBUG] TIME : " << currentTime << "  FPS : " << fps
                << std::endl;
      lastSec = currentTime;
      fps = 0;
    }
  }

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  screenWidth = width;
  screenHeight = height;
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}
