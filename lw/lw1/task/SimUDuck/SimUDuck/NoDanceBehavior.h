#pragma once
#include "IDanceBehavior.h"

class NoDanceBehavior: IDanceBehavior
{
public:
	void Dance() const override {}
};