#pragma once

#include "Graph.h"
#include "TextRenderer.h"

class LineGraph : public Graph {
private:
	sf::RectangleShape boundingBox;
	sf::VertexArray tick{ sf::Lines };
	sf::VertexArray grid{ sf::Lines };
	int xTickAmount = 0, yTickAmount = 0;
	std::vector<sf::VertexArray> graphs;
public:
	class Point {
	public:
		float x, y;
		std::string label;
		Point(float x, float y, std::string label = "") : x(x), y(y), label(label) {}
	};

	enum Flags {
		FLAG_DRAW_POINTS = 1,
		FLAG_DRAW_LINES = 2,
		FLAG_DRAW_GRID = 4
	};

	std::unordered_map<std::string, std::vector<Point>> datasets;
	std::string xLabel = "X axis", yLabel = "Y axis";
	float xScale = 1, yScale = 1;
	float xTickSpacing = 40, yTickSpacing = 40;
	float graphWidth = 500, graphHeight = 500;
	float graphXPosition = 433, graphYPosition = 100;
	float xTickStart = 0, yTickStart = 0;
	int tickFontSize = 12, legendFontSize = 12, labelFontSize = 24, headingFontSize = 36;
	sf::Color
		backgroundColor = sf::Color::White,
		outlineColor = sf::Color::Black,
		gridColor = sf::Color(128, 128, 128);

	void CreateDataSet(std::string datasetName, sf::Color color);
	void AddData(std::string datasetName, float x, float y, std::string label = "");
	void UpdateGraph();
	void UpdateGraphSettings();
	void DrawGraph(sf::RenderWindow& window, int drawFlags = 6);
};