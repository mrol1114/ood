#pragma once

#include <iostream>
#include <format>

// ������������ ���� ����������� ����������� ����������� ���������� (���������� ��� ���������)
namespace modern_graphics_lib_pro
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	// ���� � ������� RGBA, ������ ��������� ��������� �������� �� 0.0f �� 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
		float r, g, b, a;
	};

	// ����� ��� ������������ ��������� �������
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream& strm) : m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			// ���������� �������� ��� ���������
		}

		// ���� ����� ������ ���� ������ � ������ ���������
		void BeginDraw()
		{
			if (m_drawing)
			{
				throw std::logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << std::endl;
			m_drawing = true;
		}

		// ��������� ��������� �����
		void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
		{
			if (!m_drawing)
			{
				throw std::runtime_error("Can not draw line then not drawing");
			}
			m_out << std::format(R"(<line fromX="{}" fromY="{}" toX="{}" toY="{}">)",
				start.x, start.y, end.x, end.y) << std::endl
				<< std::format(R"(<color r="{}" g="{}" b="{}" a="{}"/>)",
					color.r, color.g, color.b, color.a) << std::endl
				<< "</line>";
			// ����� �������� ������ ����� BeginDraw() � EndDraw()
		}

		// ���� ����� ������ ���� ������ � ����� ���������
		void EndDraw()
		{
			if (!m_drawing)
			{
				throw std::logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << std::endl;
			m_drawing = false;
		}

	private:
		std::ostream& m_out;
		bool m_drawing = false;
	};
}
