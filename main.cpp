#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>

#define ERROR_LOG(ErrorMessage) \
    glfwTerminate();std::cout<<ErrorMessage<<std::endl; \
    return -1;

GLfloat deltaTime = 0.0f, lastTime = 0.0f;
glm::mat4 transform = glm::mat4(1.0f);
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
};

GLfloat groundVertices[] = {
    -3.0f, -0.5f, -3.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
     3.0f, -0.5f, -3.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
     3.0f, -0.5f,  3.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
     3.0f, -0.5f,  3.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -3.0f, -0.5f,  3.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -3.0f, -0.5f, -3.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
};

GLfloat cubePositions[] = {
    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f
};

GLuint cubeIndices[] = {
    0, 3, 2,  2, 1, 0,  // Back (Z-)
    4, 5, 6,  6, 7, 4,  // Front (Z+)
    0, 1, 5,  5, 4, 0,  // Bottom (Y-)
    3, 7, 6,  6, 2, 3,  // Top (Y+)
    0, 4, 7,  7, 3, 0,  // Left (X-)
    1, 2, 6,  6, 5, 1   // Right (X+)
};

struct Edge { int v0, v1; int triIndex0, triIndex1; };
Edge cubeEdges[] = {
    {0, 3, 0, 9},   // Edge 0-3: Back and Left
    {3, 2, 0, 7},   // Edge 3-2: Back and Top
    {2, 1, 1, 10},  // Edge 2-1: Back and Right
    {1, 0, 1, 4},   // Edge 1-0: Back and Bottom
    {4, 5, 2, 4},   // Edge 4-5: Front and Bottom
    {5, 6, 2, 11},  // Edge 5-6: Front and Right
    {6, 7, 3, 6},   // Edge 6-7: Front and Top
    {7, 4, 3, 8},   // Edge 7-4: Front and Left
    {0, 4, 5, 8},   // Edge 0-4: Bottom and Left
    {1, 5, 4, 11},  // Edge 1-5: Bottom and Right
    {6, 2, 7, 10},  // Edge 6-2: Top and Right
    {3, 7, 6, 9}    // Edge 3-7: Top and Left
};
const int numCubeEdges = 12;

GLuint VAO, VBO, groundVAO, groundVBO, shadowVolumeVAO, shadowVolumeVBO;
std::vector<GLfloat> shadowVolumeVertices;

static void CreateVertexBuffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GLuint lightVAO;
static void CreateLight()
{
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static void CreateGround()
{
    glGenVertexArrays(1, &groundVAO);
    glGenBuffers(1, &groundVBO);
    glBindVertexArray(groundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static void CreateShadowVolume()
{
    glGenVertexArrays(1, &shadowVolumeVAO);
    glGenBuffers(1, &shadowVolumeVBO);
    glBindVertexArray(shadowVolumeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, shadowVolumeVBO);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int screenWidth, screenHeight;
static void SetViewport(GLFWwindow* window)
{
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
}

glm::vec3 LightPos = glm::vec3(2.0f, 2.0f, 0.0f);

static void GenerateShadowVolume(glm::vec3 lightPosWorld, glm::mat4 objectTransform)
{
    shadowVolumeVertices.clear();
    const float EXTRUSION_DISTANCE = 20.0f;

    glm::vec3 worldVertices[8];
    for (int i = 0; i < 8; i++) {
        glm::vec4 worldPos = objectTransform * glm::vec4(
            cubePositions[i * 3 + 0], cubePositions[i * 3 + 1], cubePositions[i * 3 + 2], 1.0f);
        worldVertices[i] = glm::vec3(worldPos);
    }

    bool frontFacing[12];
    for (int i = 0; i < 12; i++) {
        int idx0 = cubeIndices[i * 3 + 0];
        int idx1 = cubeIndices[i * 3 + 1];
        int idx2 = cubeIndices[i * 3 + 2];
        glm::vec3 v0 = worldVertices[idx0];
        glm::vec3 v1 = worldVertices[idx1];
        glm::vec3 v2 = worldVertices[idx2];
        glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
        glm::vec3 lightDir = glm::normalize(lightPosWorld - v0);
        frontFacing[i] = glm::dot(normal, lightDir) > 0.0f;
    }

    // silhouette edges
    for (int e = 0; e < numCubeEdges; e++) {
        int tri0 = cubeEdges[e].triIndex0;
        int tri1 = cubeEdges[e].triIndex1;

        if (frontFacing[tri0] != frontFacing[tri1]) {
            int v0Idx = cubeEdges[e].v0;
            int v1Idx = cubeEdges[e].v1;

            // Orient edge so v0->v1 is CCW around light-facing triangle
            if (frontFacing[tri1]) {
                std::swap(v0Idx, v1Idx);
            }

            glm::vec3 v0 = worldVertices[v0Idx];
            glm::vec3 v1 = worldVertices[v1Idx];

            glm::vec3 v0_ext = v0 + glm::normalize(v0 - lightPosWorld) * EXTRUSION_DISTANCE;
            glm::vec3 v1_ext = v1 + glm::normalize(v1 - lightPosWorld) * EXTRUSION_DISTANCE;

            // Triangle 1: (v0, v0_ext, v1_ext)
            shadowVolumeVertices.push_back(v0.x); shadowVolumeVertices.push_back(v0.y); shadowVolumeVertices.push_back(v0.z);
            shadowVolumeVertices.push_back(v0_ext.x); shadowVolumeVertices.push_back(v0_ext.y); shadowVolumeVertices.push_back(v0_ext.z);
            shadowVolumeVertices.push_back(v1_ext.x); shadowVolumeVertices.push_back(v1_ext.y); shadowVolumeVertices.push_back(v1_ext.z);

            // Triangle 2: (v0, v1_ext, v1)
            shadowVolumeVertices.push_back(v0.x); shadowVolumeVertices.push_back(v0.y); shadowVolumeVertices.push_back(v0.z);
            shadowVolumeVertices.push_back(v1_ext.x); shadowVolumeVertices.push_back(v1_ext.y); shadowVolumeVertices.push_back(v1_ext.z);
            shadowVolumeVertices.push_back(v1.x); shadowVolumeVertices.push_back(v1.y); shadowVolumeVertices.push_back(v1.z);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, shadowVolumeVBO);
    glBufferData(GL_ARRAY_BUFFER, shadowVolumeVertices.size() * sizeof(GLfloat), shadowVolumeVertices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void RenderCube(Shader& shader, const glm::mat4& cubeTransform)
{
    shader.UseProgram();
    glm::mat4 view = camera.GetViewMatrix();
    shader.SetMatrix4fv("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight), 0.1f, 100.0f);
    shader.SetMatrix4fv("projection", projection);
    shader.SetMatrix4fv("transform", cubeTransform);
    shader.SetVec3f("LightPos", LightPos);
    shader.SetVec3f("ViewPos", camera.GetPosition());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

static void RenderGround(Shader& shader)
{
    shader.UseProgram();
    glm::mat4 view = camera.GetViewMatrix();
    shader.SetMatrix4fv("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight), 0.1f, 100.0f);
    shader.SetMatrix4fv("projection", projection);
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -2.0f));
    shader.SetMatrix4fv("transform", transform);
    shader.SetVec3f("LightPos", LightPos);
    shader.SetVec3f("ViewPos", camera.GetPosition());
    glBindVertexArray(groundVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

static void RenderLight(Shader& shader)
{
    shader.UseProgram();
    glm::mat4 view = camera.GetViewMatrix();
    shader.SetMatrix4fv("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight), 0.1f, 100.0f);
    shader.SetMatrix4fv("projection", projection);
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, LightPos);
    transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));
    shader.SetMatrix4fv("transform", transform);
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    GLFWwindow* window = glfwCreateWindow(800, 600, "F23040113", NULL, NULL);
    if (window == NULL) { ERROR_LOG("Failed to create GLFW window") }
    glfwMakeContextCurrent(window);
    if (GLEW_OK != glewInit()) { ERROR_LOG("Failed to init glew") }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    CreateVertexBuffer();
    CreateLight();
    CreateGround();
    CreateShadowVolume();
    Shader ambientShader = Shader("res/shaders/core.vs", "res/shaders/ambient.fs");
    Shader lightingShader = Shader("res/shaders/core.vs", "res/shaders/lighting.fs");
    Shader shadowShader = Shader("res/shaders/shadow.vs", "res/shaders/shadow.fs");
    Shader lightShader = Shader("res/shaders/light.vs", "res/shaders/light.fs");

    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        SetViewport(window);
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        transform = glm::mat4(1.0f);

        // Light orbits around the cube
        float angle = currentTime * 1.0f;  // 1 radian per second
        float radius = 2.0f;
        LightPos = glm::vec3(
            radius * cos(angle),
            2.0f,
            radius * sin(angle)
        );

        // CUBE ON GROUND - POSITIONED + SMALL TILT
        glm::mat4 cubeTransform = glm::mat4(1.0f);

        // Step 1: Translate to world position first
        cubeTransform = glm::translate(cubeTransform, glm::vec3(0.0f, -0.25f, -2.0f));

        // Step 2: Small rotation to show 3D (15 degrees around Y axis)
        cubeTransform = glm::rotate(cubeTransform, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // Step 3: Scale to half size
        cubeTransform = glm::scale(cubeTransform, glm::vec3(0.5, 0.5, 0.5));

        // Cube bottom at y = -0.5, resting on ground!

        GenerateShadowVolume(LightPos, cubeTransform);

        // PASS 1: Ambient lighting
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        RenderGround(ambientShader);
        RenderCube(ambientShader, cubeTransform);
        RenderLight(lightShader);

        // PASS 2: Shadow volumes - Z-PASS
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LESS);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glStencilMask(0xFF);
        glEnable(GL_CULL_FACE);

        shadowShader.UseProgram();
        glm::mat4 view = camera.GetViewMatrix();
        shadowShader.SetMatrix4fv("view", view);
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight), 0.1f, 100.0f);
        shadowShader.SetMatrix4fv("projection", projection);
        glBindVertexArray(shadowVolumeVAO);

        // Front faces - INCREMENT on depth PASS
        glCullFace(GL_BACK);
        glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(shadowVolumeVertices.size() / 3));

        // Back faces - DECREMENT on depth PASS
        glCullFace(GL_FRONT);
        glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(shadowVolumeVertices.size() / 3));

        glBindVertexArray(0);
        glDisable(GL_CULL_FACE);

        // PASS 3: Add lighting where stencil == 0
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glStencilFunc(GL_EQUAL, 0, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        RenderGround(lightingShader);
        RenderCube(lightingShader, cubeTransform);
        glDisable(GL_BLEND);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

        glfwSwapBuffers(window);
    }
    return 1;
}