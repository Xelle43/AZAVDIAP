#pragma once
#include "ButtonManager.h"
#include "general.h"
#include "SoundBoard/SoundboardManager.h"

inline void CheckButtons(){
    if(PressedButton == "AddSound"){
        addSound("New Sound","","",true);
    }

}