#pragma once

#include "Duck.h"
#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceBehavior.h"

#include <iostream>
#include <memory>

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWayBehavior, MuteQuackBehavior, DanceNoWayBehavior)
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}

	void Dance() override {}
};