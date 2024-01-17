#define CATCH_CONFIG_MAIN
#include "../../../../../../lib/catch.hpp"

#include <sstream>

#include "../AdapterClass/ModernGraphicsLibAdapter.h"
#include "../AdapterClass/ShapeDrawingLib.h"

SCENARIO("Drawing liny by adapter")
{
	std::ostringstream adapterOutput;
	std::ostringstream rendererOutput;

	ModernGraphicsLibAdapter modernLibAdapter(adapterOutput);
	modern_graphics_lib::CModernGraphicsRenderer renderer(rendererOutput);

	WHEN("moving after initializing")
	{
		modernLibAdapter.MoveTo(2, 4);
		modernLibAdapter.LineTo(3, 6);

		renderer.BeginDraw();
		renderer.DrawLine({ 2, 4 }, { 3, 6 });
		renderer.EndDraw();

		REQUIRE(adapterOutput.str() == rendererOutput.str());
	}

	WHEN("moving before initializing")
	{
		REQUIRE_THROWS(modernLibAdapter.LineTo(3, 6));
	}
}