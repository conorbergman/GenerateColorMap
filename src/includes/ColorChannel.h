#ifndef COLOR_CHANNEL
#define COLOR_CHANNEL

#pragma once

#include "includes.h"
#include "ColorBar.h"


class ColorChannel
{
private:
	int ARRAY_COUNT;
	float spacing = 1.0f;
	int selected = -1;

public:
	sf::RectangleShape container;
	sf::VertexArray value_line;
	std::vector<int> values;
	sf::Vector2f channel_position;
	sf::Vector2f channel_size;
	int CHANNEL;

	ColorChannel(sf::Vector2f position, sf::Vector2f size, int channel, int number=100)
	{
		ARRAY_COUNT = number;
		CHANNEL = channel;
		container = sf::RectangleShape(size);
		container.setPosition(position);
		container.setFillColor(sf::Color(0,0,0));

		spacing = size.x / (ARRAY_COUNT - 1.0);

		value_line = sf::VertexArray(sf::LineStrip, ARRAY_COUNT);
		values.reserve(ARRAY_COUNT);

		float y_val = position.y + (size.y / 2);
		for (int i = 0; i < ARRAY_COUNT; i++)
		{
			values.push_back(y_val);
			value_line[i] = sf::Vector2f(position.x + (spacing * i), y_val);
		}
		
		channel_position = position;
		channel_size = size;
	}

	bool inFocus(sf::Vector2i mouse_position)
	{
		return container.getGlobalBounds().contains(mouse_position.x, mouse_position.y);
	}

	void handleMouseEvents(sf::Vector2i mouse_position, ColorBar* color_bar)
	{
		
		// handle mouse events
		if (inFocus(mouse_position))
		{
			int xpos = ((int)((mouse_position.x - channel_position.x) / spacing));
			color_bar->setCurrSelected(xpos);

			if (color_bar->isNode(xpos))
			{
				int ypos = channel_position.y + ((255.0f - color_bar->getPaneColorChannel(xpos, CHANNEL)) * channel_size.y / 255.0f);
				if (fabs(mouse_position.y - ypos) < 5)
				{
					int new_color = 255 - ((float)mouse_position.y - channel_position.y) * 255.0f / channel_size.y;
					color_bar->setNodeColorChannel(xpos, new_color, CHANNEL);

				}
			}
		}
	}

	void update(ColorBar * colorbar)
	{
		for (int i = 0; i < ARRAY_COUNT; i++)
		{
			values[i] = colorbar->getPaneColorChannel(i, CHANNEL);
			value_line[i].position.y = channel_position.y + (channel_size.y * (1 - (values[i] / 255.0)));
		}

		selected = colorbar->getCurrSelected();
	}

	void draw(sf::RenderWindow * window)
	{
		window->draw(container);
		window->draw(value_line);
		if (selected != -1)
		{
			sf::RectangleShape cursor_line = sf::RectangleShape(sf::Vector2f(2, channel_size.y));
			cursor_line.setPosition(value_line[selected].position.x, channel_position.y);
			cursor_line.setFillColor(sf::Color(255, 255, 255, 100));
			window->draw(cursor_line);
		}
	}
};


#endif // !COLOR_CHANNEL


