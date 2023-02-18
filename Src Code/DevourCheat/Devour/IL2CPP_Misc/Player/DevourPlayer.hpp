#pragma once
#include "../../../IL2CppResolver/Unity/Includes.hpp"
#include <vector>
extern std::vector<Unity::CGameObject*> PlayerList(NULL);
extern Unity::CGameObject* LocalPlayer = NULL;

void GetPlayersThread() {
    /*
    * Will always lop and get the players + the localplayer
    * This runs in a separate thread to avoid lags because we're fetching the components
    * Used as a "cache" - sorta
    * I use this instead of my good old corroutine
    */
    IL2CPP::Thread::Attach(IL2CPP::Domain::Get());
    while (1) {
        PlayerList.clear();

        auto list = Unity::Object::FindObjectsOfType<Unity::CComponent>("NolanBehaviour");
        for (int i = 0; i < list->m_uMaxLength + 1; i++)
        {
            if (!list->operator[](i))
                continue;

            Unity::CGameObject* object = list->operator[](i)->GetMemberValue<Unity::CGameObject*>("gameObject"); //SurvivalPlayer(Clone)
            if (!object) {
                continue;
            }

            PlayerList.push_back(object);

            Unity::CComponent* BoltEntity = object->GetComponent("BoltEntity");
            if (BoltEntity)
            {
                if (BoltEntity->GetMemberValue<bool>("IsOwner"))//local player check
                {
                    LocalPlayer = object;
                }
            }
        }

        Sleep(20000);
    }
}