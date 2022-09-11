#include "Logger.hpp"

namespace Spyral
{
    void Logger::DestroyImpl()
    {
        if (m_DidConsoleExist)
            SetConsoleMode(m_ConsoleHandle, m_OriginalConsoleMode);

        if (!m_DidConsoleExist && m_AttachConsole)
            FreeConsole();

        DestroyG3();
        CloseOutputStreams();
    }

    void Logger::InitImpl(const std::string_view consoleName, const std::filesystem::path& file, const bool attachConsole)
    {
        m_ConsoleTitle = consoleName;
        m_File = file;
        m_AttachConsole = attachConsole;

        if (m_AttachConsole)
        {
            if (m_DidConsoleExist = ::AttachConsole(GetCurrentProcessId()); !m_DidConsoleExist)
                AllocConsole();

            if (m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); m_ConsoleHandle != nullptr)
            {
                SetConsoleTitleA(m_ConsoleTitle.data());
                SetConsoleOutputCP(CP_UTF8);

                DWORD consoleMode;
                GetConsoleMode(m_ConsoleHandle, &consoleMode);
                m_OriginalConsoleMode = consoleMode;

                // terminal like behaviour enable full color support
                consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
                // prevent clicking in terminal from suspending our main thread
                consoleMode &= ~(ENABLE_QUICK_EDIT_MODE);

                SetConsoleMode(m_ConsoleHandle, consoleMode);
            }
        }

        OpenOutputStreams();
        InitG3();
    }

    void Logger::DestroyG3()
    {
        m_Worker->removeAllSinks();
        m_Worker.reset();
    }

    void Logger::InitG3()
    {
        m_Worker = g3::LogWorker::createLogWorker();
        m_Worker->addSink(std::make_unique<LogSink>(), &LogSink::Callback);
        g3::initializeLogging(m_Worker.get());
    }

    void Logger::CloseOutputStreams()
    {
        if (m_AttachConsole)
            m_ConsoleOut.close();
        m_FileOut.close();
    }

    void Logger::OpenOutputStreams()
    {
        if (m_AttachConsole)
            m_ConsoleOut.open("CONOUT$", std::ios::out | std::ios::app);
        m_FileOut.open(m_File, std::ios::out | std::ios::trunc);
    }
}