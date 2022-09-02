#include "VMTHook.hpp"

namespace Spyral
{
    VMTHook::VMTHook(const std::string_view name, void*** vmtBaseAddr) :
        m_Name(name),
        m_VMTSize(VMTHook::GetVMTSize(*vmtBaseAddr)),
        m_Enabled(false),
        m_VMTBaseAddr(vmtBaseAddr)
    {
        m_OriginalVMT = *vmtBaseAddr;

        m_NewVMT = new void*[m_VMTSize];
        memcpy(m_NewVMT, m_OriginalVMT, m_VMTSize * sizeof(void*));
    }

    VMTHook::~VMTHook()
    {
        if (m_Enabled)
        {
            *m_VMTBaseAddr = m_OriginalVMT;
        }

        delete[] m_NewVMT;
    }

    const std::string_view VMTHook::Name() const
    {
        return m_Name;
    }

    bool VMTHook::Enable()
    {
        *m_VMTBaseAddr = m_NewVMT;

        return true;
    }

    bool VMTHook::Disable()
    {
        *m_VMTBaseAddr = m_OriginalVMT;

        return true;
    }

    std::size_t VMTHook::GetVMTSize(void** vmt)
    {
        size_t i = 0;
        for (; vmt[i] && vmt[i] < vmt; i++);
        return i;
    }
}