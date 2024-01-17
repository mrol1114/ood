#pragma once

#include "../Shape/IShape.h"
#include "../Shape/IShapes.h"

// проверить возвращение frame из группы, когда она пустая
class IShapeGroup : public IShapes, public IShape
{
};