// dllmain.cpp : Defines the entry point for the DLL application.
#include "../DevourCheat/Devour/Includes.h"
#include "../DevourCheat/Devour/IL2CPP_Misc/Player/DevourPlayer.hpp"
FILE* fp;
void CreateConsole()
{
	AllocConsole();
	SetConsoleTitleA("DevourCheat by RaizyDaizy");
	freopen_s(&fp, "CONOUT$", "w", stdout);
	cout << "[DevourCheat] Welcome To My New Cheat by RaizyDaizy" << endl;
}
void InitImGui()
{
	DevourImGuiCheat::DrawStyle();
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer{ 0 };
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView); //False Positive Warning DirectX 11 SDK(Idk Why)
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
			cout << "[DevourCheat] Successfully Getting D3D11 Device" << endl;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	DevourImGuiCheat::DrawCheatMenu();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}
DWORD WINAPI MainThr(HMODULE hModule) {
	bool init_hook = false;
	CreateConsole();
	MinhookInit();
	if (IL2CPP::Initialize(true) && IL2CPP::Thread::Attach(IL2CPP::Domain::Get()))
	{
		cout << "[DevourCheat] IL2CPP Has Been Called Succesfulled" << endl;
	}
	IL2CPP::Callback::Initialize();
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GetPlayersThread, 0, 0, 0);
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
			cout << "[DevourCheat] Kiero Has Been Successfully Initializated" << endl;
		}
		else {
			cout << "[DevourCheat] Kiero is not Initializated" << endl;
			Sleep(4500);
			exit(122);
		}
	} while (!init_hook);
	return TRUE;

}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThr, 0, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		DisableThreadLibraryCalls(hModule);
		kiero::shutdown();
		break;
	}
	return TRUE;
}

