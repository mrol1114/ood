#pragma once

#include <memory>
#include <array>
#include <algorithm>

#include "../Picture/IPicture.h"
#include "./CKeyPoint.h"
#include "./IWorkboard.h"
#include "../History/CHistory.h"
#include "../Picture/CPictureMemento.h"

class CWorkboard : public IWorkboard
{
public:
	CWorkboard(IPicture* picture, IOriginator<CPictureMemento>* originator);

	void HandleClick(double x, double y)override;
	void HandleDrag(double x, double y)override;
	void FinishDrag()override;

	void AddShape(ShapeType type)override;

	void Undo()override;
	void Redo()override;

	CPictureIterator GetShapesIterator()const override;
	std::shared_ptr<IShape> GetCurrShape()const override;

private:
	void UpdateKeyPointsCoors();
	void ResizeCurrShape(double mouseX, double mouseY);
	void MoveCurrShape(double x, double y);
	void SetIsResizing(double x, double y);

	inline static const double m_FRAME_KEY_POINTS_SIZE = 20;
	inline static const CFrame m_KEY_POINT_INIT_FRAME = {
		0, 0, m_FRAME_KEY_POINTS_SIZE, m_FRAME_KEY_POINTS_SIZE
	};
	inline static const CFrame m_DEFAULT_FRAME = { 320, 320, 100, 100 };

	std::array<CKeyPoint, 4> m_keyPoints = {
		CKeyPoint{m_KEY_POINT_INIT_FRAME},
		CKeyPoint{m_KEY_POINT_INIT_FRAME},
		CKeyPoint{m_KEY_POINT_INIT_FRAME},
		CKeyPoint{m_KEY_POINT_INIT_FRAME}
	};

	IPicture* m_picture;
	CHistory<CPictureMemento> m_history;
	bool m_isResizing = false;
	bool m_isDragging = false;
	bool m_hasLastCoor = false;
	double m_lastCoorX = 0;
	double m_lastCoorY = 0;
};