#pragma once

#include <string>

#include "./Commands/ConsoleCommandType.h"

struct ConsoleControllerItem
{
	std::string description;
	ConsoleCommandType commandType;
};