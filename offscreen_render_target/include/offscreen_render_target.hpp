#pragma once

#include <bnb/types/base_types.hpp>

#include "../../interfaces/offscreen_render_target.hpp"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace bnb
{
    class offscreen_render_target : public interfaces::offscreen_render_target
    {
    public:
        offscreen_render_target(uint32_t width, uint32_t height);

        void activate_context() override;
        void prepare_rendering() override;

        bnb::data_t read_current_buffer() override;

    private:
        void create_context();
        void load_glad_functions();

        uint32_t m_width;
        uint32_t m_height;

        GLuint m_framebuffer{ 0 };
        GLuint texture{ 0 };

        std::shared_ptr<GLFWwindow> renderer_context;
    };
} // bnb