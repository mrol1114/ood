#define CATCH_CONFIG_MAIN
#include "../../../../../../lib/catch.hpp"

#include "../Factory/lib/Painter/Painter.h"
#include "../Factory/lib/Designer/Designer.h"
#include "../Factory/lib/Shape/Factory/ShapeFactory.h"

#include <vector>
#include <sstream>

class MokeCanvas : public ICanvas
{
public:
	void SetColor(Color c)override
	{
		m_commands.push_back("set-color");
	}

	void DrawLine(Point from, Point to)override
	{
		m_commands.push_back("draw-line");
	}

	void DrawEllipse(double cx, double cy, double rx, double ry)override
	{
		m_commands.push_back("draw-ellipse");
	}

	const std::vector<std::string>& GetCommands()
	{
		return m_commands;
	}

private:
	std::vector<std::string> m_commands;
};

TEST_CASE("initializing triangle")
{
	CTriangle shape({ 3, 2 }, { 5, 7 }, { -4, 0 }, Color::Black);

	REQUIRE(shape.GetVertex1() == Point{ 3, 2 });
	REQUIRE(shape.GetVertex2() == Point{ 5, 7 });
	REQUIRE(shape.GetVertex3() == Point{ -4, 0 });
	REQUIRE(shape.GetColor() == Color::Black);
}

TEST_CASE("initializing rectangle")
{
	SECTION("with height and width greater than 0")
	{
		CRectangle shape({ 24, 45 }, 12, 24, Color::Black);

		REQUIRE(shape.GetBottomRight() == Point{ 36, 69 });
		REQUIRE(shape.GetLeftTop() == Point{ 24, 45 });
		REQUIRE(shape.GetColor() == Color::Black);
	}

	SECTION("with height lower than 0")
	{
		REQUIRE_THROWS(CRectangle({ 24, 45 }, 12, -24, Color::Black));
	}

	SECTION("with width lower than 0")
	{
		REQUIRE_THROWS(CRectangle({ 24, 45 }, -12, 24, Color::Black));
	}
}

TEST_CASE("initializing regular polygon")
{
	SECTION("with valid values")
	{
		CRegularPolygon shape({ -23, 12 }, 40, 5, Color::Black);

		REQUIRE(shape.GetCenter() == Point{ -23, 12 });
		REQUIRE(shape.GetRadius() == 40);
		REQUIRE(shape.GetVertexCount() == 5);
		REQUIRE(shape.GetColor() == Color::Black);
	}
	SECTION("with radius less than 0")
	{
		REQUIRE_THROWS(CRegularPolygon({ 24, 45 }, -12, 4, Color::Black));
	}
	SECTION("with vertex count equal 2")
	{
		REQUIRE_THROWS(CRegularPolygon({ 24, 45 }, 12, 2, Color::Black));
	}
}

TEST_CASE("initializing ellipse")
{
	SECTION("with width and height greater than 0")
	{
		CEllipse shape({ -23, 12 }, 40, 5, Color::Black);

		REQUIRE(shape.GetCenter() == Point{ -23, 12 });
		REQUIRE(shape.GetWidth() == 40);
		REQUIRE(shape.GetHeight() == 5);
		REQUIRE(shape.GetColor() == Color::Black);
	}
	SECTION("with width lower than 0")
	{
		REQUIRE_THROWS(CEllipse({ 24, 45 }, -12, 4, Color::Black));
	}
	SECTION("with height lower than 0")
	{
		REQUIRE_THROWS(CEllipse({ 24, 45 }, 12, -4, Color::Black));
	}
}

TEST_CASE("creating shapes throught factory")
{
	ShapeFactory factory;

	SECTION("creating triangle")
	{
		//auto abstractShape = factory.CreateShape("triangle black 12 12 13 13 14 14");
		auto abstractShape = factory.CreateShape("rectangle black 36 69 12 11");
		// dynamic cast
		auto shape = static_cast<CTriangle*>(abstractShape.get());

		REQUIRE(shape != nullptr);
		REQUIRE(shape->GetVertex1() == Point{ 12, 12 });
		REQUIRE(shape->GetVertex2() == Point{ 13, 13 });
		REQUIRE(shape->GetVertex3() == Point{ 14, 14 });
		REQUIRE(shape->GetColor() == Color::Black);
	}
	SECTION("creating rectangle")
	{
		auto abstractShape = factory.CreateShape("rectangle black 36 69 12 11");
		auto shape = static_cast<CRectangle*>(abstractShape.get());

		REQUIRE(shape != nullptr);
		REQUIRE(shape->GetLeftTop() == Point{ 36, 69 });
		REQUIRE(shape->GetBottomRight() == Point{ 48, 80 });
		REQUIRE(shape->GetColor() == Color::Black);
	}
	SECTION("creating regular polygon")
	{
		auto abstractShape = factory.CreateShape("regular-polygon black -23 12 40 5");
		auto shape = static_cast<CRegularPolygon*>(abstractShape.get());

		REQUIRE(shape != nullptr);
		REQUIRE(shape->GetCenter() == Point{ -23, 12 });
		REQUIRE(shape->GetRadius() == 40);
		REQUIRE(shape->GetVertexCount() == 5);
		REQUIRE(shape->GetColor() == Color::Black);
	}
	SECTION("creating ellipse")
	{
		auto abstractShape = factory.CreateShape("ellipse black -23 12 40 5");
		auto shape = static_cast<CEllipse*>(abstractShape.get());

		REQUIRE(shape != nullptr);
		REQUIRE(shape->GetCenter() == Point{ -23, 12 });
		REQUIRE(shape->GetWidth() == 40);
		REQUIRE(shape->GetHeight() == 5);
		REQUIRE(shape->GetColor() == Color::Black);
	}
	SECTION("passing wrong shape type")
	{
		REQUIRE_THROWS(factory.CreateShape("triangletr black 12 12 13 13 14 14"));
	}
	SECTION("passing wrong color")
	{
		REQUIRE_THROWS(factory.CreateShape("triangletr dark 12 12 13 13 14 14"));
	}
	SECTION("passing wrong params count")
	{
		REQUIRE_THROWS(factory.CreateShape("triangle black 12 12 13 13 14 "));
	}
}

TEST_CASE("creating draft through designer")
{
	Designer designer(
		std::make_unique<ShapeFactory>()
	);
	ShapeFactory factory;
	PictureDraft expectedDraft;

	std::string triangleDescr = "triangle black 12 12 13 13 14 14";
	std::string rectangleDescr = "rectangle black 36 69 12 11";
	std::string regularPolygonDescr = "regular-polygon black -23 12 40 5";
	std::string ellipseDescr = "ellipse black -23 12 40 5";

	expectedDraft.Addshape(factory.CreateShape(triangleDescr));
	expectedDraft.Addshape(factory.CreateShape(rectangleDescr));
	expectedDraft.Addshape(factory.CreateShape(regularPolygonDescr));
	expectedDraft.Addshape(factory.CreateShape(ellipseDescr));

	std::istringstream inputStream(
		triangleDescr + '\n'
		+ rectangleDescr + '\n'
		+ regularPolygonDescr + '\n'
		+ ellipseDescr + '\n'
	);

	unsigned int curIndex = 0;
	for (const auto& shape : designer.CreateDraft(inputStream).get()->GetShapes())
	{
		REQUIRE(shape.get() == expectedDraft.GetShapes()[curIndex++].get());
	}
}

TEST_CASE("painting draft through painter")
{
	MokeCanvas canvas;
	Painter painter;
	ShapeFactory factory;
	PictureDraft draft;

	std::string triangleDescr = "triangle black 12 12 13 13 14 14";
	std::string rectangleDescr = "rectangle black 36 69 12 11";
	std::string regularPolygonDescr = "regular-polygon black -23 12 40 5";
	std::string ellipseDescr = "ellipse black -23 12 40 3";

	draft.Addshape(factory.CreateShape(triangleDescr));
	draft.Addshape(factory.CreateShape(rectangleDescr));
	draft.Addshape(factory.CreateShape(regularPolygonDescr));
	draft.Addshape(factory.CreateShape(ellipseDescr));

	painter.DrawPicture(draft, canvas);

	REQUIRE(canvas.GetCommands() == std::vector<std::string>({ "set-color", "draw-line", "draw-line",
		"draw-line", "set-color", "draw-line", "draw-line", "draw-line", "draw-line", "set-color", "draw-line",
		"draw-line", "draw-line", "draw-line", "draw-line", "set-color", "draw-ellipse"})
	);
}