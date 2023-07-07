#include <pch.h>
#include <base.h>
using namespace Base::Hacks::WallHack::Types;

using namespace Base::Hacks::WallHack;

void Base::Hacks::WallHack::Load()
{
    DWORD old_protect;
    VirtualProtect((void*)hook_location_1, 15, PAGE_EXECUTE_READWRITE, &old_protect);
    VirtualProtect((void*)hook_location_2, 15, PAGE_EXECUTE_READWRITE, &old_protect);

    for (int i = 0; i < 8; i++) {
        old_opcodes_1[i] = *(hook_location_1 + i);
    }

    for (int i = 0; i < 6; i++) {
        old_opcodes_2[i] = *(hook_location_2 + i);
    }

    *hook_location_1 = 0xE9;
    *(DWORD*)(hook_location_1 + 1) = (DWORD)&codecave_1 - ((DWORD)hook_location_1 + 5);
    *(hook_location_1 + 5) = 0x909090;

    *hook_location_2 = 0xE9;
    *(DWORD*)(hook_location_2 + 1) = (DWORD)&codecave_2 - ((DWORD)hook_location_2 + 5);
    *(hook_location_2 + 5) = 0x90;
}

void Base::Hacks::WallHack::Unload()
{
    for (int i = 0; i < 8; i++) {
        *(hook_location_1 + i) = old_opcodes_1[i];
    }

    for (int i = 0; i < 6; i++) {
        *(hook_location_2 + i) = old_opcodes_2[i];
    }

    // CRASH
    //DWORD old_protect;
    //VirtualProtect((void*)hook_location_1, 15, PAGE_EXECUTE_READ, &old_protect);
    //VirtualProtect((void*)hook_location_2, 15, PAGE_EXECUTE_READ, &old_protect);
}

__declspec(naked) void Base::Hacks::WallHack::codecave_1()
{
    memcpy(&current_model, (void*)*current_model_p, 8);
    Base::Hacks::ConvertToLower(current_model);

    if (Active)
    {
        if (current_item == 0)
        {
            goto disable_depth_range;
        }
        else if (current_item == 1)
        {
            if (GetTeam(current_model) == 0) {
                goto disable_depth_range;
            }

            goto enable_depth_range;
        }
        else if (current_item == 2)
        {
            if (GetTeam(current_model) == 1) {
                goto disable_depth_range;
            }

            goto enable_depth_range;
        }
        else if (current_item == 3)
        {
            if (GetTeam(current_model) == 0 || GetTeam(current_model) == 1) {
                goto disable_depth_range;
            }

            goto enable_depth_range;
        }
    }

    goto enable_depth_range;

disable_depth_range:

    glDisable(GL_DEPTH_TEST);

    if (Types::current_item == T_FLAT)
        glBegin(5);
    else if (Types::current_item == T_WIREFRAME)
        glBegin(2);

    __asm
    {
        jmp retn_address_1
    }

enable_depth_range:

    glBegin(5);

    __asm
    {
        jmp retn_address_1
    }
}

__declspec(naked) void Base::Hacks::WallHack::codecave_2()
{
    __asm
    {
        call glEnd
        push 0xB71
        call glEnable
        jmp retn_address_2
    }
}