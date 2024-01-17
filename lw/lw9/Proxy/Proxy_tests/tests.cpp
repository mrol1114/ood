#define CATCH_CONFIG_MAIN
#include "../../../../lib/catch.hpp"

#include <algorithm>

#include "../Proxy/lib/Image/Image.h"

SCENARIO("testing tile")
{
	WHEN("creating tile without color")
	{
		Tile tile;

		for (int y = 0; y < Tile::SIZE; y++)
		{
			for (int x = 0; x < Tile::SIZE; x++)
			{
				REQUIRE(tile.GetPixel({ x, y }) == ' ');
			}
		}
	}

	WHEN("creating tile with color")
	{
		Tile tile('H');

		for (int y = 0; y < Tile::SIZE; y++)
		{
			for (int x = 0; x < Tile::SIZE; x++)
			{
				REQUIRE(tile.GetPixel({ x, y }) == 'H');
			}
		}
	}

	GIVEN("a tile with '$' color")
	{
		Tile tile('$');

		WHEN("getting pixel of tile outside of boundries")
		{
			REQUIRE(tile.GetPixel({ Tile::SIZE, Tile::SIZE }) == ' ');
			REQUIRE(tile.GetPixel({ -1, -1 }) == ' ');
		}

		WHEN("setting pixel of tile in boundries")
		{
			tile.SetPixel({ 0, 1 }, 'T');
			
			REQUIRE(tile.GetPixel({ 0, 1 }) == 'T');
		}

		WHEN("setting pixel of tile outside of boundries")
		{
			REQUIRE_NOTHROW(tile.SetPixel({ Tile::SIZE, Tile::SIZE }, 'T'));
			REQUIRE_NOTHROW(tile.SetPixel({ -1, -1 }, 'Y'));
			REQUIRE(tile.GetPixel({ Tile::SIZE, Tile::SIZE }) == ' ');
			REQUIRE(tile.GetPixel({ -1, -1 }) == ' ');
		}

		WHEN("copying tile")
		{
			Tile newTile = tile;

			tile.SetPixel({ 0, 0 }, 'N');
			REQUIRE(newTile.GetPixel({ 0, 0 }) == '$');
		}
	}
}

SCENARIO("testing image")
{
	WHEN("creating image with 1 tile")
	{
		Image image(Size{ 8, 8 }, '$');
		//REQUIRE(image.getTiles().size() == 1);
	}

	WHEN("creating image with 2 rows and 2 columns of tiles")
	{
		//Image image(Size{ 36, 36 });

		//REQUIRE(image.getTiles().size() == 2);
		//REQUIRE(image.getTiles()[0].size() == 2);
		//REQUIRE(image.getTiles()[1].size() == 2);
		//REQUIRE(image.getTiles()[0][0]->GetInstanceCount() == 4);
		//REQUIRE(&*image.getTiles()[0][0] == &*image.getTiles()[0][1]);
		//REQUIRE(&*image.getTiles()[0][1] == &*image.getTiles()[1][0]);
		//REQUIRE(&*image.getTiles()[1][0] == &*image.getTiles()[1][1]);
	}

	WHEN("creating image with size not divisible on Tile SIZE")
	{
		//Image image(Size{ 40, 40 });

		//REQUIRE(image.getTiles().size() == 3);
		//REQUIRE(image.getTiles()[0].size() == 3);
		//REQUIRE(image.getTiles()[1].size() == 3);
		//REQUIRE(image.getTiles()[0][0]->GetInstanceCount() == 6);
	}

	WHEN("getting pixel in boundaries")
	{
	}

	WHEN("getting pixel of image outisde of boundaries")
	{
	}

	WHEN("setting pixel in boundaries")
	{
	}

	WHEN("setting pixel of image outisde of boundaries")
	{

	}
}