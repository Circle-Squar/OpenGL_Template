# 基于CMAKE的OpenGL (GLFW) 模板

---

### ABOUT

​	这是我在学习 OPENGL 时，用于快速的构建一个 Opengl 工程而创建的 CMake 工程模板。创建这个工程时参考了 [Glitter](https://github.com/Polytonic/Glitter) 的代码模板。这个模板中包括了 [GLFW](https://www.glfw.org/) [glad](https://glad.dav1d.de/) [stb_image](https://github.com/nothings/stb) [Assimp](http://assimp.org/) [glm](https://github.com/g-truc/glm) 以及（菜得一批的）我在学习 Opengl 时写的 shader.h , texture.h .     : p

---

### How to use

```sh
git clone --recursive https://github.com/Circle-Squar/OpenGL_Template.git
```

clone 下来，如果没有dependence的话自行补齐 或使用init.sh 可以补全，如果可以请使用init.sh初始化项目，然后用cmake即可 。

##### Windows :

​	在克隆完项目后先打开CMakeLists.txt 对项目名称进行修改，然后删除与git相关的文件（毕竟没有人想无故的push到别人的仓库上）（如果有git环境也可以用init.sh去完成项目的初始化），再使用cmake工具生成VS工程(.sln文件)。

##### Unix / Linux：

如果是在shell环境运行并且有bash 可以使用初始化脚本init.sh 对项目的 项目名、项目debug方案以及使用哪个c++标准 进行快速修改，并进行cmake 动作。

如果你使用的编程环境使用 ccls 作为符号链接 ，那么init.sh会将cmake生成的compile_commands.json 链接到工程目录下，以确保工程文件的补齐功能的正确，如果没有链接可以手动链接

---

### 已知问题

Assimp中AMF文件的支持有文件会在VisualStudio （MSVC） 中报出警告："文件为使用unicode进行存储" 并会将警告视为错误。

- 解决方案： 在assimp库的工程项目的属性中找到C/C++ 并 关闭警告（W0）或是 关闭视警告为错误（WX-），或是手动找到那几个文件，把它们保存成VS要求的属性

VS会吧可执行文件生产到"项目主目录/output/(debug  /  release)"下面，而我设置的shader和resource的拷贝目标目录是"项目主目录/output/"下，这会导致VisualStudio在调试时候的不方便

- 解决方案： 可以手动将生成的文件放入正确的位置，如果您知道如何修改CMakeLists中关于vs输出位置的部分，也可以自行修改，并且请告诉我修改方法。

基于VS的所有问题的终极解决方案： 自行配置VS的项目 （狗头）。

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
* [glm](https://github.com/g-truc/glm/blob/master/copying.txt) : 
  * [MIT License](https://opensource.org/licenses/MIT)

---

### Reference

LearnOpenGL: https://learnopengl.com/

LearnOpenGL-cn: https://learnopengl-cn.github.io/

GLFW: https://www.glfw.org/

glad: https://glad.dav1d.de/

stb_image: https://github.com/nothings/stb

Glitter: https://github.com/Polytonic/Glitter

