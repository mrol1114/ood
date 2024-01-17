#include "image.h"
#include <cassert>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace
{
	static bool IsPointExceedsBoundaries(Point p, Size size) noexcept
	{
		return p.x < 0 || p.y < 0 || p.x >= size.width || p.y >= size.height;
	}
}

/**
 * ������������ ����������� ��������� �������. ���� ������� �� �������� ��������������,
 * ����������� ���������� std::out_of_range.
 */
Image::Image(Size size, char color)
{
	/* ���������� ����������� �������������� */

	if (size.height <= 0 || size.width <= 0)
	{
		throw std::out_of_range("Width and height of image must be greater then 0");
	}

	Tile tile(color);
	unsigned int rowCount = size.height / Tile::SIZE + 1;
	unsigned int columnCount = size.width / Tile::SIZE + 1;

	m_tiles.resize(rowCount);
	for (auto& rowOfTiles : m_tiles)
	{
		rowOfTiles.resize(columnCount, { tile });
	}

	m_size = size;
}

// ���������� ������ ����������� � ��������.
Size Image::GetSize() const noexcept
{
	/* ���������� ����� ��������������. */

	return m_size;
}

/**
 * ���������� ����� ������� � ��������� �����������.���� ���������� ������� �� �������
 * �����������, ���������� �������.
 */
char Image::GetPixel(Point p) const noexcept
{
	/* ���������� ����� ��������������. */

	return IsPointExceedsBoundaries(p, m_size)
		? ' '
		: m_tiles[p.y / Tile::SIZE][p.x / Tile::SIZE]->GetPixel(
			{ p.x % Tile::SIZE, p.y % Tile::SIZE });
}

/**
 * ����� ����� ������� � ��������� �����������. ���� ���������� ������� �� ������� �����������
 * �������� ������������.
 */
void Image::SetPixel(Point p, char color)
{
	/* ���������� ����� ��������������. */

	if (!IsPointExceedsBoundaries(p, m_size))
	{
		m_tiles[p.y / Tile::SIZE][p.x / Tile::SIZE].Write()->SetPixel(
			{ p.x % Tile::SIZE, p.y % Tile::SIZE }, color
		);
	}
}

const Image::Tiles& Image::getTiles() const noexcept
{
	return m_tiles;
}

/**
 * ������� � ����� out ����������� � ���� ��������.
 */
void Print(const Image& img, std::ostream& out)
{
	const auto size = img.GetSize();
	for (int y = 0; y < size.height; ++y)
	{
		for (int x = 0; x < size.width; ++x)
		{
			out.put(img.GetPixel({ x, y }));
		}
		out.put('\n');
	}
}

/**
 * ��������� ����������� �� pixels. ����� ����������� ����������� ��������� \n.
 * ������� �������� ������������ �� ���������� ��������� ������ � ����� ������� �����.
 */
Image LoadImage(const std::string& pixels)
{
	std::istringstream s(pixels);
	Size size;
	std::string line;
	while (std::getline(s, line))
	{
		size.width = std::max(size.width, static_cast<int>(line.length()));
		++size.height;
	}

	Image img(size);

	s = std::istringstream(pixels);
	for (int y = 0; y < size.height; ++y)
	{
		if (!std::getline(s, line))
			break;

		int x = 0;
		for (char ch : line)
		{
			img.SetPixel({ x++, y }, ch);
		}
	}

	return img;
}