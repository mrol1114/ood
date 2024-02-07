#pragma once

template<typename T>
class IMemento
{
public:
	virtual T State() const = 0;

	virtual ~IMemento() = default;
};