#pragma once
#include "../Devour/Includes.h"
#include "../Devour/IL2CPP_Misc/Player/DevourPlayer.hpp"
std::string GetActiveScene_Unity() 
{
        Unity::CGameObject* MapHelper = Unity::GameObject::Find("SaveHelpers");

        if (!MapHelper) {
            return "Unknown Scene";
        }

        Unity::CComponent* MapHelperData = MapHelper->GetComponent("SaveHelpers");

        if (!MapHelperData) {
            return "Unknown Scene";
        }

        return MapHelperData->GetMemberValue<Unity::System_String*>("sceneName")->ToString();
}
std::string LoadFlashlight_GetName()
{
    Unity::CGameObject* LoadFlashlight_Helper = Unity::GameObject::Find("CharacterLoader"); //CharacterLoader.cs
    if (!LoadFlashlight_Helper) 
    {
        return "CharacterLoader is Not Founded";
    }
    Unity::CComponent* LoadFlashlight_DataHelper = LoadFlashlight_Helper->GetComponent("CharacterLoader");
    if (!LoadFlashlight_DataHelper) 
    {
        return "Not Founded Flashlight Component";
    }
    std::string loadfl = LoadFlashlight_DataHelper->GetMemberValue<Unity::System_String*>("flashlightName")->ToString(); //LOL, idk why is random symbols, but it's funny :D
    return loadfl;
}
void LoadFlashlight_Helper() {
    std::string str = LoadFlashlight_GetName();
    cout << "[DevourCheat] Flashlight Name: " << str << endl;
}