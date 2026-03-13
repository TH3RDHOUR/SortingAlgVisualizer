#ifndef DRAW_VECTOR_H
#define DRAW_VECTOR_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

void drawVector(const std::vector<int>& arr, sf::RenderWindow& window, int currentIndex1, 
                int currentIndex2, int sortedStart, bool sorting, bool sorted);

#endif