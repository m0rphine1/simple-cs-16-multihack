#include <base.h>

namespace Base
{
	namespace Hacks
	{
		namespace Trigger
		{
			extern bool Unloading = false;
			unsigned char* target_address;
			extern bool Active = false;
			int Delay = 0.0f;
			HANDLE hThread;
			extern void Load();
			extern void Unload();
			extern void Thread();
		}
	}
}