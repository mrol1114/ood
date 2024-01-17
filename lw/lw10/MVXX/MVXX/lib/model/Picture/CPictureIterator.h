#pragma once

#include <memory>
#include <list>
#include <stdexcept>

#include "../Shape/IShape.h"

class CPictureIterator
{
public:
	CPictureIterator(std::list<std::shared_ptr<IShape>>& shapes)
		: m_curr(shapes.begin())
		, m_end(shapes.end())
	{
	}

	bool HasNext()const
	{
		return m_curr != m_end;
	}

	std::shared_ptr<IShape>& Get()const
	{
		return *m_curr;
	}

	void Next()
	{
		if (m_curr == m_end)
		{
			throw std::runtime_error("Iterator exceeds boudaries");
		}

		m_curr++;
	}

private:
	std::list<std::shared_ptr<IShape>>::iterator m_curr;
	std::list<std::shared_ptr<IShape>>::iterator m_end;
};