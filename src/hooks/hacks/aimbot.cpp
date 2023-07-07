#include <pch.h>
#include <base.h>
#include "hooks/players.h"

sMe me;
VecPlayers vPlayers;

using namespace Base::Hacks::Aimbot;

void Base::Hacks::Aimbot::Load()
{
	hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Thread, Base::Data::hModule, 0, nullptr);
}

void Base::Hacks::Aimbot::Thread()
{
	while (true)
	{
		//me = vPlayers[0].
		//vPlayers[1].updateEntInfo();
		//me.ent = Data::m_hw->Engfuncs->GetLocalPlayer();
		//MessageBox(NULL, vPlayers[1].getName(), "test", MB_OK);

		//PlayerInfo& player = vPlayers[1];
		
		//player.updateEntInfo();
		
		//if (player.isAlive() == false)
			//MessageBox(NULL, player.getName(), "test", MB_OK);
			
	}
}

void Base::Hacks::Aimbot::Unload()
{
	TerminateThread(hThread, 0);
}