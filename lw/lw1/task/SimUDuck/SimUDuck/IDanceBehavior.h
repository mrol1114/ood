#pragma once
class IDanceBehavior
{
public:
	~IDanceBehavior() = default;
	virtual void Dance() const = 0;
};