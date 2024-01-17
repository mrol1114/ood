#pragma once

#include <vector>
#include <stdexcept>
#include <limits>


#include "../Shape/IShape.h"
#include "./IShapeGroup.h"
#include "../Shape/IFillStyle.h"
#include "../Shape/ILineStyle.h"
#include "./CShapeGroupFillStyle.h"
#include "./CShapeGroupLineStyle.h"
#include "./CShapeGroupEnumerator.h"

class CShapeGroup : public IShapeGroup, public std::enable_shared_from_this<IShapeGroup>
{
public:
	CShapeGroup()
		: m_fillStyle(std::make_unique<CShapeGroupFillStyle>(
			std::make_shared<CShapeGroupEnumerator>(*this)
		))
		, m_lineStyle(std::make_unique<CShapeGroupLineStyle>(
			std::make_shared<CShapeGroupEnumerator>(*this)
		))
	{
	}

	CFrame GetFrame()const override
	{
		CFrame frame;
		double minX = std::numeric_limits<double>::max();
		double maxX = 0;
		double minY = std::numeric_limits<double>::max();
		double maxY = 0;

		for (const auto& shape : m_shapes)
		{
			auto shapeFrame = shape->GetFrame();

			if (shapeFrame.GetLeft() + shapeFrame.GetWidth() != 0
				&& shapeFrame.GetTop() + shapeFrame.GetLeft() != 0)
			{
				minX = shapeFrame.GetLeft() < minX ? shapeFrame.GetLeft() : minX;
				minY = shapeFrame.GetTop() < minY ? shapeFrame.GetTop() : minY;
			}

			maxX = shapeFrame.GetLeft() + shapeFrame.GetWidth() > maxX
				? shapeFrame.GetLeft() + shapeFrame.GetWidth()
				: maxX;

			maxY = shapeFrame.GetTop() + shapeFrame.GetHeight() > maxY
				? shapeFrame.GetTop() + shapeFrame.GetHeight()
				: maxY;
		}

		minX = minX == std::numeric_limits<double>::max() ? 0 : minX;
		minY = minY == std::numeric_limits<double>::max() ? 0 : minY;

		// нельзя возвращать ссылку на временный объект
		return { minX, minY, maxX - minX, maxY - minY };
	}

	void SetFrame(CFrame frame)override
	{
		auto currFrame = GetFrame();
		// деление на ноль
		// изменить название(ratio or scale)
		double diffWidth = frame.GetWidth() / currFrame.GetWidth();
		double diffHeight = frame.GetHeight() / currFrame.GetHeight();

		for (auto& shape : m_shapes)
		{
			const auto& shapeFrame = shape->GetFrame();

			shape->SetFrame({
				(shapeFrame.GetLeft() - currFrame.GetLeft()) * diffWidth + frame.GetLeft(),
				(shapeFrame.GetTop() - currFrame.GetTop()) * diffHeight + frame.GetTop(),
				shapeFrame.GetWidth() * diffWidth,
				shapeFrame.GetHeight() * diffHeight
			});
		}
	}

	ILineStylePtr const& GetLineStyle()const override
	{
		return m_lineStyle;
	}

	void SetLineStyle(ILineStylePtr style)override
	{
		m_lineStyle = std::move(style);
	}

	IFillStylePtr const& GetFillStyle()const override
	{
		return m_fillStyle;
	}

	void SetFillStyle(IFillStylePtr style)override
	{
		m_fillStyle = std::move(style);
	}

	void Draw(ICanvas& canvas)const override
	{
		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

	std::shared_ptr<IShapeGroup> GetGroup()override
	{
		return shared_from_this();
	}

	size_t GetShapeCount()const override
	{
		return m_shapes.size();
	}

	IShapePtr const& GetShapeAtIndex(size_t index)const override
	{
		EnsureIndexDoesNotExceedBoundaries(index);
		return m_shapes.at(index);
	}

	void InsertShape(IShapePtr shape, std::optional<size_t> index)override
	{
		if (!index.has_value())
		{
			m_shapes.push_back(std::move(shape));
		}
		else
		{
			EnsureIndexDoesNotExceedBoundaries(index.value());
			m_shapes.insert(m_shapes.begin() + index.value(), std::move(shape));
		}
	}

	void RemoveShapeAtIndex(size_t index)override
	{
		EnsureIndexDoesNotExceedBoundaries(index);
		m_shapes.erase(m_shapes.begin() + index);
	}

	std::string GetShapeName()const override
	{
		return "Composite";
	}

private:
	void EnsureIndexDoesNotExceedBoundaries(size_t index)const
	{
		if (m_shapes.size() <= index)
		{
			throw std::runtime_error("Index exceeds size of container");
		}
	}

	std::vector<IShapePtr> m_shapes = {};
	IFillStylePtr m_fillStyle;
	ILineStylePtr m_lineStyle;
};