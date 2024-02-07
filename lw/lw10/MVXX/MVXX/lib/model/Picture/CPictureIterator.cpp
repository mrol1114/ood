#include "./CPictureIterator.h"

#include <stdexcept>

CPictureIterator::CPictureIterator(std::list<std::shared_ptr<IShape>>& shapes)
	: m_curr(shapes.begin())
	, m_end(shapes.end())
{
}

bool CPictureIterator::HasNext()const
{
	return m_curr != m_end;
}

std::shared_ptr<IShape>& CPictureIterator::Get()const
{
	return *m_curr;
}

void CPictureIterator::Next()
{
	if (m_curr == m_end)
	{
		throw std::runtime_error("Iterator exceeds boudaries");
	}

	m_curr++;
}