#pragma once

#include "Duck.h"
#include "Fly/FlyNoWayBehavior.h"
#include "Quack/MuteQuackBehavior.h"
#include "Dance/DanceNoWayBehavior.h"

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