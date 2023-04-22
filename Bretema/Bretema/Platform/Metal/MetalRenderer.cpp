//
//  MetalRenderer.cpp
//  Bretema
//
//  Created by Cl0ud7.
//

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include "MetalRenderer.hpp"

#include <simd/simd.h>

namespace Bretema {

    MetalRenderer::MetalRenderer(MTL::Device* device) : m_Device(device->retain())
    {
        m_CommandQueue = m_Device->newCommandQueue();
    }

    MetalRenderer::~MetalRenderer()
    {
        m_CommandQueue->release();
        m_Device->release();
    }

    void MetalRenderer::draw(MTK::View* view)
    {
        NS::AutoreleasePool* Pool = NS::AutoreleasePool::alloc()->init();
        
        MTL::CommandBuffer* CmdBuffer = m_CommandQueue->commandBuffer();
        MTL::RenderPassDescriptor* RenderPDes = view->currentRenderPassDescriptor();
        MTL::RenderCommandEncoder* RenderCmdEncod = CmdBuffer->renderCommandEncoder(RenderPDes);
        
        buildShaders();
        buildBuffers();
        
        RenderCmdEncod->setRenderPipelineState(m_PSO);
        RenderCmdEncod->setVertexBuffer(m_ArgBuffer, 0, 0);
        RenderCmdEncod->useResource(m_VertexPositionBuffer, MTL::ResourceUsageRead);
        RenderCmdEncod->useResource(m_VertexColorsBuffer, MTL::ResourceUsageRead);
        RenderCmdEncod->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3) );
        
        RenderCmdEncod->endEncoding();
        CmdBuffer->presentDrawable(view->currentDrawable());
        CmdBuffer->commit();
        
        Pool->release();
    }

    void MetalRenderer::buildBuffers()
    {
        const size_t NumVertices = 3;

        simd::float3 positions[NumVertices] =
        {
            { -0.8f,  0.8f, 0.0f },
            {  0.0f, -0.8f, 0.0f },
            { +0.8f,  0.8f, 0.0f }
        };

        simd::float3 colors[NumVertices] =
        {
            {  1.0, 0.3f, 0.2f },
            {  0.8f, 1.0, 0.0f },
            {  0.8f, 0.0f, 1.0 }
        };

        const size_t positionsDataSize = NumVertices * sizeof( simd::float3 );
        const size_t colorDataSize = NumVertices * sizeof( simd::float3 );

        MTL::Buffer* VertexPositionsBuffer = m_Device->newBuffer( positionsDataSize, MTL::ResourceStorageModeManaged );
        MTL::Buffer* VertexColorsBuffer = m_Device->newBuffer( colorDataSize, MTL::ResourceStorageModeManaged );

        m_VertexPositionBuffer = VertexPositionsBuffer;
        m_VertexColorsBuffer = VertexColorsBuffer;

        memcpy( m_VertexPositionBuffer->contents(), positions, positionsDataSize );
        memcpy( m_VertexColorsBuffer->contents(), colors, colorDataSize );

        m_VertexPositionBuffer->didModifyRange( NS::Range::Make( 0, m_VertexPositionBuffer->length() ) );
        m_VertexColorsBuffer->didModifyRange( NS::Range::Make( 0, m_VertexColorsBuffer->length() ) );

        using NS::StringEncoding::UTF8StringEncoding;
        assert( m_ShaderLibrary );

        MTL::Function* pVertexFn = m_ShaderLibrary->newFunction( NS::String::string( "vertexMain", UTF8StringEncoding ) );
        MTL::ArgumentEncoder* pArgEncoder = pVertexFn->newArgumentEncoder( 0 );

        MTL::Buffer* pArgBuffer = m_Device->newBuffer( pArgEncoder->encodedLength(), MTL::ResourceStorageModeManaged );
        m_ArgBuffer = pArgBuffer;

        pArgEncoder->setArgumentBuffer( m_ArgBuffer, 0 );

        pArgEncoder->setBuffer( m_VertexPositionBuffer, 0, 0 );
        pArgEncoder->setBuffer( m_VertexColorsBuffer, 0, 1 );

        m_ArgBuffer->didModifyRange( NS::Range::Make( 0, m_ArgBuffer->length() ) );

        pVertexFn->release();
        pArgEncoder->release();
    }

    void MetalRenderer::buildShaders()
    {
        using NS::StringEncoding::UTF8StringEncoding;

        const char* shaderSrc = R"(
            #include <metal_stdlib>
            using namespace metal;

            struct v2f
            {
                float4 position [[position]];
                half3 color;
            };

            struct VertexData
            {
                device float3* positions [[id(0)]];
                device float3* colors [[id(1)]];
            };

            v2f vertex vertexMain( device const VertexData* vertexData [[buffer(0)]], uint vertexId [[vertex_id]] )
            {
                v2f o;
                o.position = float4( vertexData->positions[ vertexId ], 1.0 );
                o.color = half3(vertexData->colors[ vertexId ]);
                return o;
            }

            half4 fragment fragmentMain( v2f in [[stage_in]] )
            {
                return half4( in.color, 1.0 );
            }
        )";

        NS::Error* Error = nullptr;
        MTL::Library* Library = m_Device->newLibrary( NS::String::string(shaderSrc, UTF8StringEncoding), nullptr, &Error );
        if ( !Library )
        {
            __builtin_printf( "%s", Error->localizedDescription()->utf8String() );
            assert( false );
        }

        MTL::Function* VertexFn = Library->newFunction( NS::String::string("vertexMain", UTF8StringEncoding) );
        MTL::Function* FragFn = Library->newFunction( NS::String::string("fragmentMain", UTF8StringEncoding) );

        MTL::RenderPipelineDescriptor* RenderPipeDesc = MTL::RenderPipelineDescriptor::alloc()->init();
        RenderPipeDesc->setVertexFunction( VertexFn );
        RenderPipeDesc->setFragmentFunction( FragFn );
        RenderPipeDesc->colorAttachments()->object(0)->setPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );

        m_PSO = m_Device->newRenderPipelineState( RenderPipeDesc, &Error );
        if ( !m_PSO )
        {
            __builtin_printf( "%s", Error->localizedDescription()->utf8String() );
            assert( false );
        }

        VertexFn->release();
        FragFn->release();
        RenderPipeDesc->release();
        m_ShaderLibrary = Library;
    }
}


