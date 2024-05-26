#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

#define PI 3.1415926535

std::string RemoveTrailingZeroes(std::string number);

class Graph {
public:
	std::unordered_map<std::string, sf::Color> colors;
	std::string heading = "";

	virtual void UpdateGraph() = 0;
	virtual void UpdateGraphSettings() = 0;
};