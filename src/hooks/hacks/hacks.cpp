#include <pch.h>
#include <base.h>

using namespace Base::Hacks;

void Base::Hacks::InitHacks()
{
    WallHack::Load();
    Chams::Load();
    Bunny::Load();
    Trigger::Load();
    Aimbot::Load();
}

void Base::Hacks::ShutdownHacks()
{
    WallHack::Unload();
    Chams::Unload();
    Bunny::Unload();
    Trigger::Unload();
    Aimbot::Unload();
}

void Base::Hacks::ConvertToLower(char* str) {
    int i = 0;
    while (str[i] != '\0') {           // Karakter dizisinin sonuna kadar dön
        str[i] = std::tolower(str[i]); // Karakteri küçük harfe dönüþtür
        i++;
    }
}

int Base::Hacks::GetTeam(char current_model[])
{
    for (int i = 0; i < 4; i++) {
        if (strstr(current_model, Base::Hacks::ct_models[i]) != NULL) {
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (strstr(current_model, Base::Hacks::t_models[i]) != NULL) {
            return 1;
        }
    }

    return 2;
}

void Base::Funcs::Load()
{
    //glColor4f = (void(__stdcall*)(float, float, float, float))GetProcAddress(Base::Offsets::hOpenGL32, "glColor4f");
}
