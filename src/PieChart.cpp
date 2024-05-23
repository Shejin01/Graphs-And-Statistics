#include "PieChart.h"

PieChart::PieChart(const char* fontLocation) {
	if (!font.loadFromFile(fontLocation)) {
		std::cout << "Error while loading font.\n";
	}
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
}
void PieChart::AddData(std::string name, float value, sf::Color color) {
	data.insert({ name, value });
	colors.insert({ name, color });
}
void PieChart::DrawGraph(sf::RenderWindow& window, bool showPercentage) {
	float total = 0;
	for (auto i = data.begin(); i != data.end(); i++) {
		total += i->second;
	}

	sf::ConvexShape shape;
	float angle = 0;
	float anglePerPoint = 2 * PI / pieChartPointCount;
	for (auto value = data.begin(); value != data.end(); value++) {
		float percentage = value->second / total;
		int pointCount = ceil(pieChartPointCount * percentage) + 1;
		shape.setPointCount(pointCount);
		shape.setFillColor(colors[value->first]);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1);
		shape.setPoint(0, sf::Vector2f(graphXPosition, graphYPosition));
		float endAngle = 2 * PI * percentage + angle;
		float x, y;
		for (int i = 1; i < pointCount - 1; i++) {
			x = graphXPosition + radius * cos(angle);
			y = graphYPosition + radius * sin(angle);
			shape.setPoint(i, sf::Vector2f(x, y));
			angle += anglePerPoint;
		}
		angle = endAngle;
		x = graphXPosition + radius * cos(angle);
		y = graphYPosition + radius * sin(angle);
		shape.setPoint(pointCount - 1, sf::Vector2f(x, y));

		window.draw(shape);
	}

	text.setCharacterSize(headingFontSize);
	text.setString(heading);
	text.setPosition(graphXPosition - text.getLocalBounds().width * 0.5, graphYPosition - radius - text.getLocalBounds().height * 2);
	window.draw(text);

	// Legend
	sf::RectangleShape icon(sf::Vector2f(legendFontSize, legendFontSize));
	icon.setOutlineColor(sf::Color::Black);
	icon.setOutlineThickness(1);
	text.setCharacterSize(legendFontSize);
	int index = 0;
	for (auto color = colors.begin(); color != colors.end(); color++) {
		text.setString(color->first);
		icon.setFillColor(color->second);
		icon.setPosition(graphXPosition + radius + 10, graphYPosition - radius + legendFontSize + 5 + index * 30);
		text.setPosition(icon.getPosition().x + legendFontSize + 5, icon.getPosition().y);
		window.draw(icon);
		window.draw(text);
		index++;
	}

	// Percentage Text
	text.setCharacterSize(percentFontSize);
	angle = 0;
	for (auto value = data.begin(); value != data.end(); value++) {
		float percentage = value->second / total;
		text.setString(RemoveTrailingZeroes(std::to_string(percentage * 100)) + "%");
		float percentAngle = angle + PI * percentage;
		float x = graphXPosition + radius * 0.5 * cos(percentAngle);
		float y = graphYPosition + radius * 0.5 * sin(percentAngle);
		angle += 2 * PI * percentage;
		text.setPosition(x, y);
		window.draw(text);
	}
}