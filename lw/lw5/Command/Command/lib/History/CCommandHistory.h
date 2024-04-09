#pragma once

#include <deque>
#include <iostream>

#include "./ICommandHistory.h"

class CCommandHistory : public ICommandHistory
{
public:
	bool CanUndo()
	{
		return m_nextCommandIndex != 0;
	}

	bool CanRedo()
	{
		auto i = m_commands.size();
		return m_nextCommandIndex < m_commands.size();
	}

	void Undo()
	{
		if (!CanUndo())
		{
			throw std::logic_error("Command can not be undone");
		}

		m_commands[--m_nextCommandIndex]->Unexecute();
	}

	void Redo()
	{
		if (!CanRedo())
		{
			throw std::logic_error("Command can not be redone");
		}

		m_commands[m_nextCommandIndex]->Execute();
		m_nextCommandIndex++;
	}

	void ExecuteAndAddCommand(IDocumentCommandPtr&& command)
	{
		if (m_nextCommandIndex < m_commands.size())
		{
			command->Execute();
			for (size_t index = m_nextCommandIndex; index < m_commands.size(); index++)
			{
				DeleteCommand(index);
			}
			m_commands.resize(++m_nextCommandIndex);
			m_commands.back() = move(command);
		}
		else
		{
			m_commands.emplace_back(nullptr);

			try
			{
				command->Execute();
				m_commands.back() = move(command); 
				++m_nextCommandIndex;
				if (m_commands.size() > m_MAXIMUM_HISTORY_SIZE)
				{
					DeleteCommand(0);
					m_commands.pop_front();
				}
			}
			catch (...)
			{
				m_commands.pop_back();
				throw;
			}
		}
	}

private:
	void DeleteCommand(size_t index)
	{
		try
		{
			m_commands[index]->Delete();
		}
		catch (...)
		{
			// Do nothing
		}
	}

	static const size_t m_MAXIMUM_HISTORY_SIZE = 10;

	std::deque<IDocumentCommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};