//
//  MetalRenderer.hpp
//  Bretema
//
//  Created by Cl0ud7.
//

#ifndef MetalRenderer_hpp
#define MetalRenderer_hpp

#include <stdio.h>

#include <AppKit/AppKit.hpp>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <Foundation/Foundation.hpp>


namespace Bretema {
    class MetalRenderer
    {
    public:
        MetalRenderer(MTL::Device* device);
        ~MetalRenderer();

        void draw(MTK::View* view);
        void buildBuffers();
        void buildShaders();

    private:
        MTL::Device* m_Device;
        MTL::CommandQueue* m_CommandQueue;

        MTL::Library* m_ShaderLibrary;

        MTL::RenderPipelineState* m_PSO;
        MTL::Buffer* m_ArgBuffer;
        MTL::Buffer* m_VertexPositionBuffer;
        MTL::Buffer* m_VertexColorsBuffer;
    };
}

#endif /* MetalRenderer_hpp */
