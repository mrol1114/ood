#pragma once

#include "./ICommand.h"

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>

class Menu
{
public:
	void AddItem(
		const std::string& shortcut,
		const std::string& description,
		std::unique_ptr<ICommand>&& command)
	{
		m_items.emplace_back(shortcut, description, std::move(command));
	}

	void ExecuteCommand(std::istream& commandDescr)
	{
		if (m_exit)
		{
			throw std::runtime_error("Can not run command then already exited");
		}

		std::string commandShortcut;
		commandDescr >> commandShortcut;
		auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
			return item.shortcut == commandShortcut;
		});

		if (it != m_items.end())
		{
			try
			{
				it->command->Execute();
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else
		{
			std::cout << "Unknown command\n";
		}
	}

	void ShowInstructions()const
	{
		std::cout << "Commands list:\n";
		for (auto& item : m_items)
		{
			std::cout << "  " << item.shortcut << ": " << item.description << "\n";
		}
	}

	void Exit()
	{
		m_exit = true;
	}

	bool IsExited()
	{
		return m_exit;
	}

private:
	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, std::unique_ptr<ICommand>&& command)
			: shortcut(shortcut)
			, description(description)
			, command(std::move(command))
		{}

		std::string shortcut;
		std::string description;
		std::unique_ptr<ICommand> command;
	};
	std::vector<Item> m_items;
	bool m_exit = false;
};