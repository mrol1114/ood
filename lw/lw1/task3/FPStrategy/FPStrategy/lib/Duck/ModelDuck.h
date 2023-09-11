#pragma once

#include "Duck.h"
#include "Fly/FlyNoWayBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceNoWayBehavior.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWayBehavior, QuackBehavior, DanceNoWayBehavior)
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}

	void Dance() override {}
};
