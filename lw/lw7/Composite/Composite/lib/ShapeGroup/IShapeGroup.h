#pragma once

#include "../Shape/IShape.h"
#include "../Shape/IShapes.h"

// ��������� ����������� frame �� ������, ����� ��� ������
class IShapeGroup : public IShapes, public IShape
{
};