#ifndef TEXT_DISPLAY
#define TEXT_DISPLAY

#pragma once

#include "includes.h"
#include "ColorBar.h"

class TextDisplay
{
private:
	std::string color_text = "";
	sf::Font font;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Text text;
public:
	TextDisplay(sf::Vector2f _position, sf::Vector2f _size, sf::Font _font)
	{
		position = _position;
		size = _size;
		font = _font;
		
		text = sf::Text("", font);
		text.setPosition(position);
	}

	void update(ColorBar * colorbar)
	{
		sf::Color curr = colorbar->getPaneColor(colorbar->getCurrSelected());
		color_text = "r:"
					+ std::to_string(curr.r)
					+ " g:"
					+ std::to_string(curr.g)
					+ " b:"
					+ std::to_string(curr.b);
		text.setString(color_text);
	}

	void draw(sf::RenderWindow * window)
	{
		window->draw(text);
	}
};

#endif