#include <sstream>

#include "./lib/Canvas/CSvgCanvas.h"
#include "./lib/Slide/CSlide.h"
#include "./lib/Menu/Menu.h"
#include "./lib/Menu/Commands/AddShapeCommand.h"
#include "./lib/Menu/Commands/CreateGroupCommand.h"
#include "./lib/Menu/Commands/DeleteShapeCommand.h"
#include "./lib/Menu/Commands/DisableFillStyleCommand.h"
#include "./lib/Menu/Commands/DisableLineStyleCommand.h"
#include "./lib/Menu/Commands/DrawCommand.h"
#include "./lib/Menu/Commands/ListCommand.h"
#include "./lib/Menu/Commands/SetFillColorCommand.h"
#include "./lib/Menu/Commands/SetLineColorCommand.h"
#include "./lib/Menu/Commands/SetLineWidthCommand.h"
#include "./lib/Menu/Commands/UngroupCommand.h"
#include "./lib/Menu/Commands/HelpCommand.h"
#include "./lib/Menu/Commands/ExitCommand.h"
#include "./lib/Menu/Commands/SetFrameCommand.h"

int main()
{
	CSvgCanvas canvas("out.svg");
	CSlide slide;
	Menu menu;
	std::stringstream commandDescr;

	menu.AddItem("AddShape", "",
		std::make_unique<AddShapeCommand>(slide, commandDescr));
	menu.AddItem("CreateGroup", "",
		std::make_unique<CreateGroupCommand>(slide, commandDescr));
	menu.AddItem("DeleteShape", "",
		std::make_unique<DeleteShapeCommand>(slide, commandDescr));
	menu.AddItem("DisableFillStyle", "",
		std::make_unique<DisableFillStyleCommand>(slide, commandDescr));
	menu.AddItem("DisableLineStyle", "",
		std::make_unique<DisableLineStyleCommand>(slide, commandDescr));
	menu.AddItem("Draw", "",
		std::make_unique<DrawCommand>(slide, canvas));
	menu.AddItem("List", "",
		std::make_unique<ListCommand>(slide, std::cout));
	menu.AddItem("SetFillColor", "",
		std::make_unique<SetFillColorCommand>(slide, commandDescr));
	menu.AddItem("SetLineColor", "",
		std::make_unique<SetLineColorCommand>(slide, commandDescr));
	menu.AddItem("SetLineWidth", "",
		std::make_unique<SetLineWidthCommand>(slide, commandDescr));
	menu.AddItem("Ungroup", "",
		std::make_unique<UngroupCommand>(slide, commandDescr));
	menu.AddItem("SetFrame", "",
		std::make_unique<SetFrameCommand>(slide, commandDescr));
	menu.AddItem("Help", "",
		std::make_unique<HelpCommand>(menu));
	menu.AddItem("Exit", "",
		std::make_unique<ExitCommand>(menu));

	std::string input;
	menu.ShowInstructions();
	while (!menu.IsExited()
		&& (std::cout << ">")
		&& getline(std::cin, input))
	{
		commandDescr.str(input);
		commandDescr.clear();
		menu.ExecuteCommand(commandDescr);
	}
}