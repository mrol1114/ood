#pragma once

#include <memory>
#include <iostream>

#include "../PictureDraft/PictureDraft.h"

class IDesigner
{
public:
	virtual std::unique_ptr<PictureDraft> CreateDraft(std::istream& stream) = 0;
};