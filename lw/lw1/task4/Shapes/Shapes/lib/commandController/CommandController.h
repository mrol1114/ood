#include <iostream>
#include <sstream>
#include <unordered_map>
#include <memory>

#include "../shapes/Picture.h"
#include "./command/ICommand.h"
#include "./command/AddShapeCommand.h"
#include "./command/ChangeColorCommand.h"
#include "./command/ChangeShapeCommand.h"
#include "./command/DeleteShapeCommand.h"
#include "./command/DrawPictureCommand.h"
#include "./command/DrawShapeCommand.h"
#include "./command/ListCommand.h"
#include "./command/MovePictureCommand.h"
#include "./command/MoveShapeCommand.h"
#include "./command/HelpCommand.h"

class CommandController
{
public:
	CommandController(std::ostream& outputStream, std::shared_ptr<Picture> picture)
		: m_outputStream(outputStream)
		, m_picture(picture)
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
		std::string commandName;
		input >> commandName;

		if (commandName == m_EXIT)
		{
			return false;
		}

		auto commandType = ConvertCommandNameToType(commandName);
		m_command = CreateCommand(input, commandType);
	}

private:
	CommandType ConvertCommandNameToType(const std::string typeName)
	{
		if (!m_COMMAND_NAME_TO_TYPE.contains(typeName))
		{
			throw std::invalid_argument("Error! Command not found");
		}
		else
		{
			return m_COMMAND_NAME_TO_TYPE.at(typeName);
		}
	}

	std::unique_ptr<ICommand> CreateCommand(std::istream& input, CommandType type)
	{
		switch (type)
		{
		case CommandType::AddShape:
			return std::make_unique<AddShapeCommand>(input, m_picture);
		case CommandType::MoveShape:
			return std::make_unique<MoveShapeCommand>(input, m_picture);
		case CommandType::MovePicture:
			return std::make_unique<MovePictureCommand>(input, m_picture);
		case CommandType::DeleteShape:
			return std::make_unique<DeleteShapeCommand>(input, m_picture);
		case CommandType::DrawShape:
			return std::make_unique<DrawShapeCommand>(input, m_picture);
		case CommandType::DrawPicture:
			return std::make_unique<DrawPictureCommand>(m_picture);
		case CommandType::List:
			return std::make_unique<ListCommand>(m_outputStream, m_picture);
		case CommandType::ChangeColor:
			return std::make_unique<ChangeColorCommand>(input, m_picture);
		case CommandType::ChangeShape:
			return std::make_unique<ChangeShapeCommand>(input, m_picture);
		case CommandType::Help:
			return std::make_unique<HelpCommand>(m_outputStream, m_COMMAND_NAME_TO_TYPE);
		default:
			throw std::invalid_argument("Error! Command does not have execution class");
		}
	}

	const std::unordered_map<std::string, CommandType> m_COMMAND_NAME_TO_TYPE = {
		{"AddShape", CommandType::AddShape},
		{"MoveShape", CommandType::MoveShape},
		{"MovePicture", CommandType::MovePicture},
		{"DeleteShape", CommandType::DeleteShape},
		{"DrawShape", CommandType::DrawShape},
		{"DrawPicture", CommandType::DrawPicture},
		{"List", CommandType::List},
		{"ChangeColor", CommandType::ChangeColor},
		{"ChangeShape", CommandType::ChangeShape},
		{"Help", CommandType::Help},
	};

	const std::string m_EXIT = "exit";

	std::unique_ptr<ICommand> m_command = nullptr;
	std::ostream& m_outputStream;
	std::shared_ptr<Picture> m_picture;
};