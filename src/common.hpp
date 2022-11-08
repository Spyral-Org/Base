#pragma once

#include <Windows.h>
#include <d3d11.h>

#include <stdexcept>

#include <filesystem>
#include <iostream>

#include <functional>
#include <memory>
#include <thread>

#include <map>
#include <ranges>

#include <string_view>

#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <imgui.h>

#include "Logger/Logger.hpp"

namespace Spyral
{
    extern HANDLE gMainThread;
    extern HINSTANCE gInstance;

    extern bool gRunning;

    using namespace std::chrono_literals;
}