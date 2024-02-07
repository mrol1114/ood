#include "CShape.h"

CShape::CShape(CFrame frame)
	: m_frame(frame)
{
}

CFrame CShape::GetFrame()const
{
	return m_frame;
}

void CShape::SetFrame(CFrame frame)
{
	m_frame = frame;
}