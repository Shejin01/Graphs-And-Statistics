#include "LineGraph.h"

LineGraph::LineGraph(const char* fontLocation) {
	if (!font.loadFromFile(fontLocation)) {
		std::cout << "Error while load font.\n";
	}
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
}

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

void LineGraph::UpdateGraphBase() {
	boundingBox = sf::RectangleShape(sf::Vector2f(graphWidth, graphHeight));
	boundingBox.setFillColor(sf::Color::White);
	boundingBox.setOutlineColor(sf::Color::Black);
	boundingBox.setOutlineThickness(1);
	boundingBox.setPosition(graphXPosition, graphYPosition);

	xTickAmount = graphWidth / xTickSpacing, yTickAmount = graphHeight / yTickSpacing;

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

void LineGraph::DrawGraph(sf::RenderWindow& window, bool drawPoints) {
	window.draw(boundingBox);

	// Ticks
	text.setCharacterSize(tickFontSize);
	window.draw(tick);
	for (int i = 0; i < xTickAmount; i++) {
		text.setString(RemoveTrailingZeroes(std::to_string(xScale * i + xTickStart)));
		text.setPosition(graphXPosition + i * xTickSpacing - (text.getLocalBounds().width * 0.5), graphYPosition + graphHeight - 10 + 20);
		window.draw(text);
	}

	for (int i = 0; i < yTickAmount; i++) {
		text.setString(RemoveTrailingZeroes(std::to_string(yScale * i + yTickStart)));
		text.setPosition(graphXPosition - 10 - (text.getLocalBounds().width) - 5, graphYPosition + graphHeight - i * yTickSpacing - (text.getLocalBounds().height));
		window.draw(text);
	}

	text.setCharacterSize(labelFontSize);
	text.setString(xLabel);
	text.setPosition(graphXPosition + graphWidth * 0.5 - (text.getLocalBounds().width * 0.5), graphYPosition + graphWidth + 40);
	window.draw(text);
	text.setString(yLabel);
	text.setPosition(graphXPosition - 40, graphYPosition + graphHeight * 0.5 - (text.getLocalBounds().width * 0.5));
	text.setRotation(90);
	window.draw(text);
	text.setRotation(0);
	text.setCharacterSize(headingFontSize);
	text.setString(heading);
	text.setPosition(graphXPosition + graphWidth * 0.5 - text.getLocalBounds().width * 0.5, graphYPosition - text.getLocalBounds().height - 20);
	window.draw(text);

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
	for (int i = 0; i < graphs.size(); i++)
		window.draw(graphs[i]);

	// Legend
	sf::RectangleShape icon(sf::Vector2f(legendFontSize, legendFontSize));
	icon.setOutlineColor(sf::Color::Black);
	icon.setOutlineThickness(1);
	text.setCharacterSize(legendFontSize);
	int index = 0;
	for (auto color = colors.begin(); color != colors.end(); color++) {
		icon.setFillColor(color->second);
		icon.setPosition(graphXPosition + graphWidth - 100, graphYPosition + 20 + index * 30);
		text.setString(color->first);
		text.setPosition(icon.getPosition().x + 20, icon.getPosition().y);
		window.draw(icon);
		window.draw(text);
		index++;
	}
};