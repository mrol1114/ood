#pragma once

#include "./GraphicsLibPro.h"

// ������������ ���� ���������� ��� ��������� ����� (���������� graphics_lib)
// ��� ���������� ���������� ��� ���������
namespace shape_drawing_lib
{
	struct Point
	{
		int x;
		int y;
	};

	// ��������� ��������, ������� ����� ���� ���������� �� ������ �� graphics_lib
	class ICanvasDrawable
	{
	public:
		virtual void Draw(graphics_lib_pro::ICanvas& canvas)const = 0;
		virtual ~ICanvasDrawable() = default;
	};

	class CTriangle : public ICanvasDrawable
	{
	public:
		CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t rgbColor = 0x000000)
			: m_p1(p1)
			, m_p2(p2)
			, m_p3(p3)
			, m_rgbColor(rgbColor)
		{
		}

		void Draw(graphics_lib_pro::ICanvas& canvas)const override
		{
			canvas.SetColor(m_rgbColor);

			canvas.MoveTo(m_p1.x, m_p1.y);
			canvas.LineTo(m_p2.x, m_p2.y);

			canvas.MoveTo(m_p2.x, m_p2.y);
			canvas.LineTo(m_p3.x, m_p3.y);

			canvas.MoveTo(m_p3.x, m_p3.y);
			canvas.LineTo(m_p1.x, m_p1.y);
		}

	private:
		Point m_p1;
		Point m_p2;
		Point m_p3;
		uint32_t m_rgbColor;
	};

	class CRectangle : public ICanvasDrawable
	{
	public:
		CRectangle(const Point& leftTop, int width, int height, uint32_t rgbColor = 0x000000)
		{
			if (width < 0)
			{
				throw std::logic_error("Width can not be less then 0");
			}
			if (height < 0)
			{
				throw std::logic_error("Height can not be less then 0");
			}

			m_leftTop = leftTop;
			m_width = width;
			m_height = height;
			m_rgbColor = rgbColor;
		}

		void Draw(graphics_lib_pro::ICanvas& canvas)const override
		{
			canvas.SetColor(m_rgbColor);

			canvas.MoveTo(m_leftTop.x, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);

			canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);

			canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
			canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);

			canvas.MoveTo(m_leftTop.x, m_leftTop.y + m_height);
			canvas.LineTo(m_leftTop.x, m_leftTop.y);
		}

	private:
		Point m_leftTop;
		int m_width;
		int m_height;
		uint32_t m_rgbColor;
	};

	// ��������, ��������� �������� ICanvasDrawable-������� �� ICanvas
	class CCanvasPainter
	{
	public:
		CCanvasPainter(graphics_lib_pro::ICanvas& canvas)
			: m_canvas(canvas)
		{
		}
		void Draw(const ICanvasDrawable& drawable)
		{
			drawable.Draw(m_canvas);
		}

	private:
		graphics_lib_pro::ICanvas& m_canvas;
	};
}