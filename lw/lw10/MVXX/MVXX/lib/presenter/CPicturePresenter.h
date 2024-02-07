#pragma once

#include "../model/Picture/IPicture.h"
#include "../view/IPictureView.h"
#include "./IPicturePresenter.h"
#include "../model/Workboard/IWorkboard.h"

class CPicturePresenter : public IPicturePresenter
{
public:
	CPicturePresenter(IPictureView* view);

	void AddCircle()override;
	void AddRectangle()override;
	void AddTriangle()override;

	void HandleClickOnWorkboard(double x, double y)override;
	void HandleDrag(double x, double y)override;
	void FinishDrag()override;

	void Undo()override;
	void Redo()override;

private:
	void UpdateShapesView();

	IWorkboard* m_workboard;
	IPictureView* m_view;
};