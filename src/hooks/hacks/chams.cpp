#include <pch.h>
#include <base.h>
#include "chams.h"

using namespace Base::Hacks::Chams;
using namespace Base::Colors::Chams;

void Base::Hacks::Chams::Load()
{
    DWORD old_protect;
    VirtualProtect((void*)hook_location, 8, PAGE_EXECUTE_READWRITE, &old_protect);

    for (int i = 0; i < 7; i++) {
        old_opcodes[i] = *(hook_location + i);
    }

    *(hook_location) = 0xE9;
    *(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5);
    *(hook_location + 5) = 0x90;
    *(hook_location + 6) = 0x90;
}

void Base::Hacks::Chams::Unload()
{
    for (int i = 0; i < 7; i++) {
        *(hook_location + i) = old_opcodes[i];
    }

    // CRASH
    //DWORD old_protect;
    //VirtualProtect((void*)hook_location, 8, PAGE_EXECUTE_READ, &old_protect);
}

__declspec(naked) void Base::Hacks::Chams::codecave()
{
    __asm {
        pushad
    }

    memcpy(&current_model, (void*)*current_model_p, 8);
    ConvertToLower(current_model);

    if (Active)
    {
        if (current_item == 0)
        {
            if (GetTeam(current_model) == 0)
            {
                CurrentColor = CT::Color;
                goto enable_chams;
            }
            else if (GetTeam(current_model) == 1)
            {
                CurrentColor = T::Color;
                goto enable_chams;
            }
            else if (GetTeam(current_model) == 2)
            {
                CurrentColor = Models::Color;
                goto enable_chams;
            }

            goto disable_chams;
        }
        else if (current_item == 1)
        {
            if (GetTeam(current_model) == 0) 
            {
                CurrentColor = CT::Color;
                goto enable_chams;
            }

            goto disable_chams;
        }
        else if (current_item == 2)
        {
            if (GetTeam(current_model) == 1) 
            {
                CurrentColor = T::Color;
                goto enable_chams;
            }

            goto disable_chams;
        }
        else if (current_item == 3)
        {
            if (GetTeam(current_model) == 0) 
            {
                CurrentColor = CT::Color;
                goto enable_chams;
            }
            else if (GetTeam(current_model) == 1) 
            {
                CurrentColor = T::Color;
                goto enable_chams;
            }

            goto disable_chams;
        }
    }

    goto disable_chams;

enable_chams:
    __asm {
        popad
    }

    glColor4f
        (CurrentColor.x,
        CurrentColor.y,
        CurrentColor.z,
        CurrentColor.w);

    __asm {
        jmp ret_address
    }

disable_chams:
    __asm
    {
        popad
        push ecx
        mov ecx, dword ptr ss:[ebp-0x3C]
        push edx
        push eax
        push ecx

        call glColor4f
        jmp ret_address
    }
}
