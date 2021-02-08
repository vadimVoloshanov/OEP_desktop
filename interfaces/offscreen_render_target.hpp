#pragma once

#include <bnb/types/base_types.hpp>

namespace bnb::interfaces
{
    class offscreen_render_target
    {
    public:
        virtual ~offscreen_render_target() = default;

        //activate context for current thread
        virtual void activate_context() = 0;
        //preparing texture for effect_player
        virtual void prepare_rendering() = 0;

        //reading current buffer of active texture
        virtual bnb::data_t read_current_buffer() = 0;
    };
} // bnb::interfaces