#pragma once

#include "./IShape.h"
#include "./CShapeLineStyle.h"
#include "./CShapeFillStyle.h"

class CShape : public IShape
{
public:
	CFrame GetFrame()const override
	{
		return m_frame;
	}

	void SetFrame(CFrame frame)override
	{
		m_frame = frame;
	}

	ILineStylePtr const& GetLineStyle()const override
	{
		return m_lineStyle;
	}

	void SetLineStyle(ILineStylePtr style)override
	{
		m_lineStyle = std::move(style);
	}

	const IFillStylePtr& GetFillStyle()const override
	{
		return m_fillStyle;
	}

	void SetFillStyle(IFillStylePtr style)override
	{
		m_fillStyle = std::move(style);
	}

	std::shared_ptr<IShapeGroup> GetGroup()override
	{
		return nullptr;
	}

	void Draw(ICanvas& canvas)const override
	{
		const auto& lineStyle = GetLineStyle();
		const auto& fillStyle = GetFillStyle();

		fillStyle->IsEnabled().value()
			? canvas.SetFillColor(fillStyle->GetColor().value())
			: canvas.SetFillColor(m_TRANSPARENT_COLOR);

		if (lineStyle->IsEnabled().value())
		{
			canvas.SetLineColor(lineStyle->GetColor().value());
			canvas.SetLineWidth(lineStyle->GetLineWidth().value());
		}
		else
		{
			canvas.SetLineWidth(0);
		}

		DrawShape(canvas);
	}

protected:
	CShape(CFrame frame)
		: m_frame(frame)
		, m_fillStyle(std::make_unique<CShapeFillStyle>())
		, m_lineStyle(std::make_unique<CShapeLineStyle>())
	{
	}

	virtual void DrawShape(ICanvas& canvas)const = 0;

private:
	inline static const RGBA m_TRANSPARENT_COLOR = { 0, 0, 0, 0 };

	IFillStylePtr m_fillStyle;
	ILineStylePtr m_lineStyle;
	CFrame m_frame;
};