#pragma once

#include "BoxGraph.h"
#include "TextRenderer.h"

class LineGraph : public BoxGraph {
private:
	void DrawTicks(sf::RenderWindow& window);
	void DrawPoints(sf::RenderWindow& window);
	void DrawLines(sf::RenderWindow& window);
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
	void CreateDataSet(std::string datasetName, sf::Color color);
	void AddData(std::string datasetName, float x, float y, std::string label = "");
	void UpdateGraph();
	void DrawGraph(sf::RenderWindow& window, int drawFlags = 6);
};