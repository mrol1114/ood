#pragma once

#include <iostream>
#include <map>

#include "../Document/IDocument.h"
#include "../Command/CConsoleCommand.h"
#include "./ConsoleControllerItem.h"

#include "./Commands/DeleteItemCommand.h"
#include "./Commands/HelpCommand.h"
#include "./Commands/InsertImageCommand.h"
#include "./Commands/InsertParagraphCommand.h"
#include "./Commands/ListCommand.h"
#include "./Commands/RedoCommand.h"
#include "./Commands/ReplaceTextCommand.h"
#include "./Commands/ResizeImageCommand.h"
#include "./Commands/SaveCommand.h"
#include "./Commands/SetTitleCommand.h"
#include "./Commands/UndoCommand.h"

class ConsoleController
{
public:
	ConsoleController(std::ostream& outputStream, std::shared_ptr<IDocument> document)
		: m_outputStream(outputStream)
		, m_document(document)
	{
	}

	void ExecuteCommand()
	{
		if (!m_command)
		{
			throw std::runtime_error("Error! Executing uninitialized command");
		}
		m_command->Execute();
		m_command = nullptr;
	}

	bool ReadCommand(std::istream& input)
	{
		std::string commandShortcut;
		input >> commandShortcut;

		if (commandShortcut == m_EXIT)
		{
			return false;
		}

		auto item = GetItem(commandShortcut);
		m_command = CreateCommand(input, item.commandType);
		return true;
	}

private:
	const ConsoleControllerItem& GetItem(const std::string commandShortcut)
	{
		if (!m_COMMANDS.contains(commandShortcut))
		{
			throw std::invalid_argument("Error! Command not found");
		}
		else
		{
			return m_COMMANDS.at(commandShortcut);
		}
	}

	std::unique_ptr<IConsoleCommand> CreateCommand(std::istream& input, ConsoleCommandType commandType)
	{
		switch (commandType)
		{
		case ConsoleCommandType::DeleteItem:
			return std::make_unique<DeleteItemCommand>(input, m_document);
		case ConsoleCommandType::Help:
			return std::make_unique<HelpCommand>(m_outputStream, m_COMMANDS);
		case ConsoleCommandType::InsertImage:
			return std::make_unique<InsertImageCommand>(input, m_document);
		case ConsoleCommandType::InsertParagraph:
			return std::make_unique<InsertParagraphCommand>(input, m_document);
		case ConsoleCommandType::List:
			return std::make_unique<ListCommand>(m_document, m_outputStream);
		case ConsoleCommandType::Redo:
			return std::make_unique<RedoCommand>(m_document);
		case ConsoleCommandType::ReplaceText:
			return std::make_unique<ReplaceTextCommand>(input, m_document);
		case ConsoleCommandType::ResizeImage:
			return std::make_unique<ResizeImageCommand>(input, m_document);
		case ConsoleCommandType::Save:
			return std::make_unique<SaveCommand>(input, m_document);
		case ConsoleCommandType::SetTitle:
			return std::make_unique<SetTitleCommand>(input, m_document);
		case ConsoleCommandType::Undo:
			return std::make_unique<UndoCommand>(m_document);
		default:
			throw std::invalid_argument("Error! Command does not have execution class");
		}
	}

	const std::map<std::string, ConsoleControllerItem> m_COMMANDS = {
		{"DeleteItem", {
			"Deleting item by index. DeleteItem <position>", 
			ConsoleCommandType::DeleteItem
		}},
		{"Help", {"Printing avaible commands. Help", ConsoleCommandType::Help}},
		{"InsertImage", {
			"Inserting image to document. InsertImage <position>|end <width> <height> <path>",
			ConsoleCommandType::InsertImage
		}},
		{"InsertParagraph", {
			"Inserting paragraph to document. ", 
			ConsoleCommandType::InsertParagraph
		}},
		{"List", {"Printing List of items. List", ConsoleCommandType::List}},
		{"Redo", {"Cancels rolls back of last command. Redo", ConsoleCommandType::Redo}},
		{"ReplaceText", {
			"Replacing text of item. ReplaceText <position> <text>", 
			ConsoleCommandType::ReplaceText
		}},
		{"ResizeImage", {
			"Resizing image of item. ResizeImage <position> <width> <height>", 
			ConsoleCommandType::ResizeImage
		}},
		{"Save", {"Save current document to file. Save <path>", ConsoleCommandType::Save}},
		{"SetTitle", {"Changing title of document. SetTitle <text>", ConsoleCommandType::SetTitle}},
		{"Undo", {"Rolls back the last command. Undo", ConsoleCommandType::Undo}},
	};

	inline static const std::string m_EXIT = "exit";

	std::unique_ptr<IConsoleCommand> m_command = nullptr;
	std::ostream& m_outputStream;
	std::shared_ptr<IDocument> m_document;
};