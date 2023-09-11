#pragma once

#include "Duck.h"
#include "Fly/FlyWithWingsBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceMinuetBehavior.h"

#include <memory>

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWingsBehavior, QuackBehavior, DanceMinuetBehavior)
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};