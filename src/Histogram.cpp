#include "Histogram.h"

void Histogram::CreateDataSet(std::string datasetName, sf::Color color) {
	datasets.insert({ datasetName, std::vector<float>()});
	colors.insert({ datasetName, color });
}

void Histogram::AddData(std::string datasetName, float value) {
	datasets[datasetName].push_back(value);
}

void Histogram::UpdateGraph() {
	graphs = std::vector<sf::VertexArray>(datasets.size());
	int index = 0;
	for (auto data = datasets.begin(); data != datasets.end(); data++) {
		int totalVertexAmount = 0;
		for (int i = 0; i < data->second.size(); i++) {
			if (data->second[i] < yTickStart || i * classWidth < xTickStart) continue;
			graphs[index] = sf::VertexArray(sf::Quads, 4 * (data->second.size() - i));
			totalVertexAmount += 4 * (data->second.size() - i);
			break;
		}

		for (int i = 0; i < data->second.size(); i++) {
			if (data->second[i] < yTickStart || i * classWidth < xTickStart) continue;
			float width = xTickSpacing / (xScale * datasets.size());
			float height = data->second[i] * yTickSpacing / yScale;
			float x = graphXPosition + width * (i * datasets.size() + index);
			float y = graphYPosition + graphHeight - height;
			graphs[index][i * 4].position = sf::Vector2f(x, y + height);
			graphs[index][i * 4 + 1].position = sf::Vector2f(x, y);
			graphs[index][i * 4 + 2].position = sf::Vector2f(x + width, y);
			graphs[index][i * 4 + 3].position = sf::Vector2f(x + width, y + height);
			for (int j = 0; j < 4; j++) {
				graphs[index][i * 4 + j].color = colors[data->first];
				outline.append(graphs[index][i * 4 + j]);
				outline[outline.getVertexCount() - 1].color = sf::Color::Black;
			}
		}
		outline.append(graphs[index][0]);
		index++;
	}
}

void Histogram::DrawGraph(sf::RenderWindow& window, bool drawGrid) {
	window.draw(boundingBox);

	// Grid
	if(drawGrid) window.draw(grid);

	// Ticks
	TextRenderer::SetFontSize(tickFontSize);
	window.draw(tick);
	for (int i = 0; i < xTickAmount; i++) {
		TextRenderer::SetString(RemoveTrailingZeroes(std::to_string((xScale * i + xTickStart) * classWidth)));
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

	// Rectangles
	for (auto& graph : graphs) window.draw(graph);
	window.draw(outline);

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
}