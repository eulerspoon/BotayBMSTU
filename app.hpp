#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include "Interface/Interface.hpp"
#include "Interface/Button.hpp"
#include "Interface/ClassField.hpp"
#include "Interface/Day.hpp"
#include "Interface/Dialog.hpp"
#include "ScheduleParser/ScheduleParser.hpp"

namespace App {
    void RunApp();

    void configureDays(Interface::Day*);
    void processMouseMove(sf::RenderWindow&, Interface::Day*, Interface::Dialog&);
    void processMouseButtonPress(sf::RenderWindow&, Interface::Day* days, Interface::Dialog&);
}