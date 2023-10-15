
#include<glad/glad.h>
#include <GLFW/glfw3.h>
//��Щ���ӵ��� includeĿ¼��

#include<iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}//�ص����� ÿ�����ڵ�����Сʱ�����������

void processInput(GLFWwindow* window)
{   // glfwGetKey ��ѯ�ڴ����� �Ƿ�̶��������ڰ���״̬ �����򷵻� GLFW_PRESS else GLFW_RELEASE
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); //���ô����Ƿ�Ӧ�ùر�
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
    glfwInit(); //��ʼ��glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //����opengl�����ĵ����汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //����opengl�����ĵĴΰ汾��
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //����opengl�������ļ� �˴�ʹ�ú���ģʽ
    /*
    GLFW_OPENGL_CORE_PROFILE��ʹ�ú��������ļ�����������ļ�������ʹ��OpenGL�ĺ��Ĺ��ܣ���ʱ�Ļ�����Ĺ��ܽ������á�

    GLFW_OPENGL_COMPAT_PROFILE��ʹ�ü��������ļ�����������ļ�����ʹ��OpenGL�ĺ��Ĺ����Լ���ʱ�Ļ�����Ĺ��ܡ�

    GLFW_OPENGL_ES_PROFILE��ʹ��Ƕ��ʽϵͳ�����ļ�����������ļ�������OpenGL ES��OpenGL for Embedded Systems��������ΪǶ��ʽϵͳ���ƶ��豸������OpenGL�汾��

    GLFW_OPENGL_ANY_PROFILE��ʹ�����������ļ�����������ļ�����ʹ���κ�֧�ֵ�OpenGL�����ļ����������ġ����ݺ�Ƕ��ʽϵͳ�����ļ���
    */
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpengl", NULL, NULL);// create  window
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //ע��ú���


    //��ʼ�� glad�� glad����������opengl����ָ���ַ�ĺ���
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600); //�����ӿڵ�ά�� ǰ���������Ǵ������½ǵ�λ�� 

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
    glGenVertexArrays(1, &VAO); //����һ����������
    glGenBuffers(1, &VBO); //����һ��������
    glBindVertexArray(VAO); //��ָ���Ķ����������󶨵���ǰ�����ĵ�״̬�У�ʹ֮��Ϊ��ǰ�����Ķ����������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //unsigned int EBO;
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // �Ӱ󶨵������ĵ�VBO buffer�л�ȡ
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //��������Ϊ0������Ϊ дvertexshader��ʱ�� ������ positon = 0 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        //��Ⱦ����


        //glClearColor������һ��״̬���ú�������glClear��������һ��״̬ʹ�õĺ���
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // ǰ��������ʱrgb���� 0-1 ������͸���� 0-1 1��ʾ��ȫ��͸��
        glClear(GL_COLOR_BUFFER_BIT); // �������� color depth stencil ��ɫ ��ȣ�z-buffer ģ��
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glUseProgram(shaderProgram); //ͨ������ glUseProgram��ָ������ɫ�������ں�������Ⱦ��������Ч��
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //��鲢��������δ����Ĵ����¼� �����ö�Ӧ�Ļص������������Ӧ���¼������߼�
        glfwPollEvents();
        glfwSwapBuffers(window); // ��double buffer������ʹ�� �����Ƶ�ͼ��Ӻ󻺳��������ƻ����� ������ǰ����������ʾ������
 
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