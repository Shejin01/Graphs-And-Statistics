#pragma once

#include "BoxGraph.h"
#include "TextRenderer.h"

class Histogram : public BoxGraph {
private:
	sf::VertexArray outline{sf::LinesStrip};
	void DrawTicks(sf::RenderWindow& window);
	void DrawRectangles(sf::RenderWindow& window);
public:
	std::unordered_map<std::string, std::vector<float>> datasets;
	float classWidth = 5;

	Histogram();
	void CreateDataSet(std::string datasetName, sf::Color color);
	void AddData(std::string datasetName, float value);
	void UpdateGraph();
	void DrawGraph(sf::RenderWindow& window, bool drawGrid);
};