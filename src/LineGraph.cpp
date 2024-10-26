#include "LineGraph.h"

void LineGraph::CreateDataSet(std::string datasetName, sf::Color color) {
	datasets.insert({ datasetName, std::vector<Point>() });
	colors.insert({ datasetName, color });
}

void LineGraph::AddData(std::string datasetName, float x, float y, std::string label) {
	datasets[datasetName].push_back(Point(x, y, label));
}

void LineGraph::UpdateGraph() {
	for (auto& graph : graphs) graph.clear();

	int graphIndex = 0;
	for (auto data = datasets.begin(); data != datasets.end(); data++) {
		graphs.push_back(sf::VertexArray(sf::LinesStrip));
		int startIndex = 0;
		for (int i = 0; i < data->second.size(); i++) {
			if (data->second[i].x >= xTickStart && data->second[i].y >= yTickStart) {
				startIndex = i;
				break;
			}
		}
		for (int i = 0; i < data->second.size() - startIndex; i++) {
			graphs[graphIndex].append(sf::Vertex(sf::Vector2f(
				graphXPosition + (data->second[i + startIndex].x - xTickStart) * xTickSpacing / xScale,
				graphYPosition + graphHeight - (data->second[i + startIndex].y - yTickStart) * yTickSpacing / yScale),
				colors[data->first]
			));
		}
		graphIndex++;
	}
}

void LineGraph::DrawTicks(sf::RenderWindow& window) {
	window.draw(tick);
	TextRenderer::SetFontSize(tickFontSize);
	for (int i = 0; i < xTickAmount; i++) {
		TextRenderer::SetString(RemoveTrailingZeroes(std::to_string(xScale * i + xTickStart)));
		TextRenderer::RenderText(graphXPosition + i * xTickSpacing - (TextRenderer::text.getLocalBounds().width * 0.5), graphYPosition + graphHeight - 10 + 20);
	}
	for (int i = 0; i < yTickAmount; i++) {
		TextRenderer::SetString(RemoveTrailingZeroes(std::to_string(yScale * i + yTickStart)));
		TextRenderer::RenderText(graphXPosition - 10 - (TextRenderer::text.getLocalBounds().width) - 5, graphYPosition + graphHeight - i * yTickSpacing - (TextRenderer::text.getLocalBounds().height));
	}
}

void LineGraph::DrawPoints(sf::RenderWindow& window) {
	sf::CircleShape point(3, 8);
	point.setOrigin(3, 3);
	int graphIndex = 0;
	for (auto data = datasets.begin(); data != datasets.end(); data++) {
		point.setFillColor(colors[data->first]);
		int startIndex = 0;
		for (int i = 0; i < data->second.size(); i++) {
			if (data->second[i].x >= xTickStart && data->second[i].y >= yTickStart) {
				startIndex = i;
				break;
			}
		}
		for (int i = 0; i < data->second.size() - startIndex; i++) {
			point.setPosition(graphs[graphIndex][i].position);
			window.draw(point);
		}
		graphIndex++;
	}
}

void LineGraph::DrawLines(sf::RenderWindow& window) {
	for (auto& graph : graphs)
		window.draw(graph);
}

void LineGraph::DrawGraph(sf::RenderWindow& window, int drawFlags) {
	window.draw(boundingBox);
	if (drawFlags & FLAG_DRAW_GRID) window.draw(grid);
	DrawTicks(window);
	DrawText(window);
	if (drawFlags & FLAG_DRAW_POINTS) DrawPoints(window);
	if (drawFlags & FLAG_DRAW_LINES) DrawLines(window);
	DrawLegend(window);
};