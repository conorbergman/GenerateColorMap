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

	ColorMapContainer color_map(sf::Vector2f(40,50), sf::Vector2f(720,500), font);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			color_map.update(event, &window);
		}

		// Draw Window 
		window.clear();
		color_map.draw(&window);
		window.display();
	}

	return 0;
}