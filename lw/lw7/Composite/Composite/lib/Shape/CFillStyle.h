#pragma once

#include "./IStyle.h"

class CFillStyle : public IStyle
{
public:
	bool IsEnabled()const override
	{
		return m_isEnabled;
	}

	void Enable(bool enable)override
	{
		m_isEnabled = enable;
	}

private:
	bool m_isEnabled = false;
};