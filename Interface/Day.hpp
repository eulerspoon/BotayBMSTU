#pragma once
#include "Interface.hpp"
#include "Button.hpp"
#include "ClassField.hpp"


class Interface::Day {
public:
    Day() {
        classes = new Interface::ClassField[14];
        times = new Interface::Button[7];

        ch.setBgColor(sf::Color::White);
        ch.setTextColor(sf::Color::Black);
        ch.setCharacterSize(Interface::SUBJECT_NAME_CHAR_SIZE);
        ch.setSize({Interface::CLASS_FIELD_WIDTH, Interface::WEEK_DAY_HEIGHT});
        ch.setText(L"ЧС");

        zn.setBgColor(sf::Color::White);
        zn.setTextColor(sf::Color::Black);
        zn.setCharacterSize(Interface::SUBJECT_NAME_CHAR_SIZE);
        zn.setSize({Interface::CLASS_FIELD_WIDTH, Interface::WEEK_DAY_HEIGHT});
        zn.setText(L"ЗН");

        std::wstring classTimes[7]{
            L"08:30-10:05",
            L"10:15-11:50", 
            L"12:00-13:35",
            L"13:50-15:25",
            L"15:40-17:15",
            L"17:25-19:00",
            L"19:10-20:45"};
        for (int i = 0; i < 7; i++) {
            times[i].setBgColor(sf::Color::White);
            times[i].setTextColor(sf::Color::Black);
            times[i].setCharacterSize(Interface::SUBJECT_NAME_CHAR_SIZE);
            times[i].setSize({Interface::TIMES_WIDTH, Interface::CLASS_FIELD_HEIGHT});
            times[i].setText(classTimes[i]);
        }
    }

    ~Day() { delete[] classes; delete[] times; }

    void setPosition(sf::Vector2f pos) {
        weekDay.setPosition(pos);
        ch.setPosition({
            pos.x + Interface::TIMES_WIDTH + Interface::CLASS_FIELD_INDENT,
            pos.y});
        zn.setPosition({
            pos.x + Interface::TIMES_WIDTH + Interface::CLASS_FIELD_WIDTH + 2 * Interface::CLASS_FIELD_INDENT,
            pos.y});
        for (int i = 0; i < 7; i++) {
            times[i].setPosition(
                {pos.x,
                pos.y + Interface::WEEK_DAY_HEIGHT + 
                i * Interface::CLASS_FIELD_HEIGHT + (i + 1) * Interface::CLASS_FIELD_INDENT});
            classes[i].setPosition(
                {pos.x + Interface::TIMES_WIDTH + Interface::CLASS_FIELD_INDENT,
                pos.y + Interface::WEEK_DAY_HEIGHT + 
                i * (Interface::CLASS_FIELD_HEIGHT) + (i + 1) * Interface::CLASS_FIELD_INDENT});
            classes[i + 7].setPosition(
                {pos.x + Interface::TIMES_WIDTH + Interface::CLASS_FIELD_WIDTH + 2 * Interface::CLASS_FIELD_INDENT,
                pos.y + Interface::WEEK_DAY_HEIGHT + 
                i * (Interface::CLASS_FIELD_HEIGHT) + (i + 1) * Interface::CLASS_FIELD_INDENT});
        }
    }

    void draw(sf::RenderWindow& window) {
        weekDay.draw(window);
        ch.draw(window);
        zn.draw(window);
        for (int i = 0; i < 14; i++) {
            if (i < 7) times[i].draw(window);
            classes[i].draw(window);
        }
    }

    Interface::Button& getWeekDay() { return weekDay; }
    Interface::Button& getTime(int i) { return times[i]; }
    Interface::Button& getCh() { return ch; }
    Interface::Button& getZn() { return zn; }

    void setWeekDay(int dayNumber) {
        std::wstring weekDayStr;
        switch (dayNumber) {
            case 0:
                weekDayStr = L"Понедельник";
                break;
            case 1:
                weekDayStr = L"Вторник";
                break;
            case 2:
                weekDayStr = L"Среда";
                break;
            case 3:
                weekDayStr = L"Четверг";
                break;
            case 4:
                weekDayStr = L"Пятница";
                break;
            case 5:
                weekDayStr = L"Суббота";
        }
        weekDay = Interface::Button(
            weekDayStr, 
            {Interface::WEEK_DAY_WIDTH, Interface::WEEK_DAY_HEIGHT},
            Interface::WEEK_DAY_CHAR_SIZE,
            sf::Color::White,
            sf::Color::Black);
    }

    void setFont(sf::Font& font) {
        for (int j = 0; j < 14; j++)
			classes[j].setFont(font);
		getWeekDay().setFont(font);
		
		for (int j = 0; j < 7; j++) getTime(j).setFont(font);
		getCh().setFont(font);
		getZn().setFont(font);
    }

    Interface::ClassField& operator[] (int index) { return classes[index]; }

private:
    Interface::ClassField* classes;
    Interface::Button* times;
    Interface::Button ch;
    Interface::Button zn;
    Interface::Button weekDay;
};