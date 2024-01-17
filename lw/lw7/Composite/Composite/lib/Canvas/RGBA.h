#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <format>

class RGBA
{
public:
	RGBA(uint8_t red, uint8_t green, uint8_t blue, float alpha)
		: m_red(red)
		, m_green(green)
		, m_blue(blue)
		, m_alpha(alpha)
	{
		if (!(m_MIN_ALPHA <= alpha && alpha <= m_MAX_ALPHA))
		{
			throw std::logic_error("alpha of rgba color must be in interval from 0 to 1");
		}
	}

	uint8_t GetRed()const
	{
		return m_red;
	}

	uint8_t GetGreen()const
	{
		return m_green;
	}

	uint8_t GetBlue()const
	{
		return m_blue;
	}

	float GetAlpha()const
	{
		return m_alpha;
	}

	bool operator==(const RGBA& other)const
	{
		return m_red == other.m_red
			&& m_green == other.m_green
			&& m_blue == other.m_blue
			&& m_alpha == other.m_alpha;
	}

	bool operator!=(const RGBA& other)const
	{
		return !(*this == other);
	}

	friend std::ostream& operator<<(std::ostream& stream, const RGBA& color)
	{
		return stream << std::format("{} {} {} {}", color.GetRed(), color.GetGreen(),
			color.GetBlue(), color.GetAlpha());
	}

private:
	inline static const float m_MIN_ALPHA = 0;
	inline static const float m_MAX_ALPHA = 1;

	uint8_t m_red = 0;
	uint8_t m_green = 0;
	uint8_t m_blue = 0;
	float m_alpha = 1;
};