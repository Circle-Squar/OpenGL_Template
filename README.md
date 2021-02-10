# 基于GLFW使用CMAKE的OpenGL工程模板

---

### ABOUT

​	这是我在学习 OPENGL 时，用于快速的构建一个 Opengl 工程而创建的 CMake 工程模板。创建这个工程时参考了 [Glitter](https://github.com/Polytonic/Glitter) 的代码模板。这个模板中包括了 [GLFW](https://www.glfw.org/) [glad](https://glad.dav1d.de/) [stb_image](https://github.com/nothings/stb) [Assimp](http://assimp.org/)以及在学习 Opengl 时写的 shader.h , texture.h .

这个版本由于vs编译会出错，已经弃用了.

---

### How to use

```sh
git clone --recursive https://github.com/Circle-Squar/OpenGL_Template.git
```

clone 下来，如果没有dependence的话自行补齐，然后用cmake即可 。

如果是在shell环境运行并且有bash 可以使用初始化脚本init.sh 对项目的 项目名、项目debug方案以 及 非msvc使用哪个c++标准 进行快速修改

如果你使用的编程环境使用 ccls 作为符号链接 ，那么你需要将cmake生成的compile_commands.json 链接到工程目录下，以确保工程文件的链接正确

---

### License

* GLFW : [GLFW_LICENSE](https://www.glfw.org/license.html)
  * [zlib/libpng licens](https://opensource.org/licenses/zlib-license.php)
* glad : [GLAD_LICENSE](https://github.com/Dav1dde/glad/blob/master/LICENSE)
  *  [MIT License](https://opensource.org/licenses/MIT)
  * [Apache License](http://www.apache.org/licenses/LICENSE-2.0)
* Assimp: [License](https://github.com/assimp/assimp/blob/master/LICENSE)
* stb_image : [STB_LICENSE](https://github.com/nothings/stb/blob/master/LICENSE)
  *  [single-file public domain (or MIT licensed) libraries](https://opensource.org/licenses/MIT)
  * [Unlicense](https://unlicense.org/)
* [LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL/blob/master/LICENSE.md)

---

### Reference

LearnOpenGL: https://learnopengl.com/

LearnOpenGL-cn: https://learnopengl-cn.github.io/

GLFW: https://www.glfw.org/

glad: https://glad.dav1d.de/

stb_image: https://github.com/nothings/stb

Glitter: https://github.com/Polytonic/Glitter

