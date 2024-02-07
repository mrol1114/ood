#pragma once

#include <wx/wx.h>
#include <wx/listbook.h>
#include <string>

#include "./Canvas/CCanvas.h"
#include "../presenter/CPicturePresenter.h"
#include "./IPictureView.h"

class CPictureView : public wxFrame, public IPictureView
{
public:
	CPictureView(const std::string& title, const wxPoint& pos, const wxSize& size);

	void UpdateWorkboard(const Shapes& shapes)override;

private:
	void OnAddCircle(wxCommandEvent& event);

	void OnAddTriangle(wxCommandEvent& event);

	void OnAddRectangle(wxCommandEvent& event);

	void OnUndo(wxCommandEvent& event);

	void OnRedo(wxCommandEvent& event);

	void OnCanvasMouseDown(wxCommandEvent& event);

	void OnCanvasMouseUp(wxCommandEvent& event);

	void OnCanvasMouseDrag(wxCommandEvent& event);

	void AddShapesToCanvas(const std::list<Shape>& shapes);

	void AddFrameToCanvas(Shape* shape);

	wxPanel* CreateButtonPanel(wxWindow* parent);

	CCanvas* m_canvas;
	IPicturePresenter* m_presenter;
};