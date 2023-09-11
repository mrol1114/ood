#pragma once

#include "Duck.h"
#include "Fly/FlyNoWayBehavior.h"
#include "Quack/SqueakBehavior.h"
#include "Dance/DanceNoWayBehavior.h"

#include <iostream>

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWayBehavior, SqueakBehavior, DanceNoWayBehavior)
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}

	void Dance() override {}
};