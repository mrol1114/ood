#include <iostream>

#include "Condiments.h"
#include "Beverages.h"

void DialogWithUser()
{
	std::cout << "Type 1 for coffee or 2 for tea\n";
	int beverageChoice;
	std::cin >> beverageChoice;

	std::unique_ptr<IBeverage> beverage;

	if (beverageChoice == 1)
	{
		beverage = std::make_unique<CCoffee>();
	}
	else if (beverageChoice == 2)
	{
		beverage = std::make_unique<CTea>();
	}
	else
	{
		return;
	}

	int condimentChoice;
	for (;;)
	{
		std::cout << "1 - Lemon, 2 - Cinnamon, 3 - Cream, 4 - chocolate, 5 - Liquor, 0 - Checkout"
			<< std::endl;
		std::cin >> condimentChoice;

		if (condimentChoice == 1)
		{
			beverage = std::make_unique<CLemon>(move(beverage));
		}
		else if (condimentChoice == 2)
		{
			beverage = std::make_unique<CCinnamon>(move(beverage));
		}
		else if (condimentChoice == 3)
		{
			beverage = std::make_unique<CCream>(move(beverage));
		}
		else if (condimentChoice == 4)
		{
			std::cout << "enter number of chocolate slices, maximum 5" << std::endl;
			unsigned int numberOfSlices;
			std::cin >> numberOfSlices;

			beverage = std::make_unique<CChocolate>(move(beverage), numberOfSlices);
		}
		else if (condimentChoice == 5)
		{
			std::cout << "0 - Nutty, 1 - Chocolate" << std::endl;
			unsigned int varietyType;
			std::cin >> varietyType;

			beverage = std::make_unique<CLiquor>(
				move(beverage),
				static_cast<CLiquorType>(varietyType)
			);
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
	DialogWithUser();
}