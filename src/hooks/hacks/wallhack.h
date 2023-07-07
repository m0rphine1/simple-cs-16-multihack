#include <base.h>

namespace Base
{
	namespace Hacks
	{
		namespace WallHack
		{
			const char* listbox_items[] = { "All Models", "CT", "T", "CT + T" };
			int current_item = 3;

			unsigned char* hook_location_1 = (unsigned char*)0x038C7062;
			DWORD retn_address_1 = 0x038C706A;
			unsigned char* hook_location_2 = (unsigned char*)0x038C7162;
			DWORD retn_address_2 = 0x038C7168;

			__declspec() void codecave_1();
			__declspec() void codecave_2();

			int* current_model_p = reinterpret_cast<int*>(0x3EB84B0);
			char current_model[9];

			BYTE old_opcodes_1[8];
			BYTE old_opcodes_2[6];

			extern bool Active = false;

			extern void Load();
			extern void Unload();

			namespace Types
			{
				constexpr auto T_FLAT = 0;
				constexpr auto T_WIREFRAME = 1;;

				const char* listbox_items[] = { "Flat", "Wireframe" };
				int current_item = T_FLAT;
				//extern int Type = T_WIREFRAME;
			}
		}
	}
}