#pragma once

#include <list>
#include <stdexcept>

#include "./IPicture.h"
#include "../History/CCommandHistory.h"
#include "../Shape/Factory/CShapeFactory.h"
#include "Command/AddShapeCommand.h"
#include "Command/SetCurrShapeCommand.h"

class CPicture : public IPicture
{
public:
	CPicture(double width, double height)
		: m_history(std::make_unique<CCommandHistory>())
	{
		if (width < 0 || height < 0)
		{
			throw std::invalid_argument("");
		}

		m_height = height;
		m_width = width;
	}

	std::shared_ptr<IShape> GetCurrShape()const override
	{
		return m_currShape;
	}

	void SetCurrShape(std::shared_ptr<IShape> shape)override
	{
		m_history->ExecuteAndAddCommand(std::make_unique<SetCurrShapeCommand>(
			m_currShape, shape
		));
	}

	void AddShape(CFrame frame, ShapeType type)override
	{
		m_history->ExecuteAndAddCommand(std::make_unique<AddShapeCommand>(
			m_shapes, CShapeFactory::CreateShape(type, frame, *m_history.get())
		));
	}

	std::shared_ptr<IShape> GetShapeByCoors(double x, double y) const override
	{
		for (const auto& shape : m_shapes)
		{
			if (shape->IsShapeIncludePoint(x, y))
			{
				return shape;
			}
		}

		return nullptr;
	}

	void MoveCurrShapeForward()override
	{
		EnsureCurrShapeExists();
	}

	void MoveCurrShapeBack()override
	{
		EnsureCurrShapeExists();
	}

	void ChangePositionOfCurrShape(double x, double y)override
	{
		EnsureCurrShapeExists();

		x = x < 0 ? 0 : x;
		x = x > m_width - m_currShape->GetFrame().GetWidth()
			? m_width - m_currShape->GetFrame().GetWidth()
			: x;

		y = y < 0 ? 0 : y;
		y = y > m_height - m_currShape->GetFrame().GetHeight()
			? m_height - m_currShape->GetFrame().GetHeight()
			: y;

		m_currShape->SetFrame({ x, y,
			m_currShape->GetFrame().GetWidth(),
			m_currShape->GetFrame().GetHeight()
		});
	}

	void ChangeSizeOfCurrShape(double x, double y, double width, double height)override
	{
		x = x < 0 ? 0 : x;
		width = x > m_width - width ? m_width - x : width;
		width = width < m_MINIMUM_SHAPE_SIZE ? m_MINIMUM_SHAPE_SIZE : width;

		y = y < 0 ? 0 : y;
		height = y > m_height - height ? m_height - y : height;
		height = height < m_MINIMUM_SHAPE_SIZE ? m_MINIMUM_SHAPE_SIZE : height;

		m_currShape->SetFrame({ x, y, width, height });
	}

	const std::list<std::shared_ptr<IShape>>& GetShapes()override
	{
		return m_shapes;
	}

	CPictureIterator GetIterator()override
	{
		return CPictureIterator(m_shapes);
	}

	void Undo()override
	{
		if (m_history->CanUndo())
		{
			m_history->Undo();
		}
	}

	void Redo()override
	{
		if (m_history->CanRedo())
		{
			m_history->Redo();
		}
	}

private:
	void EnsureCurrShapeExists()
	{
		if (!m_currShape)
		{
			throw std::runtime_error("Curr shape does not initialized");
		}
	}

	const double m_MINIMUM_SHAPE_SIZE = 20;

	std::unique_ptr<ICommandHistory> m_history;
	std::shared_ptr<IShape> m_currShape = nullptr;
	std::list<std::shared_ptr<IShape>> m_shapes = {};

	double m_width;
	double m_height;
	unsigned int m_nextLevel = 0;
};