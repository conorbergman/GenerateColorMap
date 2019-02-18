#ifndef COLOR_BAR
#define COLOR_BAR

#pragma once

#include "includes.h"

struct node
{
	float position; // normalized position along spectrum
	sf::Color color;
	node * prev;
	node * next;
};

class ColorBar
{
private:
	const int BAND_WIDTH = 700;
	const int BAND_HEIGHT = 50;
	int NUMBER, curr_selected = -1;
	float PANE_WIDTH, TOLERANCE = 0.02;
	node head;
	node tail;
	node prev_node;
	node next_node;
public:
	std::vector<sf::RectangleShape> panes;
	sf::Vector2f position;

	ColorBar(sf::Vector2f position, sf::Color start_color = sf::Color(255, 255, 255), sf::Color end_color = sf::Color(0, 0, 0), int number = 100)
	{
		NUMBER = number;
		PANE_WIDTH = BAND_WIDTH / (float)NUMBER;

		panes.reserve(NUMBER);

		this->position = position;

		head = { 0,start_color,nullptr,&tail };
		tail = { 1,end_color,&head,nullptr };

		prev_node = head;
		next_node = tail;

		for (int i = 0; i < NUMBER; i++)
		{
			panes.push_back(sf::RectangleShape(sf::Vector2f(PANE_WIDTH, BAND_HEIGHT)));
			//panes[i].setFillColor(sf::Color(255 * ((NUMBER - i) / (float)NUMBER), 255 * (i / (float)NUMBER), 100));
			panes[i].setFillColor(calculateColor(&prev_node, &next_node, i / (float)NUMBER));
			panes[i].setPosition(position.x + PANE_WIDTH * i, position.y);
		}
	}

	sf::Color calculateColor(node* prev, node* next, float distance)
	{
		float increment = (distance - prev->position) / (next->position - prev->position);
		float r = prev->color.r + (next->color.r - prev->color.r) * increment;
		float g = prev->color.g + (next->color.g - prev->color.g) * increment;
		float b = prev->color.b + (next->color.b - prev->color.b) * increment;

		return sf::Color(r, g, b);
	}

	bool inFocus(sf::Vector2i mouse_position)
	{
		return mouse_position.x >= position.x && mouse_position.x <= (position.x + BAND_WIDTH)
			&& mouse_position.y >= position.y && mouse_position.y <= (position.y + BAND_HEIGHT);
	}

	void addNode(float mouse_position_x, sf::Color color)
	{
		float distance = ((mouse_position_x - position.x) / (float)BAND_WIDTH);
		std::cout << distance << std::endl;
		node* curr = &head;
		node* tmp;
		while ((distance > curr->position) && (curr->next != nullptr))
		{
			curr = curr->next;
		}
		// update existing node if it is selected
		if (fabs(distance - curr->position) < TOLERANCE) // check if within tolerance
		{
			curr->color = color;
		} 
		// otherwise create a new node before curr
		else
		{
			node* new_node = new node{ distance, color, nullptr, nullptr };
			tmp = curr->prev;
			if (tmp != nullptr)
			{
				tmp->next = new_node;
			}
			new_node->prev = tmp;
			new_node->next = curr;
			curr->prev = new_node;
		}
		updateColorBar();
	}

	void updateColorBar()
	{
		node* curr = &head;
		for (int i = 0; i < NUMBER; i++)
		{
			if ((i / (float)NUMBER) > curr->next->position)
			{
				curr = curr->next;
			}
			panes[i].setFillColor(calculateColor(curr, curr->next, i / (float)NUMBER));
		}
	}

	bool isNode(int index)
	{
		float distance = ((float)index) / NUMBER;
		node * curr = &head;
		while (curr != nullptr)
		{
			if (fabs(distance - curr->position) < TOLERANCE)
				return true;
			curr = curr->next;
		}
		return false;
	}

	node * getNode(int index)
	{
		float distance = ((float)index) / NUMBER;
		node * curr = &head;
		while (curr != nullptr)
		{
			if (fabs(distance - curr->position) < TOLERANCE)
				return curr;
			curr = curr->next;
		}
		return curr;
	}

	void setNodeColorChannel(int index, int color, int channel)
	{
		node* selected = getNode(index);
		switch (channel)
		{
		case RED:
			selected->color.r = color;
			break;
		case GREEN:
			selected->color.g = color;
			break;
		case BLUE:
			selected->color.b = color;
			break;
		default:
			break;
		}
		updateColorBar();
	}

	int getCurrSelected()
	{
		return curr_selected;
	}

	float getCurrSelectedDistance()
	{
		return curr_selected / (float) NUMBER;
	}

	sf::RectangleShape* getPaneAt(int p)
	{
		return &panes[p];
	}

	void setCurrSelected(int p)
	{
		curr_selected = p;
	}

	int getPaneColorChannel(int p, int channel)
	{
		switch (channel)
		{
		case RED:
			return panes[p].getFillColor().r;
		case GREEN:
			return panes[p].getFillColor().g;
		case BLUE:
			return panes[p].getFillColor().b;
		default:
			return panes[p].getFillColor().r;
		}
	}

	sf::Color getPaneColor(int p)
	{
		return panes[p].getFillColor();
	}

	void setPaneColor(int p, sf::Color color)
	{
		panes[p].setFillColor(color);
	}

	void setPaneColorChannel(int p, int color, int channel)
	{
		sf::Color new_color = getPaneColor(p);
		switch (channel)
		{
		case RED:
			new_color.r = color;
			break;
		case GREEN:
			new_color.g = color;
			break;
		case BLUE:
			new_color.b = color;
			break;
		default:
			break;
		}
		panes[p].setFillColor(new_color);
	}

	void handleMouseEvents(sf::Vector2i mouse_position)
	{
		// check rectangles

		for (int i = 0; i < NUMBER; i++)
		{
			sf::FloatRect rect;
			rect = panes[i].getGlobalBounds();
			if (rect.contains(mouse_position.x, mouse_position.y))
			{
				if (curr_selected != -1)
					panes[curr_selected].setOutlineThickness(0);
				panes[i].setOutlineThickness(1);
				curr_selected = i;

				/*
				*color_text = "r:";
				*color_text += std::to_string(panes[i].getFillColor().r);
				*color_text += " g:";
				*color_text += std::to_string(panes[i].getFillColor().g);
				*color_text += " b:";
				*color_text += std::to_string(panes[i].getFillColor().b);
				*/
				//flags[NOT_SELECTED] = 0;
				//flags[KEYBOARD_INPUT] = 0;
			}
		}
	}

	void update()
	{

	}


	void draw(sf::RenderWindow * window)
	{
		for (int i = 0; i < NUMBER; i++)
		{
			window->draw(panes[i]);
		}
		if (curr_selected != -1)
			window->draw(panes[curr_selected]);
		
	}
};



#endif