#pragma once

#include <vector>
#include <stdexcept>
#include <algorithm>

#include "./ISlide.h"
#include "../ShapeGroup/CShapeGroup.h"

class CSlide : public ISlide
{
public:
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
		if (index.has_value())
		{
			EnsureIndexDoesNotExceedBoundaries(index.value());
			m_shapes.insert(m_shapes.begin() + index.value(), std::move(shape));
		}
		else
		{
			m_shapes.push_back(std::move(shape));
		}
	}

	void RemoveShapeAtIndex(size_t index)override
	{
		EnsureIndexDoesNotExceedBoundaries(index);
		m_shapes.erase(m_shapes.begin() + index);
	}

	void CreateGroup(const std::vector<size_t>& shapeIndexes)override
	{
		// size_t cant be lower then 0
		if (shapeIndexes.size() == 0)
		{
			throw std::runtime_error("Can not create group without shapes");
		}

		std::vector<size_t> sortedIndexes = shapeIndexes;
		std::sort(sortedIndexes.begin(), sortedIndexes.end());

		EnsureIndexDoesNotExceedBoundaries(sortedIndexes.back());

		IShapePtr group = std::make_shared<CShapeGroup>();
		for (size_t index = 0; index < shapeIndexes.size(); index++)
		{
			// не передавать nullptr
			group->GetGroup()->InsertShape(m_shapes.at(shapeIndexes[index]), std::nullopt);
		}

		m_shapes.push_back(group);
		for (size_t index = 0; index < sortedIndexes.size(); index++)
		{
			m_shapes.erase(m_shapes.begin() + sortedIndexes[sortedIndexes.size() - index - 1]);
		}
	}

	void Ungroup(size_t groupIndex)override
	{
		EnsureIndexDoesNotExceedBoundaries(groupIndex);
		EnsureItemIsComposite(groupIndex);

		auto group = m_shapes.at(groupIndex)->GetGroup();
		size_t currSize = m_shapes.size();

		try
		{
			for (size_t index = 0; index < group->GetShapeCount(); index++)
			{
				m_shapes.push_back(group->GetShapeAtIndex(index));
			}
		}
		catch (...)
		{
			for (size_t count = currSize; count < m_shapes.size(); count++)
			{
				m_shapes.pop_back();
			}
			throw;
		}

		m_shapes.erase(m_shapes.begin() + groupIndex);
	}

private:
	void EnsureIndexDoesNotExceedBoundaries(size_t index)const
	{
		if (m_shapes.size() <= index)
		{
			throw std::runtime_error("Index exceeds size of container");
		}
	}

	void EnsureItemIsComposite(size_t index)const
	{
		if (!m_shapes.at(index)->GetGroup())
		{
			throw std::runtime_error("Item is not composite");
		}
	}

	std::vector<IShapePtr> m_shapes;
};