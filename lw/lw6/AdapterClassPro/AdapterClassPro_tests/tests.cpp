#define CATCH_CONFIG_MAIN
#include "../../../../../../lib/catch.hpp"

#include <sstream>

#include "../AdapterClassPro/ModernGraphicsLibAdapter.h"
#include "../AdapterClassPro/ShapeDrawingLib.h"

SCENARIO("Drawing liny by adapter")
{
	std::ostringstream adapterOutput;
	std::ostringstream rendererOutput;

	ModernGraphicsLibAdapter modernLibAdapter(adapterOutput);
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

	WHEN("executing LineTo before MoveTo")
	{
		REQUIRE_THROWS(modernLibAdapter.LineTo(3, 6));
	}
}