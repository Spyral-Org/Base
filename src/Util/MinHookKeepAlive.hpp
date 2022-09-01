#pragma once
#include "MinHook.h"

namespace Spyral
{
    struct MinHookKeepAlive
    {
        MinHookKeepAlive()
        {
            MH_Initialize();
        }

        ~MinHookKeepAlive()
        {
            MH_Uninitialize();
        }

        MinHookKeepAlive(const MinHookKeepAlive&) = delete;
        MinHookKeepAlive(MinHookKeepAlive&&) noexcept = delete;
        MinHookKeepAlive& operator=(const MinHookKeepAlive&) = delete;
        MinHookKeepAlive& operator=(MinHookKeepAlive&&) noexcept = delete;

        void ApplyQueued()
        {
            MH_ApplyQueued();
        }
    };
}