#pragma once

#include "./ICanvas.h"

#include <fstream>
#include <vector>
#include <string>
#include <format>

#include "./ICanvas.h"

class CSvgCanvas : public ICanvas
{
public:
	CSvgCanvas(const std::string& outFileName)
	{
		m_outFileName = outFileName;
	}
	
	void BeginPath()override
	{
		m_tags.push_back(std::format("<path fill=\"rgba({}, {}, {}, {})\" "
			"stroke=\"rgba({}, {}, {}, {})\" stroke-width=\"{}\" d=\"",
			m_fillColor.GetRed(), m_fillColor.GetGreen(),
			m_fillColor.GetBlue(), m_fillColor.GetAlpha(),
			m_lineColor.GetRed(), m_lineColor.GetGreen(),
			m_lineColor.GetBlue(), m_lineColor.GetAlpha(), m_lineWidth
		));
		m_isPathOpen = true;
	}

	void EndPath()override
	{
		m_tags.push_back(m_SVG_PATH_CLOSING_TAG);
		m_isPathOpen = false;
		SaveToFile();
	}

	void SetFillColor(RGBA color)override
	{
		m_fillColor = color;
	}

	void SetLineColor(RGBA color)override
	{
		m_lineColor = color;
	}

	void SetLineWidth(double lineWidth)override
	{
		m_lineWidth = lineWidth;
	}

	void MoveTo(Point to)override
	{
		m_tags.push_back(std::format("M {} {}", to.x, to.y));
	}

	void LineTo(Point to)override
	{
		m_tags.push_back(std::format(" L {} {}", to.x, to.y));
	}

	void DrawEllipse(double cx, double cy, double rx, double ry)override
	{
		if (m_isPathOpen)
		{
			throw std::runtime_error("Can not draw ellipse then path is open");
		}
		m_tags.push_back(std::format(
			"<ellipse cx=\"{}\" cy=\"{}\" rx=\"{}\" ry=\"{}\" fill=\"rgba({}, {}, {}, {})\" "
			"stroke = \"rgba({}, {}, {}, {})\" stroke-width=\"{}\" />",
			cx, cy, rx, ry, m_fillColor.GetRed(), m_fillColor.GetGreen(),
			m_fillColor.GetBlue(), m_fillColor.GetAlpha(),
			m_lineColor.GetRed(), m_lineColor.GetGreen(),
			m_lineColor.GetBlue(), m_lineColor.GetAlpha(), m_lineWidth
		));
		SaveToFile();
	}

	void Clear()override
	{
		m_tags.clear();
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

	inline static const std::string m_SVG_OPENING_TAG = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">";
	inline static const std::string m_SVG_CLOSING_TAG = "</svg>";
	inline static const std::string m_SVG_PATH_CLOSING_TAG = "\"/>";

	bool m_isPathOpen = false;
	std::string m_outFileName;
	std::vector<std::string> m_tags;
	double m_lineWidth = 0;
	RGBA m_lineColor = { 0, 0, 0, 0 };
	RGBA m_fillColor = { 0, 0, 0, 0 };
};