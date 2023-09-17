#pragma once

#include <functional>
#include <iostream>

using DanceStrategy = std::function<void()>;

void DanceMinuetBehavior()
{
	std::cout << "I'm dancing minuet!!" << std::endl;
}

void DanceNoWayBehavior() {}

void DanceWaltzBehavior()
{
	std::cout << "I'm dancing waltz!!" << std::endl;
}