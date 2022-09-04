#pragma once
#include "MinHook.h"

namespace Spyral
{
    struct MinHook
    {
        MinHook()
        {
            MH_Initialize();
        }

        ~MinHook()
        {
            MH_Uninitialize();
        }

        MinHook(const MinHook&) = delete;
        MinHook(MinHook&&) noexcept = delete;
        MinHook& operator=(const MinHook&) = delete;
        MinHook& operator=(MinHook&&) noexcept = delete;

        void ApplyQueued()
        {
            MH_ApplyQueued();
        }
    };
}