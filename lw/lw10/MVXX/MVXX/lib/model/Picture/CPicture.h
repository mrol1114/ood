#pragma once

#include <list>
#include <memory>

#include "./IPicture.h"
#include "../History/IOriginator.h"
#include "./CPictureMemento.h"

class CPicture : public IPicture, public IOriginator<CPictureMemento>
{
public:
	CPicture(double width, double height);

	std::shared_ptr<IShape> GetCurrShape()const override;
	void SetCurrShape(std::shared_ptr<IShape> shape)override;

	void AddShape(CFrame frame, ShapeType type)override;
	std::shared_ptr<IShape> GetShapeByCoors(double x, double y)const override;

	void ChangePositionOfCurrShape(double x, double y)override;
	void ChangeSizeOfCurrShape(double x, double y, double width, double height)override;

	CPictureIterator GetIterator()override;

	// умный указатель
	CPictureMemento* Save()override;

	void Restore(CPictureMemento* memento)override;

private:
	void EnsureCurrShapeExists();

	inline static const double m_MINIMUM_SHAPE_SIZE = 20;

	std::shared_ptr<IShape> m_currShape = nullptr;
	std::list<std::shared_ptr<IShape>> m_shapes = {};

	double m_width;
	double m_height;
};