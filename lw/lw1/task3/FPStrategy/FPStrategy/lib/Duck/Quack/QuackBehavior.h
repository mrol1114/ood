#pragma once

#include <functional>
#include <iostream>

using QuackStrategy = std::function<void()>;

void MuteQuackBehavior() {}

void QuackBehavior()
{
	std::cout << "Quack Quack!!!" << std::endl;
}

void SqueakBehavior()
{
	std::cout << "Squeek!!!" << std::endl;
}