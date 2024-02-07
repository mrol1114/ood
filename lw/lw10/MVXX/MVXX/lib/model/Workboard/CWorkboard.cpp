#include "./CWorkboard.h"

CWorkboard::CWorkboard(IPicture* picture, IOriginator<CPictureMemento>* originator)
	: m_picture(picture)
	, m_history(originator)
{
}

void CWorkboard::HandleClick(double x, double y)
{
	auto clickedShape = m_picture->GetShapeByCoors(x, y);

	if (m_picture->GetCurrShape())
	{
		UpdateKeyPointsCoors();
		SetIsResizing(x, y);

		if (!m_isResizing)
		{
			m_picture->SetCurrShape(clickedShape);
		}
	}
	else
	{
		m_picture->SetCurrShape(clickedShape);

		if (m_picture->GetCurrShape())
		{
			UpdateKeyPointsCoors();
			SetIsResizing(x, y);
		}
	}

	m_lastCoorX = x;
	m_lastCoorY = y;
	m_hasLastCoor = true;
}

void CWorkboard::HandleDrag(double x, double y)
{
	if (!m_hasLastCoor || !m_picture->GetCurrShape())
	{
		return;
	}
	if (!m_isDragging)
	{
		m_isDragging = true;
		m_history.Save();
	}

	UpdateKeyPointsCoors();
	if (m_isResizing)
	{
		ResizeCurrShape(x, y);
	}
	else
	{
		MoveCurrShape(x, y);
	}

	m_lastCoorX = x;
	m_lastCoorY = y;
	m_hasLastCoor = true;
}

void CWorkboard::FinishDrag()
{
	if (m_isDragging)
	{
		m_history.Save();
		m_isDragging = false;
	}
}

void CWorkboard::AddShape(ShapeType type)
{
	m_history.Save();
	m_picture->AddShape(m_DEFAULT_FRAME, type);
	m_history.Save();
}

void CWorkboard::Undo()
{
	m_history.Undo();
	m_history.Undo();
}

void CWorkboard::Redo()
{
	m_history.Redo();
	m_history.Redo();
}

CPictureIterator CWorkboard::GetShapesIterator() const
{
	return m_picture->GetIterator();
}

std::shared_ptr<IShape> CWorkboard::GetCurrShape() const
{
	return m_picture->GetCurrShape();
}

void CWorkboard::UpdateKeyPointsCoors()
{
	m_keyPoints[0].SetFrame({
		m_picture->GetCurrShape()->GetFrame().GetLeft() - m_FRAME_KEY_POINTS_SIZE / 2,
		m_picture->GetCurrShape()->GetFrame().GetTop() - m_FRAME_KEY_POINTS_SIZE / 2,
		m_FRAME_KEY_POINTS_SIZE,
		m_FRAME_KEY_POINTS_SIZE
	});

	m_keyPoints[1].SetFrame({
		m_picture->GetCurrShape()->GetFrame().GetLeft()
		+ m_picture->GetCurrShape()->GetFrame().GetWidth() - m_FRAME_KEY_POINTS_SIZE / 2,
		m_picture->GetCurrShape()->GetFrame().GetTop() - m_FRAME_KEY_POINTS_SIZE / 2,
		m_FRAME_KEY_POINTS_SIZE,
		m_FRAME_KEY_POINTS_SIZE
	});

	m_keyPoints[2].SetFrame({
		m_picture->GetCurrShape()->GetFrame().GetLeft()
		+ m_picture->GetCurrShape()->GetFrame().GetWidth() - m_FRAME_KEY_POINTS_SIZE / 2,
		m_picture->GetCurrShape()->GetFrame().GetTop()
		+ m_picture->GetCurrShape()->GetFrame().GetHeight() - m_FRAME_KEY_POINTS_SIZE / 2,
		m_FRAME_KEY_POINTS_SIZE,
		m_FRAME_KEY_POINTS_SIZE
	});

	m_keyPoints[3].SetFrame({
		m_picture->GetCurrShape()->GetFrame().GetLeft() - m_FRAME_KEY_POINTS_SIZE / 2,
		m_picture->GetCurrShape()->GetFrame().GetTop()
		+ m_picture->GetCurrShape()->GetFrame().GetHeight() - m_FRAME_KEY_POINTS_SIZE / 2,
		m_FRAME_KEY_POINTS_SIZE,
		m_FRAME_KEY_POINTS_SIZE
	});
}

void CWorkboard::ResizeCurrShape(double mouseX, double mouseY)
{
	double mouseDiffX = mouseX - m_lastCoorX;
	double mouseDiffY = mouseY - m_lastCoorY;
	double left = m_picture->GetCurrShape()->GetFrame().GetLeft();
	double top = m_picture->GetCurrShape()->GetFrame().GetTop();
	double width = m_picture->GetCurrShape()->GetFrame().GetWidth();
	double height = m_picture->GetCurrShape()->GetFrame().GetHeight();

	if (mouseX - left > m_FRAME_KEY_POINTS_SIZE)
	{
		width += mouseDiffX;
	}
	else
	{
		left += mouseDiffX;
		width -= mouseDiffX;
	}

	if (mouseY - top > m_FRAME_KEY_POINTS_SIZE)
	{
		height += mouseDiffY;
	}
	else
	{
		top += mouseDiffY;
		height -= mouseDiffY;
	}

	m_picture->ChangeSizeOfCurrShape(
		left, top, width, height
	);
}

void CWorkboard::MoveCurrShape(double x, double y)
{
	m_picture->ChangePositionOfCurrShape(
		x - m_lastCoorX + m_picture->GetCurrShape()->GetFrame().GetLeft(),
		y - m_lastCoorY + m_picture->GetCurrShape()->GetFrame().GetTop()
	);
}

void CWorkboard::SetIsResizing(double x, double y)
{
	m_isResizing = false;
	for (auto& keyPoint : m_keyPoints)
	{
		if (keyPoint.IsShapeIncludePoint(x, y))
		{
			m_isResizing = true;
			return;
		}
	}
}