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

void LineGraph::UpdateGraphSettings() {
	boundingBox = sf::RectangleShape(sf::Vector2f(graphWidth, graphHeight));
	boundingBox.setFillColor(sf::Color::White);
	boundingBox.setOutlineColor(sf::Color::Black);
	boundingBox.setOutlineThickness(1);
	boundingBox.setPosition(graphXPosition, graphYPosition);

	xTickAmount = graphWidth / xTickSpacing;
	yTickAmount = graphHeight / yTickSpacing;

	tick.clear();
	for (int i = 0; i < xTickAmount; i++) {
		tick.append(sf::Vertex(
			sf::Vector2f(graphXPosition + i * xTickSpacing, graphYPosition + graphHeight - 10),
			sf::Color::Black
		));
		tick.append(tick[tick.getVertexCount() - 1]);
		tick[tick.getVertexCount() - 1].position.y += 20;
	}

	for (int i = 0; i < yTickAmount; i++) {
		tick.append(sf::Vertex(
			sf::Vector2f(graphXPosition - 10, graphYPosition + graphHeight - i * yTickSpacing),
			sf::Color::Black
		));
		tick.append(tick[tick.getVertexCount() - 1]);
		tick[tick.getVertexCount() - 1].position.x += 20;
	}
}

void LineGraph::DrawGraph(sf::RenderWindow& window, bool drawPoints, bool drawLines) {
	window.draw(boundingBox);

	// Ticks
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

	TextRenderer::SetFontSize(labelFontSize);
	TextRenderer::SetString(xLabel);
	TextRenderer::RenderText(graphXPosition + graphWidth * 0.5 - (TextRenderer::text.getLocalBounds().width * 0.5), graphYPosition + graphWidth + 40);
	TextRenderer::SetString(yLabel);
	TextRenderer::text.setRotation(90);
	TextRenderer::RenderText(graphXPosition - 40, graphYPosition + graphHeight * 0.5 - (TextRenderer::text.getLocalBounds().width * 0.5));
	TextRenderer::text.setRotation(0);
	TextRenderer::SetFontSize(headingFontSize);
	TextRenderer::SetString(heading);
	TextRenderer::RenderText(graphXPosition + graphWidth * 0.5 - TextRenderer::text.getLocalBounds().width * 0.5, graphYPosition - TextRenderer::text.getLocalBounds().height - 20);

	// Line
	if (drawPoints) {
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
	if (drawLines) {
		for (int i = 0; i < graphs.size(); i++)
			window.draw(graphs[i]);
	}

	// Legend
	sf::RectangleShape icon(sf::Vector2f(legendFontSize, legendFontSize));
	icon.setOutlineColor(sf::Color::Black);
	icon.setOutlineThickness(1);
	TextRenderer::SetFontSize(legendFontSize);
	int index = 0;
	for (auto color = colors.begin(); color != colors.end(); color++) {
		icon.setFillColor(color->second);
		icon.setPosition(graphXPosition + graphWidth - 100, graphYPosition + 20 + index * 30);
		window.draw(icon);
		TextRenderer::RenderText(color->first, icon.getPosition().x + 20, icon.getPosition().y);
		index++;
	}
};