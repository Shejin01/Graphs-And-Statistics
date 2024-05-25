#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class TextRenderer {
public:
	static sf::Font font;
	static sf::Text text;
	static sf::RenderWindow* window;

	static void LoadFont(const char* fontLocation) {
		if (!font.loadFromFile(fontLocation)) {
			std::cout << "Error while load font.\n";
		}
		text.setFont(font);
		text.setFillColor(sf::Color::Black);
	}

	static void AttachWindow(sf::RenderWindow* targetWindow) {
		window = targetWindow;
	}

	static void SetFontSize(int fontSize) {
		text.setCharacterSize(fontSize);
	}

	static void RenderText(std::string textString, float x, float y) {
		text.setString(textString);
		text.setPosition(x, y);
		window->draw(text);
	}

	static void RenderText(std::string textString, sf::Vector2f position) {
		text.setString(textString);
		text.setPosition(position);
		window->draw(text);
	}
};