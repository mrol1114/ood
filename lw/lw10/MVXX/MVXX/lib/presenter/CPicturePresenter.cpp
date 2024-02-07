#include "./CPicturePresenter.h"

#include <memory>
#include <map>

#include "../model/Picture/CPicture.h"
#include "../model/Workboard/CWorkboard.h"
#include "../view/Shapes.h"

namespace
{
	const std::map<ShapeType, std::string> MODEL_TYPE_TO_STRING_ALLIAS = {
		{ ShapeType::Ellipse, "ellipse" },
		{ ShapeType::Rectangle, "rectangle" },
		{ ShapeType::Triangle, "triangle" },
	};
}

CPicturePresenter::CPicturePresenter(IPictureView* view)
	: m_view(view)
{
	CPicture* picture = new CPicture(640, 480);
	m_workboard = new CWorkboard(picture, picture);
}

void CPicturePresenter::AddCircle()
{
	m_workboard->AddShape(ShapeType::Ellipse);
	UpdateShapesView();
}

void CPicturePresenter::AddRectangle()
{
	m_workboard->AddShape(ShapeType::Rectangle);
	UpdateShapesView();
}

void CPicturePresenter::AddTriangle()
{
	m_workboard->AddShape(ShapeType::Triangle);
	UpdateShapesView();
}

void CPicturePresenter::HandleClickOnWorkboard(double x, double y)
{
	m_workboard->HandleClick(x, y);
	UpdateShapesView();
}

void CPicturePresenter::HandleDrag(double x, double y)
{
	m_workboard->HandleDrag(x, y);
	UpdateShapesView();
}

void CPicturePresenter::FinishDrag()
{
	m_workboard->FinishDrag();
}

void CPicturePresenter::Undo()
{
	m_workboard->Undo();
	UpdateShapesView();
}

void CPicturePresenter::Redo()
{
	m_workboard->Redo();
	UpdateShapesView();
}

void CPicturePresenter::UpdateShapesView()
{
	auto shapeIterator = m_workboard->GetShapesIterator();
	Shapes shapes;

	while (shapeIterator.HasNext())
	{
		auto& modelShape = shapeIterator.Get();
		shapes.shapes.push_back({
			MODEL_TYPE_TO_STRING_ALLIAS.at(modelShape->GetType()),
			modelShape->GetFrame().GetLeft(), modelShape->GetFrame().GetTop(),
			modelShape->GetFrame().GetWidth(), modelShape->GetFrame().GetHeight()
		});

		if (modelShape == m_workboard->GetCurrShape())
		{
			shapes.currShape = &shapes.shapes.back();
		}
		shapeIterator.Next();
	}

	m_view->UpdateWorkboard(shapes);
}