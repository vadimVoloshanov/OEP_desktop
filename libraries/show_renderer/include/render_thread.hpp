#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <thread>
#include <async++.h>

#include "renderer.hpp"

namespace render {

class render_thread
{
public:
    render_thread(GLFWwindow* window, int32_t width, int32_t height);

    ~render_thread();

    void surface_changed(int32_t width, int32_t height);

    void update_data(bnb::full_image_t image);
    void update_data(bnb::data_t data);
    void update_context();

    template<typename F>
    auto schedule(const F& f)
    {
        return async::spawn(m_scheduler, f);
    }

private:
    void thread_func();

    std::unique_ptr<bnb::renderer> m_renderer { nullptr };
    GLFWwindow* m_window;
    std::thread m_thread;
    std::atomic<bool> m_cancellation_flag;
    async::fifo_scheduler m_scheduler;

    int32_t m_cur_width;
    int32_t m_cur_height;

    bnb::color_plane m_cur_y_plane = nullptr;
    bnb::color_plane m_cur_uv_plane = nullptr;

    uint8_t* m_y_row_ptr;
    uint8_t* m_uv_row_ptr;
};

} //render