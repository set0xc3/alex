#include "alex_application.h"

int 
main()
{
    startup_application();
    application_run();
    
    return 0;
}

#if 0
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include "alex.h"
#include "alex_imgui.h"
#include "alex_logger.h"

internal void 
glfw_error_callback(i32 error, const char* description)
{
    LOG_ERROR("[GLFW] %d: %s", error, description);
}

int 
main()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return -1;
    
    // GL 3.0 + GLSL 130
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    
    // Create window with graphics context
    app.window = glfwCreateWindow(1280, 720, "AlexEngine", 0, 0);
    if (!app.window)
        return -1;
    glfwMakeContextCurrent(app.window);
    glfwSwapInterval(1); // Enable vsync
    
    imgui_init(&app);
    
    // Our state
    b8 show_demo_window = true;
    b8 show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    // Main loop
    while (!glfwWindowShouldClose(app.window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        
        imgui_begin();
        
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            local_variable f32 f = 0.0f;
            local_variable i32 counter = 0;
            
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            
            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);
            
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (f32*)&clear_color); // Edit 3 floats representing a color
            
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        
        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
        
        // Rendering
        i32 display_w, display_h;
        glfwGetFramebufferSize(app.window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        
        imgui_end(&app);
        
        glfwSwapBuffers(app.window);
    }
    
    // Cleanup
    imgui_release();
    
    glfwDestroyWindow(app.window);
    glfwTerminate();
    
    return 0;
}
#endif