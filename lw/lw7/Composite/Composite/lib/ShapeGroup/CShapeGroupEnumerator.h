#pragma once

#include <functional>

#include "../ShapeGroup/IShapeGroupEnumerator.h"

class CShapeGroupEnumerator : public IShapeGroupEnumerator
{
public:
	CShapeGroupEnumerator(IShapeGroup& group)
		: m_group(group)
	{
	}

	void EnumerateAll(CShapeGroupEnumeratorCallback callback)override
	{
		for (size_t index = 0; index < m_group.GetShapeCount(); index++)
		{
			callback(*m_group.GetShapeAtIndex(index).get());
		}
	}

private:
	IShapeGroup& m_group;
};