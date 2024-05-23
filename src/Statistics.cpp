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