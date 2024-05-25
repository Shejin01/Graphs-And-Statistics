#include "PieChart.h"

void PieChart::AddData(std::string name, float value, sf::Color color) {
	data.insert({ name, value });
	colors.insert({ name, color });
}

void PieChart::UpdateGraph() {
	for (auto i = data.begin(); i != data.end(); i++) {
		total += i->second;
	}

	float angle = 0;
	float anglePerPoint = 2 * PI / pieChartPointCount;
	int shapeIndex = 0;;
	for (auto value = data.begin(); value != data.end(); value++) {
		float percentage = value->second / total;
		int pointCount = ceil(pieChartPointCount * percentage) + 1;
		shapes.push_back(sf::ConvexShape());
		shapes[shapeIndex].setPointCount(pointCount);
		shapes[shapeIndex].setFillColor(colors[value->first]);
		shapes[shapeIndex].setOutlineColor(sf::Color::Black);
		shapes[shapeIndex].setOutlineThickness(1);
		shapes[shapeIndex].setPoint(0, sf::Vector2f(graphXPosition, graphYPosition));
		float endAngle = 2 * PI * percentage + angle;
		float x, y;
		for (int i = 1; i < pointCount - 1; i++) {
			x = graphXPosition + radius * cos(angle);
			y = graphYPosition + radius * sin(angle);
			shapes[shapeIndex].setPoint(i, sf::Vector2f(x, y));
			angle += anglePerPoint;
		}
		angle = endAngle;
		x = graphXPosition + radius * cos(angle);
		y = graphYPosition + radius * sin(angle);
		shapes[shapeIndex].setPoint(pointCount - 1, sf::Vector2f(x, y));
		shapeIndex++;
	}

	angle = 0;
	for (auto value = data.begin(); value != data.end(); value++) {
		float percentage = value->second / total;
		float percentAngle = angle + PI * percentage;
		float x = graphXPosition + radius * 0.5 * cos(percentAngle);
		float y = graphYPosition + radius * 0.5 * sin(percentAngle);
		angle += 2 * PI * percentage;
		percentTextPos.push_back(sf::Vector2f(x, y));
	}
}

void PieChart::DrawGraph(sf::RenderWindow& window, bool showPercentage) {
	for (auto& shape : shapes) window.draw(shape);

	TextRenderer::SetFontSize(headingFontSize);
	TextRenderer::SetString(heading);
	TextRenderer::RenderText(graphXPosition - TextRenderer::text.getLocalBounds().width * 0.5, graphYPosition - radius - TextRenderer::text.getLocalBounds().height * 2);

	// Legend
	sf::RectangleShape icon(sf::Vector2f(legendFontSize, legendFontSize));
	icon.setOutlineColor(sf::Color::Black);
	icon.setOutlineThickness(1);
	TextRenderer::SetFontSize(legendFontSize);
	int index = 0;
	for (auto color = colors.begin(); color != colors.end(); color++) {
		icon.setFillColor(color->second);
		icon.setPosition(graphXPosition + radius + 10, graphYPosition - radius + legendFontSize + 5 + index * 30);
		window.draw(icon);
		TextRenderer::RenderText(color->first, icon.getPosition().x + legendFontSize + 5, icon.getPosition().y);
		index++;
	}

	// Percentage Text
	TextRenderer::SetFontSize(percentFontSize);
	int textPosIndex = 0;
	for (auto value = data.begin(); value != data.end(); value++) {
		float percentage = value->second / total;

		TextRenderer::RenderText(RemoveTrailingZeroes(std::to_string(percentage * 100)) + "%", percentTextPos[textPosIndex]);
		textPosIndex++;
	}
}