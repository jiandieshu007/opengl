
#include<glad/glad.h>
#include <GLFW/glfw3.h>
//这些都加到了 include目录下

#include<iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}//回调函数 每当窗口调整大小时调用这个函数

void processInput(GLFWwindow* window)
{   // glfwGetKey 查询在窗口中 是否固定按键处于按下状态 若是则返回 GLFW_PRESS else GLFW_RELEASE
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); //设置窗口是否应该关闭
}

const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 apos;\n"
"layout(location = 1) in vec3 acolor;\n"
"out vec3 ourcolor;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(apos, 1.0);\n"
"   ourcolor = acolor;\n"
"}\0";



const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourcolor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(ourcolor,1.0f);\n"
"}\0";

float vertices[] = {
    -0.5f,-0.5f, 0.0f,0.3f,0.4f,0.4f,
    0.5f, -0.5f, 0.0f,1.0f,0.2f,0.4f,
    0.0f, 0.5f, 0.0f,0.0f,0.7f,1.0f
    //-0.5f,0.5f,0.0f
};
unsigned int indices[] = {
    0,1,2,1,2,3
};

int main() {
    glfwInit(); //初始化glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //设置opengl上下文的主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //设置opengl上下文的次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置opengl的配置文件 此处使用核心模式
    /*
    GLFW_OPENGL_CORE_PROFILE：使用核心配置文件。这个配置文件限制了使用OpenGL的核心功能，过时的或废弃的功能将不可用。

    GLFW_OPENGL_COMPAT_PROFILE：使用兼容配置文件。这个配置文件允许使用OpenGL的核心功能以及过时的或废弃的功能。

    GLFW_OPENGL_ES_PROFILE：使用嵌入式系统配置文件。这个配置文件适用于OpenGL ES（OpenGL for Embedded Systems），它是为嵌入式系统和移动设备开发的OpenGL版本。

    GLFW_OPENGL_ANY_PROFILE：使用任意配置文件。这个配置文件允许使用任何支持的OpenGL配置文件，包括核心、兼容和嵌入式系统配置文件。
    */
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpengl", NULL, NULL);// create  window
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //将我们窗口的上下文设置为当前线程的主上下文
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //注册该函数


    //初始化 glad， glad是用来管理opengl函数指针地址的函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600); //设置视口的维度 前两个参数是窗口左下角的位置 

    int success;
    char errorinfo[512];



    unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(VertexShader);

    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(VertexShader, 512, NULL, errorinfo);
        std::cout << errorinfo << std::endl;
    }

    unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(FragmentShader);

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(FragmentShader, 512, NULL, errorinfo);
        std::cout << errorinfo << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, VertexShader);
    glAttachShader(shaderProgram, FragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, errorinfo);
        std::cout << errorinfo << std::endl;
    }
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO); //生成一个顶点数组
    glGenBuffers(1, &VBO); //生成一个缓冲区
    glBindVertexArray(VAO); //将指定的顶点数组对象绑定到当前上下文的状态中，使之成为当前操作的顶点数组对象。
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //unsigned int EBO;
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // 从绑定到上下文的VBO buffer中获取
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //这里设置为0就是因为 写vertexshader的时候 设置了 positon = 0 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        //渲染代码


        //glClearColor函数是一个状态设置函数，而glClear函数则是一个状态使用的函数
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // 前三个参数时rgb分量 0-1 后者是透明度 0-1 1表示完全不透明
        glClear(GL_COLOR_BUFFER_BIT); // 三个掩码 color depth stencil 颜色 深度（z-buffer 模板
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glUseProgram(shaderProgram); //通过调用 glUseProgram，指定的着色器程序将在后续的渲染调用中生效。
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //检查并处理所有未处理的窗口事件 并调用对应的回调函数或出发相应的事件处理逻辑
        glfwPollEvents();
        glfwSwapBuffers(window); // 在double buffer环境中使用 将绘制的图像从后缓冲区（绘制缓冲区 交换到前缓冲区（显示缓冲区
 
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
	return 0;
}