//
//  Window.cpp
//  Bretema
//
//  Created by Cl0ud7.
//

#include "Window.hpp"

#include "OpenGLWindow.hpp"

#ifdef __APPLE__
    #include "MetalWindow.hpp"
#endif

namespace Bretema {

    Window* Window::Create(const WindowConfig& props)
    {
    #ifdef __APPLE__
        //#ifdef METAL
        return new MetalWindow(props);
        //#else
        //return new OpenGLWindow(props);
        //#endif
    #elif _WIN64
        /* Windows x64  */
        return new OpenGLWindow(props);
    #else
        //("Unknown platform!");
        return nullptr;
    #endif
    }

}

