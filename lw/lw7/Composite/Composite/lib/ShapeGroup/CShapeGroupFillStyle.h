#pragma once

#include "../Shape/IFillStyle.h"
#include "./IShapeGroupEnumerator.h"

class CShapeGroupFillStyle : public IFillStyle
{
public:
	CShapeGroupFillStyle(std::shared_ptr<IShapeGroupEnumerator> groupEnumerator)
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
				isEnabled = shape.GetFillStyle()->IsEnabled();
				isInitialized = true;
				return;
			}
			if (!isEnabled.has_value() || !shape.GetFillStyle()->IsEnabled().has_value()
				|| isEnabled.value() != shape.GetFillStyle()->IsEnabled().value())
			{
				isEnabled = std::nullopt;
			}
		});

		return isEnabled;
	}

	void Enable(bool enable)override
	{
		m_groupEnumerator->EnumerateAll([enable](IShape& shape) {
			shape.GetFillStyle()->Enable(enable);
		});
	}

	void SetColor(RGBA color)override
	{
		m_groupEnumerator->EnumerateAll([color](IShape& shape) {
			shape.GetFillStyle()->SetColor(color);
		});
	}

	std::optional<RGBA> GetColor()const override
	{
		std::optional<RGBA> color = std::nullopt;
		bool isInitialized = false;

		m_groupEnumerator->EnumerateAll([&](IShape& shape) {
			if (!isInitialized)
			{
				color = shape.GetFillStyle()->GetColor();
				isInitialized = true;
				return;
			}
			if (!color.has_value() || !shape.GetFillStyle()->GetColor().has_value()
				|| color.value() != shape.GetFillStyle()->GetColor().value())
			{
				color = std::nullopt;
			}
		});

		return color;
	}

private:
	std::shared_ptr<IShapeGroupEnumerator> m_groupEnumerator;
};