#include "./CPictureView.h"

#include <map>

namespace
{
	enum class Ids
	{
		AddCircleButton = wxID_LAST + 1,
		AddTriangleButton,
		AddRectangleButton,
		UndoButton,
		RedoButton,
		Canvas,
	};

	const std::map<std::string, CCanvasShapeType> MODEL_TYPE_TO_CANVAS_TYPE = {
		{ "ellipse", CCanvasShapeType::Ellipse },
		{ "rectangle", CCanvasShapeType::Rectangle },
		{ "triangle", CCanvasShapeType::Triangle },
	};

	const wxColor DEFAULT_SHAPE_COLOR = wxColor(100, 200, 200);
	const wxColor DEFAULT_FRAME_COLOR = wxColor(100, 200, 300);
	const double DEFAULT_FRAME_KEY_POINT_SIZE = 20;
}

CPictureView::CPictureView(const std::string& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
	, m_presenter(new CPicturePresenter(this))
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	auto* buttonPanel = CreateButtonPanel(this);
	m_canvas = new CCanvas(this, wxWindowID(Ids::Canvas), wxDefaultPosition, wxSize(640, 480));

	mainSizer->Add(buttonPanel, 0, wxALL, 10);
	mainSizer->Add(m_canvas, 0, wxALL, 10);
	this->SetSizerAndFit(mainSizer);

	Bind(wxEVT_BUTTON, &CPictureView::OnAddCircle, this, wxWindowID(Ids::AddCircleButton));
	Bind(wxEVT_BUTTON, &CPictureView::OnAddRectangle, this, wxWindowID(Ids::AddRectangleButton));
	Bind(wxEVT_BUTTON, &CPictureView::OnAddTriangle, this, wxWindowID(Ids::AddTriangleButton));
	Bind(wxEVT_BUTTON, &CPictureView::OnUndo, this, wxWindowID(Ids::UndoButton));
	Bind(wxEVT_BUTTON, &CPictureView::OnRedo, this, wxWindowID(Ids::RedoButton));
	m_canvas->Bind(CANVAS_MOUSE_DOWN, &CPictureView::OnCanvasMouseDown, this);
	m_canvas->Bind(CANVAS_MOUSE_DRAG, &CPictureView::OnCanvasMouseDrag, this);
	m_canvas->Bind(CANVAS_MOUSE_UP, &CPictureView::OnCanvasMouseUp, this);
}

void CPictureView::UpdateWorkboard(const Shapes& shapes)
{
	m_canvas->Clear();

	AddShapesToCanvas(shapes.shapes);
	if (shapes.currShape)
	{
		AddFrameToCanvas(shapes.currShape);
	}

	m_canvas->Draw();
}

void CPictureView::OnAddCircle(wxCommandEvent& event)
{
	m_presenter->AddCircle();
}

void CPictureView::OnAddTriangle(wxCommandEvent& event)
{
	m_presenter->AddTriangle();
}

void CPictureView::OnAddRectangle(wxCommandEvent& event)
{
	m_presenter->AddRectangle();
}

void CPictureView::OnUndo(wxCommandEvent& event)
{
	m_presenter->Undo();
}

void CPictureView::OnRedo(wxCommandEvent& event)
{
	m_presenter->Redo();
}

void CPictureView::OnCanvasMouseDown(wxCommandEvent& event)
{
	m_presenter->HandleClickOnWorkboard(event.GetInt(), event.GetExtraLong());
}

void CPictureView::OnCanvasMouseUp(wxCommandEvent& event)
{
	m_presenter->FinishDrag();
}

void CPictureView::OnCanvasMouseDrag(wxCommandEvent& event)
{
	m_presenter->HandleDrag(event.GetInt(), event.GetExtraLong());
}

void CPictureView::AddShapesToCanvas(const std::list<Shape>& shapes)
{
	for (const auto& shape : shapes)
	{
		CCanvasFrame frame(
			wxRealPoint(shape.left, shape.top), shape.width, shape.height
		);

		switch (MODEL_TYPE_TO_CANVAS_TYPE.at(shape.type))
		{
		case CCanvasShapeType::Ellipse:
			m_canvas->AddEllipse(frame, DEFAULT_SHAPE_COLOR, DEFAULT_SHAPE_COLOR, true, false);
			break;
		case CCanvasShapeType::Rectangle:
			m_canvas->AddRectangle(frame, DEFAULT_SHAPE_COLOR, DEFAULT_SHAPE_COLOR, true, false);
			break;
		case CCanvasShapeType::Triangle:
			m_canvas->AddTriangle(frame, DEFAULT_SHAPE_COLOR, DEFAULT_SHAPE_COLOR, true, false);
			break;
		}
	}
}

void CPictureView::AddFrameToCanvas(Shape* shape)
{
	CCanvasFrame frame(
		wxRealPoint(shape->left, shape->top), shape->width, shape->height
	);

	m_canvas->AddRectangle(frame, DEFAULT_FRAME_COLOR, DEFAULT_FRAME_COLOR, false, true);
	m_canvas->AddEllipse(
		{ wxRealPoint(frame.pos.x - DEFAULT_FRAME_KEY_POINT_SIZE / 2,
		frame.pos.y - DEFAULT_FRAME_KEY_POINT_SIZE / 2), DEFAULT_FRAME_KEY_POINT_SIZE,
		DEFAULT_FRAME_KEY_POINT_SIZE }, DEFAULT_FRAME_COLOR, wxBG_STYLE_PAINT, true, true
	);
	m_canvas->AddEllipse(
		{ wxRealPoint(frame.pos.x + frame.width - DEFAULT_FRAME_KEY_POINT_SIZE / 2,
		frame.pos.y - DEFAULT_FRAME_KEY_POINT_SIZE / 2), DEFAULT_FRAME_KEY_POINT_SIZE,
		DEFAULT_FRAME_KEY_POINT_SIZE }, DEFAULT_FRAME_COLOR, wxBG_STYLE_PAINT, true, true
	);
	m_canvas->AddEllipse(
		{ wxRealPoint(frame.pos.x + frame.width - DEFAULT_FRAME_KEY_POINT_SIZE / 2,
		frame.pos.y + frame.height - DEFAULT_FRAME_KEY_POINT_SIZE / 2),
		DEFAULT_FRAME_KEY_POINT_SIZE, DEFAULT_FRAME_KEY_POINT_SIZE },
		DEFAULT_FRAME_COLOR, wxBG_STYLE_PAINT, true, true
	);
	m_canvas->AddEllipse(
		{ wxRealPoint(frame.pos.x - DEFAULT_FRAME_KEY_POINT_SIZE / 2,
		frame.pos.y + frame.height - DEFAULT_FRAME_KEY_POINT_SIZE / 2),
		DEFAULT_FRAME_KEY_POINT_SIZE, DEFAULT_FRAME_KEY_POINT_SIZE
		}, DEFAULT_FRAME_COLOR, wxBG_STYLE_PAINT, true, true
	);
}

wxPanel* CPictureView::CreateButtonPanel(wxWindow* parent)
{
	wxPanel* panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(640, 80));
	wxButton* addRectButton = new wxButton(
		panel, wxWindowID(Ids::AddRectangleButton), "Add Rect", wxDefaultPosition, wxSize(80, 60)
	);
	wxButton* addTriangleButton = new wxButton(
		panel, wxWindowID(Ids::AddTriangleButton), "Add Triangle", wxDefaultPosition, wxSize(80, 60)
	);
	wxButton* addEllipseButton = new wxButton(
		panel, wxWindowID(Ids::AddCircleButton), "Add Ellipse", wxDefaultPosition, wxSize(80, 60)
	);
	wxButton* undoButton = new wxButton(
		panel, wxWindowID(Ids::UndoButton), "Undo", wxDefaultPosition, wxSize(80, 60)
	);
	wxButton* redoButton = new wxButton(
		panel, wxWindowID(Ids::RedoButton), "Redo", wxDefaultPosition, wxSize(80, 60)
	);

	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(addRectButton, 0, wxALL, 10);
	sizer->Add(addTriangleButton, 0, wxALL, 10);
	sizer->Add(addEllipseButton, 0, wxALL, 10);
	sizer->Add(undoButton, 0, wxALL, 10);
	sizer->Add(redoButton, 0, wxALL, 10);
	panel->SetSizer(sizer);

	return panel;
}