#define CATCH_CONFIG_MAIN
#include "../../../../../../lib/catch.hpp"

#include <sstream>

#include "../AdapterPro/ModernGraphicsLibAdapter.h"
#include "../AdapterPro/ShapeDrawingLib.h"

SCENARIO("Drawing liny by adapter")
{
	std::ostringstream adapterOutput;
	std::ostringstream rendererOutput;

	std::shared_ptr<modern_graphics_lib_pro::CModernGraphicsRenderer> adapterRenderer =
		std::make_shared<modern_graphics_lib_pro::CModernGraphicsRenderer>(adapterOutput);
	ModernGraphicsLibAdapter modernLibAdapter(adapterRenderer);

	modern_graphics_lib_pro::CModernGraphicsRenderer renderer(rendererOutput);

	WHEN("moving after initializing")
	{
		modernLibAdapter.MoveTo(2, 4);
		modernLibAdapter.SetColor(0xFFFFFFFF);
		modernLibAdapter.LineTo(3, 6);

		renderer.BeginDraw();
		renderer.DrawLine({ 2, 4 }, { 3, 6 }, { 1, 1, 1, 1 });
		renderer.EndDraw();

		REQUIRE(adapterOutput.str() == rendererOutput.str());
	}

	WHEN("moving before initializing")
	{
		REQUIRE_THROWS(modernLibAdapter.LineTo(3, 6));
	}
}