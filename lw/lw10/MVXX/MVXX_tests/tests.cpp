#define CATCH_CONFIG_MAIN
#include "../../../../lib/catch.hpp"

#include <list>

#include "../MVXX/lib/view/IPictureView.h"
#include "../MVXX/lib/presenter/CPicturePresenter.h"
#include "../MVXX/lib/model/Workboard/CWorkboard.h"
#include "../MVXX/lib/model/Picture/CPicture.h"

class MockView : public IPictureView
{
public:
	MockView(std::list<Shapes>& shapesList)
		: m_shapesList(shapesList)
	{
	}

	void UpdateWorkboard(const Shapes& shapes)override
	{
		m_shapesList.push_back({});

		for (const auto& shape : shapes.shapes)
		{
			m_shapesList.back().shapes.push_back(shape);

			if (&shape == shapes.currShape)
			{
				m_shapesList.back().currShape = &m_shapesList.back().shapes.back();
			}
		}
	}

private:
	std::list<Shapes>& m_shapesList;
};

SCENARIO("testing picture")
{
	CPicture picture(640, 480);

	REQUIRE(picture.GetCurrShape() == nullptr);

	GIVEN("a picture with triangle, rectangle and ellispe")
	{
		picture.AddShape({ 100, 100, 100, 100 }, ShapeType::Rectangle);
		picture.AddShape({ 100, 100, 100, 100 }, ShapeType::Triangle);
		picture.AddShape({ 300, 300, 100, 100 }, ShapeType::Ellipse);

		WHEN("getting shape by coors")
		{
			REQUIRE(picture.GetShapeByCoors(150, 150)->GetType() == ShapeType::Triangle);
			REQUIRE(picture.GetShapeByCoors(120, 120)->GetType() == ShapeType::Rectangle);
			REQUIRE(picture.GetShapeByCoors(340, 340)->GetType() == ShapeType::Ellipse);
			REQUIRE(!picture.GetShapeByCoors(310, 310));
		}

		WHEN("setting current shape")
		{
			picture.SetCurrShape(picture.GetShapeByCoors(150, 150));
			REQUIRE(picture.GetCurrShape()->GetType() == ShapeType::Triangle);
		}

		WHEN("changing position of current shape")
		{
			picture.SetCurrShape(picture.GetShapeByCoors(150, 150));

			picture.ChangePositionOfCurrShape(0, 0);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetLeft() == 0);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetTop() == 0);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetWidth() == 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetHeight() == 100);

			picture.ChangePositionOfCurrShape(540, 380);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetLeft() == 540);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetTop() == 380);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetWidth() == 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetHeight() == 100);
		}

		WHEN("trying to set position of current shape outside of picture")
		{
			picture.SetCurrShape(picture.GetShapeByCoors(150, 150));

			picture.ChangePositionOfCurrShape(-1, -1);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetLeft() == 0);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetTop() == 0);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetWidth() == 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetHeight() == 100);

			picture.ChangePositionOfCurrShape(541, 381);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetLeft() == 540);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetTop() == 380);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetWidth() == 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetHeight() == 100);

			picture.ChangePositionOfCurrShape(541, 361);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetLeft() == 540);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetTop() == 361);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetWidth() == 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetHeight() == 100);
		}

		WHEN("resizing current shape")
		{
			picture.SetCurrShape(picture.GetShapeByCoors(150, 150));

			picture.ChangeSizeOfCurrShape(100, 100, 200, 200);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetLeft() == 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetTop() == 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetWidth() == 200);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetHeight() == 200);
		}

		WHEN("trying to move resize with size exceding picture borders")
		{
			picture.SetCurrShape(picture.GetShapeByCoors(150, 150));

			picture.ChangeSizeOfCurrShape(-1, -1, 100, 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetLeft() == 0);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetTop() == 0);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetWidth() == 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetHeight() == 100);

			picture.ChangeSizeOfCurrShape(541, 381, 100, 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetLeft() == 541);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetTop() == 381);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetWidth() == 99);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetHeight() == 99);

			picture.ChangeSizeOfCurrShape(540, 460, 120, 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetLeft() == 540);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetTop() == 460);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetWidth() == 100);
			REQUIRE(picture.GetCurrShape()->GetFrame().GetHeight() == 20);
		}
	}
}

SCENARIO("testing presenter")
{
	std::list<Shapes> shapesList;
	MockView mockView(shapesList);
	CPicturePresenter presenter(&mockView);

	WHEN("adding circle")
	{
		presenter.AddCircle();

		REQUIRE(shapesList.size() == 1);
		REQUIRE(shapesList.back().shapes.front().type == "ellipse");
	}

	WHEN("adding triangle")
	{
		presenter.AddTriangle();

		REQUIRE(shapesList.size() == 1);
		REQUIRE(shapesList.back().shapes.front().type == "triangle");
	}

	WHEN("adding rectangle")
	{
		presenter.AddRectangle();

		REQUIRE(shapesList.size() == 1);
		REQUIRE(shapesList.back().shapes.front().type == "rectangle");
	}

	GIVEN("a presenter with added ellipse")
	{
		presenter.AddCircle();

		WHEN("Handle click")
		{
			presenter.HandleClickOnWorkboard(400, 400);

			REQUIRE(shapesList.size() == 2);
			REQUIRE(shapesList.back().currShape);
			REQUIRE(shapesList.back().currShape->type == "ellipse");
		}

		WHEN("moving shape")
		{
			presenter.HandleClickOnWorkboard(360, 360);
			REQUIRE(shapesList.size() == 2);
			REQUIRE(shapesList.back().currShape);
			REQUIRE(shapesList.back().currShape->left == 320);
			REQUIRE(shapesList.back().currShape->top == 320);
			REQUIRE(shapesList.back().currShape->width == 100);
			REQUIRE(shapesList.back().currShape->height == 100);

			presenter.HandleDrag(350, 355);
			REQUIRE(shapesList.size() == 3);
			REQUIRE(shapesList.back().currShape);
			REQUIRE(shapesList.back().currShape->left == 310);
			REQUIRE(shapesList.back().currShape->top == 315);
			REQUIRE(shapesList.back().currShape->width == 100);
			REQUIRE(shapesList.back().currShape->height == 100);

			presenter.HandleDrag(345, 360);
			REQUIRE(shapesList.size() == 4);
			REQUIRE(shapesList.back().currShape);
			REQUIRE(shapesList.back().currShape->left == 305);
			REQUIRE(shapesList.back().currShape->top == 320);
			REQUIRE(shapesList.back().currShape->width == 100);
			REQUIRE(shapesList.back().currShape->height == 100);
		}

		WHEN("resizing shape")
		{
			presenter.HandleClickOnWorkboard(360, 360);
			presenter.HandleClickOnWorkboard(320, 320);
			REQUIRE(shapesList.back().currShape);
			REQUIRE(shapesList.back().currShape->left == 320);
			REQUIRE(shapesList.back().currShape->top == 320);
			REQUIRE(shapesList.back().currShape->width == 100);
			REQUIRE(shapesList.back().currShape->height == 100);

			presenter.HandleDrag(305, 300);
			REQUIRE(shapesList.back().currShape);
			REQUIRE(shapesList.back().currShape->left == 305);
			REQUIRE(shapesList.back().currShape->top == 300);
			REQUIRE(shapesList.back().currShape->width == 115);
			REQUIRE(shapesList.back().currShape->height == 120);

			presenter.HandleDrag(315, 305);
			REQUIRE(shapesList.back().currShape);
			REQUIRE(shapesList.back().currShape->left == 315);
			REQUIRE(shapesList.back().currShape->top == 305);
			REQUIRE(shapesList.back().currShape->width == 105);
			REQUIRE(shapesList.back().currShape->height == 115);
		}
	}
}

SCENARIO("testing history usage")
{
	std::list<Shapes> shapesList;
	MockView mockView(shapesList);
	CPicturePresenter presenter(&mockView);

	WHEN("adding shape")
	{
		presenter.AddRectangle();

		REQUIRE(shapesList.size() == 1);
		REQUIRE(shapesList.back().shapes.size() == 1);

		presenter.Undo();

		REQUIRE(shapesList.size() == 2);
		REQUIRE(shapesList.back().shapes.size() == 0);

		presenter.Redo();

		REQUIRE(shapesList.size() == 3);
		REQUIRE(shapesList.back().shapes.size() == 1);
	}

	WHEN("adding shape after undo")
	{
		presenter.AddRectangle();
		presenter.Undo();
		presenter.AddRectangle();

		REQUIRE(shapesList.back().shapes.size() == 1);

		presenter.Redo();
		REQUIRE(shapesList.back().shapes.size() == 1);
	}

	GIVEN("a presenter with shape")
	{
		presenter.AddCircle();

		WHEN("moving shape")
		{
			presenter.HandleClickOnWorkboard(360, 360);

			presenter.HandleDrag(350, 355);
			presenter.HandleDrag(345, 360);
			presenter.FinishDrag();

			presenter.Undo();

			REQUIRE(shapesList.size() == 5);
			REQUIRE(shapesList.back().shapes.front().left == 320);
			REQUIRE(shapesList.back().shapes.front().top == 320);

			presenter.Redo();

			REQUIRE(shapesList.size() == 6);
			REQUIRE(shapesList.back().shapes.front().left == 305);
			REQUIRE(shapesList.back().shapes.front().top == 320);
		}

		WHEN("resizing shape")
		{
			presenter.HandleClickOnWorkboard(360, 360);
			presenter.HandleClickOnWorkboard(320, 320);

			presenter.HandleDrag(305, 300);
			presenter.HandleDrag(315, 305);
			presenter.FinishDrag();

			presenter.Undo();

			REQUIRE(shapesList.back().shapes.front().left == 320);
			REQUIRE(shapesList.back().shapes.front().top == 320);
			REQUIRE(shapesList.back().shapes.front().width == 100);
			REQUIRE(shapesList.back().shapes.front().height == 100);

			presenter.Redo();

			REQUIRE(shapesList.back().shapes.front().left == 315);
			REQUIRE(shapesList.back().shapes.front().top == 305);
			REQUIRE(shapesList.back().shapes.front().width == 105);
			REQUIRE(shapesList.back().shapes.front().height == 115);
		}
	}
}