#pragma once
#include "Interface.hpp"
#include "Button.hpp"
#include <iostream>

class Interface::Dialog {
public:
    Dialog() {
        active = false;
        borderSize = 2;
    }

    Dialog(sf::Vector2f size, sf::Color bgColor, int newBorderSize = 2) {
        dialog.setSize(size);
        dialog.setFillColor(bgColor);
        active = false;

        closeButton.setSize({size.x / 10, size.y / 20});
        closeButton.setBgColor(sf::Color::Red);

        borderSize = newBorderSize;
        border.setSize({size.x + 2 * borderSize, size.y + 2 * borderSize});
        border.setFillColor(sf::Color::Black);
        number = Interface::DIALOG_CLASSES_NUMBER_X * Interface::DIALOG_CLASSES_NUMBER_Y;
        classVariants = new Interface::Button[number];
        for (int i = 0; i < number; i++) {
            classVariants[i].setBgColor(sf::Color::White);
            classVariants[i].setTextColor(sf::Color::Black);
            classVariants[i].setCharacterSize(Interface::SUBJECT_NAME_CHAR_SIZE);
            classVariants[i].setSize({Interface::CLASS_FIELD_WIDTH, Interface::CLASS_FIELD_HEIGHT});
        }
    }

    ~Dialog() { delete[] classVariants; }

    void setPosition(sf::Vector2f pos) {
        dialog.setPosition({pos.x + borderSize, pos.y + borderSize});
        border.setPosition(pos);
        closeButton.setPosition({pos.x + dialog.getGlobalBounds().width * 0.9 + borderSize, pos.y + borderSize});
        int curX = pos.x + borderSize + Interface::CLASS_FIELD_INDENT;
        int curY = pos.y + borderSize + Interface::CLASS_FIELD_INDENT;
        for (int i = 0; i < number; i++) {
            if (i % Interface::DIALOG_CLASSES_NUMBER_X == 0 && i != 0) {
                curX = pos.x + borderSize + Interface::CLASS_FIELD_INDENT;
                curY += Interface::CLASS_FIELD_HEIGHT + Interface::CLASS_FIELD_INDENT;
            }
            classVariants[i].setPosition({curX, curY});
            curX += Interface::CLASS_FIELD_WIDTH + Interface::CLASS_FIELD_INDENT;
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(border);
        window.draw(dialog);
        for (int i = 0; i < number; i++) {
            classVariants[i].draw(window);
        }
        //closeButton.draw(window);
    }

    void setSize(sf::Vector2f size) { dialog.setSize(size); }

    void setBgColor(sf::Color newBgColor) { dialog.setFillColor(newBgColor); }

    void changeActive() { active = !active; }

    bool isActive() { return active; }

    Interface::Button& getCloseButton() { return closeButton; }

    Interface::Button& getClassVariant(int i) { return classVariants[i]; }

    int getNumber() { return number; }

    bool isFocused(sf::RenderWindow& window) {
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;

        float dialogX = dialog.getPosition().x;
        float dialogX2 = dialog.getPosition().x + dialog.getGlobalBounds().width;
        float dialogY = dialog.getPosition().y;
        float dialogY2 = dialog.getPosition().y + dialog.getGlobalBounds().height;

        return mouseX < dialogX2 && mouseX > dialogX && mouseY < dialogY2 && mouseY > dialogY;
    }

private:
    sf::RectangleShape dialog;
    sf::RectangleShape border;
    int borderSize;
    Interface::Button closeButton;
    bool active;
    int number;
    Interface::Button* classVariants;
};