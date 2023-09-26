#pragma once

#include <memory>

#include "./ICommand.h"
#include "../../shapes/Picture.h"

class DrawPictureCommand : public ICommand
{
public:
	DrawPictureCommand(std::shared_ptr<Picture> picture)
		: m_picture(picture)
	{
	}

	void Execute() override
	{
		m_picture->DrawPicture();

		for (const auto& id : m_picture->GetIds())
		{
		}
	}

private:
	std::shared_ptr<Picture> m_picture;
};