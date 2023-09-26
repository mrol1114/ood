#include "ICanvas.h"
#include <vector>
#include <fstream>
#include <iostream>

class SvgCanvas: public ICanvas
{
public:
	SvgCanvas(const std::string& outFileName)
	{
		m_outFileName = outFileName;
	}

	void SetColor(Color c) override
	{
		m_c = c;
	}

	void MoveTo(double x, double y) override
	{
		m_currentPositionX = x;
		m_currentPositionY = y;
	}

	void LineTo(double x, double y) override
	{
		m_tags.push_back("<line x1=\"" + std::to_string(m_currentPositionX) + "\""
			" y1=\"" + std::to_string(m_currentPositionY) + "\" x2=\"" + std::to_string(x) + "\""
			" y2=\"" + std::to_string(y) + "\" stroke = \"" + m_c + "\"/>");
		SaveToFile();
	}

	void DrawEllipse(double cx, double cy, double rx, double ry) override
	{
		m_tags.push_back("<ellipse cx=\"" + std::to_string(cx) + "\""
			" cy=\"" + std::to_string(cy) + "\" rx=\"" + std::to_string(rx) + "\""
			" ry=\"" + std::to_string(ry) + "\""
			" stroke = \"" + m_c + "\"/>");
		SaveToFile();
	}

	void DrawText(double left, double top, double fontSize,
		const std::string& text) override
	{
		m_tags.push_back("<text x = \"" + std::to_string(left) + "\"" 
			" y = \"" + std::to_string(top) + "\" stroke = \"" + m_c + "\""
			" font-size=\"" + std::to_string(fontSize) + "\" >" + text + "</text>");
		SaveToFile();
	}

private:
	void SaveToFile()
	{
		std::ofstream outFile(m_outFileName);

		outFile << m_SVG_OPENING_TAG;
		for (const std::string& tag: m_tags)
		{
			outFile << tag;
		}
		outFile << m_SVG_CLOSING_TAG;
	}

	std::string const m_SVG_OPENING_TAG = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">";
	std::string const m_SVG_CLOSING_TAG = "</svg>";

	std::string m_outFileName;
	std::vector<std::string> m_tags;
	Color m_currentColor;
	double m_currentPositionX;
	double m_currentPositionY;
};