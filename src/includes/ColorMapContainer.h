#ifndef COLOR_MAP_CONTAINER
#define COLOR_MAP_CONTAINER

#pragma once

#include "includes.h"
#include "ColorBar.h"
#include "ColorChannel.h"
#include "InputBox.h"

class ColorMapContainer
{
private:
	int NUMBER = 500;

	ColorChannel* redChannel;
	ColorChannel* greenChannel;
	ColorChannel* blueChannel;

	ColorBar* colorBar;

	InputBox* inputBox;

	sf::RectangleShape container;

	sf::Vector2f position;
	sf::Vector2f size;
public:


	ColorMapContainer(sf::Vector2f position_, sf::Vector2f size_, sf::Font font)
	{
		position = position_;
		size = size_;

		sf::Color start_color(255, 255, 255);
		sf::Color end_color(0, 0, 0);

		// initialize main container
		container = sf::RectangleShape(size);
		container.setPosition(position);
		container.setFillColor(sf::Color(55, 57, 67));

		// initialize color bar
		colorBar = new ColorBar(sf::Vector2f(position.x + 10, position.y + 100), sf::Color(255, 255, 255), sf::Color(0, 0, 0), NUMBER);
		// initialize color channels
		redChannel = new ColorChannel(sf::Vector2f(position.x + 10, position.y + 200), sf::Vector2f(700, 90), RED, NUMBER);
		greenChannel = new ColorChannel(sf::Vector2f(position.x + 10, position.y + 300), sf::Vector2f(700, 90), GREEN, NUMBER);
		blueChannel = new ColorChannel(sf::Vector2f(position.x + 10, position.y + 400), sf::Vector2f(700, 90), BLUE, NUMBER);
		// initialize input box
		inputBox = new InputBox(sf::Vector2f(100, 100), font, "#", sf::Vector2f(160, 45));
	}

	void update(sf::Event event, sf::RenderWindow * window)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// handle color channel mouse events
			redChannel->handleMouseEvents(mouse_position, colorBar);
			greenChannel->handleMouseEvents(mouse_position, colorBar);
			blueChannel->handleMouseEvents(mouse_position, colorBar);
			// handle color bar mouse events
			colorBar->handleMouseEvents(mouse_position);
		}
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (inputBox->in_focus)
			{
				inputBox->update(event, colorBar);
				redChannel->handleMouseEvents(mouse_position, colorBar);
				greenChannel->handleMouseEvents(mouse_position, colorBar);
				blueChannel->handleMouseEvents(mouse_position, colorBar);
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// select / move node
				// if input box is visible, check if it contains mouse
				if (inputBox->isVisible())
				{
					inputBox->handleMouseEvents(mouse_position);
				}
				// handle color bar mouse events
				colorBar->handleMouseEvents(mouse_position);
				// handle color channel mouse events
				redChannel->handleMouseEvents(mouse_position, colorBar);
				greenChannel->handleMouseEvents(mouse_position, colorBar);
				blueChannel->handleMouseEvents(mouse_position, colorBar);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				// add nodes
				if (colorBar->inFocus(mouse_position) ||
					redChannel->inFocus(mouse_position) ||
					blueChannel->inFocus(mouse_position) ||
					greenChannel->inFocus(mouse_position))
				{
					colorBar->addNode(mouse_position.x, inputBox->inputToColor());
				}
			}
			break;
		default:
			break;
		}
		redChannel->update(colorBar);
		greenChannel->update(colorBar);
		blueChannel->update(colorBar);
	}

	void draw(sf::RenderWindow * window)
	{
		window->draw(container);
		colorBar->draw(window);
		redChannel->draw(window);
		greenChannel->draw(window);
		blueChannel->draw(window);
		inputBox->draw(window);
	}
};


#endif
