#pragma once

#include "Statistics.h"
#include "TextRenderer.h"

class PieChart {
private:
	float total = 0;
	std::vector<sf::ConvexShape> shapes;
	std::vector<sf::Vector2f> percentTextPos;
public:
	std::unordered_map<std::string, float> data;
	std::unordered_map<std::string, sf::Color> colors;
	std::string heading = "";
	float graphXPosition = 683, graphYPosition = 348;
	float radius = 200;
	int percentFontSize = 24, legendFontSize = 24, headingFontSize = 36;
	int pieChartPointCount = 100;

	void AddData(std::string name, float value, sf::Color color);
	void UpdateGraph();
	void DrawGraph(sf::RenderWindow& window, bool showPercentage = true);
};
