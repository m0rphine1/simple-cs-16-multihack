#include <pch.h>
#include <base.h>
#include "bunnyhop.h"

using namespace Base::Hacks::Bunny;

void Base::Hacks::Bunny::Load()
{
	hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Thread, Base::Data::hModule, 0, nullptr);
}

void Base::Hacks::Bunny::Unload()
{
	TerminateThread(hThread, 0);
}

void Base::Hacks::Bunny::Thread()
{
	POINT cursorPos;

	while (true)
	{
		if (Base::Hacks::Bunny::Active)
		{			
			if (GetAsyncKeyState(VK_SPACE) && GetForegroundWindow() == Base::Data::hWindow)
			{
				if (*Base::Offsets::m_dwOnGround != 0)
				{
					*Base::Offsets::m_dwForceJump = 2;
				}
			}
		}

		// Auto Strafer
		if (Base::Hacks::Strafer::Active)
		{
			if (GetAsyncKeyState(VK_SPACE))
			{
				if (*Base::Offsets::m_dwOnGround == 0)
				{
					int x = GetSystemMetrics(SM_CXSCREEN) / 2;
					GetCursorPos(&cursorPos);

					if (cursorPos.x > x)
					{
						*Base::Offsets::dwForceLeft = 0;
						*Base::Offsets::dwForceRight = 6;
					}
					if (cursorPos.x < x)
					{
						*Base::Offsets::dwForceLeft = 6;
						*Base::Offsets::dwForceRight = 0;
					}
				}
			}
		}
	}
}
