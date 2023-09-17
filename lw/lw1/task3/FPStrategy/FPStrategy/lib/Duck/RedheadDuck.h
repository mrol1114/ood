#pragma once

#include "Duck.h"
#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceBehavior.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWingsBehavior(), QuackBehavior, DanceMinuetBehavior)
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};