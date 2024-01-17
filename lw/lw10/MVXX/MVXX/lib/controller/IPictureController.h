#pragma once

class IPictureController
{
public:
	virtual void AddCircle() = 0;

	virtual void AddRectangle() = 0;

	virtual void AddTriangle() = 0;

	virtual void HandleClickOnWorkboard(double x, double y) = 0;

	virtual void HandleDrag(double x, double y) = 0;

	virtual void Undo() = 0;

	virtual void Redo() = 0;

	virtual ~IPictureController() = default;
};