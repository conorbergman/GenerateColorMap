#ifndef INPUT_BOX
#define INPUT_BOX

#pragma once

#include "includes.h"

class InputBox
{
private:
	sf::Vector2f margins = sf::Vector2f(5,5);
	int MAX_INPUT_LENGTH = 6;
public:
	sf::RectangleShape container;
	sf::RectangleShape input_container;
	std::string input_string = "";
	sf::Text label_text;
	bool in_focus = 0;
	sf::Vector2f container_position;
	sf::Vector2f input_container_position;
	sf::Vector2f container_size;
	sf::Vector2f input_container_size;
	sf::Font font;
	std::vector<int> input_vector;

	InputBox(sf::Vector2f position, sf::Font text_font, std::string label_string, sf::Vector2f size=sf::Vector2f(100, 50))
	{
		font = text_font;
		label_text = sf::Text(label_string, font);
		label_text.setPosition(position + sf::Vector2f(0,2));
		// create main container
		container = sf::RectangleShape(size);
		container.setPosition(position);
		container.setFillColor(sf::Color(55,57,67));
		// create input container
		input_container_position = sf::Vector2f(position.x + margins.x + label_text.getGlobalBounds().width, position.y + margins.y);
		input_container_size = size - margins - margins - sf::Vector2f(label_text.getGlobalBounds().width, 0);
		input_container = sf::RectangleShape(input_container_size);
		input_container.setPosition(input_container_position);
		input_container.setFillColor(sf::Color(0, 0, 0));

		
		container_position = position;
		container_size = size;
	}

	void handleMouseEvents(sf::Vector2i mouse_position)
	{
		in_focus = input_container.getGlobalBounds().contains(mouse_position.x, mouse_position.y);
	}

	bool isVisible()
	{
		return 1;
	}

	sf::Color inputToColor()
	{
		if (input_vector.size() != 6)
		{
			return sf::Color(255,255,255);
		}
		int r, g, b;
		r = 16 * input_vector[0] + input_vector[1];
		g = 16 * input_vector[2] + input_vector[3];
		b = 16 * input_vector[4] + input_vector[5];
		return sf::Color(r,g,b);
	}

	void update(sf::Event event, ColorBar* color_bar)
	{
		if (in_focus)
		{
			if (input_string.length() < MAX_INPUT_LENGTH)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Num1:
					input_vector.push_back(1);
					input_string += std::to_string(1);
					break;
				case sf::Keyboard::Num2:
					input_vector.push_back(2);
					input_string += std::to_string(2);
					break;
				case sf::Keyboard::Num3:
					input_vector.push_back(3);
					input_string += std::to_string(3);
					break;
				case sf::Keyboard::Num4:
					input_vector.push_back(4);
					input_string += std::to_string(4);
					break;
				case sf::Keyboard::Num5:
					input_vector.push_back(5);
					input_string += std::to_string(5);
					break;
				case sf::Keyboard::Num6:
					input_vector.push_back(6);
					input_string += std::to_string(6);
					break;
				case sf::Keyboard::Num7:
					input_vector.push_back(7);
					input_string += std::to_string(7);
					break;
				case sf::Keyboard::Num8:
					input_vector.push_back(8);
					input_string += std::to_string(8);
					break;
				case sf::Keyboard::Num9:
					input_vector.push_back(9);
					input_string += std::to_string(9);
					break;
				case sf::Keyboard::Num0:
					input_vector.push_back(0);
					input_string += std::to_string(0);
					break;
				case sf::Keyboard::A:
					input_vector.push_back(10);
					input_string += "a";
					break;
				case sf::Keyboard::B:
					input_vector.push_back(11);
					input_string += "b";
					break;
				case sf::Keyboard::C:
					input_vector.push_back(12);
					input_string += "c";
					break;
				case sf::Keyboard::D:
					input_vector.push_back(13);
					input_string += "d";
					break;
				case sf::Keyboard::E:
					input_vector.push_back(14);
					input_string += "e";
					break;
				case sf::Keyboard::F:
					input_vector.push_back(15);
					input_string += "f";
					break;
				case sf::Keyboard::BackSpace:
					if (input_string.length() > 0)
					{
						input_vector.pop_back();
						input_string.pop_back();
					}
					break;
				default:
					break;
				}
			} // end if strlen < MAX_INPUT
			else
			{
				switch (event.key.code)
				{
				case sf::Keyboard::BackSpace:
					if (input_string.length() > 0)
					{
						input_vector.pop_back();
						input_string.pop_back();
					}
					break;
				case sf::Keyboard::Enter:
					if (color_bar->getCurrSelected() != -1)
					{
						color_bar->addNode(color_bar->getCurrSelectedDistance(), inputToColor());
					}
				default:
					break;
				}
			}
		}
	}

	void draw(sf::RenderWindow * window)
	{
		window->draw(container);
		window->draw(input_container);
		window->draw(label_text);
		sf::Text input_text(input_string, font);
		input_text.setFillColor(sf::Color(255, 255, 255));
		input_text.setPosition(input_container_position);
		window->draw(input_text);
	}
};

#endif
