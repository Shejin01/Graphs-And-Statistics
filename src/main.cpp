#include <iostream>
#include <SFML/Graphics.hpp>
#include "Statistics.h"

int WIDTH = 1366, HEIGHT = 697;
int FPS = 60;

void TestCase1(LineGraph& lineGraph);

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Graphs & Statistics", 7U, settings);
	window.setFramerateLimit(FPS);

	LineGraph lineGraph("fonts/arial.ttf");

	lineGraph.heading = "Graph";
	lineGraph.CreateDataSet("Sine Wave", sf::Color::Black);
	lineGraph.CreateDataSet("Cosine Wave", sf::Color::Red);
	
	float t = 0;
	while (window.isOpen()) {
		lineGraph.AddData("Sine Wave", t * 0.1, sin(t * 0.1) + 5);
		lineGraph.AddData("Cosine Wave", t * 0.1, cos(t * 0.1) + 5);
		t++;
		if (lineGraph.datasets["Sine Wave"].size() > 200) lineGraph.datasets["Sine Wave"].erase(lineGraph.datasets["Sine Wave"].begin());
		if (lineGraph.datasets["Cosine Wave"].size() > 200) lineGraph.datasets["Cosine Wave"].erase(lineGraph.datasets["Cosine Wave"].begin());
		if (t * 0.1 > lineGraph.graphWidth / lineGraph.xTickSpacing) lineGraph.xTickStart += 0.1;

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
		lineGraph.DrawGraph(window, false);
		window.display();
	}

	return 0;
}

void TestCase1(LineGraph& lineGraph) {
	lineGraph.CreateDataSet("Default", sf::Color::Black);
	lineGraph.AddData("Default", 0, 0);
	lineGraph.AddData("Default", 1, 2);
	lineGraph.AddData("Default", 2, 4);
	lineGraph.AddData("Default", 3, 8);
	lineGraph.AddData("Default", 4, 5);
	lineGraph.AddData("Default", 5.5, 10.3);
	lineGraph.CreateDataSet("Secondary", sf::Color::Red);
	lineGraph.AddData("Secondary", 0, 3);
	lineGraph.AddData("Secondary", 1, 4);
	lineGraph.AddData("Secondary", 2, 2);
	lineGraph.AddData("Secondary", 3, 7);
	lineGraph.AddData("Secondary", 4, 1);
	lineGraph.AddData("Secondary", 5, 0);
}