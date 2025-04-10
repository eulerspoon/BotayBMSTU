#include "app.hpp"

void App::RunApp() {
    sf::RenderWindow window = sf::RenderWindow{ sf::VideoMode::getDesktopMode(), "BotayBMSTU" };
	window.setFramerateLimit(144);
	std::cout << window.getSize().x << " " << window.getSize().y << std::endl;
	sf::Font nakula;
	nakula.loadFromFile("resources/nakula.ttf");

	Interface::Dialog classChooseDialog(
		{
			Interface::DIALOG_WIDTH,
			Interface::DIALOG_HEIGHT},
		sf::Color(190, 190, 190));
	classChooseDialog.setPosition({
		(window.getSize().x - Interface::DIALOG_WIDTH) / 2,
		(window.getSize().y - Interface::DIALOG_HEIGHT) / 2});
	for (int i = 0; i < classChooseDialog.getNumber(); i++) classChooseDialog.getClassVariant(i).setFont(nakula);

	Interface::Day days[6];
	App::configureDays(days);
	for (int i = 0; i < 6; i++) days[i].setFont(nakula);

	while(window.isOpen()) {
		sf::Event event;

		while ( window.pollEvent(event) ) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
				case sf::Event::MouseMoved:
					processMouseMove(window, days, classChooseDialog);
					break;
				case sf::Event::MouseButtonPressed:
					processMouseButtonPress(window, days, classChooseDialog);
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape && classChooseDialog.isActive()) {
						classChooseDialog.changeActive();
					}
					break;
			}
		}

		window.clear();
		for (int i = 0; i < 6; i++) days[i].draw(window);
		if (classChooseDialog.isActive()) classChooseDialog.draw(window);
		window.display();
	}
}

void App::configureDays(Interface::Day* days) {
	for (int i = 0; i < 6; i++) {
		days[i].setWeekDay(i);
		if (i < 3) {
			days[i].setPosition({2 + i * Interface::DAY_WIDTH + (i + 1)*Interface::CLASS_FIELD_INDENT + i * 6, 20});
		} else {
			days[i].setPosition({2 + (i - 3) * Interface::DAY_WIDTH + 
			(i - 3 + 1) * Interface::CLASS_FIELD_INDENT + (i - 3) * 6, 20 + 20 + Interface::DAY_HEIGHT});
		}
	}
}

void App::processMouseMove(sf::RenderWindow& window, Interface::Day* days, Interface::Dialog& classChooseDialog) {
	for (int dayIndex = 0; dayIndex < 6; dayIndex++) {
		for (int classIndex = 0; classIndex < 14; classIndex++) {
			if (days[dayIndex][classIndex].isMouseOver(window) && !classChooseDialog.isActive()) {
				days[dayIndex][classIndex].setBgColor(sf::Color(190, 190, 190));
			} else {
				days[dayIndex][classIndex].setBgColor(sf::Color::White);
			}
		}
	}
	for (int i = 0; i < classChooseDialog.getNumber(); i++) {
		if (classChooseDialog.getClassVariant(i).isMouseOver(window)) {
			classChooseDialog.getClassVariant(i).setBgColor(sf::Color(190, 190, 190));
		} else {
			classChooseDialog.getClassVariant(i).setBgColor(sf::Color::White);
		}
	}
}

void App::processMouseButtonPress(sf::RenderWindow& window, Interface::Day* days, Interface::Dialog& classChooseDialog) {
	static int curClassIndex, curDayIndex;
	sf::Text newText;
	if (classChooseDialog.isActive()) {
		for (int i = 0; i < classChooseDialog.getNumber(); i++) {
			if (classChooseDialog.getClassVariant(i).isMouseOver(window)) {
				newText = classChooseDialog.getClassVariant(i).getText();
				days[curDayIndex][curClassIndex].setText(newText.getString());
				classChooseDialog.changeActive();
			}
		}
	} else {
		for (int dayIndex = 0; dayIndex < 6; dayIndex++) {
			for (int classIndex = 0; classIndex < 14; classIndex++) {
				if (days[dayIndex][classIndex].isMouseOver(window)) {
					curClassIndex = classIndex;
					curDayIndex = dayIndex;
					std::vector<std::wstring> goodClasses = ScheduleParser::getClasses(dayIndex, classIndex);
					if (!classChooseDialog.isActive()) classChooseDialog.changeActive();
					for (int i = 0; i < goodClasses.size(); i++) {
						classChooseDialog.getClassVariant(i).setText(goodClasses[i]);
					}
				}
			}
		}
	}
}

