#include <pch.h>
#include <base.h>
#include "ImCandy/candy.h"
#include <chrono>
#include "group_panel.cpp"
//#include "image.h"

static bool ContextCreated = false;
static HGLRC g_Context = (HGLRC)NULL;
bool firstFrame = true;

BOOL __stdcall Base::Hooks::SwapBuffers(_In_ HDC hdc)
{
	Data::hWindow = WindowFromDC(hdc);
	HGLRC oContext = wglGetCurrentContext();

	if (!Data::oWndProc)
		Data::oWndProc = (WndProc_t)SetWindowLongPtr(Data::hWindow, WNDPROC_INDEX, (LONG_PTR)Hooks::WndProc);

	if (!ContextCreated)
	{
		g_Context = wglCreateContext(hdc);
		wglMakeCurrent(hdc, g_Context);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		GLint m_viewport[4];
		glGetIntegerv(GL_VIEWPORT, m_viewport);

		glOrtho(0, m_viewport[2], m_viewport[3], 0, 1, -1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor(0, 0, 0, 0);
		ContextCreated = true;
	}

	wglMakeCurrent(hdc, g_Context);

	if (!Data::InitImGui && ContextCreated)
	{
		Menu::InitializeContext(Data::hWindow);
		Data::InitImGui = true;
	}

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (Data::ShowWatermark)
	{
		auto start = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		ImGui::SetNextWindowPos({ 15,15 });
		ImGui::SetNextWindowSize({ 296,30 });

		ImGui::Begin("WTR", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
		ImGui::Text("m0rphooks.tech | %s", std::ctime(&end_time));
		ImGui::End();
	}

	if (Data::ShowMenu)
	{
		//ImCandy::Theme_Nord();

		if (firstFrame)
		{
			RECT rect;
			GetClientRect(Base::Data::hWindow, &rect);
			int gameWidth = rect.right - rect.left;
			int gameHeight = rect.bottom - rect.top;
			ImVec2 windowPos(gameWidth * 0.5f, gameHeight * 0.5f);
			ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
			firstFrame = false;
		}

		ImGui::SetNextWindowSize(ImVec2(680, 435));
		ImGui::Begin("MNU", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

		if (ImGui::Button("Main", ImVec2(327, 30)))
			Menu::Tab = 0;
		ImGui::SameLine();
		if (ImGui::Button("Colors", ImVec2(327, 30)))
			Menu::Tab = 1;

		if (Menu::Tab == 0)
		{
			ImGui::BeginGroupPanel("LEGITBOT");
			//ImGui::Text("LEGITBOT");

			ImGui::Checkbox(("Aimbot"), &Base::Hacks::Aimbot::Active);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Currently not working. We are working for a fix");

			ImGui::SetNextItemWidth(200);
			ImGui::SliderFloat("Aimbot FOV", &Base::Hacks::Aimbot::Fov, 0.0f, 180.0f, "%f");
			ImGui::SetNextItemWidth(200);
			ImGui::SliderFloat("Aimbot Smooth", &Base::Hacks::Aimbot::Smooth, 0.0f, 10.0f, "%f");

			ImGui::Checkbox(("TriggerBot"), &Base::Hacks::Trigger::Active);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Fire automatically while aiming at the enemy");

			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("TriggerBot Delay", &Base::Hacks::Trigger::Delay, 0, 1000, "%d");
			

			ImGui::EndGroupPanel();

			ImGui::SameLine();
			ImGui::BeginGroupPanel("VISUALS");
			//ImGui::Text("VISUALS");
			ImGui::Checkbox(("WallHack"), &Base::Hacks::WallHack::Active);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("See enemies and teammates through walls");

			//ImGui::SameLine();
			ImGui::SetNextItemWidth(200);
			if (ImGui::BeginCombo("WallHack Group", Base::Hacks::WallHack::listbox_items[Base::Hacks::WallHack::current_item])) {
				for (int i = 0; i < IM_ARRAYSIZE(Base::Hacks::WallHack::listbox_items); i++) {
					bool is_selected = (Base::Hacks::WallHack::current_item == i);
					if (ImGui::Selectable(Base::Hacks::WallHack::listbox_items[i], is_selected))
						Base::Hacks::WallHack::current_item = i;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::SetNextItemWidth(200);
			if (ImGui::BeginCombo("WallHack Type", Base::Hacks::WallHack::Types::listbox_items[Base::Hacks::WallHack::Types::current_item])) {
				for (int i = 0; i < IM_ARRAYSIZE(Base::Hacks::WallHack::Types::listbox_items); i++) {
					bool is_selected = (Base::Hacks::WallHack::Types::current_item == i);
					if (ImGui::Selectable(Base::Hacks::WallHack::Types::listbox_items[i], is_selected))
						Base::Hacks::WallHack::Types::current_item = i;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			ImGui::Checkbox(("Chams"), &Base::Hacks::Chams::Active);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Colored models");

			//ImGui::SameLine();
			ImGui::SetNextItemWidth(200);
			if (ImGui::BeginCombo("Chams Group", Base::Hacks::Chams::listbox_items[Base::Hacks::Chams::current_item])) {
				for (int i = 0; i < IM_ARRAYSIZE(Base::Hacks::Chams::listbox_items); i++) {
					bool is_selected = (Base::Hacks::Chams::current_item == i);
					if (ImGui::Selectable(Base::Hacks::Chams::listbox_items[i], is_selected))
						Base::Hacks::Chams::current_item = i;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			
			ImGui::EndGroupPanel();

			ImGui::BeginGroupPanel("MISC", ImVec2(ImGui::GetItemRectSize().x + 5.0f, ImGui::GetItemRectSize().y));
			//ImGui::Text("MISC");
			ImGui::Checkbox(("BunnyHop"), &Base::Hacks::Bunny::Active);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Jump automatically and go faster");

			ImGui::Checkbox(("Auto Strafer"), &Base::Hacks::Strafer::Active);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Automatically direct your movement");

			
			ImGui::EndGroupPanel();

			ImGui::SameLine();
			ImGui::BeginGroupPanel("Menu Settings", ImVec2(ImGui::GetItemRectSize().x - 5.0f, ImGui::GetItemRectSize().y));
			//ImGui::Text("MENU");
			ImGui::Checkbox(("Watermark"), &Data::ShowWatermark);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Show cheat watermark in the corner of the screen");

			if (ImGui::Button("Unload"))
			{
				ImGui::EndGroupPanel();
				ImGui::End();
				ImGui::Render();
				ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
				wglMakeCurrent(hdc, oContext);
				wglDeleteContext(g_Context);

				Base::Detach();
				return Data::oSwapBuffers(hdc);
			}
			
			ImGui::EndGroupPanel();

			ImGui::Text("user : admin");
			ImGui::Text("product : trial");
			ImGui::Text("expires : 30/06/23");

			//if (ImGui::IsItemHovered())
				//ImGui::SetTooltip("Currently not working. Press END for unload");
		}
		if (Menu::Tab == 1)
		{
			//ImGui::ColorEdit4("Models", (float*)&Base::Colors::Chams::Models::Color, ImGuiColorEditFlags_PickerHueWheel);

			ImGui::Text("Chams Colors");
			//ImGui::Text("Models Color");
			//ImGui::SameLine();
			if (ImGui::Button("Models Color Picker"))
			{
				Base::Colors::Chams::Models::ColorPickerOpen = !Base::Colors::Chams::Models::ColorPickerOpen;
			}

			//ImGui::Text("CT Color");
			//ImGui::SameLine();
			if (ImGui::Button("CT Color Picker"))
			{
				Base::Colors::Chams::CT::ColorPickerOpen = !Base::Colors::Chams::CT::ColorPickerOpen;
			}

			//ImGui::Text("T Color");
			//ImGui::SameLine();
			if (ImGui::Button("T Color Picker"))
			{
				Base::Colors::Chams::T::ColorPickerOpen = !Base::Colors::Chams::T::ColorPickerOpen;
			}

			if (Base::Colors::Chams::Models::ColorPickerOpen)
			{
				ImGui::SetNextWindowSize(ImVec2(300, 300));
				ImGui::Begin("Models Color Picker", &Base::Colors::Chams::Models::ColorPickerOpen);
				ImGui::ColorPicker4("Pick a Color", (float*)&Base::Colors::Chams::Models::Color);
				ImGui::End();
			}

			if (Base::Colors::Chams::CT::ColorPickerOpen)
			{
				ImGui::SetNextWindowSize(ImVec2(300, 300));
				ImGui::Begin("CT Color Picker", &Base::Colors::Chams::CT::ColorPickerOpen);
				ImGui::ColorPicker4("Pick a Color", (float*)&Base::Colors::Chams::CT::Color);
				ImGui::End();
			}

			if (Base::Colors::Chams::T::ColorPickerOpen)
			{
				ImGui::SetNextWindowSize(ImVec2(300, 300));
				ImGui::Begin("T Color Picker", &Base::Colors::Chams::T::ColorPickerOpen);
				ImGui::ColorPicker4("Pick a Color", (float*)&Base::Colors::Chams::T::Color);
				ImGui::End();
			}
		}
		

		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	wglMakeCurrent(hdc, oContext);
	return Data::oSwapBuffers(hdc);
}