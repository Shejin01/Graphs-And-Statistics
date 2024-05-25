#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

#define PI 3.1415926535

std::string RemoveTrailingZeroes(std::string number);
void RenderText(std::string text, int fontSize, sf::Vector2f position, sf::RenderWindow& window);

class Point {
public:
	float x, y;
	std::string label;
	Point(float x, float y, std::string label = "") : x(x), y(y), label(label) {}
};