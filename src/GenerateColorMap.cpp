#include <iostream>

#include "ColorMapContainer.h"

int main()
{
	const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
	int NUMBER = 500;
	bool flags[2] = {0, 1};
	// Create main window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Generate Color Map");
	window.setKeyRepeatEnabled(0);

	std::vector<int> keyboard_values;
	sf::Font font;
	font.loadFromFile("res/fonts/arial.ttf");
	std::string color_text = "";
	std::string button_text = "";
	sf::Text text(color_text, font);
	sf::Text rgb_text(button_text, font);
	rgb_text.setPosition(sf::Vector2f(7 * WINDOW_WIDTH / 8, 5 * WINDOW_HEIGHT / 6));

	ColorMapContainer color_map(sf::Vector2f(40,50), sf::Vector2f(720,500), font);


	while (window.isOpen())
	{
		
		// check mouse input
		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{	
			sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
			
			colorBar.handleMouseEvents(mouse_position);
			rgbInput.handleMouseEvent(mouse_position);

			if (flags[NOT_SELECTED])
			{
				color_text = "";
				colorBar.setCurrSelected(-1);
				flags[KEYBOARD_INPUT] = 0;
			}
			text.setString(color_text);
		}
		*/

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			color_map.update(event, &window);
		}

		button_text = "";
		for (int key : keyboard_values)
		{
			button_text +=  std::to_string(key);
		}
		rgb_text.setString(button_text);

		// Draw Window 
		window.clear();
		
		color_map.draw(&window);

		window.draw(text);
		window.draw(rgb_text);
		window.display();
	}

	return 0;
}