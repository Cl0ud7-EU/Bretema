//
//  Window.hpp
//  Bretema
//
//  Created by Cl0ud7.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include <iostream>

namespace Bretema {

    struct WindowConfig
    {
        uint32_t Height = 1280;
        uint32_t Width = 720;
        std::string Title = "Game Engine";
    };

    class Window
    {
    public:
        
        static Window* Create(const WindowConfig& = WindowConfig());
        
        virtual ~Window() {}
        virtual void Update() = 0;
        
    };

}

#endif /* Window_hpp */
