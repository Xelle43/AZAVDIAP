#pragma once
#include "general.h"
#include "SoundBoard/SoundboardManager.h"
#include "ButtonManager.h"
namespace LoadJson {
    void Load(){

    json config;
    std::ifstream in(gerneral::configPath);

    if(!in)
    {
        std::cout << "Keine Json gefunden path: "<< gerneral::configPath << std::endl;
    }
    else{
        in >> config;
    
        for(auto& sound : config["sounds"])
        {
            addSound("New Sound",sound["key"],sound["path"],false);
        }
        }
    UpdateSoundboardButton();
    }
}