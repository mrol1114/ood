#pragma once

#include <vector>
#include <stdexcept>

#include "./IPicture.h"

class Picture : public IPicture
{
public:
	Picture(double width, double height)
	{
		if (width < 0 || height < 0)
		{
			throw std::invalid_argument("");
		}

		m_height = height;
		m_width = width;
	}

	std::shared_ptr<IShape> GetCurrShape() const override
	{
		return m_currShape;
	}

	void SetCurrShape(std::shared_ptr<IShape> shape)override
	{
		m_currShape = shape;
	}

	void AddShape(std::shared_ptr<IShape> shape)override
	{
		m_shapes.push_back(shape);
	}

	std::shared_ptr<IShape> GetShapeByCoors(double x, double y) const override
	{
		std::shared_ptr<IShape> resShape = nullptr;

		for (const auto& shape : m_shapes)
		{
			if (shape->IsShapeIncludePoint(x, y) 
				&& (!resShape || resShape->GetFrame().GetDepth() < shape->GetFrame().GetDepth()))
			{
				resShape = shape;
			}
		}

		return resShape;
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

		if (x >= 0 && y >= 0 && x <= m_width && y <= m_height)
		{
			m_currShape->SetFrame({x, y, 
				m_currShape->GetFrame().GetWidth(), 
				m_currShape->GetFrame().GetHeight(),
				m_currShape->GetFrame().GetDepth()
			});
		}
	}

	CPictureIterator GetIterator() override
	{
		return CPictureIterator(m_shapes);
	}

private:
	void EnsureCurrShapeExists()
	{
		if (!m_currShape)
		{
			throw std::runtime_error("Curr shape does not initialized");
		}
	}

	std::shared_ptr<IShape> m_currShape = nullptr;
	std::vector<std::shared_ptr<IShape>> m_shapes = {};

	double m_width;
	double m_height;
	unsigned int m_nextLevel = 0;
};