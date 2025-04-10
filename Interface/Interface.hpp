#pragma once
#include "SFML/Graphics.hpp"

namespace Interface {
    const int CLASS_FIELD_WIDTH = 262;
    const int CLASS_FIELD_HEIGHT = 62;
    const int SUBJECT_NAME_CHAR_SIZE = 20;
    const int WEEK_DAY_CHAR_SIZE = 18;
    const int CLASS_FIELD_INDENT = 2;
    const int WEEK_DAY_WIDTH = 105;
    const int WEEK_DAY_HEIGHT = 30;
    const int DAY_HEIGHT = WEEK_DAY_HEIGHT + 7 * (CLASS_FIELD_HEIGHT + CLASS_FIELD_INDENT);
    const int DAY_WIDTH = 2 * CLASS_FIELD_WIDTH + WEEK_DAY_WIDTH + 2 * CLASS_FIELD_INDENT;
    const int TIMES_WIDTH = WEEK_DAY_WIDTH;

    const int DIALOG_CLASSES_NUMBER_X = 6;
    const int DIALOG_CLASSES_NUMBER_Y = 14;
    const int DIALOG_WIDTH = 4 + CLASS_FIELD_WIDTH * DIALOG_CLASSES_NUMBER_X + 
    (DIALOG_CLASSES_NUMBER_X - 1) * CLASS_FIELD_INDENT;
    const int DIALOG_HEIGHT = 4 + CLASS_FIELD_HEIGHT * DIALOG_CLASSES_NUMBER_Y + 
    (DIALOG_CLASSES_NUMBER_Y - 1) * CLASS_FIELD_INDENT;

    class Button;
    class Textbox;

    class Day;
    class ClassField;
    class Dialog;
    class ExtendedButton;

    class ButtonCreator;
    class concreteCreator;
}

enum Week {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};