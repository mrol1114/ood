#pragma once

#include "./ShapeDrawingLib.h"
#include "./ModernGraphicsLib.h"
#include "./ModernGraphicLibAdapter.h"

// Пространство имен приложения (доступно для модификации)
namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
		CRectangle rectangle({ 30, 40 }, 18, 24);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		std::shared_ptr<modern_graphics_lib::CModernGraphicsRenderer> renderer = 
			std::make_shared<modern_graphics_lib::CModernGraphicsRenderer>(std::cout);

		ModernGraphicLibAdapter modernLibAdapter(renderer);
		shape_drawing_lib::CCanvasPainter painter(modernLibAdapter);
		PaintPicture(painter);
	}
}