#define CATCH_CONFIG_MAIN
#include "../../../../../../lib/catch.hpp"

#include <sstream>

#include "../Adapter/ModernGraphicLibAdapter.h"
#include "../Adapter/ShapeDrawingLib.h"

SCENARIO("Drawing liny by adapter")
{
	std::ostringstream adapterOutput;
	std::ostringstream rendererOutput;

	std::shared_ptr<modern_graphics_lib::CModernGraphicsRenderer> adapterRenderer =
		std::make_shared<modern_graphics_lib::CModernGraphicsRenderer>(adapterOutput);
	ModernGraphicLibAdapter modernLibAdapter(adapterRenderer);

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