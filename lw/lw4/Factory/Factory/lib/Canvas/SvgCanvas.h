#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "./ICanvas.h"

class SvgCanvas : public ICanvas
{
public:
	SvgCanvas(const std::string& outFileName)
	{
		m_outFileName = outFileName;
	}

	void SetColor(Color color)override
	{
		m_currentColor = color;
	}

	void DrawLine(Point from, Point to)override
	{
		m_tags.push_back("<line x1=\"" + std::to_string(from.x) + "\""
			+ " y1=\"" + std::to_string(from.y) + "\" x2=\"" + std::to_string(to.x) + "\""
			+ " y2=\"" + std::to_string(to.y) + "\" stroke = \"#" 
			+ m_COLOR_PALETTE_MAP.at(m_currentColor) + "\"/>");
		SaveToFile();
	}

	void DrawEllipse(double cx, double cy, double width, double height)override
	{
		m_tags.push_back("<ellipse cx=\"" + std::to_string(cx) + "\""
			+ " cy=\"" + std::to_string(cy) + "\" rx=\"" + std::to_string(width/2) + "\""
			+ " ry=\"" + std::to_string(height/2) + "\""
			+ " stroke = \"#" + m_COLOR_PALETTE_MAP.at(m_currentColor) + "\"/>");
		SaveToFile();
	}

private:
	void SaveToFile()
	{
		std::ofstream outFile(m_outFileName);

		outFile << m_SVG_OPENING_TAG;
		for (const std::string& tag : m_tags)
		{
			outFile << tag;
		}
		outFile << m_SVG_CLOSING_TAG;
	}

	std::string const m_SVG_OPENING_TAG = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">";
	std::string const m_SVG_CLOSING_TAG = "</svg>";
	std::map<Color, std::string> const m_COLOR_PALETTE_MAP = {
		{Color::Green, "00FF00"},
		{Color::Red, "FF0000"},
		{Color::Blue, "0000FF"},
		{Color::Yellow, "FFFF00"},
		{Color::Pink, "FFC0CB"},
		{Color::Black, "000000"},
	};

	std::string m_outFileName;
	std::vector<std::string> m_tags;
	Color m_currentColor;
};