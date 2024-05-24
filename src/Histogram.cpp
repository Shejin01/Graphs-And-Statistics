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

void Histogram::UpdateGraphSettings() {
	boundingBox = sf::RectangleShape(sf::Vector2f(graphWidth, graphHeight));
	boundingBox.setFillColor(sf::Color::White);
	boundingBox.setOutlineColor(sf::Color::Black);
	boundingBox.setOutlineThickness(1);
	boundingBox.setPosition(graphXPosition, graphYPosition);

	xTickAmount = graphWidth / xTickSpacing;
	yTickAmount = graphHeight / yTickSpacing;

	tick.clear();
	for (int i = 0; i < xTickAmount; i++) {
		tick.append(sf::Vertex(
			sf::Vector2f(graphXPosition + i * xTickSpacing, graphYPosition + graphHeight - 10),
			sf::Color::Black
		));
		tick.append(tick[tick.getVertexCount() - 1]);
		tick[tick.getVertexCount() - 1].position.y += 20;
	}
	for (int i = 0; i < yTickAmount; i++) {
		tick.append(sf::Vertex(
			sf::Vector2f(graphXPosition - 10, graphYPosition + graphHeight - i * yTickSpacing),
			sf::Color::Black
		));
		tick.append(tick[tick.getVertexCount() - 1]);
		tick[tick.getVertexCount() - 1].position.x += 20;
	}
}

void Histogram::DrawGraph(sf::RenderWindow& window) {
	window.draw(boundingBox);

	// Ticks
	text.setCharacterSize(tickFontSize);
	window.draw(tick);
	for (int i = 0; i < xTickAmount; i++) {
		text.setString(RemoveTrailingZeroes(std::to_string((xScale * i + xTickStart) * classWidth)));
		text.setPosition(graphXPosition + i * xTickSpacing - (text.getLocalBounds().width * 0.5), graphYPosition + graphHeight - 10 + 20);
		window.draw(text);
	}

	for (int i = 0; i < yTickAmount; i++) {
		text.setString(RemoveTrailingZeroes(std::to_string(yScale * i + yTickStart)));
		text.setPosition(graphXPosition - 10 - (text.getLocalBounds().width) - 5, graphYPosition + graphHeight - i * yTickSpacing - (text.getLocalBounds().height));
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