#define CATCH_CONFIG_MAIN
#include "../../../../../../lib/catch.hpp"

#include "../Composite/lib/Canvas/RGBA.h"
#include "../Composite/lib/Shape/CShape.h"
#include "../Composite/lib/ShapeGroup/CShapeGroup.h"
#include "../Composite/lib/Slide/CSlide.h"
#include "../Composite/lib/Shape/Factory/CShapeFactory.h"

SCENARIO("working with CShapeGroup")
{
	CShapeGroup group;

	REQUIRE(group.GetShapeCount() == 0);
	REQUIRE_THROWS(group.GetShapeAtIndex(0));
	REQUIRE(group.GetFrame().GetLeft() == 0);
	REQUIRE(group.GetFrame().GetTop() == 0);
	REQUIRE(group.GetFrame().GetWidth() == 0);
	REQUIRE(group.GetFrame().GetHeight() == 0);

	WHEN("getting frame of group with empty group and shape")
	{
		group.InsertShape(std::make_shared<CShapeGroup>(), std::nullopt);

		REQUIRE(group.GetFrame().GetLeft() == 0);
		REQUIRE(group.GetFrame().GetTop() == 0);
		REQUIRE(group.GetFrame().GetWidth() == 0);
		REQUIRE(group.GetFrame().GetHeight() == 0);

		group.InsertShape(std::make_shared<CRectangle>(
			CFrame(100, 100, 150, 80)
		), std::nullopt);

		auto groupFrame = group.GetFrame();
		REQUIRE(group.GetFrame().GetLeft() == 100);
		REQUIRE(group.GetFrame().GetTop() == 100);
		REQUIRE(group.GetFrame().GetWidth() == 150);
		REQUIRE(group.GetFrame().GetHeight() == 80);
	}

	WHEN("inserting shape at back")
	{
		std::shared_ptr<IShape> shape = std::make_shared<CRectangle>(
			CFrame(100, 100, 150, 80)
		);
		group.InsertShape(shape, {});

		REQUIRE(group.GetShapeCount() == 1);
		REQUIRE(group.GetShapeAtIndex(0).get() == shape.get());
		REQUIRE_THROWS(group.GetShapeAtIndex(1));
	}

	WHEN("inserting at position in empty group")
	{
		std::shared_ptr<IShape> shape = std::make_shared<CRectangle>(
			CFrame(100, 100, 150, 80)
		);

		REQUIRE_THROWS(group.InsertShape(shape, 0));
	}

	GIVEN("a group with 3 shapes")
	{
		std::shared_ptr<IShape> rectangle = std::make_shared<CRectangle>(
			CFrame(100, 100, 150, 80)
		);
		std::shared_ptr<IShape> triangle = std::make_shared<CTriangle>(
			CFrame(350, 200, 150, 80)
		);
		std::shared_ptr<IShape> ellipse = std::make_shared<CEllipse>(
			CFrame(500, 500, 200, 200)
		);

		rectangle->GetFillStyle()->SetColor({ 255, 0, 255, 1 });
		triangle->GetFillStyle()->SetColor({ 100, 80, 75, 1 });
		ellipse->GetFillStyle()->SetColor({ 100, 80, 75, 1 });

		ellipse->GetFillStyle()->Enable(true);

		rectangle->GetLineStyle()->SetColor({ 255, 0, 255, 1 });
		rectangle->GetLineStyle()->SetLineWidth(10);
		triangle->GetLineStyle()->SetColor({ 100, 80, 75, 1 });
		triangle->GetLineStyle()->SetLineWidth(6);
		ellipse->GetLineStyle()->SetColor({ 100, 80, 75, 1 });
		ellipse->GetLineStyle()->SetLineWidth(2);

		triangle->GetLineStyle()->Enable(true);

		group.InsertShape(rectangle, {});
		group.InsertShape(triangle, {});
		group.InsertShape(ellipse, {});

		REQUIRE(group.GetShapeCount() == 3);
		REQUIRE(group.GetFillStyle()->IsEnabled() == std::nullopt);
		REQUIRE(group.GetFillStyle()->GetColor() == std::nullopt);
		REQUIRE(group.GetLineStyle()->IsEnabled() == std::nullopt);
		REQUIRE(group.GetLineStyle()->GetColor() == std::nullopt);
		REQUIRE(group.GetLineStyle()->GetLineWidth() == std::nullopt);
		REQUIRE(group.GetFrame().GetLeft() == 100);
		REQUIRE(group.GetFrame().GetTop() == 100);
		REQUIRE(group.GetFrame().GetWidth() == 600);
		REQUIRE(group.GetFrame().GetHeight() == 600);

		WHEN("changing frame size")
		{
			CFrame frame(100, 100, 300, 300);

			group.SetFrame(frame);

			REQUIRE(group.GetFrame().GetLeft() == 100);
			REQUIRE(group.GetFrame().GetTop() == 100);
			REQUIRE(group.GetFrame().GetWidth() == 300);
			REQUIRE(group.GetFrame().GetHeight() == 300);

			REQUIRE(rectangle->GetFrame().GetLeft() == 100);
			REQUIRE(rectangle->GetFrame().GetTop() == 100);
			REQUIRE(rectangle->GetFrame().GetWidth() == 75);
			REQUIRE(rectangle->GetFrame().GetHeight() == 40);

			REQUIRE(triangle->GetFrame().GetLeft() == 225);
			REQUIRE(triangle->GetFrame().GetTop() == 150);
			REQUIRE(triangle->GetFrame().GetWidth() == 75);
			REQUIRE(triangle->GetFrame().GetHeight() == 40);

			REQUIRE(ellipse->GetFrame().GetLeft() == 300);
			REQUIRE(ellipse->GetFrame().GetTop() == 300);
			REQUIRE(ellipse->GetFrame().GetWidth() == 100);
			REQUIRE(ellipse->GetFrame().GetHeight() == 100);
		}

		WHEN("changing frame position")
		{
			CFrame frame(300, 300, 600, 600);

			group.SetFrame(frame);

			REQUIRE(group.GetFrame().GetLeft() == 300);
			REQUIRE(group.GetFrame().GetTop() == 300);
			REQUIRE(group.GetFrame().GetWidth() == 600);
			REQUIRE(group.GetFrame().GetHeight() == 600);

			REQUIRE(rectangle->GetFrame().GetLeft() == 300);
			REQUIRE(rectangle->GetFrame().GetTop() == 300);
			REQUIRE(rectangle->GetFrame().GetWidth() == 150);
			REQUIRE(rectangle->GetFrame().GetHeight() == 80);

			REQUIRE(triangle->GetFrame().GetLeft() == 550);
			REQUIRE(triangle->GetFrame().GetTop() == 400);
			REQUIRE(triangle->GetFrame().GetWidth() == 150);
			REQUIRE(triangle->GetFrame().GetHeight() == 80);

			REQUIRE(ellipse->GetFrame().GetLeft() == 700);
			REQUIRE(ellipse->GetFrame().GetTop() == 700);
			REQUIRE(ellipse->GetFrame().GetWidth() == 200);
			REQUIRE(ellipse->GetFrame().GetHeight() == 200);
		}

		WHEN("inserting shape at position")
		{
			std::shared_ptr<IShape> shape = std::make_shared<CRectangle>(
				CFrame(200, 100, 150, 80)
			);
			group.InsertShape(shape, 1);

			REQUIRE(group.GetShapeCount() == 4);
			REQUIRE(group.GetShapeAtIndex(1).get() == shape.get());
		}

		WHEN("enable shape fill color")
		{
			group.GetFillStyle()->Enable(true);

			REQUIRE(group.GetFillStyle()->IsEnabled() == true);
			REQUIRE(rectangle->GetFillStyle()->IsEnabled() == true);
			REQUIRE(triangle->GetFillStyle()->IsEnabled() == true);
			REQUIRE(ellipse->GetFillStyle()->IsEnabled() == true);
		}

		WHEN("setting fill color")
		{
			RGBA color(255, 100, 255, 1);

			group.GetFillStyle()->SetColor(color);

			REQUIRE(group.GetFillStyle()->GetColor().value() == color);
			REQUIRE(rectangle->GetFillStyle()->GetColor().value() == color);
			REQUIRE(triangle->GetFillStyle()->GetColor().value() == color);
			REQUIRE(ellipse->GetFillStyle()->GetColor().value() == color);
		}

		WHEN("enable shape line color")
		{
			group.GetLineStyle()->Enable(true);

			REQUIRE(group.GetLineStyle()->IsEnabled() == true);
			REQUIRE(rectangle->GetLineStyle()->IsEnabled() == true);
			REQUIRE(triangle->GetLineStyle()->IsEnabled() == true);
			REQUIRE(ellipse->GetLineStyle()->IsEnabled() == true);
		}

		WHEN("setting line color")
		{
			RGBA color(255, 100, 255, 1);

			group.GetLineStyle()->SetColor(color);

			REQUIRE(group.GetLineStyle()->GetColor().value() == color);
			REQUIRE(rectangle->GetLineStyle()->GetColor().value() == color);
			REQUIRE(triangle->GetLineStyle()->GetColor().value() == color);
			REQUIRE(ellipse->GetLineStyle()->GetColor().value() == color);
		}

		WHEN("setting line width")
		{
			double lineWidth = 3;

			group.GetLineStyle()->SetLineWidth(lineWidth);

			REQUIRE(group.GetLineStyle()->GetLineWidth() == lineWidth);
			REQUIRE(rectangle->GetLineStyle()->GetLineWidth() == lineWidth);
			REQUIRE(triangle->GetLineStyle()->GetLineWidth() == lineWidth);
			REQUIRE(ellipse->GetLineStyle()->GetLineWidth() == lineWidth);
		}

		WHEN("deleting shape")
		{
			group.RemoveShapeAtIndex(1);

			REQUIRE(group.GetShapeCount() == 2);
			REQUIRE(group.GetShapeAtIndex(0).get() == rectangle.get());
			REQUIRE(group.GetShapeAtIndex(1).get() == ellipse.get());
			REQUIRE_THROWS(group.GetShapeAtIndex(2));
		}
	}
}

SCENARIO("working with CSlide")
{
	CSlide slide;

	std::shared_ptr<IShape> rectangle = std::make_shared<CRectangle>(
		CFrame(100, 100, 150, 80)
	);
	std::shared_ptr<IShape> triangle = std::make_shared<CTriangle>(
		CFrame(350, 200, 150, 80)
	);
	std::shared_ptr<IShape> ellipse = std::make_shared<CEllipse>(
		CFrame(500, 500, 200, 200)
	);

	rectangle->GetFillStyle()->SetColor({ 255, 0, 255, 1 });
	triangle->GetFillStyle()->SetColor({ 100, 80, 75, 1 });
	ellipse->GetFillStyle()->SetColor({ 100, 80, 75, 1 });

	ellipse->GetFillStyle()->Enable(true);

	rectangle->GetLineStyle()->SetColor({ 255, 0, 255, 1 });
	rectangle->GetLineStyle()->SetLineWidth(10);
	triangle->GetLineStyle()->SetColor({ 100, 80, 75, 1 });
	triangle->GetLineStyle()->SetLineWidth(6);
	ellipse->GetLineStyle()->SetColor({ 100, 80, 75, 1 });
	ellipse->GetLineStyle()->SetLineWidth(2);

	triangle->GetLineStyle()->Enable(true);

	slide.InsertShape(rectangle, {});
	slide.InsertShape(triangle, {});
	slide.InsertShape(ellipse, {});

	GIVEN("a slide with 3 simple shapes")
	{
		WHEN("creating group")
		{
			slide.CreateGroup({ 0, 2 });

			REQUIRE(slide.GetShapeCount() == 2);
			REQUIRE(slide.GetShapeAtIndex(0).get() == triangle.get());
			REQUIRE(slide.GetShapeAtIndex(1)->GetGroup());
			REQUIRE(slide.GetShapeAtIndex(1)->GetGroup()->GetShapeCount() == 2);
			REQUIRE(slide.GetShapeAtIndex(1)->GetGroup()->GetShapeAtIndex(0).get() == rectangle.get());
			REQUIRE(slide.GetShapeAtIndex(1)->GetGroup()->GetShapeAtIndex(1).get() == ellipse.get());
		}
	}
	GIVEN("a slide with simple shape and 1 group")
	{
		slide.CreateGroup({ 0, 2 });

		WHEN("ungroup")
		{
			slide.Ungroup(1);

			REQUIRE(slide.GetShapeCount() == 3);
			REQUIRE(slide.GetShapeAtIndex(0).get() == triangle.get());
			REQUIRE(slide.GetShapeAtIndex(1).get() == rectangle.get());
			REQUIRE(slide.GetShapeAtIndex(2).get() == ellipse.get());
		}

		WHEN("trying to ungroup shape")
		{
			REQUIRE_THROWS(slide.Ungroup(0));
		}

		WHEN("removing group")
		{
			slide.RemoveShapeAtIndex(1);

			REQUIRE(slide.GetShapeCount() == 1);
			REQUIRE(slide.GetShapeAtIndex(0).get() == triangle.get());
			REQUIRE_THROWS(slide.GetShapeAtIndex(1));
		}
	}
}