#include "Statistics.h"

std::string RemoveTrailingZeroes(std::string number) {
	int size = static_cast<int>(number.length());
	for (int i = 0; i < size; i++) {
		if (number[i] == '.') {
			number.erase(number.begin() + i + 2, number.end());
			break;
		}
	}
	return number;
}

Point::Point(float x, float y, std::string label) : x(x), y(y), label(label) {}

LineGraph::LineGraph(const char* fontLocation) {
	if (!font.loadFromFile(fontLocation)) {
		std::cout << "Error while load font.\n";
	}
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
}

void LineGraph::CreateDataSet(std::string name, sf::Color color) {
	datasets.insert({ name, std::vector<Point>() });
	colors.insert({ name, color });
}

void LineGraph::AddData(std::string name, float x, float y, std::string label) {
	datasets[name].push_back(Point(x, y, label));
}

void LineGraph::DrawGraph(sf::RenderWindow& window, bool drawPoints) {
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
		text.setString(RemoveTrailingZeroes(std::to_string(xScale * i + xTickStart)));
		text.setPosition(tick[0].position.x - (text.getLocalBounds().width*0.5), tick[0].position.y + 20);
		window.draw(text);
	}

	tick[0].position.x = graphXPosition - 10;
	tick[1].position.x = graphXPosition + 10;
	for (int i = 0; i < yTickAmount; i++) {
		tick[0].position.y = graphYPosition + graphHeight - i * yTickSpacing;
		tick[1].position.y = graphYPosition + graphHeight - i * yTickSpacing;
		window.draw(tick);
		text.setString(RemoveTrailingZeroes(std::to_string(yScale * i + yTickStart)));
		text.setPosition(tick[0].position.x - (text.getLocalBounds().width)-5, tick[0].position.y - (text.getLocalBounds().height));
		window.draw(text);
	}

	text.setCharacterSize(labelFontSize);
	text.setString(xLabel);
	text.setPosition(graphXPosition + graphWidth * 0.5 - (text.getLocalBounds().width*0.5), graphYPosition + graphWidth + 40);
	window.draw(text);
	text.setString(yLabel);
	text.setPosition(graphXPosition - 40, graphYPosition + graphHeight * 0.5 - (text.getLocalBounds().width*0.5));
	text.setRotation(90);
	window.draw(text);
	text.setRotation(0);
	text.setCharacterSize(headingFontSize);
	text.setString(heading);
	text.setPosition(graphXPosition + graphWidth*0.5 - text.getLocalBounds().width*0.5, graphYPosition - text.getLocalBounds().height - 20);
	window.draw(text);

	// Line
	sf::CircleShape point(3, 8);
	if (drawPoints) {
		point.setOrigin(3, 3);
	}
	for (auto data = datasets.begin(); data != datasets.end(); data++) {
		point.setFillColor(colors[data->first]);
		int startIndex = 0;
		for (int i = 0; i < data->second.size(); i++) {
			if (data->second[i].x >= xTickStart && data->second[i].y >= yTickStart) {
				startIndex = i;
				break;
			}
		}
		sf::VertexArray graph(sf::LinesStrip, data->second.size()-startIndex);
		for (int i = 0; i < data->second.size()-startIndex; i++) {
			graph[i].position = sf::Vector2f(
				graphXPosition + (data->second[i+startIndex].x - xTickStart) * xTickSpacing / xScale, 
				graphYPosition + graphHeight - (data->second[i+startIndex].y - yTickStart) * yTickSpacing / yScale
			);
			graph[i].color = colors[data->first];
			if (drawPoints) {
				point.setPosition(graph[i].position);
				window.draw(point);
			}
		}
		window.draw(graph);
	}

	// Legend
	sf::RectangleShape icon(sf::Vector2f(legendFontSize, legendFontSize));
	icon.setOutlineColor(sf::Color::Black);
	icon.setOutlineThickness(1);
	text.setCharacterSize(legendFontSize);
	int index = 0;
	for (auto color = colors.begin(); color != colors.end(); color++) {
		icon.setFillColor(color->second);
		icon.setPosition(graphXPosition + graphWidth - 100, graphYPosition + 20 + index * 30);
		text.setString(color->first);
		text.setPosition(icon.getPosition().x + 20, icon.getPosition().y);
		window.draw(icon);
		window.draw(text);
		index++;
	}
};