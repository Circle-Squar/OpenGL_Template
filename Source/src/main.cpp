#include <glad/glad.h>
#include <shader.hpp>

#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

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
  float vertices[] = {-0.5f, 0.5f,  0.0f, //
                      -0.5f, -0.5f, 0.0f, //
                      0.5f,  -0.5f, 0.0f, //

                      -0.5f, 0.5f,  0.0f, //
                      0.5f,  -0.5f, 0.0f, //
                      0.5f,  0.5f,  0.0f};

  unsigned VBO, VAO;

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  std::vector<float> dotVertices;
  float angle = 0.0f;
  float LastPos[2] = {0.0, 1.0};
  float ThisPos[2] = {0.0, 1.0};
  float R = 1.0f;
  float Center[2] = {0.0f, 0.0f};
  while (angle <= 360 + 1.0f) {
    angle += 1.0;
    LastPos[0] = ThisPos[0];
    LastPos[1] = ThisPos[1];
    ThisPos[0] = sin(glm::radians(angle)) * R + Center[0];
    ThisPos[1] = cos(glm::radians(angle)) * R + Center[1];
    dotVertices.push_back(ThisPos[0]);
    dotVertices.push_back(ThisPos[1]);
    dotVertices.push_back(0.0f);

    dotVertices.push_back(0.0f);
    dotVertices.push_back(0.0f);
    dotVertices.push_back(0.0f);

    dotVertices.push_back(LastPos[0]);
    dotVertices.push_back(LastPos[1]);
    dotVertices.push_back(0.0f);
  }

  float *CircleVert = new float[dotVertices.size()];
  for (int i = 0; i < dotVertices.size(); i++) {
    CircleVert[i] = dotVertices[i];
  }

  unsigned dotVBO, dotVAO;
  glGenVertexArrays(1, &dotVAO);
  glBindVertexArray(dotVAO);
  glGenBuffers(1, &dotVBO);
  glBindBuffer(GL_ARRAY_BUFFER, dotVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dotVertices.size(), CircleVert,
               GL_STREAM_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  //========//
  // Shader //
  //==============================================
  Shader shader("./shader/a.vs", "./shader/a.fs");
  Shader dot("./shader/dot.vs", "./shader/dot.fs");

  //============//
  // Randr Loop //
  //===================================
  glClearColor(0.8f, 0.8f, 0.7f, 1.0f);

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

    shader.setFloat("Fixx", (float)screenWidth);
    shader.setFloat("Fixy", (float)screenHeight);

    glm::mat4 Modul = glm::mat4(1.0f);
    Modul = glm::translate(Modul, glm::vec3(0.0f, 0.2f, 0.0f));
    Modul = glm::rotate(Modul, (float)glm::radians(30.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f));
    Modul = glm::rotate(Modul, (float)glm::radians(sin(glfwGetTime()) * 180),
                        glm::vec3(0.0f, 0.0f, 1.0f));

    shader.setMat4("Modul", Modul);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    dot.use();

    dot.setFloat("Fixx", (float)screenWidth);
    dot.setFloat("Fixy", (float)screenHeight);

    glm::mat4 dotModul = glm::mat4(1.0f);
    dotModul = glm::mat4(1.0f);
    dotModul = glm::translate(dotModul, glm::vec3(0.0f, -0.8f, 0.0f));
    dotModul = glm::scale(dotModul, glm::vec3(0.02f, 0.02f, 1.0f));
    dot.setMat4("Modul", dotModul);

    glBindVertexArray(dotVAO);
    glDrawArrays(GL_TRIANGLES, 0, dotVertices.size());

    dotModul = glm::translate(
        glm::mat4(1.0f), glm::vec3(sin((currentTime)*2) * 0.25, -0.8f, 0.0f));
    dotModul = glm::scale(dotModul, glm::vec3(0.02f, 0.02f, 1.0f));
    dot.setMat4("Modul", dotModul);
    glBindVertexArray(dotVAO);
    glDrawArrays(GL_TRIANGLES, 0, dotVertices.size());

    dotModul = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(cos((currentTime + glm::radians(45.0f)) * 2) * 0.25, -0.8f,
                  0.0f));
    dotModul = glm::scale(dotModul, glm::vec3(0.02f, 0.02f, 1.0f));
    dot.setMat4("Modul", dotModul);
    glBindVertexArray(dotVAO);
    glDrawArrays(GL_TRIANGLES, 0, dotVertices.size());
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
