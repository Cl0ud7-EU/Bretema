//
//  Application.hpp
//  Bretema
//
//  Created by Cl0ud7.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>
#include "Window.hpp"
#include <chrono>

namespace Bretema
{
    class Application
    {
    public:
        Application();
        ~Application();
        
        void Run();
    private:
        
        bool m_IsRunning = true;
        std::unique_ptr<Window> m_Window = nullptr;
        
        // Just for test until find a good way to enable VSYNC in metal c++
        const double targetFrameRate = 60.0;
        const double limitFPS = 1.0 / targetFrameRate;
    };

    Application* NewApp();
}

#endif /* Application_hpp */
