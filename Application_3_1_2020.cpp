#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Object.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "models/SphereData.h"

// GL 3.0 + GLSL 130
const char* glsl_version = "#version 130";
//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << ":(" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions0[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, //0
         0.5f, -0.5f, 1.0f, 0.0f,//1
         0.5f, 0.5f, 1.0f, 1.0f, //2
         -0.5f, 0.5f, 0.0f, 1.0f//3
    };


    float positions[] = {
        -50.0f, -50.0f, 0.0f, 0.0f, //0
         50.0f, -50.0f, 1.0f, 0.0f,//1
         50.0f, 50.0f, 1.0f, 1.0f, //2
         -50.0f, 50.0f, 0.0f, 1.0f//3
    };


    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    //VertexArray va;
    VertexBuffer vb(sphereVertices, sphereVerticesLength * sizeof(float));

    VertexBufferLayout layout;
    layout.push <float>(3);
    //layout.push<float>(2);
    //va.addBuffer(vb, layout);

    

    IndexBuffer ib(sphereElements, sphereElementsLength);   

    //glm::mat4 proj = glm::ortho(-0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));


    glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

  

    Shader shader("res/shaders/Basic.shader");
    //shader.bind();
 

    Object sphere = Object(vb, ib, layout, shader, glm::mat4(1.0f));

    Texture texture("res/textures/cherno_logo.png");
    texture.bind();
    

  /*  va.unbind();
    shader.unbind();
    vb.unbind();
    ib.unbind();*/

    Renderer renderer;
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glm::vec3 translation = glm::vec3(0, 0, 0);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
       

        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.90f, 1.00f);

        //// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::SliderFloat("Translation X", &translation.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("Translation Y", &translation.y, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("Translation z", &translation.z, -1.00f, 1.00f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
     
        }
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //
        //shader.bind();
        //shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
      /*  {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = proj * view * model;
            shader.setUniformMat4f("u_MVP", mvp);
            renderer.draw(va, ib, shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 mvp = proj * view * model;
            shader.setUniformMat4f("u_MVP", mvp);
            renderer.draw(va, ib, shader);
        }*/
        shader.bind();
        sphere.transform(glm::translate(glm::mat4(1.0f), translation));
        shader.setUniformMat4f("u_proj", proj);
        shader.setUniformMat4f("u_view", view);
        sphere.setAllData();
        renderer.draw(sphere.getVArray(), sphere.getIBuffer(), sphere.getShader());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }    
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}


