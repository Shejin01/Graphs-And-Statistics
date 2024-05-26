#pragma once

#include "Statistics.h"
#include "TextRenderer.h"

class Histogram {
private:
	sf::RectangleShape boundingBox;
	sf::VertexArray tick{sf::Lines};
	int xTickAmount = 0, yTickAmount = 0;
	std::vector<sf::VertexArray> graphs;
	sf::VertexArray outline{sf::LinesStrip};
public:
	std::unordered_map<std::string, std::vector<float>> datasets;
	std::unordered_map<std::string, sf::Color> colors;
	std::string xLabel = "Class Interval", yLabel = "Frequency", heading = "";
	float xScale = 1, yScale = 1;
	float xTickSpacing = 40, yTickSpacing = 40;
	float graphWidth = 500, graphHeight = 500;
	float graphXPosition = 433, graphYPosition = 100;
	float xTickStart = 0, yTickStart = 0;
	int tickFontSize = 12, legendFontSize = 12, labelFontSize = 24, headingFontSize = 36;
	float classWidth = 5;

	void CreateDataSet(std::string datasetName, sf::Color color);
	void AddData(std::string datasetName, float value);
	void UpdateGraph();
	void UpdateGraphSettings();
	void DrawGraph(sf::RenderWindow& window);
};