#pragma once
#include "IDanceBehavior.h"
#include <iostream>

class WaltzBehavior : IDanceBehavior
{
public:
	void Dance() const override
	{
		std::cout << "Dancing waltz" << std::endl;
	}
};