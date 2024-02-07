#pragma once

#include <memory>
#include <list>

#include "../History/IMemento.h"
#include "../Shape/CShape.h"

struct CPictureData
{
	std::list<std::shared_ptr<IShape>> shapes;
	std::shared_ptr<IShape> currShape;
};

class CPictureMemento : public IMemento<CPictureData>
{
public:
	CPictureMemento(CPictureData data)
		: m_data(data)
	{
	}

	CPictureData State()const override
	{
		return m_data;
	}

private:
	CPictureData m_data;
};