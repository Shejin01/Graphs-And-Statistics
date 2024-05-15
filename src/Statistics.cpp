#include "Statistics.h"

Point::Point(float x, float y, std::string label) : x(x), y(y), label(label) {}

LineGraph::LineGraph(const char* fontLocation) {
	if (!font.loadFromFile(fontLocation)) {
		std::cout << "Error while load font.\n";
	}
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
}

void LineGraph::AddData(float x, float y, std::string label) {
	data.push_back(Point(x, y, label));
}

void LineGraph::DrawGraph(sf::RenderWindow& window) {
	sf::RectangleShape boundingBox(sf::Vector2f(graphWidth, graphHeight));
	boundingBox.setFillColor(sf::Color::White);
	boundingBox.setOutlineColor(sf::Color::Black);
	boundingBox.setOutlineThickness(1);
	boundingBox.setPosition(graphXPosition, graphYPosition);
	window.draw(boundingBox);

	// Ticks
	text.setCharacterSize(12);
	int xTickAmount = graphWidth / xTickSpacing, yTickAmount = graphHeight / yTickSpacing;
	sf::VertexArray tick(sf::LinesStrip, 2);
	tick[0].color = sf::Color::Black;
	tick[1].color = sf::Color::Black;
	tick[0].position.y = graphYPosition + graphHeight - 10;
	tick[1].position.y = graphYPosition + graphHeight + 10;
	for (int i = 1; i < xTickAmount; i++) {
		tick[0].position.x = graphXPosition + i * xTickSpacing;
		tick[1].position.x = graphXPosition + i * xTickSpacing;
		window.draw(tick);
		text.setString(std::to_string(xScale * i));
		text.setPosition(tick[0].position.x - 5, tick[0].position.y + 20);
		window.draw(text);
	}

	tick[0].position.x = graphXPosition - 10;
	tick[1].position.x = graphXPosition + 10;
	for (int i = 1; i < yTickAmount; i++) {
		tick[0].position.y = graphYPosition + graphHeight - i * yTickSpacing;
		tick[1].position.y = graphYPosition + graphHeight - i * yTickSpacing;
		window.draw(tick);
		text.setString(std::to_string(yScale * i));
		text.setPosition(tick[0].position.x - 20, tick[0].position.y - 5);
		window.draw(text);
	}

	text.setCharacterSize(24);
	text.setString(xLabel);
	text.setPosition(graphXPosition + graphWidth * 0.5 - 50, graphYPosition + graphWidth + 40);
	window.draw(text);
	text.setString(yLabel);
	text.setPosition(graphXPosition - 40, graphYPosition + graphHeight * 0.5 - 50);
	text.setRotation(90);
	window.draw(text);
	text.setRotation(0);

	sf::VertexArray graph(sf::LinesStrip, data.size());
	for (int i = 0; i < data.size(); i++) {
		graph[i].position = sf::Vector2f(graphXPosition + data[i].x * xTickSpacing, graphYPosition + graphHeight - data[i].y * yTickSpacing);
		graph[i].color = sf::Color::Black;
	}
	window.draw(graph);
};