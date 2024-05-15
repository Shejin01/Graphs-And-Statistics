#include <iostream>
#include <SFML/Graphics.hpp>
#include "Statistics.h"

int WIDTH = 1366, HEIGHT = 697;
int FPS = 60;

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Graphs & Statistics", 7U, settings);
	window.setFramerateLimit(FPS);

	LineGraph lineGraph("fonts/arial.ttf");
	lineGraph.AddData(1, 2);
	lineGraph.AddData(2, 4);
	lineGraph.AddData(3, 8);
	lineGraph.AddData(4, 5);
	lineGraph.AddData(5.5, 10.3);

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

		window.clear(sf::Color(139, 240, 72));
		lineGraph.DrawGraph(window);
		window.display();
	}

	return 0;
}