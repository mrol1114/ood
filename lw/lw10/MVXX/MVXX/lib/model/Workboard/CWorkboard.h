#pragma once

#include <memory>
#include <array>
#include <algorithm>

#include "../Picture/IPicture.h"
#include "./KeyPoint.h"
#include "./IWorkboard.h"

class CWorkboard : public IWorkboard
{
public:
	CWorkboard(IPicture* picture)
		: m_picture(picture)
	{
	}

	void HandleClick(double x, double y)override
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

	void HandleDrag(double x, double y)override
	{
		if (!m_hasLastCoor || !m_picture->GetCurrShape())
		{
			return;
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

	void AddShapeToDefaultPosition(ShapeType type)override
	{
		m_picture->AddShape(m_DEFAULT_FRAME, type);
	}

	IPicture* GetPicture()const override
	{
		return m_picture;
	}

private:
	void UpdateKeyPointsCoors()
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

	void ResizeCurrShape(double mouseX, double mouseY)
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

	void MoveCurrShape(double x, double y)
	{
		m_picture->ChangePositionOfCurrShape(
			x - m_lastCoorX + m_picture->GetCurrShape()->GetFrame().GetLeft(),
			y - m_lastCoorY + m_picture->GetCurrShape()->GetFrame().GetTop()
		);
	}

	void SetIsResizing(double x, double y)
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

	const double m_FRAME_KEY_POINTS_SIZE = 20;
	const CFrame m_KEY_POINT_INIT_FRAME = {
		0, 0, m_FRAME_KEY_POINTS_SIZE, m_FRAME_KEY_POINTS_SIZE
	};
	const CFrame m_DEFAULT_FRAME = { 320, 320, 100, 100 };

	std::array<KeyPoint, 4> m_keyPoints = {
		KeyPoint{m_KEY_POINT_INIT_FRAME},
		KeyPoint{m_KEY_POINT_INIT_FRAME},
		KeyPoint{m_KEY_POINT_INIT_FRAME},
		KeyPoint{m_KEY_POINT_INIT_FRAME}
	};

	IPicture* m_picture;
	bool m_isResizing = false;
	bool m_hasLastCoor = false;
	double m_lastCoorX = 0;
	double m_lastCoorY = 0;
};