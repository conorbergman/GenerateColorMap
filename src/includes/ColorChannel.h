#ifndef COLOR_CHANNEL
#define COLOR_CHANNEL

#pragma once

#include "includes.h"

struct point {
	float x;
	float y;
};

class ColorChannel
{
private:
	int ARRAY_COUNT = 101;
	int spacing = 1;

public:
	sf::RectangleShape container;
	sf::VertexArray value_line;
	std::vector<point> values;
	sf::Vector2f channel_position;

	ColorChannel(sf::Vector2f position, sf::Vector2f size)
	{
		container = sf::RectangleShape(size);
		container.setPosition(position);
		container.setFillColor(sf::Color(55,57,67));

		spacing = size.x / (ARRAY_COUNT - 1);

		value_line = sf::VertexArray(sf::LineStrip, ARRAY_COUNT);
		values.reserve(ARRAY_COUNT);

		float y_val = position.y + (size.y / 2);
		for (int i = 0; i < ARRAY_COUNT; i++)
		{
			values.push_back(point{ position.x + (spacing * i), y_val });
			value_line[i] = sf::Vector2f(values[i].x, y_val);
		}
		
		channel_position = position;
	}

	void DrawChannel(sf::RenderWindow * window)
	{
		window->draw(container);
		window->draw(value_line);
	}
};


#endif // !COLOR_CHANNEL


