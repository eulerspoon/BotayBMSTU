#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window = sf::RenderWindow{ sf::VideoMode::getDesktopMode(), "BotayBMSTU" };
	window.setFramerateLimit(144);

	while(window.isOpen()) {
		for (auto event = sf::Event{}; window.pollEvent(event);) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
		
		}

		window.clear();
		window.display();
	}

	return 0;
}
