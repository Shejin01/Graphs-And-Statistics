#include "BoxGraph.h"

void BoxGraph::UpdateGraphSettings() {
	boundingBox = sf::RectangleShape(sf::Vector2f(graphWidth, graphHeight));
	boundingBox.setFillColor(backgroundColor);
	boundingBox.setOutlineColor(outlineColor);
	boundingBox.setOutlineThickness(1);
	boundingBox.setPosition(graphXPosition, graphYPosition);

	xTickAmount = graphWidth / xTickSpacing;
	yTickAmount = graphHeight / yTickSpacing;

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