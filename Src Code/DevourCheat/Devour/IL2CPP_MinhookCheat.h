#pragma once
#include <MinHook.h>
#define MH_FASTCALL_IL2CPP __fastcall*
#define MH_STDCALL_IL2CPP __stdcall
void MinhookInit() 
{
	MH_Initialize();
}

namespace Devour_Offsets //Initializating Offsets :D 
{
	uintptr_t game_assembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll"); //GameAssembly Address
	uintptr_t SetRank_addr = 0x739D70; //SetRank Address
	uintptr_t FoV_FunctionAddress = 0x43E2F0; //Field of View Address :D
	uintptr_t SetPurgatoryAddress = 0x4595E0;
	uintptr_t LoadFlashlight_address = 0x657590;
}
void(MH_FASTCALL_IL2CPP SetRank_o)(DWORD*, int32_t, DWORD*);
void MH_STDCALL_IL2CPP SetRankTo10_hack(DWORD* __this, int32_t rank, DWORD* method) 
{
	rank = 10;
	return SetRank_o(__this, rank, method);
}
void MH_STDCALL_IL2CPP SetRankTo20_hack(DWORD* __this, int32_t rank, DWORD* method)
{
	rank = 20;
	return SetRank_o(__this, rank, method);
}
void MH_STDCALL_IL2CPP SetRankTo100_hack(DWORD* __this, int32_t rank, DWORD* method)
{
	rank = 100;
	return SetRank_o(__this, rank, method);
}
void MH_STDCALL_IL2CPP SetRankTo666_hack(DWORD* __this, int32_t rank, DWORD* method)
{
	rank = 666;
	return SetRank_o(__this, rank, method);
}
void(MH_FASTCALL_IL2CPP SetFoVFunction_o)(DWORD*, float, DWORD*);
void MH_STDCALL_IL2CPP SetFoVFunctionTo100_hack(DWORD* __this, float fov, DWORD* method) 
{
	fov = 100.0F;
	return SetFoVFunction_o(__this, fov, method);
}
void MH_STDCALL_IL2CPP SetFoVFunctionTo200_hack(DWORD* __this, float fov, DWORD* method)
{
	fov = 200.0F;
	return SetFoVFunction_o(__this, fov, method);
}
void MH_STDCALL_IL2CPP SetFoVFunctionTo250_hack(DWORD* __this, float fov, DWORD* method)
{
	fov = 250.0F;
	return SetFoVFunction_o(__this, fov, method);
}
void(MH_FASTCALL_IL2CPP SetPurgatory_o)(DWORD*, bool, DWORD*);
void MH_STDCALL_IL2CPP SetPurgatory_H(DWORD* __this, bool active, DWORD* method) 
{
	active = true;

	return SetPurgatory_o(__this, active, method);
}
namespace DevourCheat 
{
	void InitFunctionFoVIn100()
	{
		MH_CreateHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::FoV_FunctionAddress), &SetFoVFunctionTo100_hack, (LPVOID*)&SetFoVFunction_o);
		MH_EnableHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::FoV_FunctionAddress));
	}
	void InitFunctionFoVIn200()
	{
		MH_CreateHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::FoV_FunctionAddress), &SetFoVFunctionTo200_hack, (LPVOID*)&SetFoVFunction_o);
		MH_EnableHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::FoV_FunctionAddress));
	}
	void InitFunctionFoVIn250()
	{
		MH_CreateHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::FoV_FunctionAddress), &SetFoVFunctionTo250_hack, (LPVOID*)&SetFoVFunction_o);
		MH_EnableHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::FoV_FunctionAddress));
	}
	void InitRankTo10() 
	{
		MH_CreateHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetRank_addr), &SetRankTo10_hack, (LPVOID*)&SetRank_o);
		MH_EnableHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetRank_addr));
	}
	void InitRankTo20() 
	{
		MH_CreateHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetRank_addr), &SetRankTo20_hack, (LPVOID*)&SetRank_o);
		MH_EnableHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetRank_addr));
	}
	void InitRankTo100() 
	{
		MH_CreateHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetRank_addr), &SetRankTo100_hack, (LPVOID*)&SetRank_o);
		MH_EnableHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetRank_addr));
	}
	void InitRankTo666() 
	{
		MH_CreateHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetRank_addr), &SetRankTo666_hack, (LPVOID*)&SetRank_o);
		MH_EnableHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetRank_addr));
	}
	void SetPurgatory() 
	{
		MH_CreateHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetPurgatoryAddress), &SetPurgatory_H, (LPVOID*)&SetPurgatory_o);
		MH_EnableHook(reinterpret_cast<LPVOID*>(Devour_Offsets::game_assembly + Devour_Offsets::SetPurgatoryAddress));
	}
}