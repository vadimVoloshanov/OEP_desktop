#pragma once

#include <async++.h>

#include <bnb/effect_player/interfaces/all.hpp>
#include <bnb/effect_player/utility.hpp>

#include "../../interfaces/offscreen_effect_player.hpp"
#include "../../interfaces/offscreen_render_target.hpp"

#include "pixel_buffer.hpp"

namespace bnb
{
    class offscreen_effect_player: public interfaces::offscreen_effect_player,
                                   public std::enable_shared_from_this<offscreen_effect_player>
    {
    public:
        static std::shared_ptr<interfaces::offscreen_effect_player> create(
            const std::vector<std::string>& path_to_resources, const std::string& client_token,
            int32_t width, int32_t height, bool manual_audio,
            std::shared_ptr<interfaces::offscreen_render_target> ort = nullptr);

    private:
        offscreen_effect_player(const std::vector<std::string>& path_to_resources,
            const std::string& client_token,
            int32_t width, int32_t height, bool manual_audio,
            std::shared_ptr<interfaces::offscreen_render_target> ort);

    public:
        ~offscreen_effect_player();

        void process_image_async(std::shared_ptr<full_image_t> image,
                std::function<void(std::shared_ptr<interfaces::pixel_buffer> callback)>) override;
        // std::shared_ptr<interfaces::pixel_buffer> process_image_sync(std::shared_ptr<full_image_t> image) override;

        void load_effect(const std::string& effect_path) override;
        void unload_effect() override;

        void pause() override;
        void resume() override;

        void enable_audio(bool enable) override;

        void call_js_method(const std::string& method, const std::string& param) override;

    private:
        template<typename F>
        auto schedule(const F& f)
        {
            return async::spawn(m_scheduler, f);
        }

        friend class pixel_buffer;

        void get_active_texture_id(std::function<void(uint32_t texture_id)> callback);
        void read_current_buffer(std::function<void(bnb::data_t data)> callback);

    private:
        bnb::utility m_utility;
        std::shared_ptr<interfaces::effect_player> m_ep;
        std::shared_ptr<interfaces::offscreen_render_target> m_ort;

        std::atomic<bool> m_cancellation_flag;

        std::thread m_render_thread;
        async::fifo_scheduler m_scheduler;

        std::shared_ptr<interfaces::pixel_buffer> current_frame;
    };
} // bnb