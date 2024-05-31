#pragma once
#include "Interface.hpp"

class Interface::ClassField : public Interface::Button {
public:
    ClassField(std::wstring subjectName = L"") : Interface::Button::Button(
        subjectName, 
        {Interface::CLASS_FIELD_WIDTH, Interface::CLASS_FIELD_HEIGHT}, 
        Interface::SUBJECT_NAME_CHAR_SIZE,
        sf::Color::White,
        sf::Color::Black) {}
};