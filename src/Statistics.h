#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

#define PI 3.1415926535

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
	sf::RectangleShape boundingBox;
	sf::VertexArray tick{ sf::Lines };
	int xTickAmount, yTickAmount;
	std::vector<sf::VertexArray> graphs;
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
	void CreateDataSet(std::string datasetName, sf::Color color);
	void AddData(std::string datasetName, float x, float y, std::string label = "");
	void UpdateGraph();
	void DrawGraph(sf::RenderWindow& window, bool drawPoints = true);
};

class PieChart {
private:
	sf::Font font;
	sf::Text text;
public:
	std::unordered_map<std::string, float> data;
	std::unordered_map<std::string, sf::Color> colors;
	std::string heading = "";
	float graphXPosition = 683, graphYPosition = 348;
	float radius = 200;
	int percentFontSize = 24, legendFontSize = 24, headingFontSize = 36;
	int pieChartPointCount = 100;

	PieChart(const char* fontLocation);
	void AddData(std::string name, float value, sf::Color color);
	void DrawGraph(sf::RenderWindow& window, bool showPercentage = true);
};

class Histogram {
private:
	sf::Font font;
	sf::Text text;
public:
	std::vector<float> data;
	sf::Color color;
	std::string xLabel = "Class Interval", yLabel = "Frequency", heading = "";
	float xScale = 1, yScale = 1;
	float xTickSpacing = 40, yTickSpacing = 40;
	float graphWidth = 500, graphHeight = 500;
	float graphXPosition = 433, graphYPosition = 100;
	float xTickStart = 0, yTickStart = 0;
	int tickFontSize = 12, legendFontSize = 12, labelFontSize = 24, headingFontSize = 36;
	float classWidth = 5;

	Histogram(const char* fontLocation);
	void AddData(float value);
	void DrawGraph(sf::RenderWindow& window);
};