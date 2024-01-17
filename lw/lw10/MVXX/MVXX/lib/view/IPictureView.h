#pragma once

#include <list>

#include "./Shapes.h"

class IPictureView
{
public:
	virtual void UpdateWorkboard(const Shapes& shapes) = 0;

	virtual ~IPictureView() = default;
};