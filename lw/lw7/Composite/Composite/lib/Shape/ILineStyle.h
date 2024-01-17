#pragma once

#include <memory>
#include <optional>

#include  "../Canvas/RGBA.h"

class ILineStyle
{
public:
	virtual std::optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual void SetColor(RGBA color) = 0;
	virtual std::optional<RGBA> GetColor()const = 0;

	virtual void SetLineWidth(double lineWidth) = 0;
	virtual std::optional<double> GetLineWidth()const = 0;

	virtual ~ILineStyle() = default;
};

using ILineStylePtr = std::unique_ptr<ILineStyle>;