#include "./lib/Designer/Designer.h"
#include "./lib/Painter/Painter.h"
#include "./lib/Shape/Factory/ShapeFactory.h"
#include "./lib/Canvas/SvgCanvas.h"

int main()
{
	Designer designer(
		std::make_unique<ShapeFactory>()
	);
	Painter painter;
	SvgCanvas canvas("out.svg");

	auto draft = designer.CreateDraft(std::cin);
	painter.DrawPicture(*draft.get(), canvas);
}