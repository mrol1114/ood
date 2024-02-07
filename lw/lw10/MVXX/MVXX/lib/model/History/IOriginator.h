#pragma once

#include "./IMemento.h"

template<typename MementoType>
class IOriginator
{
public:
	virtual MementoType* Save() = 0;

	virtual void Restore(MementoType* memento) = 0;

	virtual ~IOriginator() = default;
};