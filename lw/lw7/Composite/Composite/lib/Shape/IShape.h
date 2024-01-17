#pragma once

#include <memory>
#include <optional>

#include "./CFrame.h"
#include "./IFillStyle.h"
#include "./IlineStyle.h"
#include "../Canvas/ICanvas.h"
#include "../Canvas/IDrawable.h"

class IShapeGroup;

class IShape : public IDrawable
{
public:
	virtual CFrame GetFrame()const = 0;
	virtual void SetFrame(CFrame frame) = 0;

	virtual ILineStylePtr const& GetLineStyle()const = 0;
	virtual void SetLineStyle(ILineStylePtr style) = 0;

	virtual IFillStylePtr const& GetFillStyle()const = 0;
	virtual void SetFillStyle(IFillStylePtr style) = 0;

	virtual std::shared_ptr<IShapeGroup> GetGroup() = 0;

	virtual std::string GetShapeName()const = 0;

	virtual ~IShape() = default;
};

using IShapePtr = std::shared_ptr<IShape>;