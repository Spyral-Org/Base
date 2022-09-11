#include "../common.hpp"
#include "Logger.hpp"
#include "LogSink.hpp"

namespace Spyral
{
    void LogSink::Callback(g3::LogMessageMover log)
    {
        if (auto& cout = Logger::GetInstance().m_ConsoleOut; cout.is_open())
            cout << log.get().toString(LogSink::FormatConsole) << std::flush;

        if (auto& file = Logger::GetInstance().m_FileOut; file.is_open())
            file << log.get().toString(LogSink::FormatFile) << std::flush;
    }

    LogColor LogSink::GetColor(const LEVELS level)
    {
        switch (level.value)
        {
        case g3::kDebugValue:
            return LogColor::BLUE;
        case g3::kInfoValue:
            return LogColor::GREEN;
        case g3::kWarningValue:
            return LogColor::YELLOW;
        }
        return g3::internal::wasFatal(level) ? LogColor::RED : LogColor::WHITE;
    }

    std::string LogSink::FormatConsole(const g3::LogMessage& msg)
    {
        LogColor color = LogSink::GetColor(msg._level);
        std::stringstream out;

        out
            << "[" << msg.timestamp("%H:%M:%S") << "]"
            << ADD_COLOR_TO_STREAM(color)
            << "[" << msg.level() << "/"
            << msg.file() << ":" << msg.line() << "]"
            << RESET_STREAM_COLOR
            << ": ";

        return out.str();
    }

    std::string LogSink::FormatFile(const g3::LogMessage& msg)
    {
        std::stringstream out;

        out
            << "[" << msg.timestamp("%H:%M:%S") << "]"
            << "[" << msg.level() << "/"
            << msg.file() << ":" << msg.line() << "]"
            << ": ";

        return out.str();
    }
}