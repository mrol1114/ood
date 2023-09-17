#pragma once

#include <functional>
#include <iostream>

using FlyStrategy = std::function<void()>;

void FlyNoWayBehavior() {}

FlyStrategy FlyWithWingsBehavior()
{
	return [flightsCount = 0]() mutable -> void
	{
		std::cout << "Flight number: " << ++flightsCount << std::endl;
		std::cout << "I'm flying with wings!!" << std::endl;
	};
}