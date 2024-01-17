#pragma once

#include <memory>
#include <optional>

#include  "../Canvas/RGBA.h"

class IFillStyle
{
public:
	virtual std::optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual void SetColor(RGBA color) = 0;
	virtual std::optional<RGBA> GetColor()const = 0;

	virtual ~IFillStyle() = default;
};

using IFillStylePtr = std::unique_ptr<IFillStyle>;