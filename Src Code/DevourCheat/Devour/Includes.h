#pragma once
#include "../IL2CppResolver/Main.hpp"
#include "../IL2CppResolver/Includes.hpp"
#include "../IL2CppResolver/Defines.hpp"
#include "../ImGui/imconfig.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_internal.h"
#include "../ImGui/imstb_rectpack.h"
#include "../ImGui/imstb_textedit.h"
#include "../ImGui/imstb_truetype.h"
#include "../Devour/htchand_font.hpp"
#include "../Devour/IL2CPP_MinhookCheat.h"
#include "../Devour/il2cpp_devourhack.hpp"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <MinHook.h> //MinHookLib by TsudaKageyu
#include <d3d11.h> //D3D11 Hook
#include "../kiero/kiero.h" //Kiero Library for Initializating DirectX, OpenGL and Vulkan
#pragma comment (lib, "d3d11.lib") //D3D11 Library
#pragma warning (disable : 6387) //Disabling This Warning 
using namespace std;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //Calling ImGui Method :D
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
namespace DevourImGuiCheat
{
	void DrawCheatMenu() 
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;
		ImGui::Begin("DevourCheat by RaizyDaizy", 0, flags);
		ImGui::SetNextWindowSize(ImVec2(650, 550)); //Window Size
		ImGui::TextColored(ImVec4(155, 45, 122, 255), "Welcome to my Cheat for DEVOUR");
		if (ImGui::BeginMenu("FoV Hack")) 
		{
			if (ImGui::Button("Set FoV To 100", ImVec2(150, 150)))
			{
				DevourCheat::InitFunctionFoVIn100();
			}
			if (ImGui::Button("Set FoV To 200", ImVec2(150, 150))) {
				DevourCheat::InitFunctionFoVIn200();
			}
			if (ImGui::Button("Set FoV To 250", ImVec2(150, 150))) {
				DevourCheat::InitFunctionFoVIn250();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Rank Hack")) 
		{
			if (ImGui::Button("Set Rank To 10", ImVec2(155, 155)))
			{
				DevourCheat::InitRankTo10();
			}
			if (ImGui::Button("Set Rank To 20", ImVec2(155, 155))) {
				DevourCheat::InitRankTo20();
			}
			if (ImGui::Button("Set Rank To 100", ImVec2(155, 155)))
			{
				DevourCheat::InitRankTo100();
			}
			if (ImGui::Button("Set Rank To 666", ImVec2(155, 155))) {
				DevourCheat::InitRankTo666();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Misc Hack")) 
		{
			if (ImGui::Button("Set Purgatory", ImVec2(150, 150))) 
			{
				DevourCheat::SetPurgatory();
			}
			if (ImGui::Button("LoadFlashlight Get Name", ImVec2(155, 235))) {
				LoadFlashlight_Helper();
			}
			ImGui::TextColored(ImVec4(230, 150, 55, 255), "Scene Name --> %s", GetActiveScene_Unity());
			ImGui::TextColored(ImVec4(210, 0, 0, 255), "Flashlight Name --> %s", LoadFlashlight_GetName());
			ImGui::EndMenu();
		}
		ImGui::End();
		ImGui::Render();
	}
	void DrawStyle() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg] = ImColor(55, 55, 155, 255);
		style.Colors[ImGuiCol_TitleBg] = ImColor(44, 155, 70, 255);
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(44, 155, 70, 255);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(40, 40, 215, 255);
		style.Colors[ImGuiCol_Button] = ImColor(100, 0, 0, 255);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(15, 44, 30, 255);
		style.Colors[ImGuiCol_ButtonActive] = ImColor(55, 200, 70, 255);
		style.Colors[ImGuiCol_CheckMark] = ImColor(200, 154, 133, 255);
		style.Colors[ImGuiCol_FrameBg] = ImColor(53, 11, 65, 255);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(35, 122, 122, 255);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(55, 210, 144, 255);
		style.Colors[ImGuiCol_Header] = ImColor(250, 211, 130, 255);
		style.Colors[ImGuiCol_HeaderActive] = ImColor(210, 35, 155, 255);
		style.Colors[ImGuiCol_HeaderHovered] = ImColor(44, 44, 44, 255);
		style.Colors[ImGuiCol_Tab] = ImColor(230, 155, 0, 255);
		style.Colors[ImGuiCol_TabActive] = ImColor(230, 155, 0, 255);
		style.Colors[ImGuiCol_TabHovered] = ImColor(100, 25, 25, 255);
		style.Colors[ImGuiCol_Text] = ImColor(125, 172, 45, 255);
		style.Colors[ImGuiCol_TextDisabled] = ImColor(155, 0, 57, 255);
		style.Colors[ImGuiCol_MenuBarBg] = ImColor(155, 0, 0, 150);
		style.Colors[ImGuiCol_PopupBg] = ImColor(144, 210, 74, 255);
		style.FrameBorderSize = 0.7f; //Drawing Frame Border Size
		style.Alpha = 1.0f;
		style.WindowBorderSize = 0.6F;
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromMemoryTTF(htchand, sizeof(htchand), 25.F);
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
	}
}