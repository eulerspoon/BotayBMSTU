#pragma once
#include "Interface.hpp"

class Interface::ButtonCreator {
    virtual ~ButtonCreator() {}
    virtual Button* createClassField() = 0;
    virtual Button* createExtendedButton() = 0;
    virtual void remove(Button* button) = 0;
};

class Interface::ConcreteCreator : Interface::ButtonCreator {
public:
    ~ClassFieldCreator() {}
    Button* createClassField() { return new Interface::ClassField; }
    Button* createExtendedButton() { return new Interface::ExtendedButton; }
    void remove(Button* button) { delete button; }
}