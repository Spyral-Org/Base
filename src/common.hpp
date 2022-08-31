#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include <stdexcept>

#include <filesystem>
#include <iostream>

#include <thread>

#include <string_view>

namespace Spyral
{
    extern std::thread gMainThread;
    extern HINSTANCE gInstance;

    extern bool gRunning;

    using namespace std::chrono_literals;
}