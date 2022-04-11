#include <engine/engine.h>
#include <game/chuncks/Block.h>
#include <game/Camera.h>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window, float _delta);

void GLAPIENTRY ErrorOccurredGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    bool debug = false;
    printf("\nMessage from OpenGL:\nSource: 0x%x\nType: 0x%x\n"
        "Id: 0x%x\nSeverity: 0x%x\n", source, type, id, severity);
    printf("%s\n", message);

    exit(-1);
}

float coords[2] = { 640.0f, 480.0f };
Cam camera(coords[0], coords[1]);
float lastX = coords[0] / 2.0f;
float lastY = coords[1] / 2.0f;
bool firstMouse = true;

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    window = glfwCreateWindow(640, 480, "Tab", NULL, NULL);
    if (window == GLFW_FALSE)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    GLenum error = glewInit();
    if (GLEW_OK != error)
    {
        std::cout << "Error: %s\n" << glewGetErrorString(error);
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;

    Block block(0);

    VertexArray vao;
    VertexBuffer vb(block.getPosition(), block.getPositionSize());

    VertexBufferLayout layout;
    layout.Push<float>(3);

    vao.AddBuffer(vb, layout);
    IndexBuffer ib(block.getIndices(), block.getIndicesSize());

    

    Shader shader("res/shader_files/main.shader");
    shader.Bind();

    std::vector<std::string> texPath =
    {
        "res/textures/sand.png",
        "res/textures/sand.png",
        "res/textures/sand.png",
        "res/textures/sand.png",
        "res/textures/sand.png",
        "res/textures/sand.png"
    };

    Texture texture(texPath);
    texture.Bind();
    shader.SetUniform1i("uTexture", 0);

    vao.Unbind();
    vb.Unbind();
    shader.Unbind();
    texture.Unbind();

    Renderer renderer;

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(ErrorOccurredGL, NULL);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        renderer.Clear();

        shader.Bind();
        texture.Bind();

        processInput(window, deltaTime);

        glm::mat4 camTick = camera.CamTick(window);

        for (int i = 0; i < 50; i++)
        {
            for (int k = 0; k < 50; k++)
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((-i * 200), -300, (-k * 200)));
                glm::mat4 mvp = camTick * model;
                shader.SetUniformMat4f("uMVP", mvp);
                renderer.Draw(vao, ib, shader);
            }
        }

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    vao.Unbind();
    shader.Unbind();
    ib.Unbind();
    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void processInput(GLFWwindow* window, float _delta)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Cam::FORWARD, _delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Cam::BACKWARD, _delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Cam::LEFT, _delta);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Cam::RIGHT, _delta);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(Cam::UP, _delta);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(Cam::DOWN, _delta);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}