#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

std::string RemoveTrailingZeroes(std::string number);

class Point {
public:
	float x, y;
	std::string label;
	Point(float x, float y, std::string label = "");
};

class LineGraph {
private:
	sf::Font font;
	sf::Text text;
public:
	std::unordered_map<std::string, std::vector<Point>> datasets;
	std::unordered_map<std::string, sf::Color> colors;
	std::string xLabel = "X axis", yLabel = "Y axis", heading = "";
	float xScale = 1, yScale = 1;
	float xTickSpacing = 40, yTickSpacing = 40;
	float graphWidth = 500, graphHeight = 500;
	float graphXPosition = 433, graphYPosition = 100;
	float xTickStart = 0, yTickStart = 0;
	int tickFontSize = 12, legendFontSize = 12, labelFontSize = 24, headingFontSize = 36;

	LineGraph(const char* fontLocation);
	void CreateDataSet(std::string name, sf::Color color);
	void AddData(std::string name, float x, float y, std::string label = "");
	void DrawGraph(sf::RenderWindow& window, bool drawPoints = true);
};