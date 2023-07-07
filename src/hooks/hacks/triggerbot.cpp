#include <pch.h>
#include <base.h>

using namespace Base::Hacks::Trigger;

void Base::Hacks::Trigger::Load()
{
    DWORD oldp;
    VirtualProtect(Base::Offsets::dwForceAttack, 4, PAGE_EXECUTE_READWRITE, &oldp);
    target_address = (unsigned char*)Base::Offsets::hClientDll + 0x125291;
    hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Thread, Base::Data::hModule, 0, nullptr);
}

void Base::Hacks::Trigger::Unload()
{
    TerminateThread(hThread, 0);
}

void Base::Hacks::Trigger::Thread()
{
    while (true)
    {
        if (!Base::Data::Detached) 
        {
            if (Active)
            {
                if (!GetAsyncKeyState(VK_LBUTTON))
                {
                    if (*target_address == 'E' && *Base::Offsets::dwWeaponId != 29)
                    {
                        *Base::Offsets::dwForceAttack = 2;
                    }
                }
            }
        }
        else
            return;

        Sleep(Delay);
    }
}
