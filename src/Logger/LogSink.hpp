#pragma once
#include "../common.hpp"
#include "LogColor.hpp"
#include <g3log/g3log.hpp>

namespace Spyral
{
    struct LogSink
    {
        void Callback(g3::LogMessageMover log);

        static LogColor GetColor(const LEVELS level);

        static std::string FormatConsole(const g3::LogMessage& msg);
        static std::string FormatFile(const g3::LogMessage& msg);
    };
}