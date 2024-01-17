#pragma once

#include "../ICommand.h"
#include "../Menu.h"

class ExitCommand : public ICommand
{
public:
	ExitCommand(Menu& menu)
		: m_menu(menu)
	{
	}

	void Execute()override
	{
		m_menu.Exit();
	}

private:
	Menu& m_menu;
};