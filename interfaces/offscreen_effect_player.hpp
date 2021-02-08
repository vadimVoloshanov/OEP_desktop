#pragma once

#include <bnb/types/full_image.hpp>

#include "pixel_buffer.hpp"

namespace bnb {

    using pb_callback = std::function<void(std::shared_ptr<interfaces::pixel_buffer>)>;

namespace interfaces
{
    class offscreen_effect_player
    {
    public:
        virtual ~offscreen_effect_player() = default;

        //an asynchronous method for passing a frame to effect_player, and calling callback as a frame will be processed
        virtual void process_image_async(std::shared_ptr<full_image_t> image, pb_callback callback) = 0;

        //loading effect 
        virtual void load_effect(const std::string& effect_path) = 0;
        //unload effect
        virtual void unload_effect() = 0;

        //pause in effect player
        virtual void pause() = 0;
        //resume in effect player
        virtual void resume() = 0;

        //enable audio for effect
        virtual void enable_audio(bool enable) = 0;

        //call js method
        virtual void call_js_method(const std::string& method, const std::string& param) = 0;
    };
}
} // bnb::interfaces