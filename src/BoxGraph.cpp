#include "BoxGraph.h"

void BoxGraph::UpdateGraphSettings() {
	boundingBox = sf::RectangleShape(sf::Vector2f(graphWidth, graphHeight));
	boundingBox.setFillColor(backgroundColor);
	boundingBox.setOutlineColor(outlineColor);
	boundingBox.setOutlineThickness(1);
	boundingBox.setPosition(graphXPosition, graphYPosition);

	xTickAmount = graphWidth / xTickSpacing + 1;
	yTickAmount = graphHeight / yTickSpacing + 1;

	tick.clear();
	grid.clear();
	for (int i = 0; i < xTickAmount; i++) {
		tick.append(sf::Vertex(
			sf::Vector2f(graphXPosition + i * xTickSpacing, graphYPosition + graphHeight - 10),
			sf::Color::Black
		));
		tick.append(tick[tick.getVertexCount() - 1]);
		tick[tick.getVertexCount() - 1].position.y += 20;

		grid.append(sf::Vertex(
			sf::Vector2f(graphXPosition + i * xTickSpacing, graphYPosition + graphHeight),
			gridColor
		));
		grid.append(grid[grid.getVertexCount() - 1]);
		grid[grid.getVertexCount() - 1].position.y -= graphHeight;
	}

	for (int i = 0; i < yTickAmount; i++) {
		tick.append(sf::Vertex(
			sf::Vector2f(graphXPosition - 10, graphYPosition + graphHeight - i * yTickSpacing),
			sf::Color::Black
		));
		tick.append(tick[tick.getVertexCount() - 1]);
		tick[tick.getVertexCount() - 1].position.x += 20;

		grid.append(sf::Vertex(
			sf::Vector2f(graphXPosition, graphYPosition + graphHeight - i * yTickSpacing),
			gridColor
		));
		grid.append(grid[grid.getVertexCount() - 1]);
		grid[grid.getVertexCount() - 1].position.x += graphWidth;
	}
}

void BoxGraph::DrawText(sf::RenderWindow& window) {
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
}

void BoxGraph::DrawLegend(sf::RenderWindow& window) {
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