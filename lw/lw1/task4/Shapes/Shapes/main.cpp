#include <iostream>
#include <sstream>
#include <memory>

#include "./lib/commandController/CommandController.h"
#include "./lib/shapes/Picture.h"
#include "./lib/canvas/SvgCanvas.h"

void ValidateParams(int argc)
{
	if (argc != 1)
	{
		throw std::invalid_argument("Invalid run! Run with parameter <program> <outputFileName>");
	}
}

std::shared_ptr<ICanvas> GetSvgCanvas(const std::string& outFileName)
{
	return std::make_shared<SvgCanvas>(outFileName);
}

int main(int argc, char* argv[])
{
	//ValidateParams(argc);

	std::string outFileName = "s.svg";
	std::shared_ptr<Picture> picture = std::make_shared<Picture>(GetSvgCanvas(outFileName));
	CommandController controller(std::cout, picture);

	std::string input;
	std::cout << ">";
	while (std::getline(std::cin, input))
	{
		std::istringstream stream(input);

		try
		{
			if (!controller.ReadCommand(stream))
			{
				return 0;
			}

			controller.ExecuteCommand();
			std::cout << "Executed" << std::endl;
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}

		std::cout << ">";
	}

	return 0;
}