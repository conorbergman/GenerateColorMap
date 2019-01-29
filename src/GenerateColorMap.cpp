#include <iostream>

#include "ColorChannel.h"
#include "ColorBar.h"

int main()
{
	const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600, BAND_WIDTH = 600, NUMBER = 100;
	const int OFFSET = (WINDOW_WIDTH - BAND_WIDTH) / 2;
	const int BOX_WIDTH = BAND_WIDTH / NUMBER;
	const int NUM_BUTTONS = 2;
	int selected_rect = -1;
	bool keyboard_input = 0;
	// Create main window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Generate Color Map");
	window.setKeyRepeatEnabled(0);

	std::vector<sf::RectangleShape> rectangles;
	std::vector<sf::RectangleShape> buttons;
	std::vector<int> keyboard_values;
	rectangles.reserve(NUMBER);
	buttons.reserve(NUM_BUTTONS);
	sf::Font font;
	font.loadFromFile("res/fonts/arial.ttf");
	std::string color_text = "";
	std::string button_text = "";
	sf::Text text(color_text, font);
	sf::Text rgb_text(button_text, font);
	rgb_text.setPosition(sf::Vector2f(7 * WINDOW_WIDTH / 8, 5 * WINDOW_HEIGHT / 6));

	ColorChannel rChannel(sf::Vector2f(50, 300), sf::Vector2f(700, 90));
	ColorChannel gChannel(sf::Vector2f(50, 400), sf::Vector2f(700, 90));
	ColorChannel bChannel(sf::Vector2f(50, 500), sf::Vector2f(700, 90));


	for (int i = 0; i < NUMBER; i++)
	{
		sf::RectangleShape r = sf::RectangleShape(sf::Vector2f(BOX_WIDTH, 8 * BOX_WIDTH));
		r.setFillColor(sf::Color(255-i, i, 100));
		r.setPosition(OFFSET + BOX_WIDTH * i, 200.0f);
		rectangles.push_back(r);
	}

	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		sf::RectangleShape b = sf::RectangleShape(sf::Vector2f(50, 50));
		b.setFillColor(sf::Color(100,100,100));
		b.setPosition(100 + i * 200, 400);
		buttons.push_back(b);
	}

	while (window.isOpen())
	{
		
		// check mouse input
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{	
			sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
			// check rectangles
			bool not_selected = 1;
			
			for (int i = 0; i < NUMBER; i++)
			{
				sf::FloatRect rect;
				rect = rectangles[i].getGlobalBounds();
				if (rect.contains(mouse_position.x, mouse_position.y))
				{
					//std::cout << "x: " << mouse_position.x << " y: " << mouse_position.y << std::endl;
					selected_rect = i;
					rectangles[i].setOutlineThickness(1);
					color_text = "r:";
					color_text += std::to_string(rectangles[i].getFillColor().r);
					color_text += " g:";
					color_text += std::to_string(rectangles[i].getFillColor().g);
					color_text += " b:";
					color_text += std::to_string(rectangles[i].getFillColor().b);
					not_selected = 0;
					keyboard_input = 0;
				}
				else
				{
					rectangles[i].setOutlineThickness(0);
				}
			}
			
			// check buttons
			for (int i = 0; i < NUM_BUTTONS; i++)
			{
				sf::FloatRect rect = buttons[i].getGlobalBounds();
				if (rect.contains(mouse_position.x, mouse_position.y))
				{
					if (selected_rect != -1)
						rectangles[selected_rect].setFillColor(sf::Color(255, 0, 255));
					not_selected = 0;
					keyboard_input = 1;
				}
			}

			if (not_selected)
			{
				color_text = "";
				selected_rect = -1;
				keyboard_input = 0;
			}
			text.setString(color_text);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (keyboard_input)
				{
					switch (event.key.code)
					{
					case sf::Keyboard::Num1:
						keyboard_values.push_back(1);
						break;
					case sf::Keyboard::Num2:
						keyboard_values.push_back(2);
						break;
					case sf::Keyboard::Num3:
						keyboard_values.push_back(3);
						break;
					case sf::Keyboard::Num4:
						keyboard_values.push_back(4);
						break;
					case sf::Keyboard::Num5:
						keyboard_values.push_back(5);
						break;
					case sf::Keyboard::Num6:
						keyboard_values.push_back(6);
						break;
					case sf::Keyboard::Num7:
						keyboard_values.push_back(7);
						break;
					case sf::Keyboard::Num8:
						keyboard_values.push_back(8);
						break;
					case sf::Keyboard::Num9:
						keyboard_values.push_back(9);
						break;
					case sf::Keyboard::Num0:
						keyboard_values.push_back(0);
						break;
					default:
						break;
					}
				}
			}
		}

		button_text = "";
		for (int key : keyboard_values)
		{
			button_text +=  std::to_string(key);
		}
		rgb_text.setString(button_text);

		window.clear();
		for (sf::RectangleShape rectangle : rectangles)
		{
			window.draw(rectangle);
		}
		for (sf::RectangleShape button : buttons)
		{
			window.draw(button);
		}

		rChannel.DrawChannel(&window);
		gChannel.DrawChannel(&window);
		bChannel.DrawChannel(&window);
		window.draw(text);
		window.draw(rgb_text);
		window.display();
	}

	return 0;
}