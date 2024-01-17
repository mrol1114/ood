#pragma once

#include <memory>
#include <optional>
#include <stdexcept>

#include "./GraphicsLib.h"
#include "./ModernGraphicsLib.h"

class ModernGraphicLibAdapter : public graphics_lib::ICanvas
{
	using ModernLibPtr = std::shared_ptr<modern_graphics_lib::CModernGraphicsRenderer>;
public:
	ModernGraphicLibAdapter(ModernLibPtr modernLibPtr)
		: m_modernLibPtr(modernLibPtr)
	{
	}

	// —тавит "перо" в точку x, y
	void MoveTo(int x, int y)override
	{
		m_curX = x;
		m_curY = y;
	}
	// –исует линию с текущей позиции, передвига€ перо в точку x,y 
	void LineTo(int x, int y)override
	{
		if (!m_curX.has_value() || !m_curY.has_value())
		{
			throw std::runtime_error("Current values is not initialized");
		}

		m_modernLibPtr->BeginDraw();
		m_modernLibPtr->DrawLine({m_curX.value() , m_curY.value()}, {x, y});
		m_modernLibPtr->EndDraw();
	}

private:
	ModernLibPtr m_modernLibPtr;
	std::optional<int> m_curX;
	std::optional<int> m_curY;
};