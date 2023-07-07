#include <pch.h>
#include <base.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Base::Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)
		Data::WmKeys[wParam] = uMsg;

	switch(uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case Data::Keys::ToggleMenu:
		{
			if (!Data::ShowMenu)
			{
				Data::m_hw->cl_funcs->pIN_DeactivateMouse();
				Data::ShowMenu = true;
			}
			else
			{
				Data::m_hw->cl_funcs->pIN_ActivateMouse();
				Data::ShowMenu = false;
				SetCursorPos(Data::m_hw->Engfuncs->GetWindowCenterX(), Data::m_hw->Engfuncs->GetWindowCenterY());
			}
			break;
		}
		case Data::Keys::DetachDll:
			Base::Detach();
			break;
		}
	case WM_MOUSEMOVE:
		if (Data::ShowMenu)
			return 0;
	}

	if (Data::ShowMenu && Data::InitImGui)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(Data::oWndProc, hWnd, uMsg, wParam, lParam);
}
