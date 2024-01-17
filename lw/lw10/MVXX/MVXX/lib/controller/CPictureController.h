#pragma once

#include <memory>
#include <map>

#include "../model/Picture/CPicture.h"
#include "../model/Shape/Factory/CShapeFactory.h"
#include "../view/IPictureView.h"
#include "./IPictureController.h"
#include "../model/Workboard/CWorkboard.h"
#include "../view/Shapes.h"

class CPictureController : public IPictureController
{
public:
	CPictureController(IPictureView* view)
		: m_workboard(new CWorkboard(new CPicture(640, 480)))
		, m_view(view)
	{
	}

	void AddCircle()override
	{
		m_workboard->AddShapeToDefaultPosition(ShapeType::Ellipse);
		UpdateShapesView();
	}

	void AddRectangle()override
	{
		m_workboard->AddShapeToDefaultPosition(ShapeType::Rectangle);
		UpdateShapesView();
	}

	void AddTriangle()override
	{
		m_workboard->AddShapeToDefaultPosition(ShapeType::Triangle);
		UpdateShapesView();
	}

	void HandleClickOnWorkboard(double x, double y)
	{
		auto prevCurrShape = m_workboard->GetPicture()->GetCurrShape();
		m_workboard->HandleClick(x, y);
		if (prevCurrShape != m_workboard->GetPicture()->GetCurrShape())
		{
			UpdateShapesView();
		}
	}

	void HandleDrag(double x, double y)
	{
		m_workboard->HandleDrag(x, y);
		UpdateShapesView();
	}

	void Undo()override
	{
		m_workboard->GetPicture()->Undo();
		UpdateShapesView();
	}

	void Redo()override
	{
		m_workboard->GetPicture()->Redo();
		UpdateShapesView();
	}

private:
	void UpdateShapesView()
	{
		auto shapeIterator = m_workboard->GetPicture()->GetIterator();
		Shapes shapes;

		while (shapeIterator.HasNext())
		{
			auto& modelShape = shapeIterator.Get();
			shapes.shapes.push_back({ 
				m_CANVAS_TYPE_TO_MODEL_TYPE.at(modelShape->GetType()),
				modelShape->GetFrame().GetLeft(), modelShape->GetFrame().GetTop(),
				modelShape->GetFrame().GetWidth(), modelShape->GetFrame().GetHeight()
			});

			if (modelShape == m_workboard->GetPicture()->GetCurrShape())
			{
				shapes.currShape = &shapes.shapes.back();
			}
			shapeIterator.Next();
		}

		m_view->UpdateWorkboard(shapes);
	}

	const std::map<ShapeType, std::string> m_CANVAS_TYPE_TO_MODEL_TYPE = {
		{ ShapeType::Ellipse, "ellipse" },
		{ ShapeType::Rectangle, "rectangle" },
		{ ShapeType::Triangle, "triangle" },
	};

	IWorkboard* m_workboard;
	IPictureView* m_view;
};