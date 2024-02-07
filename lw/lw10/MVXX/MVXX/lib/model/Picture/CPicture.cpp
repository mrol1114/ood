#include "./CPicture.h"

#include "../Shape/Factory/CShapeFactory.h"

CPicture::CPicture(double width, double height)
{
	if (width < 0 || height < 0)
	{
		throw std::invalid_argument("");
	}

	m_height = height;
	m_width = width;
}

// selection должен быть отделенн от доменной модели
std::shared_ptr<IShape> CPicture::GetCurrShape()const
{
	return m_currShape;
}

void CPicture::SetCurrShape(std::shared_ptr<IShape> shape)
{
	m_currShape = shape;
}

void CPicture::AddShape(CFrame frame, ShapeType type)
{
	m_shapes.push_front(CShapeFactory::CreateShape(type, frame));
}

std::shared_ptr<IShape> CPicture::GetShapeByCoors(double x, double y)const 
{
	for (const auto& shape : m_shapes)
	{
		if (shape->IsShapeIncludePoint(x, y))
		{
			return shape;
		}
	}

	return nullptr;
}

void CPicture::ChangePositionOfCurrShape(double x, double y)
{
	EnsureCurrShapeExists();

	x = x < 0 ? 0 : x;
	x = x > m_width - m_currShape->GetFrame().GetWidth()
		? m_width - m_currShape->GetFrame().GetWidth()
		: x;

	y = y < 0 ? 0 : y;
	y = y > m_height - m_currShape->GetFrame().GetHeight()
		? m_height - m_currShape->GetFrame().GetHeight()
		: y;

	m_currShape->SetFrame({ x, y,
		m_currShape->GetFrame().GetWidth(),
		m_currShape->GetFrame().GetHeight()
	});
}

void CPicture::ChangeSizeOfCurrShape(double x, double y, double width, double height)
{
	x = x < 0 ? 0 : x;
	width = x > m_width - width ? m_width - x : width;
	width = width < m_MINIMUM_SHAPE_SIZE ? m_MINIMUM_SHAPE_SIZE : width;

	y = y < 0 ? 0 : y;
	height = y > m_height - height ? m_height - y : height;
	height = height < m_MINIMUM_SHAPE_SIZE ? m_MINIMUM_SHAPE_SIZE : height;

	m_currShape->SetFrame({ x, y, width, height });
}

CPictureIterator CPicture::GetIterator()
{
	return CPictureIterator(m_shapes);
}

CPictureMemento* CPicture::Save()
{
	std::list<std::shared_ptr<IShape>> shapes;
	std::shared_ptr<IShape> currShape = nullptr;

	for (auto& shape : m_shapes)
	{
		// для создания копии использоваит паттерн прототип
		shapes.push_back(CShapeFactory::CreateShape(shape->GetType(), shape->GetFrame()));
		if (shape == m_currShape)
		{
			currShape = shapes.back();
		}
	}

	return new CPictureMemento({ shapes, currShape });
}

// передача по ссылке
void CPicture::Restore(CPictureMemento* memento)
{
	auto state = memento->State();

	m_shapes = state.shapes;
	m_currShape = state.currShape;
}

void CPicture::EnsureCurrShapeExists()
{
	if (!m_currShape)
	{
		throw std::runtime_error("Curr shape does not initialized");
	}
}