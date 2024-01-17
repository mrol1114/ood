#pragma once

#include "./IFillStyle.h"

class CShapeFillStyle : public IFillStyle
{
public:
	CShapeFillStyle(RGBA color = { 0, 0, 0, 1 })
		: m_color(color)
	{
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

private:
	RGBA m_color;
	bool m_isEnabled = false;
};