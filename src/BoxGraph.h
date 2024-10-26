#pragma once

#include "Graph.h"
#include "TextRenderer.h"

class BoxGraph : public Graph {
private:
	sf::RectangleShape boundingBox;
	sf::VertexArray tick{ sf::Lines };
	sf::VertexArray grid{ sf::Lines };
	int xTickAmount = 0, yTickAmount = 0;
	std::vector<sf::VertexArray> graphs;
public:
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

	void UpdateGraphSettings();

	friend class LineGraph;
	friend class Histogram;
};