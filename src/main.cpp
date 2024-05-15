#include <iostream>
#include <SFML/Graphics.hpp>

int WIDTH = 500, HEIGHT = 500;
int FPS = 60;

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Graphs & Statistics", 7U, settings);

	sf::CircleShape shape(100, 100);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(100, 100);
	shape.setPosition(250, 250);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}

			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				}
			}
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}