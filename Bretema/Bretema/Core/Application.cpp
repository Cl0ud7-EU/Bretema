//
//  Application.cpp
//  Bretema
//
//  Created by Cl0ud7.
//

#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>

#include "Application.hpp"

namespace Bretema {

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
        
    }
    
    void Application::Run()
    {
        
        double DeltaTime = 0;
        int Count = 0;
        while (m_IsRunning)
        {
            // Just for test until find a good way to enable VSYNC in metal c++
            auto StartTime = glfwGetTime();
            m_Window->Update();
            auto EndTime = glfwGetTime();
            DeltaTime += (EndTime - StartTime) / limitFPS;
            
            if (DeltaTime > 16.6)
            {
                Count++;
                DeltaTime = 0;
            }
            
            if (Count == 10)
            {
                m_IsRunning = false;
            }
        }
    }
}
