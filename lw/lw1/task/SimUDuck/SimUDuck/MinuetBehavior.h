#pragma once
#include "IDanceBehavior.h"
#include <iostream>

class MinuetBehavior : IDanceBehavior
{
public:
	void Dance() const override
	{
		std::cout << "Dancing minuet" << std::endl;
	}
};