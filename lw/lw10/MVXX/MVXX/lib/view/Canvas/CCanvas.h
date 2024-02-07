#pragma once

#include <wx/wx.h>
#include <list>

#include "./CanvasShape/CCanvasShape.h"

wxDECLARE_EVENT(CANVAS_MOUSE_DOWN, wxCommandEvent);
wxDECLARE_EVENT(CANVAS_MOUSE_UP, wxCommandEvent);
wxDECLARE_EVENT(CANVAS_MOUSE_DRAG, wxCommandEvent);

class CCanvas : public wxPanel
{
public:
    CCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);

    void AddRectangle(CCanvasFrame frame, wxColor fillColor, wxColor strokeColor,
        bool isFillEnabled, bool isStrokeEnabled);
    void AddEllipse(CCanvasFrame frame, wxColor fillColor, wxColor strokeColor,
        bool isFillEnabled, bool isStrokeEnabled);
    void AddTriangle(CCanvasFrame frame, wxColor fillColor, wxColor strokeColor,
        bool isFillEnabled, bool isStrokeEnabled);

    void Clear();
    void Draw();

private:
    void OnPaint(wxPaintEvent& evt);
    void OnMouseDown(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);

    void static DrawTriangle(wxGraphicsContext* gc, CCanvasFrame frame);

    std::list<CCanvasShape> m_shapes;
};