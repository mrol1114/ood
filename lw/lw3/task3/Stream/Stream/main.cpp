#include <iostream>
#include <algorithm>
#include <random>
#include "./lib/Parser/CommandParametersParser.h"
#include "./lib/FileAssembler.h"

// не должна принимать дополнительнгый параметр
int main(int argc, char* argv[])
{
	try
	{
		CommandParametersParser parser;
		AssembleFile(parser.Parse(argc, argv));
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
	}
}