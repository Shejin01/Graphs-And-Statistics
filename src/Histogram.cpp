#include "Histogram.h"

void Histogram::CreateDataSet(std::string datasetName, sf::Color color) {
	datasets.insert({ datasetName, std::vector<float>()});
	colors.insert({ datasetName, color });
}

void Histogram::AddData(std::string datasetName, float value) {
	datasets[datasetName].push_back(value);
}

void Histogram::UpdateGraphSettings() {
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

void Histogram::DrawGraph(sf::RenderWindow& window) {
	window.draw(boundingBox);

	// Ticks
	TextRenderer::SetFontSize(tickFontSize);
	window.draw(tick);
	for (int i = 0; i < xTickAmount; i++) {
		TextRenderer::RenderText(
			RemoveTrailingZeroes(std::to_string((xScale * i + xTickStart) * classWidth)),
			graphXPosition + i * xTickSpacing - (TextRenderer::text.getLocalBounds().width * 0.5), graphYPosition + graphHeight - 10 + 20
		);
	}

	for (int i = 0; i < yTickAmount; i++) {
		TextRenderer::RenderText(
			RemoveTrailingZeroes(std::to_string(yScale * i + yTickStart)),
			graphXPosition - 10 - (TextRenderer::text.getLocalBounds().width) - 5, graphYPosition + graphHeight - i * yTickSpacing - (TextRenderer::text.getLocalBounds().height)
		);
	}

	TextRenderer::SetFontSize(labelFontSize);
	TextRenderer::RenderText(xLabel, graphXPosition + graphWidth * 0.5 - (TextRenderer::text.getLocalBounds().width * 0.5), graphYPosition + graphWidth + 40);
	TextRenderer::text.setRotation(90);
	TextRenderer::RenderText(yLabel, graphXPosition - 40, graphYPosition + graphHeight * 0.5 - (TextRenderer::text.getLocalBounds().width * 0.5));
	TextRenderer::text.setRotation(0);
	TextRenderer::SetFontSize(headingFontSize);
	TextRenderer::RenderText(heading, graphXPosition + graphWidth * 0.5 - TextRenderer::text.getLocalBounds().width * 0.5, graphYPosition - TextRenderer::text.getLocalBounds().height - 20);

	// Rectangles
	sf::RectangleShape rect;
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
	int index = 0;
	for (auto data = datasets.begin(); data != datasets.end(); data++) {
		rect.setFillColor(colors[data->first]);
		for (int i = 0; i < data->second.size(); i++) {
			if (data->second[i] < yTickStart || i * classWidth < xTickStart) continue;
			rect.setSize(sf::Vector2f(xTickSpacing / (xScale * datasets.size()), data->second[i] * yTickSpacing / yScale));
			rect.setPosition(graphXPosition + rect.getSize().x * (i * datasets.size() + index), graphYPosition + graphHeight - rect.getSize().y);
			window.draw(rect);
		}
		index++;
	}

	// Legend
	sf::RectangleShape icon(sf::Vector2f(legendFontSize, legendFontSize));
	icon.setOutlineColor(sf::Color::Black);
	icon.setOutlineThickness(1);
	TextRenderer::SetFontSize(legendFontSize);
	index = 0;
	for (auto color = colors.begin(); color != colors.end(); color++) {
		icon.setFillColor(color->second);
		icon.setPosition(graphXPosition + graphWidth - 100, graphYPosition + 20 + index * 30);
		window.draw(icon);
		TextRenderer::RenderText(color->first, icon.getPosition().x + 20, icon.getPosition().y);
		index++;
	}
}