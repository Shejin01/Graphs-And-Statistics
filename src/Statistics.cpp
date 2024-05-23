#include "Statistics.h"

std::string RemoveTrailingZeroes(std::string number) {
	int size = static_cast<int>(number.length());
	for (int i = 0; i < size; i++) {
		if (number[i] == '.') {
			number.erase(number.begin() + i + 2, number.end());
			break;
		}
	}
	return number;
}

Point::Point(float x, float y, std::string label) : x(x), y(y), label(label) {}

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
	boundingBox = sf::RectangleShape(sf::Vector2f(graphWidth, graphHeight));
	boundingBox.setFillColor(sf::Color::White);
	boundingBox.setOutlineColor(sf::Color::Black);
	boundingBox.setOutlineThickness(1);
	boundingBox.setPosition(graphXPosition, graphYPosition);

	xTickAmount = graphWidth / xTickSpacing, yTickAmount = graphHeight / yTickSpacing;
	
	tick.clear();
	for (auto& graph : graphs) graph.clear();

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
void LineGraph::DrawGraph(sf::RenderWindow& window, bool drawPoints) {
	window.draw(boundingBox);

	// Ticks
	text.setCharacterSize(tickFontSize);
	window.draw(tick);
	for (int i = 0; i < xTickAmount; i++) {
		text.setString(RemoveTrailingZeroes(std::to_string(xScale * i + xTickStart)));
		text.setPosition(graphXPosition + i * xTickSpacing - (text.getLocalBounds().width*0.5), graphYPosition + graphHeight - 10 + 20);
		window.draw(text);
	}

	for (int i = 0; i < yTickAmount; i++) {
		text.setString(RemoveTrailingZeroes(std::to_string(yScale * i + yTickStart)));
		text.setPosition(graphXPosition - 10 - (text.getLocalBounds().width)-5, graphYPosition + graphHeight - i * yTickSpacing - (text.getLocalBounds().height));
		window.draw(text);
	}

	text.setCharacterSize(labelFontSize);
	text.setString(xLabel);
	text.setPosition(graphXPosition + graphWidth * 0.5 - (text.getLocalBounds().width*0.5), graphYPosition + graphWidth + 40);
	window.draw(text);
	text.setString(yLabel);
	text.setPosition(graphXPosition - 40, graphYPosition + graphHeight * 0.5 - (text.getLocalBounds().width*0.5));
	text.setRotation(90);
	window.draw(text);
	text.setRotation(0);
	text.setCharacterSize(headingFontSize);
	text.setString(heading);
	text.setPosition(graphXPosition + graphWidth*0.5 - text.getLocalBounds().width*0.5, graphYPosition - text.getLocalBounds().height - 20);
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


PieChart::PieChart(const char* fontLocation) {
	if (!font.loadFromFile(fontLocation)) {
		std::cout << "Error while loading font.\n";
	}
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
}
void PieChart::AddData(std::string name, float value, sf::Color color) {
	data.insert({ name, value });
	colors.insert({ name, color });
}
void PieChart::DrawGraph(sf::RenderWindow& window, bool showPercentage) {
	float total = 0;
	for (auto i = data.begin(); i != data.end(); i++) {
		total += i->second;
	}

	sf::ConvexShape shape;
	float angle = 0;
	float anglePerPoint = 2 * PI / pieChartPointCount;
	for (auto value = data.begin(); value != data.end(); value++) {
		float percentage = value->second / total;
		int pointCount = ceil(pieChartPointCount * percentage) + 1;
		shape.setPointCount(pointCount);
		shape.setFillColor(colors[value->first]);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1);
		shape.setPoint(0, sf::Vector2f(graphXPosition, graphYPosition));
		float endAngle = 2 * PI * percentage + angle;
		float x, y;
		for (int i = 1; i < pointCount-1; i++) {
			x = graphXPosition + radius * cos(angle);
			y = graphYPosition + radius * sin(angle);
			shape.setPoint(i, sf::Vector2f(x, y));
			angle += anglePerPoint;
		}
		angle = endAngle;
		x = graphXPosition + radius * cos(angle);
		y = graphYPosition + radius * sin(angle);
		shape.setPoint(pointCount - 1, sf::Vector2f(x, y));

		window.draw(shape);
	}

	text.setCharacterSize(headingFontSize);
	text.setString(heading);
	text.setPosition(graphXPosition - text.getLocalBounds().width * 0.5, graphYPosition - radius - text.getLocalBounds().height*2);
	window.draw(text);

	// Legend
	sf::RectangleShape icon(sf::Vector2f(legendFontSize, legendFontSize));
	icon.setOutlineColor(sf::Color::Black);
	icon.setOutlineThickness(1);
	text.setCharacterSize(legendFontSize);
	int index = 0;
	for (auto color = colors.begin(); color != colors.end(); color++) {
		text.setString(color->first);
		icon.setFillColor(color->second);
		icon.setPosition(graphXPosition + radius + 10, graphYPosition - radius + legendFontSize + 5 + index * 30);
		text.setPosition(icon.getPosition().x + legendFontSize + 5, icon.getPosition().y);
		window.draw(icon);
		window.draw(text);
		index++;
	}

	// Percentage Text
	text.setCharacterSize(percentFontSize);
	angle = 0;
	for (auto value = data.begin(); value != data.end(); value++) {
		float percentage = value->second / total;
		text.setString(RemoveTrailingZeroes(std::to_string(percentage*100)) + "%");
		float percentAngle = angle + PI * percentage;
		float x = graphXPosition + radius*0.5 * cos(percentAngle);
		float y = graphYPosition + radius*0.5 * sin(percentAngle);
		angle += 2 * PI * percentage;
		text.setPosition(x, y);
		window.draw(text);
	}
}

Histogram::Histogram(const char* fontLocation) {
	if (!font.loadFromFile(fontLocation)) {
		std::cout << "Error while loading font.\n";
	}
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
}
void Histogram::AddData(float value) {
	data.push_back(value);
}
void Histogram::DrawGraph(sf::RenderWindow& window) {
	sf::RectangleShape boundingBox(sf::Vector2f(graphWidth, graphHeight));
	boundingBox.setFillColor(sf::Color::White);
	boundingBox.setOutlineColor(sf::Color::Black);
	boundingBox.setOutlineThickness(1);
	boundingBox.setPosition(graphXPosition, graphYPosition);
	window.draw(boundingBox);

	// Ticks
	text.setCharacterSize(tickFontSize);
	int xTickAmount = graphWidth / xTickSpacing, yTickAmount = graphHeight / yTickSpacing;
	sf::VertexArray tick(sf::LinesStrip, 2);
	tick[0].color = sf::Color::Black;
	tick[1].color = sf::Color::Black;
	tick[0].position.y = graphYPosition + graphHeight - 10;
	tick[1].position.y = graphYPosition + graphHeight + 10;
	for (int i = 0; i < xTickAmount; i++) {
		tick[0].position.x = graphXPosition + i * xTickSpacing;
		tick[1].position.x = graphXPosition + i * xTickSpacing;
		window.draw(tick);
		text.setString(RemoveTrailingZeroes(std::to_string((xScale * i + xTickStart)*classWidth)));
		text.setPosition(tick[0].position.x - (text.getLocalBounds().width * 0.5), tick[0].position.y + 20);
		window.draw(text);
	}

	tick[0].position.x = graphXPosition - 10;
	tick[1].position.x = graphXPosition + 10;
	for (int i = 0; i < yTickAmount; i++) {
		tick[0].position.y = graphYPosition + graphHeight - i * yTickSpacing;
		tick[1].position.y = graphYPosition + graphHeight - i * yTickSpacing;
		window.draw(tick);
		text.setString(RemoveTrailingZeroes(std::to_string(yScale * i + yTickStart)));
		text.setPosition(tick[0].position.x - (text.getLocalBounds().width) - 5, tick[0].position.y - (text.getLocalBounds().height));
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

	// Rectangles
	sf::RectangleShape rect;
	rect.setFillColor(color);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
	for (int i = 0; i < data.size(); i++) {
		if (data[i] < yTickStart || i * classWidth < xTickStart) continue;
		rect.setSize(sf::Vector2f(xTickSpacing / xScale , data[i] * yTickSpacing / yScale));
		rect.setPosition(graphXPosition + rect.getSize().x * i, graphYPosition + graphHeight - rect.getSize().y);
		window.draw(rect);
	}
}