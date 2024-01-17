#pragma once

#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

#include "./GraphicsLibPro.h"
#include "./ModernGraphicsLibPro.h"

class ModernGraphicsLibAdapter 
	: public graphics_lib_pro::ICanvas
	// private
	, public modern_graphics_lib_pro::CModernGraphicsRenderer
{
	using ModernLibPtr = std::shared_ptr<modern_graphics_lib_pro::CModernGraphicsRenderer>;
public:
	ModernGraphicsLibAdapter(std::ostream& strm)
		: modern_graphics_lib_pro::CModernGraphicsRenderer(strm)
	{
		BeginDraw();
	}

	~ModernGraphicsLibAdapter()
	{
		EndDraw();
	}

	void SetColor(uint32_t rgbColor) override
	{
		m_rgbaColor = ConvertUintToRGBA(rgbColor);
	}

	void MoveTo(int x, int y)override
	{
		m_curX = x;
		m_curY = y;
	}

	void LineTo(int x, int y)override
	{
		if (!m_curX.has_value() || !m_curY.has_value() || !m_rgbaColor.has_value())
		{
			throw std::runtime_error("Current values is not initialized");
		}

		// вызывать только один раз BeginDraw();
		DrawLine({ m_curX.value() , m_curY.value() }, { x, y }, m_rgbaColor.value());
	}

private:
	modern_graphics_lib_pro::CRGBAColor ConvertUintToRGBA(uint32_t color)
	{
		//array
		std::vector<float> colorValues(4);

		for (auto& value : colorValues)
		{
			value = static_cast<float>(color & 0xFF);
			value /= 0xFF;
			color >>= 8;
		}

		return { colorValues[0], colorValues[1], colorValues[2], colorValues[3] };
	}

	std::optional<modern_graphics_lib_pro::CRGBAColor> m_rgbaColor = std::nullopt;
	std::optional<int> m_curX = std::nullopt;
	std::optional<int> m_curY = std::nullopt;
};