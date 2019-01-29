#ifndef COLOR_BAR
#define COLOR_BAR

#pragma once

#include "includes.h"

class ColorBar
{
private:
	int BAND_WIDTH = 600, NUMBER = 100, PANE_WIDTH = BAND_WIDTH / NUMBER;
public:
	std::vector<sf::RectangleShape> panes;


	ColorBar(sf::Vector2f position) 
	{
		panes.reserve(NUMBER);

		for (int i = 0; i < NUMBER; i++)
		{
			panes.push_back(sf::RectangleShape(sf::Vector2f(PANE_WIDTH, 8 * PANE_WIDTH)));
			panes[i].setFillColor(sf::Color(255 - i, i, 100));
			panes[i].setPosition(position.x + PANE_WIDTH * i, position.y);
		}
	}

	void HandleMouseEvents(sf::Vector2i mouse_position, bool flags[], int* selected_rect, std::string* color_text)
	{
		// check rectangles

		for (int i = 0; i < NUMBER; i++)
		{
			sf::FloatRect rect;
			rect = panes[i].getGlobalBounds();
			if (rect.contains(mouse_position.x, mouse_position.y))
			{
				if (*selected_rect != -1)
				{
					panes[*selected_rect].setOutlineThickness(0);
					panes[i].setOutlineThickness(1);
					*selected_rect = i;
				}
				
				*color_text = "r:";
				*color_text += std::to_string(panes[i].getFillColor().r);
				*color_text += " g:";
				*color_text += std::to_string(panes[i].getFillColor().g);
				*color_text += " b:";
				*color_text += std::to_string(panes[i].getFillColor().b);
				flags[NOT_SELECTED] = 0;
				flags[KEYBOARD_INPUT] = 0;
			}
		}
	}

	void Draw(sf::RenderWindow * window)
	{
		for (int i = 0; i < NUMBER; i++)
		{
			window->draw(panes[i]);
		}
		
	}
};



#endif