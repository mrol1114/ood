#pragma once

#include <wx/wx.h>
#include <wx/listbook.h>
#include <string>
#include <map>

#include "./Canvas/CCanvas.h"
#include "../controller/CPictureController.h"
#include "./IPictureView.h"

class CPictureView : public wxFrame, public IPictureView
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

public:
	CPictureView(const std::string& title, const wxPoint& pos, const wxSize& size)
		: wxFrame(nullptr, wxID_ANY, title, pos, size)
		, m_controller(new CPictureController(this))
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
	}

	void UpdateWorkboard(const Shapes& shapes)override
	{
		m_canvas->Clear();

		AddShapesToCanvas(shapes.shapes);
		if (shapes.currShape)
		{
			AddFrameToCanvas(shapes.currShape);
		}

		m_canvas->Draw();
	}

private:
	void OnAddCircle(wxCommandEvent& event)
	{
		m_controller->AddCircle();
	}

	void OnAddTriangle(wxCommandEvent& event)
	{
		m_controller->AddTriangle();
	}

	void OnAddRectangle(wxCommandEvent& event)
	{
		m_controller->AddRectangle();
	}

	void OnUndo(wxCommandEvent& event)
	{
		m_controller->Undo();
	}

	void OnRedo(wxCommandEvent& event)
	{
		m_controller->Redo();
	}

	void OnCanvasMouseDown(wxCommandEvent& event)
	{
		m_controller->HandleClickOnWorkboard(event.GetInt(), event.GetExtraLong());
	}

	void OnCanvasMouseDrag(wxCommandEvent& event)
	{
		m_controller->HandleDrag(event.GetInt(), event.GetExtraLong());
	}

	void AddShapesToCanvas(const std::vector<Shape>& shapes)
	{
		for (const auto& shape : shapes)
		{
			CCanvasFrame frame(
				wxRealPoint(shape.left, shape.top), shape.width, shape.height
			);

			switch (m_MODEL_TYPE_TO_CANVAS_TYPE.at(shape.type))
			{
			case CCanvasShapeType::Ellipse:
				m_canvas->AddEllipse(frame, m_DEFAULT_SHAPE_COLOR, m_DEFAULT_SHAPE_COLOR, true, false);
				break;
			case CCanvasShapeType::Rectangle:
				m_canvas->AddRectangle(frame, m_DEFAULT_SHAPE_COLOR, m_DEFAULT_SHAPE_COLOR, true, false);
				break;
			case CCanvasShapeType::Triangle:
				m_canvas->AddTriangle(frame, m_DEFAULT_SHAPE_COLOR, m_DEFAULT_SHAPE_COLOR, true, false);
				break;
			}
		}
	}

	void AddFrameToCanvas(Shape* shape)
	{
		CCanvasFrame frame(
			wxRealPoint(shape->left, shape->top), shape->width, shape->height
		);

		m_canvas->AddRectangle(frame, m_DEFAULT_FRAME_COLOR, m_DEFAULT_FRAME_COLOR, false, true);
		m_canvas->AddEllipse(
			{wxRealPoint(frame.pos.x - m_DEFAULT_FRAME_KEY_POINT_SIZE / 2,
			frame.pos.y - m_DEFAULT_FRAME_KEY_POINT_SIZE / 2), m_DEFAULT_FRAME_KEY_POINT_SIZE,
			m_DEFAULT_FRAME_KEY_POINT_SIZE}, m_DEFAULT_FRAME_COLOR, wxBG_STYLE_PAINT, true, true
		);
		m_canvas->AddEllipse(
			{wxRealPoint(frame.pos.x + frame.width - m_DEFAULT_FRAME_KEY_POINT_SIZE / 2,
			frame.pos.y - m_DEFAULT_FRAME_KEY_POINT_SIZE / 2), m_DEFAULT_FRAME_KEY_POINT_SIZE,
			m_DEFAULT_FRAME_KEY_POINT_SIZE}, m_DEFAULT_FRAME_COLOR, wxBG_STYLE_PAINT, true, true
		);
		m_canvas->AddEllipse(
			{wxRealPoint(frame.pos.x + frame.width - m_DEFAULT_FRAME_KEY_POINT_SIZE / 2,
			frame.pos.y + frame.height - m_DEFAULT_FRAME_KEY_POINT_SIZE / 2), 
			m_DEFAULT_FRAME_KEY_POINT_SIZE, m_DEFAULT_FRAME_KEY_POINT_SIZE}, 
			m_DEFAULT_FRAME_COLOR, wxBG_STYLE_PAINT, true, true
		);
		m_canvas->AddEllipse(
			{wxRealPoint(frame.pos.x - m_DEFAULT_FRAME_KEY_POINT_SIZE / 2,
			frame.pos.y + frame.height - m_DEFAULT_FRAME_KEY_POINT_SIZE / 2), 
			m_DEFAULT_FRAME_KEY_POINT_SIZE, m_DEFAULT_FRAME_KEY_POINT_SIZE
			}, m_DEFAULT_FRAME_COLOR, wxBG_STYLE_PAINT, true, true
		);
	}

	wxPanel* CreateButtonPanel(wxWindow* parent)
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

	const std::map<std::string, CCanvasShapeType> m_MODEL_TYPE_TO_CANVAS_TYPE = {
		{ "ellipse", CCanvasShapeType::Ellipse },
		{ "rectangle", CCanvasShapeType::Rectangle },
		{ "triangle", CCanvasShapeType::Triangle },
	};

	const wxColor m_DEFAULT_SHAPE_COLOR = wxColor(100, 200, 200);
	const wxColor m_DEFAULT_FRAME_COLOR = wxColor(100, 200, 300);
	const double m_DEFAULT_FRAME_KEY_POINT_SIZE = 20;

	CCanvas* m_canvas;
	IPictureController* m_controller;
};