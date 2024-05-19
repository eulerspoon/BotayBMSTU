#include "app.hpp"

void App::RunApp() {
	typedef Interface::Button Button;

    sf::RenderWindow window = sf::RenderWindow{ sf::VideoMode::getDesktopMode(), "BotayBMSTU" };
	window.setFramerateLimit(144);
	std::cout << window.getSize().x << " " << window.getSize().y << std::endl;
	sf::Font nakula;
	nakula.loadFromFile("resources/nakula.ttf");

	Interface::Day days[6];
	for (int i = 0; i < 6; i++) {
		days[i].setWeekDay(i);
		if (i < 3) {
			days[i].setPosition({2 + i * Interface::DAY_WIDTH + (i + 1)*Interface::CLASS_FIELD_INDENT + i * 6, 20});
		} else {
			days[i].setPosition({2 + (i - 3) * Interface::DAY_WIDTH + 
			(i - 3 + 1) * Interface::CLASS_FIELD_INDENT + (i - 3) * 6, 20 + 20 + Interface::DAY_HEIGHT});
		}

		for (int j = 0; j < 14; j++)
			days[i][j].setFont(nakula);
		days[i].getWeekDay().setFont(nakula);
		
		for (int j = 0; j < 7; j++) days[i].getTime(j).setFont(nakula);
		days[i].getCh().setFont(nakula);
		days[i].getZn().setFont(nakula);
		
	}

	Interface::Day monday;
	monday.setWeekDay(0);
	monday.setPosition({3, 20});
	for (int i = 0; i < 14; i++)
		monday[i].setFont(nakula);
	monday.getWeekDay().setFont(nakula);
	for (int i = 0; i < 7; i++) monday.getTime(i).setFont(nakula);
	monday.getCh().setFont(nakula);
	monday.getZn().setFont(nakula);

	while(window.isOpen()) {
		sf::Event event;

		while ( window.pollEvent(event) ) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
				case sf::Event::MouseMoved:
					for (int dayIndex = 0; dayIndex < 6; dayIndex++) {
						for (int classIndex = 0; classIndex < 14; classIndex++) {
							if (days[dayIndex][classIndex].isMouseOver(window)) {
								days[dayIndex][classIndex].setBgColor(sf::Color(190, 190, 190));
							} else {
								days[dayIndex][classIndex].setBgColor(sf::Color::White);
							}
						}
					}
					break;
				case sf::Event::MouseButtonPressed:
					for (int dayIndex = 0; dayIndex < 6; dayIndex++) {
						for (int classIndex = 0; classIndex < 14; classIndex++) {
							if (days[dayIndex][classIndex].isMouseOver(window)) {
								std::cout << "Day " << dayIndex << " class " << classIndex << std::endl;
							}
						}
					}
					break;
			}
		}

		window.clear();
		for (int i = 0; i < 6; i++) days[i].draw(window);
		window.display();
	}
}