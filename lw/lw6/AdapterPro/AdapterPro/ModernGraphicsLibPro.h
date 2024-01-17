#pragma once

#include <iostream>
#include <format>

// Пространство имен обновленной современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib_pro
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
		float r, g, b, a;
	};

	// Класс для современного рисования графики
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream& strm) : m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			// Реализация остается без изменения
		}

		// Этот метод должен быть вызван в начале рисования
		void BeginDraw()
		{
			if (m_drawing)
			{
				throw std::logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << std::endl;
			m_drawing = true;
		}

		// Выполняет рисование линии
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
			// Можно вызывать только между BeginDraw() и EndDraw()
		}

		// Этот метод должен быть вызван в конце рисования
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
