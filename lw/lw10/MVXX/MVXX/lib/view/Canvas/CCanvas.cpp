#include "CCanvas.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

wxDEFINE_EVENT(CANVAS_MOUSE_DOWN, wxCommandEvent);
wxDEFINE_EVENT(CANVAS_MOUSE_UP, wxCommandEvent);
wxDEFINE_EVENT(CANVAS_MOUSE_DRAG, wxCommandEvent);

CCanvas::CCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &CCanvas::OnPaint, this, id);
    Bind(wxEVT_LEFT_DOWN, &CCanvas::OnMouseDown, this, id);
    Bind(wxEVT_MOTION, &CCanvas::OnMouseMove, this, id);
    Bind(wxEVT_LEFT_UP, &CCanvas::OnMouseUp, this, id);
}

void CCanvas::AddRectangle(CCanvasFrame frame, wxColor fillColor, wxColor strokeColor,
    bool isFillEnabled, bool isStrokeEnabled)
{
    m_shapes.push_back(
        { frame, CCanvasShapeType::Rectangle, fillColor, strokeColor, isFillEnabled, isStrokeEnabled }
    );
}

void CCanvas::AddEllipse(CCanvasFrame frame, wxColor fillColor, wxColor strokeColor,
    bool isFillEnabled, bool isStrokeEnabled)
{
    m_shapes.push_back(
        { frame, CCanvasShapeType::Ellipse, fillColor, strokeColor, isFillEnabled, isStrokeEnabled }
    );
}

void CCanvas::AddTriangle(CCanvasFrame frame, wxColor fillColor, wxColor strokeColor,
    bool isFillEnabled, bool isStrokeEnabled)
{
    m_shapes.push_back(
        { frame, CCanvasShapeType::Triangle, fillColor, strokeColor, isFillEnabled, isStrokeEnabled }
    );
}

void CCanvas::Clear()
{
    m_shapes.clear();
}

void CCanvas::Draw()
{
    Refresh();
}

void CCanvas::OnPaint(wxPaintEvent& evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        for (const auto& shape : m_shapes)
        {
            gc->SetBrush(shape.isFillEnabled ? wxBrush(shape.fillColor) : *wxTRANSPARENT_BRUSH);
            gc->SetPen(wxPen(shape.strokeColor));

            switch (shape.type)
            {
            case CCanvasShapeType::Triangle:
                DrawTriangle(gc, shape.frame);
                break;
            case CCanvasShapeType::Rectangle:
                gc->DrawRectangle(shape.frame.pos.x, shape.frame.pos.y,
                    shape.frame.width, shape.frame.height);
                break;
            case CCanvasShapeType::Ellipse:
                gc->DrawEllipse(shape.frame.pos.x, shape.frame.pos.y,
                    shape.frame.width, shape.frame.height);
                break;
            }
        }

        delete gc;
    }
}

void CCanvas::OnMouseDown(wxMouseEvent& event)
{
    wxCommandEvent newEvent(CANVAS_MOUSE_DOWN, GetId());
    newEvent.SetEventObject(this);
    newEvent.SetInt(event.GetPosition().x);
    newEvent.SetExtraLong(event.GetPosition().y);

    ProcessWindowEvent(newEvent);
}

void CCanvas::OnMouseUp(wxMouseEvent& event)
{
    wxCommandEvent newEvent(CANVAS_MOUSE_UP, GetId());
    newEvent.SetEventObject(this);

    ProcessWindowEvent(newEvent);
}

void CCanvas::OnMouseMove(wxMouseEvent& event)
{
    if (event.Dragging()) {
        if (event.LeftIsDown()) {
            wxCommandEvent newEvent(CANVAS_MOUSE_DRAG, GetId());
            newEvent.SetEventObject(this);
            newEvent.SetInt(event.GetPosition().x);
            newEvent.SetExtraLong(event.GetPosition().y);

            ProcessWindowEvent(newEvent);
        }
    }
}

void CCanvas::DrawTriangle(wxGraphicsContext* gc, CCanvasFrame frame)
{
    auto path = gc->CreatePath();

    wxPoint2DDouble points[3] = {
        {frame.pos.x, frame.pos.y + frame.height},
        {frame.pos.x + frame.width / 2, frame.pos.y},
        {frame.pos.x + frame.width, frame.pos.y + frame.height}
    };

    gc->DrawLines(3, points);
}