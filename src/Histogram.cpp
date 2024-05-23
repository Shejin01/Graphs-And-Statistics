#include "Histogram.h"

Histogram::Histogram(const char* fontLocation) {
	if (!font.loadFromFile(fontLocation)) {
		std::cout << "Error while loading font.\n";
	}
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
}
void Histogram::AddData(float value) {
	data.push_back(value);
}
void Histogram::DrawGraph(sf::RenderWindow& window) {
	sf::RectangleShape boundingBox(sf::Vector2f(graphWidth, graphHeight));
	boundingBox.setFillColor(sf::Color::White);
	boundingBox.setOutlineColor(sf::Color::Black);
	boundingBox.setOutlineThickness(1);
	boundingBox.setPosition(graphXPosition, graphYPosition);
	window.draw(boundingBox);

	// Ticks
	text.setCharacterSize(tickFontSize);
	int xTickAmount = graphWidth / xTickSpacing, yTickAmount = graphHeight / yTickSpacing;
	sf::VertexArray tick(sf::LinesStrip, 2);
	tick[0].color = sf::Color::Black;
	tick[1].color = sf::Color::Black;
	tick[0].position.y = graphYPosition + graphHeight - 10;
	tick[1].position.y = graphYPosition + graphHeight + 10;
	for (int i = 0; i < xTickAmount; i++) {
		tick[0].position.x = graphXPosition + i * xTickSpacing;
		tick[1].position.x = graphXPosition + i * xTickSpacing;
		window.draw(tick);
		text.setString(RemoveTrailingZeroes(std::to_string((xScale * i + xTickStart) * classWidth)));
		text.setPosition(tick[0].position.x - (text.getLocalBounds().width * 0.5), tick[0].position.y + 20);
		window.draw(text);
	}

	tick[0].position.x = graphXPosition - 10;
	tick[1].position.x = graphXPosition + 10;
	for (int i = 0; i < yTickAmount; i++) {
		tick[0].position.y = graphYPosition + graphHeight - i * yTickSpacing;
		tick[1].position.y = graphYPosition + graphHeight - i * yTickSpacing;
		window.draw(tick);
		text.setString(RemoveTrailingZeroes(std::to_string(yScale * i + yTickStart)));
		text.setPosition(tick[0].position.x - (text.getLocalBounds().width) - 5, tick[0].position.y - (text.getLocalBounds().height));
		window.draw(text);
	}

	text.setCharacterSize(labelFontSize);
	text.setString(xLabel);
	text.setPosition(graphXPosition + graphWidth * 0.5 - (text.getLocalBounds().width * 0.5), graphYPosition + graphWidth + 40);
	window.draw(text);
	text.setString(yLabel);
	text.setPosition(graphXPosition - 40, graphYPosition + graphHeight * 0.5 - (text.getLocalBounds().width * 0.5));
	text.setRotation(90);
	window.draw(text);
	text.setRotation(0);
	text.setCharacterSize(headingFontSize);
	text.setString(heading);
	text.setPosition(graphXPosition + graphWidth * 0.5 - text.getLocalBounds().width * 0.5, graphYPosition - text.getLocalBounds().height - 20);
	window.draw(text);

	// Rectangles
	sf::RectangleShape rect;
	rect.setFillColor(color);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
	for (int i = 0; i < data.size(); i++) {
		if (data[i] < yTickStart || i * classWidth < xTickStart) continue;
		rect.setSize(sf::Vector2f(xTickSpacing / xScale, data[i] * yTickSpacing / yScale));
		rect.setPosition(graphXPosition + rect.getSize().x * i, graphYPosition + graphHeight - rect.getSize().y);
		window.draw(rect);
	}
}