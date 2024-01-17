#pragma once
#include <array>
#include <cassert>

#include "../Geom/geom.h"

class Tile
{
public:
	// ������ ����� 8*8 ��������.
	constexpr static int SIZE = 8;

private:
	using Pixels = std::array<std::array<char, SIZE>, SIZE>;

public:
	// ����������� �� ���������. ��������� ���� ��������� ������.
	Tile(char color = ' ') noexcept
	{
		/* ���������� ����������� ��� ��������������. */

		for (auto& pixelRow : m_pixels)
		{
			pixelRow.fill(color);
		}

		// -------------- �� ������� ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
		// -------------- �� ������� ------------
	}

	Tile(const Tile& other)
	{
		/* ���������� ����������� ��� ��������������. */

		m_pixels = other.m_pixels;

		// -------------- �� ������� ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
		// -------------- �� ������� ------------
	}

	~Tile()
	{
		// -------------- �� ������� ------------
		--m_instanceCount; // ��������� ������� ������.
		assert(m_instanceCount >= 0);
		// -------------- �� ������� ------------
	}

	/**
	 * �������� ���� ������� �����.
	 * ���� ���������� ������� �� ������� �����, ����� ������ �� ������.
	 */
	void SetPixel(Point p, char color) noexcept
	{
		/* ���������� ����������� ��� ��������������. */
		if (!IsPointExceedsBoundaries(p))
		{
			m_pixels[p.y][p.x] = color;
		}
	}

	/**
	 * ���������� ���� �������. ���� ���������� ������� �� ������� �����, ������������ ������.
	 */
	char GetPixel(Point p) const noexcept
	{
		/* ���������� ����������� ���������� ��������������. */
		return IsPointExceedsBoundaries(p)
			? ' '
			: m_pixels[p.y][p.x];
	}

	// ���������� ���������� ���������� ������ Tile � ���������.
	static int GetInstanceCount() noexcept
	{
		// -------------- �� ������� ------------
		return m_instanceCount;
		// -------------- �� ������� ------------
	}

private:
	static bool IsPointExceedsBoundaries(Point p) noexcept
	{
		return p.x < 0 || p.y < 0 || p.x >= SIZE || p.y >= SIZE;
	}


	// -------------- �� ������� ------------
	inline static int m_instanceCount = 0;
	// -------------- �� ������� ------------

	/* ���������� ����� ���� ��� �������� �������� �����. */
	Pixels m_pixels;
};