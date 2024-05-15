#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Point {
public:
	float x, y;
	std::string label;
	Point(float x, float y, std::string label = "");
};

class LineGraph {
public:
	std::vector<Point> data;
	std::string xLabel = "X axis", yLabel = "Y axis";
	int xScale = 1, yScale = 1;
	int xTickSpacing = 40, yTickSpacing = 40;
	int graphWidth = 500, graphHeight = 500;
	int graphXPosition = 433, graphYPosition = 100;

	sf::Font font;
	sf::Text text;

	LineGraph(const char* fontLocation);
	void AddData(float x, float y, std::string label = "");
	void DrawGraph(sf::RenderWindow& window);
};