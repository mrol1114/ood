#pragma once

#include <memory>
#include <list>
#include <stdexcept>

#include "../Shape/IShape.h"

class CPictureIterator
{
public:
	CPictureIterator(std::list<std::shared_ptr<IShape>>& shapes);

	bool HasNext()const;

	std::shared_ptr<IShape>& Get()const;

	void Next();

private:
	std::list<std::shared_ptr<IShape>>::iterator m_curr;
	std::list<std::shared_ptr<IShape>>::iterator m_end;
};