#include "./lib/ConsoleController/ConsoleController.h"
#include "./lib/Document/CHtmlDocument.h"
#include "./lib/History/CCommandHistory.h"
#include "./lib/System/CFileSystemServices.h"

int main()
{
	ConsoleController controller(
		std::cout, 
		std::make_shared<CHtmlDocument>(
			std::make_shared<CFileSystemServices>()
		)
	);

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