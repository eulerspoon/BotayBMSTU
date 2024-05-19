#pragma once
#include "SFML/Graphics.hpp"
#include "Interface.hpp"
#include <iostream>

class Interface::Button {
public:
    Button() {}
    Button(std::wstring t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
        text.setString(t);
        text.setColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgColor);
    }


    void setPosition(sf::Vector2f pos) {
        button.setPosition(pos);
        // float xTextPos = (pos.x + button.getGlobalBounds().width / 2.5) - (text.getGlobalBounds().width / 2);
        // float yTextPos = (pos.y + button.getGlobalBounds().height / 2.5) - (text.getGlobalBounds().height / 2);

        // float xTextPos = pos.x + (button.getGlobalBounds().width - text.getCharacterSize() * text.getString().getSize()) / 2;
        // float yTextPos = pos.y + (button.getGlobalBounds().height - text.getGlobalBounds().height) / 2;
        float xTextPos = pos.x + 2;
        float yTextPos = pos.y + button.getGlobalBounds().height / 2 - 20;

        text.setPosition({xTextPos, yTextPos});
    }

    void draw(sf::RenderWindow& window) {
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow& window) {
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;

        float buttonX = button.getPosition().x;
        float buttonX2 = button.getPosition().x + button.getGlobalBounds().width;
        float buttonY = button.getPosition().y;
        float buttonY2 = button.getPosition().y + button.getGlobalBounds().height;

        return mouseX < buttonX2 && mouseX > buttonX && mouseY < buttonY2 && mouseY > buttonY;
    }

    void setText(std::wstring newText) { text.setString(newText); }
    void setSize(sf::Vector2f size) { button.setSize(size); }
    void setBgColor(sf::Color newBgColor) { button.setFillColor(newBgColor); }
    void setTextColor(sf::Color newTextColor) { text.setColor(newTextColor); }
    void setFont(sf::Font& newFont) { text.setFont(newFont); }
    void setCharacterSize(int charSize) { text.setCharacterSize(charSize); }

    Interface::Button& operator= (const Interface::Button& newButton) {
        button = newButton.button;
        text = newButton.text;
        return *this;
    }

private:
    sf::RectangleShape button;
    sf::Text text;
};