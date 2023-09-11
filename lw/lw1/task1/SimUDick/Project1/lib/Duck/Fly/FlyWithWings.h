#pragma once

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		countFlights++;
		std::cout << "Flight number: " << countFlights << std::endl;
		std::cout << "I'm flying with wings!!" << std::endl;
	}

private:
	unsigned int countFlights = 0;
};
