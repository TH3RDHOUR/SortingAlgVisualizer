#ifndef DRAW_VECTOR_H
#define DRAW_VECTOR_H

#include <SFML/Graphics.hpp>
#include "sorting/visual_state.h"

void drawVector(std::vector<int>& arr, const VisualState& state, sf::RenderWindow& window);

#endif