#include "../Hooks.hpp"
#include "../../Hooking.hpp"

namespace Spyral
{
    BOOL Kernel32::IsDebuggerPresent()
    {
        LOG(G3LOG_DEBUG) << "IsDebuggerPresent was called!";
        return FALSE;
        // return Hooking::GetHook<IATHook*>("IsDebuggerPresent")->Original<decltype(&Kernel32::IsDebuggerPresent)>()();
    }
}