#pragma once
#include <base.h>

namespace Base
{
	namespace Hacks
	{
		namespace Bunny
		{
			HANDLE hThread;
			extern bool Active = false;

			extern void Load();
			extern void Unload();
			extern void Thread();
		}

		namespace Strafer
		{
			extern bool Active = false;
		}
	}
}