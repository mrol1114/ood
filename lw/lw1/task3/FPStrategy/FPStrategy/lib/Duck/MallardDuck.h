#pragma once

#include "Duck.h"
#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceBehavior.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWingsBehavior(), QuackBehavior, DanceWaltzBehavior)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};