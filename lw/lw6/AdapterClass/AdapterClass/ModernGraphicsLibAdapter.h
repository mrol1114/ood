#pragma once

#include <optional>

#include "./GraphicsLib.h"
#include "./ModernGraphicsLib.h"

class ModernGraphicsLibAdapter 
	: public graphics_lib::ICanvas
	, public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	ModernGraphicsLibAdapter(std::ostream& strm)
		: modern_graphics_lib::CModernGraphicsRenderer(strm)
	{
	}

	void MoveTo(int x, int y)override
	{
		m_curX = x;
		m_curY = y;
	}

	void LineTo(int x, int y)override
	{
		if (!m_curX.has_value() || !m_curY.has_value())
		{
			throw std::runtime_error("Cuurrent ooint is not initialized");
		}

		BeginDraw();
		DrawLine({ m_curX.value() , m_curY.value() }, { x, y });
		EndDraw();
	}

private:
	std::optional<int> m_curX = std::nullopt;
	std::optional<int> m_curY = std::nullopt;
};