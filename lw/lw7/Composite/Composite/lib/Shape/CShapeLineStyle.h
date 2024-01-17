#pragma once

#include "./ILineStyle.h"

class CShapeLineStyle : public ILineStyle
{
public:
	CShapeLineStyle(RGBA color = { 0, 0, 0, 1 }, double lineWidth = 0)
		: m_color(color)
		, m_lineWidth(lineWidth)
	{
		ValidateLineWidth(lineWidth);
	}

	std::optional<bool> IsEnabled()const override
	{
		return m_isEnabled;
	}

	void Enable(bool enable)override
	{
		m_isEnabled = enable;
	}

	void SetColor(RGBA color)override
	{
		m_color = color;
	}

	std::optional<RGBA> GetColor()const override
	{
		return m_color;
	}

	void SetLineWidth(double lineWidth)override
	{
		ValidateLineWidth(lineWidth);
		m_lineWidth = lineWidth;
	}

	std::optional<double> GetLineWidth()const override
	{
		return m_lineWidth;
	}

private:
	void ValidateLineWidth(double lineWidth)
	{
		if (lineWidth < 0)
		{
			throw std::runtime_error("Line width must not be negative");
		}
	}

	RGBA m_color;
	bool m_isEnabled = false;
	double m_lineWidth;
};