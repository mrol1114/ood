#pragma once

const enum class CommandType
{
	AddShape,
	MoveShape,
	MovePicture,
	DeleteShape,
	DrawShape,
	DrawPicture,
	List,
	ChangeColor,
	ChangeShape,
	Help,
};

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual void Execute() = 0;
};