#include <base.h>
#include "wallhack.h"
#include "chams.h"
#include "bunnyhop.h"
#include "triggerbot.h"
#include "aimbot.h"

namespace Base
{
	namespace Hacks
	{
		extern void InitHacks();
		extern void ShutdownHacks();

		extern int GetTeam(char current_model[]);

		extern void ConvertToLower(char* str);

		const char* t_models[] = { "arctic", "leet", "guerilla", "terror" };
		const char* ct_models[] = { "gign", "gsg9", "sas", "urban" };
	}

	namespace Offsets
	{
		HMODULE hOpenGL32 = GetModuleHandleA("opengl32.dll");
		HMODULE hHwDll = GetModuleHandleA("hw.dll");
		HMODULE hClientDll = GetModuleHandleA("client.dll");

		DWORD hw_base = (DWORD)hHwDll;
		DWORD client_base = (DWORD)hClientDll;

		DWORD* m_dwOnGround = (DWORD*)(hw_base + 0x122E2D4);
		DWORD* m_dwForceJump = (DWORD*)(client_base + 0x131434);
		DWORD* dwForceAttack = (DWORD*)((DWORD)client_base + 0x131370);
		DWORD* dwForceLeft = (DWORD*)((DWORD)client_base + 0x131418);
		DWORD* dwForceRight = (DWORD*)((DWORD)client_base + 0x131458);
		DWORD* dwWeaponId = (DWORD*)((DWORD)hw_base + 0x108DD90);
	}

	namespace Funcs
	{
		extern void Load();
		//void(__stdcall* glColor4f)(float, float, float, float) = NULL;
	}
}