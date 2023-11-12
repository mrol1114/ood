#include <iostream>

#include "Condiments.h"
#include "Beverages.h"

void DialogWithUser()
{
	std::cout << "Type 1 for latte, 2 for cappuccino, 3 for tea, 4 for milkshake\n";
	int beverageChoice;
	std::cin >> beverageChoice;

	std::unique_ptr<IBeverage> beverage;

	if (beverageChoice == 1)
	{
		std::cout << "0 - standard, 1 - double\n";
		int varietyChoice;
		std::cin >> varietyChoice;

		beverage = std::make_unique<CLatte>(
			static_cast<LatteSizeType>(varietyChoice)
		);
	}
	else if (beverageChoice == 2)
	{
		std::cout << "0 - standard, 1 - double\n";
		int varietyChoice;
		std::cin >> varietyChoice;

		beverage = std::make_unique<CCappuccino>(
			static_cast<CappuccinoSizeType>(varietyChoice)
		);
	}
	else if (beverageChoice == 3)
	{
		std::cout << "0 - oolong tea, 1 - black tea, 2 - eark grey tea, 3 - cheeky fruit tea\n";
		int varietyChoice;
		std::cin >> varietyChoice;

		beverage = std::make_unique<CTea>(
			static_cast<TeaVarietyType>(varietyChoice)
		);
	}
	else if (beverageChoice == 4)
	{
		std::cout << "0 - small, 1 - medium, 2 - big\n";
		int sizeChoice;
		std::cin >> sizeChoice;

		beverage = std::make_unique<CMilkshake>(
			static_cast<MilkshakeSizeType>(sizeChoice)
		);
	}
	else
	{
		return;
	}

	int condimentChoice;
	for (;;)
	{
		std::cout << "1 - Lemon, 2 - Cinnamon, 0 - Checkout" << std::endl;
		std::cin >> condimentChoice;

		if (condimentChoice == 1)
		{
			beverage = std::make_unique<CLemon>(move(beverage));
		}
		else if (condimentChoice == 2)
		{
			beverage = std::make_unique<CCinnamon>(move(beverage));
		}
		else if (condimentChoice == 0)
		{
			break;
		}
		else
		{
			return;
		}
	}

	std::cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << std::endl;
}

int main()
{
	try
	{
		DialogWithUser();
	}
	catch(std::exception& ex)
	{
		std::cout << ex.what();
	}
}