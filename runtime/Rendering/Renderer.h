/*
Copyright(c) 2016-2023 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ====================
#include "Renderer_Definitions.h"
#include "../RHI/RHI_Texture.h"
#include "../Math/Rectangle.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Plane.h"
#include "Event.h"
#include "Mesh.h"
#include "Renderer_Buffers.h"
#include "Font/Font.h"
#include <unordered_map>
//===============================

namespace Spartan
{
    //= FWD DECLARATIONS =
    class Entity;
    class Camera;
    class Light;
    namespace Math
    {
        class BoundingBox;
        class Frustum;
    }
    //====================

    class SP_CLASS Renderer
    {
    public:
        static void Initialize();
        static void Shutdown();
        static void Tick();
        static void PostTick();

        // primitive rendering (useful for debugging)
        static void DrawLine(const Math::Vector3& from, const Math::Vector3& to, const Math::Vector4& color_from = debug_color, const Math::Vector4& color_to = debug_color, const float duration = 0.0f, const bool depth = true);
        static void DrawTriangle(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Math::Vector4& color = debug_color, const float duration = 0.0f, const bool depth = true);
        static void DrawBox(const Math::BoundingBox& box, const Math::Vector4& color = debug_color, const float duration = 0.0f, const bool depth = true);
        static void DrawCircle(const Math::Vector3& center, const Math::Vector3& axis, const float radius, uint32_t segment_count, const Math::Vector4& color = debug_color, const float duration = 0.0f, const bool depth = true);
        static void DrawSphere(const Math::Vector3& center, float radius, uint32_t segment_count, const Math::Vector4& color = debug_color, const float duration = 0.0f, const bool depth = true);
        static void DrawDirectionalArrow(const Math::Vector3& start, const Math::Vector3& end, float arrow_size, const Math::Vector4& color = debug_color, const float duration = 0.0f, const bool depth = true);
        static void DrawPlane(const Math::Plane& plane, const Math::Vector4& color = debug_color, const float duration = 0.0f, const bool depth = true);
        static void DrawString(const std::string& text, const Math::Vector2& position_screen_percentage);

        // options
        template<typename T>
        static T GetOption(const Renderer_Option option) { return static_cast<T>(GetOptions()[option]); }
        static void SetOption(Renderer_Option option, float value);
        static std::unordered_map<Renderer_Option, float>& GetOptions();
        static void SetOptions(const std::unordered_map<Renderer_Option, float>& options);

        // swapchain
        static RHI_SwapChain* GetSwapChain();
        static void Present();

        // mip generation
        static void AddTextureForMipGeneration(RHI_Texture* texture);
        static void Pass_GenerateMips(RHI_CommandList* cmd_list, RHI_Texture* texture);

        // misc
        static void SetGlobalShaderResources(RHI_CommandList* cmd_list);
        static uint64_t GetFrameNum();
        static RHI_Api_Type GetRhiApiType();
        static void Screenshot(const std::string& file_path);

        //= RESOLUTION/SIZE =============================================================================
        // biewport
        static const RHI_Viewport& GetViewport();
        static void SetViewport(float width, float height);

        // resolution render
        static const Math::Vector2& GetResolutionRender();
        static void SetResolutionRender(uint32_t width, uint32_t height, bool recreate_resources = true);

        // resolution output
        static const Math::Vector2& GetResolutionOutput();
        static void SetResolutionOutput(uint32_t width, uint32_t height, bool recreate_resources = true);
        //===============================================================================================
        // 
        //= RHI RESOURCES====================
        static RHI_CommandList* GetCmdList();
        //===================================

        //= RESOURCES ===========================================================================================
        static RHI_Texture* GetFrameTexture();
        static std::shared_ptr<Camera> GetCamera();
        static std::unordered_map<Renderer_Entity, std::vector<std::shared_ptr<Entity>>>& GetEntities();

        // get all
        static std::array<std::shared_ptr<RHI_Texture>, render_target_count>& GetRenderTargets();
        static std::array<std::shared_ptr<RHI_Shader>, shader_count>& GetShaders();
        static std::array<std::shared_ptr<RHI_ConstantBuffer>, 3>& GetConstantBuffers();
        static std::array<std::shared_ptr<RHI_StructuredBuffer>, 2>& GetStructuredBuffers();

        // get individual
        static std::shared_ptr<RHI_RasterizerState> GetRasterizerState(const Renderer_RasterizerState type);
        static std::shared_ptr<RHI_DepthStencilState> GetDepthStencilState(const Renderer_DepthStencilState type);
        static std::shared_ptr<RHI_BlendState> GetBlendState(const Renderer_BlendState type);
        static std::shared_ptr<RHI_Texture> GetRenderTarget(const Renderer_RenderTexture type);
        static std::shared_ptr<RHI_Shader> GetShader(const Renderer_Shader type);
        static std::shared_ptr<RHI_Sampler> GetSampler(const Renderer_Sampler type);
        static std::shared_ptr<RHI_ConstantBuffer> GetConstantBuffer(const Renderer_ConstantBuffer type);
        static std::shared_ptr<RHI_StructuredBuffer> GetStructuredBuffer(const Renderer_StructuredBuffer type);
        static std::shared_ptr<RHI_Texture> GetStandardTexture(const Renderer_StandardTexture type);
        static std::shared_ptr<Mesh> GetStandardMesh(const Renderer_MeshType type);
        static std::shared_ptr<Font> GetFont();
        //=======================================================================================================

    private:
        // constant buffers
        static void UpdateConstantBufferFrame(RHI_CommandList* cmd_list, const bool set = true);
        static void UpdateConstantBufferLight(RHI_CommandList* cmd_list, const std::shared_ptr<Light> light);
        static void UpdateConstantBufferMaterial(RHI_CommandList* cmd_list, Material* material);
        static void PushPassConstants(RHI_CommandList* cmd_list);

        // resource creation
        static void CreateConstantBuffers();
        static void CreateStructuredBuffers();
        static void CreateDepthStencilStates();
        static void CreateRasterizerStates();
        static void CreateBlendStates();
        static void CreateFonts();
        static void CreateStandardMeshes();
        static void CreateStandardTextures();
        static void CreateShaders();
        static void CreateSamplers(const bool create_only_anisotropic = false);
        static void CreateRenderTextures(const bool create_render, const bool create_output, const bool create_fixed, const bool create_dynamic);

        // passes - core
        static void Pass_Frame(RHI_CommandList* cmd_list);
        static void Pass_ShadowMaps(RHI_CommandList* cmd_list, const bool is_transparent_pass = false);
        static void Pass_ReflectionProbes(RHI_CommandList* cmd_list);
        static void Pass_Depth_Prepass(RHI_CommandList* cmd_list, const bool is_transparent_pass = false);
        static void Pass_GBuffer(RHI_CommandList* cmd_list, const bool is_transparent_pass = false);
        static void Pass_Ssgi(RHI_CommandList* cmd_list);
        static void Pass_Ssr(RHI_CommandList* cmd_list, RHI_Texture* tex_in, const bool is_transparent_pass = false);
        static void Pass_Sss_Bend(RHI_CommandList* cmd_list);
        static void Pass_AtmosphericScattering(RHI_CommandList* cmd_list);
        static void Pass_BrdfSpecularLut(RHI_CommandList* cmd_list);
        static void Pass_Blur_Gaussian(RHI_CommandList* cmd_list, RHI_Texture* tex_in, const bool depth_aware, const float radius, const float sigma, const uint32_t mip = rhi_all_mips);
        // passes - debug/editor
        static void Pass_Grid(RHI_CommandList* cmd_list, RHI_Texture* tex_out);
        static void Pass_Lines(RHI_CommandList* cmd_list, RHI_Texture* tex_out);
        static void Pass_DebugMeshes(RHI_CommandList* cmd_list, RHI_Texture* tex_out);
        static void Pass_Outline(RHI_CommandList* cmd_list, RHI_Texture* tex_out);
        static void Pass_Icons(RHI_CommandList* cmd_list, RHI_Texture* tex_out);
        static void Pass_Text(RHI_CommandList* cmd_list, RHI_Texture* tex_out);
        // passes - post-process
        static void Pass_PostProcess(RHI_CommandList* cmd_list);
        static void Pass_ToneMappingGammaCorrection(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);
        static void Pass_Fxaa(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);
        static void Pass_FilmGrain(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);
        static void Pass_ChromaticAberration(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);
        static void Pass_MotionBlur(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);
        static void Pass_DepthOfField(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);
        static void Pass_Debanding(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);
        static void Pass_Bloom(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);
        // passes - Lighting
        static void Pass_Light(RHI_CommandList* cmd_list, const bool is_transparent_pass = false);
        static void Pass_Light_Composition(RHI_CommandList* cmd_list, RHI_Texture* tex_out, const bool is_transparent_pass = false);
        static void Pass_Light_ImageBased(RHI_CommandList* cmd_list, RHI_Texture* tex_out, const bool is_transparent_pass = false);
        // passes - amd fidelityfx
        static void Pass_Ffx_Cas(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);
        static void Pass_Ffx_Spd(RHI_CommandList* cmd_list, RHI_Texture* tex);
        static void Pass_Ffx_Fsr2(RHI_CommandList* cmd_list, RHI_Texture* tex_in, RHI_Texture* tex_out);

        // event handlers
        static void OnMaterialChanged();
        static void OnWorldResolved(sp_variant data);
        static void OnClear();
        static void OnFullScreenToggled();

        // lines
        static void Lines_OneFrameStart();
        static void Lines_OnFrameEnd();

        // frame
        static void OnFrameStart(RHI_CommandList* cmd_list);
        static void OnFrameEnd(RHI_CommandList* cmd_list);

        // common texture binding
        static void SetTexturesGfbuffer(RHI_CommandList* cmd_list);
        static void SetTexturesMaterial(RHI_CommandList* cmd_list, Material* material);

        // misc
        static void DestroyResources();

        // misc
        static std::unordered_map<Renderer_Entity, std::vector<std::shared_ptr<Entity>>> m_renderables;
        static Cb_Frame m_cb_frame_cpu;
        static Pcb_Pass m_cb_pass_cpu;
        static Cb_Light m_cb_light_cpu;
        static Cb_Material m_cb_material_cpu;
        static std::shared_ptr<RHI_VertexBuffer> m_vertex_buffer_lines;
        static bool m_brdf_specular_lut_rendered;
        static std::vector<RHI_Vertex_PosCol> m_line_vertices;
        static std::vector<float> m_lines_duration;
        static uint32_t m_lines_index_depth_off;
        static uint32_t m_lines_index_depth_on;
        static RHI_CommandPool* m_cmd_pool;
        static std::shared_ptr<Camera> m_camera;
        static uint32_t m_resource_index;
    };
}
