//
//  MetalWindow.hpp
//  Bretema
//
//  Created by Cl0ud7.
//

#ifndef MetalWindow_hpp
#define MetalWindow_hpp

#include <stdio.h>

#define GLFW_INCLUDE_NONE
#import <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#import <GLFW/glfw3native.h>

#include "Window.hpp"
#include "ViewDelegate.hpp"

namespace Bretema {

    class MetalWindow : public Window
    {
    public:
        
        MetalWindow(const WindowConfig& config);
        virtual ~MetalWindow();
        
        void Update();
        void Close();

    private:
        
        virtual void Init(const WindowConfig& config);
        
        GLFWwindow* m_GLFWWindow;
        
        NS::Window* m_Window;
        MTK::View* m_View = nullptr;
        MTL::Device* m_Device = nullptr;
        MTK::ViewDelegate* m_ViewDelegate = nullptr;
    };
}

#endif /* MetalWindow_hpp */
