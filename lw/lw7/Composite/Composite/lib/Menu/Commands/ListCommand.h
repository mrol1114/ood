#pragma once

#include <iostream>

#include "../../Slide/ISlide.h"
#include "../ICommand.h"

class ListCommand : public ICommand
{
public:
	ListCommand(ISlide& slide, std::ostream& output)
		: m_slide(slide)
		, m_output(output)
	{
	}

	void Execute()override
	{
		for (size_t index = 0; index < m_slide.GetShapeCount(); index++)
		{
			m_output << index + 1 << ". ";
			PrintShape(m_slide.GetShapeAtIndex(index), m_output);
		}
	}

private:
	static void PrintShape(IShapePtr shape, std::ostream& output,
		std::string currIndent = "", std::string addIndent = "    ")
	{
		output << currIndent << shape->GetShapeName()
			<< " Top " << shape->GetFrame().GetTop()
			<< " Left " << shape->GetFrame().GetLeft()
			<< " Width " << shape->GetFrame().GetWidth()
			<< " Height " << shape->GetFrame().GetHeight();

		output << " LineRGBA ";
		PrintIsEnabled(shape->GetLineStyle()->IsEnabled(), output);
		output << " ";
		PrintOptional<RGBA>(shape->GetLineStyle()->GetColor(), output);
		output << " LineWidth ";
		PrintOptional<double>(shape->GetLineStyle()->GetLineWidth(), output);

		output << " FillRGBA ";
		PrintIsEnabled(shape->GetFillStyle()->IsEnabled(), output);
		output << " ";
		PrintOptional<RGBA>(shape->GetFillStyle()->GetColor(), output);

		output << std::endl;

		if (shape->GetGroup())
		{
			for (size_t index = 0; index < shape->GetGroup()->GetShapeCount(); index++)
			{
				PrintShape(shape->GetGroup()->GetShapeAtIndex(index),
					output, currIndent + addIndent, addIndent
				);
			}
		}
	}

	template <typename T>
	static void PrintOptional(std::optional<T> optValue, std::ostream& output)
	{
		if (optValue.has_value())
		{
			output << optValue.value();
		}
		else
		{
			output << "undefined";
		}
	}

	static void PrintIsEnabled(std::optional<bool> isEnabled, std::ostream& output)
	{
		if (isEnabled.has_value())
		{
			output << (isEnabled.value() ? "enabled" : "disabled");
		}
		else
		{
			output << "undefined";
		}
	}

	ISlide& m_slide;
	std::ostream& m_output;
};