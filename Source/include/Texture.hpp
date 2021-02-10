#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <stb_image.h>
#include <string>

unsigned int TextureFromFile(const char *path, const std::string &directory,
                             bool gamma = false);

unsigned int TextureFromFile(const char *path, const std::string &directory,
                             bool gamma) {
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data =
      stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 2)
      format = GL_RG;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "[ERROR] : Failed to load texture at path: " << path
              << std::endl;
    stbi_image_free(data);
  }
  return textureID;
}

//
//############################################################################//
unsigned int LoadTexture(const char *path) {
  std::string filename = std::string(path);
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrChannel;
  unsigned char *data =
      stbi_load(filename.c_str(), &width, &height, &nrChannel, 0);
  if (data) {
    GLenum format;
    if (nrChannel == 1)
      format = GL_RGB;
    else if (nrChannel == 2)
      format = GL_RG;
    else if (nrChannel == 3)
      format = GL_RGB;
    else if (nrChannel == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "[ERROR] : Failed to load texture at path: " << path
              << std::endl;
    stbi_image_free(data);
  }
  return textureID;
}

#endif
