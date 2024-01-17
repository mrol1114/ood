#pragma once

#include <memory>

#include "../Shape/ILineStyle.h"
#include "./IShapeGroupEnumerator.h"

class CShapeGroupLineStyle : public ILineStyle
{
public:
	CShapeGroupLineStyle(std::shared_ptr<IShapeGroupEnumerator> groupEnumerator)
		: m_groupEnumerator(groupEnumerator)
	{
	}

	std::optional<bool> IsEnabled()const override
	{
		std::optional<bool> isEnabled = std::nullopt;
		bool isInitialized = false;

		m_groupEnumerator->EnumerateAll([&](IShape& shape) {
			if (!isInitialized)
			{
				isEnabled = shape.GetLineStyle()->IsEnabled();
				isInitialized = true;
				return;
			}
			if (!isEnabled.has_value() || !shape.GetLineStyle()->IsEnabled().has_value()
				|| isEnabled.value() != shape.GetLineStyle()->IsEnabled().value())
			{
				isEnabled = std::nullopt;
			}
		});

		return isEnabled;
	}

	void Enable(bool enable)override
	{
		m_groupEnumerator->EnumerateAll([enable](IShape& shape) {
			shape.GetLineStyle()->Enable(enable);
		});
	}

	void SetColor(RGBA color)override
	{
		m_groupEnumerator->EnumerateAll([color](IShape& shape) {
			shape.GetLineStyle()->SetColor(color);
		});
	}

	std::optional<RGBA> GetColor()const override
	{
		std::optional<RGBA> color = std::nullopt;
		bool isInitialized = false;

		m_groupEnumerator->EnumerateAll([&](IShape& shape) {
			if (!isInitialized)
			{
				color = shape.GetLineStyle()->GetColor();
				isInitialized = true;
				return;
			}
			if (!color.has_value() || !shape.GetLineStyle()->GetColor().has_value()
				|| color.value() != shape.GetLineStyle()->GetColor().value())
			{
				color = std::nullopt;
			}
		});

		return color;
	}

	void SetLineWidth(double lineWidth)override
	{
		m_groupEnumerator->EnumerateAll([lineWidth](IShape& shape) {
			shape.GetLineStyle()->SetLineWidth(lineWidth);
		});
	}

	std::optional<double> GetLineWidth()const override
	{
		std::optional<double> lineWidth = std::nullopt;
		bool isInitialized = false;

		m_groupEnumerator->EnumerateAll([&](IShape& shape) {
			if (!isInitialized)
			{
				lineWidth = shape.GetLineStyle()->GetLineWidth();
				isInitialized = true;
				return;
			}
			if (!lineWidth.has_value() || !shape.GetLineStyle()->GetLineWidth().has_value()
				|| lineWidth.value() != shape.GetLineStyle()->GetLineWidth().value())
			{
				lineWidth = std::nullopt;
			}
		});

		return lineWidth;
	}

private:
	std::shared_ptr<IShapeGroupEnumerator> m_groupEnumerator;
};