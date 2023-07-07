#pragma once
#include <base.h>

namespace Base
{
	namespace Hacks
	{
		namespace Chams
		{
			const char* listbox_items[] = { "All Models", "CT", "T", "CT + T" };
			int current_item = 0;

			BYTE old_opcodes[6];
			unsigned char* hook_location = (unsigned char*)0x038C7129;
			unsigned char* ret_address = (unsigned char*)0x038C7136;

			int* current_model_p = reinterpret_cast<int*>(0x3EB84B0);
			char current_model[9];

			extern bool Active = false;
			extern void Load();
			extern void Unload();
			__declspec() void codecave();
		}
	}

	namespace Colors
	{
		namespace Chams
		{
			ImVec4 CurrentColor;

			namespace Models
			{
				ImVec4 Color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				static bool ColorPickerOpen = false;
			}

			namespace CT
			{
				ImVec4 Color = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
				static bool ColorPickerOpen = false;
			}

			namespace T
			{
				ImVec4 Color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
				static bool ColorPickerOpen = false;
			}
		}
	}
}
