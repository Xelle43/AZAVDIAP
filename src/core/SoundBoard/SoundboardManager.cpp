#include "SoundboardManager.h"
#include "SoundboardEntry.h"
#include <fstream>
#include <iostream>
#include <string>

void addSound(std::string name,std::string text,std::string path, bool IsnewSound){
    int tempy = 60 + (counter * 60); 
    counter++;
    yPosAddButton = 60 +(counter * 60);
    SoundboardEntry newSound(name, tempy, counter);
    Sounds.push_back(newSound);
    gerneral::justAdded = true;
    for( auto& s : Sounds)
    {
        if(s.GetName() == "button") s.UpdateY(60 +( counter * 60));
        UpdateButtonPosY((60+(counter * 60)), "AddSound");
    }

    
    
    
    
    json config;
    std::ifstream in(gerneral::configPath);

    if(!in)
    {
        std::cout << "Keine Json gefunden path: "<< gerneral::configPath << std::endl;
    }
    else{
        in >> config;

        if(IsnewSound)
        {
            config["sounds"].push_back({
            {"id", counter},
            {"key", ""},
            {"path", ""},
            });

        std::ofstream out(gerneral::configPath);
        out << config.dump(4);
        }
        else{
            newSound.SetKey(text);
            newSound.SetPath(path);
        }
        
        
        
    }
    
}

void RenderSoundboard(){
    for(auto& s : Sounds)
    {
        s.Draw();
    }
}
void CheckButtonPressed(){
    for(auto& s : Sounds)
    {
        if(s.isPressed())
        {
            ButtonName = s.GetName();
        }
    }
}
std::string GetButtonPressedName(){
    return ButtonName;
}

void InitSoundboardAddButton(){
    SoundboardEntry button(60);
    Sounds.push_back(button);
}
void UpdateSoundBoardBoxes(){
    for(auto& s: Sounds){
        s.UpdateBoxes();
    }
    gerneral::justAdded = false; 
}