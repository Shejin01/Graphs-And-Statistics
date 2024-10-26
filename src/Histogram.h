#pragma once

#include "BoxGraph.h"
#include "TextRenderer.h"

class Histogram : public BoxGraph {
private:
	sf::VertexArray outline{sf::LinesStrip};
public:
	std::unordered_map<std::string, std::vector<float>> datasets;
	std::string xLabel = "Class Interval", yLabel = "Frequency";
	float classWidth = 5;

	void CreateDataSet(std::string datasetName, sf::Color color);
	void AddData(std::string datasetName, float value);
	void UpdateGraph();
	void DrawGraph(sf::RenderWindow& window, bool drawGrid);
};