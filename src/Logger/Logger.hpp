#pragma once
#include "../common.hpp"
#include <fstream>
#include <iostream>
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include "LogSink.hpp"

namespace Spyral
{
#define ADD_COLOR_TO_STREAM(color) "\x1b[" << int(color) << "m"
#define RESET_STREAM_COLOR "\x1b[0m"

    class Logger final
    {
    public:
        ~Logger() = default;
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;

        static void Destroy()
        {
            GetInstance().DestroyImpl();
        }
        static void Init(const std::string_view consoleName, const std::filesystem::path& file, const bool attachConsole = true)
        {
            GetInstance().InitImpl(consoleName, file, attachConsole);
        }

    private:
        Logger() {};

        static Logger& GetInstance()
        {
            static Logger i{};
            return i;
        }

        void DestroyImpl();
        void InitImpl(const std::string_view consoleName, const std::filesystem::path& file, const bool attachConsole);

        void DestroyG3();
        void InitG3();

        void CloseOutputStreams();
        void OpenOutputStreams();

    private:
        friend struct LogSink;

        bool m_AttachConsole;
		bool m_DidConsoleExist;

		std::string_view m_ConsoleTitle;
		DWORD m_OriginalConsoleMode;
		HANDLE m_ConsoleHandle;

		std::ofstream m_ConsoleOut;
        std::filesystem::path m_File;
        std::ofstream m_FileOut;

        std::unique_ptr<g3::LogWorker> m_Worker;


    };
}