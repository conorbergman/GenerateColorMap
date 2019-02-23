#ifndef SUBMIT_BUTTON
#define SUBMIT_BUTTON

#pragma once

#include <iostream>
#include <fstream>

#include "includes.h"
#include "ColorBar.h"


class SubmitButton
{
private:
	sf::RectangleShape container;
public:
	SubmitButton(sf::Vector2f position, sf::Vector2f size = sf::Vector2f(100, 50))
	{
		container = sf::RectangleShape(size);
	}

	/*
	#ifndef COLOR_MAP
	#define COLOR_MAP

	#pragma once

	sf::Color ColorMap(float value)
	{
		if (value <= v1)
		{
			float increment = (distance - prev->position) / (next->position - prev->position);
			float r = prev->color.r + (next->color.r - prev->color.r) * increment;
			float g = prev->color.g + (next->color.g - prev->color.g) * increment;
			float b = prev->color.b + (next->color.b - prev->color.b) * increment;

			return sf::Color(r,g,b);
		}
		else if ()
		{
		}
		return sf::Color(255,255,255);
	}
	*/
	void generateColorMapHeader(ColorBar* colorbar)
	{
		// create header text file
		std::string output = "#ifndef COLOR_MAP\n#define COLOR_MAP\n\n#pragma once\n";
		output += "sf::Color ColorMap(float value)\n{\n";
		node* curr = colorbar->getNode(0);
		curr = curr->next;
		while (curr != nullptr)
		{
			output += "\n\tif (value <= " + std::to_string(curr->position) + ")\n\t{\n\t\t"
				   + "float increment = (value - " + std::to_string(curr->prev->position) + ") / (" +
				     std::to_string(curr->position) + " - " + std::to_string(curr->prev->position) + ");\n\t\t"
			       + "float r = " + std::to_string(curr->prev->color.r) + " + (" + std::to_string(curr->color.r) +
				     " - " + std::to_string(curr->prev->color.r) + ") * increment;\n\t\t"
			       + "float g = " + std::to_string(curr->prev->color.g) + " + (" + std::to_string(curr->color.g) +
				     " - " + std::to_string(curr->prev->color.g) + ") * increment;\n\t\t"
			       + "float b = " + std::to_string(curr->prev->color.b) + " + (" + std::to_string(curr->color.b) +
				     " - " + std::to_string(curr->prev->color.b) + ") * increment;\n\n\t\t"
			       + "return sf::Color(r, g, b);\n\t}";

			curr = curr->next;
		}
		output += "\n\treturn sf::Color(255,255,255);\n}\n\n";
		output += "#endif";
		
		// write to output file
		std::ofstream headerFile;
		headerFile.open("CustomColorMap.txt");
		headerFile << output;
		headerFile.close();
	}
};


#endif
