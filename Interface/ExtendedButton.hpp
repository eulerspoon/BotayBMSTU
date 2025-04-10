#pragma once
#include "Interface.hpp"

class Interface::ExtendedButton : public Interface::Button {
public:
    ExtendedButton(std::wstring subjectName = L"") : Interface::Button::Button(
        subjectName, 
        {Interface::CLASS_FIELD_WIDTH * 3, Interface::CLASS_FIELD_HEIGHT}, 
        Interface::SUBJECT_NAME_CHAR_SIZE,
        sf::Color::White,
        sf::Color::Black) { isActive = false; }
    
    int getActive() { return isActive; }
    void changeActive() { isActive = !isActive; }
private:
    bool isActive;
};
