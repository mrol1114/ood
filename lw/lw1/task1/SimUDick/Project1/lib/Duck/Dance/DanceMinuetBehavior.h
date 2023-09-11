#pragma once

#include "IDanceBehavior.h"
#include <iostream>

class DanceMinuetBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing minuet!!" << std::endl;
	}
};
