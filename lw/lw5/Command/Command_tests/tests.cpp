#define CATCH_CONFIG_MAIN
#include "../../../../lib/catch.hpp"
#include <boost/test/unit_test.hpp>
#include <fakeit/boost/fakeit.hpp>

#include <vector>

#include "../Command/lib/Document/DocumentItem/Image/CImage.h"
#include "../Command/lib/History/CCommandHistory.h"
#include "../Command/lib/System/IFileSystemServices.h"
#include "../Command/lib/Document/CHtmlDocument.h"

class SpyCommand : public CDocumentCommand
{
public:
	SpyCommand(std::shared_ptr<std::vector<std::string>> array, unsigned int index)
		: m_array(array)
		, m_index(index)
	{
	}

	~SpyCommand()
	{
		m_array->push_back("delete" + std::to_string(m_index));
	}

private:
	void DoExecute()override
	{
		m_array->push_back("execute" + std::to_string(m_index));
	}

	void DoUnexecute()override
	{
		m_array->push_back("unexecute" + std::to_string(m_index));
	}

	std::shared_ptr<std::vector<std::string>> m_array;
	unsigned int m_index;
};

SCENARIO("initializing image")
{
	CCommandHistory history;

	WHEN("initializing with width and height in interval(1, 10000)")
	{
		CImage image("images/adwa", 100, 500, history);

		REQUIRE(image.GetPath() == "images/adwa");
		REQUIRE(image.GetWidth() == 100);
		REQUIRE(image.GetHeight() == 500);
	}

	WHEN("Initializing with min value")
	{
		CImage image("images/adwa", 1, 1, history);

		REQUIRE(image.GetPath() == "images/adwa");
		REQUIRE(image.GetWidth() == 1);
		REQUIRE(image.GetHeight() == 1);
	}

	WHEN("Initializing with max value")
	{
		CImage image("images/adwa", 10000, 10000, history);

		REQUIRE(image.GetPath() == "images/adwa");
		REQUIRE(image.GetWidth() == 10000);
		REQUIRE(image.GetHeight() == 10000);
	}

	WHEN("Initializing with value more then max")
	{
		REQUIRE_THROWS(CImage("images/adwa", 10001, 10000, history));
		REQUIRE_THROWS(CImage("images/adwa", 10000, 10001, history));
	}

	WHEN("Initializing with value lower then max")
	{
		REQUIRE_THROWS(CImage("images/adwa", 0, 10000, history));
		REQUIRE_THROWS(CImage("images/adwa", 10000, 0, history));
	}
}

SCENARIO("testing history")
{
	CCommandHistory history;
	std::shared_ptr<std::vector<std::string>> array = std::make_shared<std::vector<std::string>>();
	GIVEN("empty history")
	{
		REQUIRE(!history.CanRedo());
		REQUIRE(!history.CanUndo());
		REQUIRE_THROWS(history.Redo());
		REQUIRE_THROWS(history.Undo());

		WHEN("adding Commands")
		{
			history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 1));
			history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 2));

			REQUIRE(array->size() == 2);
			REQUIRE(array->at(0) == "execute1");
			REQUIRE(array->at(1) == "execute2");
		}
	}

	GIVEN("history with 3 mock unexecuted commands")
	{
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 1));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 2));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 3));

		REQUIRE(!history.CanRedo());
		REQUIRE(history.CanUndo());

		WHEN("undo commands")
		{
			history.Undo();
			history.Undo();
			history.Undo();

			REQUIRE(!history.CanUndo());
			REQUIRE(history.CanRedo());
			REQUIRE_THROWS(history.Undo());
			REQUIRE(array->at(3) == "unexecute3");
			REQUIRE(array->at(4) == "unexecute2");
			REQUIRE(array->at(5) == "unexecute1");
		}

		WHEN("adding command after undo")
		{
			history.Undo();
			history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 4));

			REQUIRE(array->at(4) == "execute4");
			REQUIRE(array->at(5) == "delete3");
			REQUIRE(!history.CanRedo());
			REQUIRE(history.CanUndo());

		}
	}

	GIVEN("history with 3 mock executed  commands")
	{
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 1));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 2));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 3));

		history.Undo();
		history.Undo();
		history.Undo();

		WHEN("redo commands")
		{
			history.Redo();
			history.Redo();
			history.Redo();

			REQUIRE(history.CanUndo());
			REQUIRE(!history.CanRedo());
			REQUIRE_THROWS(history.Redo());
			REQUIRE(array->at(6) == "execute1");
			REQUIRE(array->at(7) == "execute2");
			REQUIRE(array->at(8) == "execute3");
		}
	}

	GIVEN("history with maximum number of commands")
	{
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 1));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 2));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 3));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 4));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 5));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 6));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 7));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 8));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 9));
		history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 10));

		REQUIRE(!history.CanRedo());
		REQUIRE(history.CanUndo());

		WHEN("adding new command")
		{
			history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 11));

			REQUIRE(array->at(10) == "execute11");
			REQUIRE(array->at(11) == "delete1");
		}

		WHEN("adding new command after undo 2 commands")
		{
			history.Undo();
			history.Undo();
			history.ExecuteAndAddCommand(std::make_unique<SpyCommand>(array, 11));

			REQUIRE(array->at(12) == "execute11");
			REQUIRE(array->at(13) == "delete10");
			REQUIRE(array->at(14) == "delete9");
		}
	}
}

// print message about assertion fail
SCENARIO("executing document commands")
{
	fakeit::Mock<IFileSystemServices> fileSystemServices;
	fakeit::Fake(Dtor(fileSystemServices));

	CHtmlDocument document(std::shared_ptr<IFileSystemServices>(&fileSystemServices.get()));

	fakeit::Fake(Method(fileSystemServices, CreateDirectoryIfNotExists));
	fakeit::Fake(Method(fileSystemServices, CopyFileByPath));
	fakeit::Fake(Method(fileSystemServices, WriteToFile));

	WHEN("insert paragraph outside of boundaries")
	{
		REQUIRE_THROWS(document.InsertParagraph("new world", 1));
	}

	WHEN("insert image outside of boundaries")
	{
		REQUIRE_THROWS(document.InsertImage("folder/recent/r.png", 200, 300, 1));
	}

	WHEN("insert image")
	{
		document.InsertImage("folder/recent/r.png", 200, 300);

		INFO("Checks possibility of undo");
		REQUIRE(document.CanUndo());
		INFO("Checks items count");
		REQUIRE(document.GetItemsCount() == 1);
		INFO("Checks image width");
		REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 200);
		INFO("Checks image height");
		REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 300);
		INFO("Checks fileName");
		REQUIRE(document.GetItem(0).GetImage()->GetPath().filename() != "r");
		INFO("Checks file extension");
		REQUIRE(document.GetItem(0).GetImage()->GetPath().extension() == ".png");
		INFO("Checks parent path");
		REQUIRE(document.GetItem(0).GetImage()->GetPath().parent_path() == "images");

		INFO("Checks creation of directory images");
		REQUIRE_NOTHROW(fakeit::Verify(Method(fileSystemServices, CreateDirectoryIfNotExists).Using("images")));
		INFO("Checks copy of given image");
		REQUIRE_NOTHROW(fakeit::Verify(Method(fileSystemServices, CopyFileByPath).Using(
			"folder/recent/r.png",
			document.GetItem(0).GetImage()->GetPath().string()
		)));
	}

	WHEN("undo insert image")
	{
		document.InsertImage("folder/recent/r.png", 200, 300);

		document.Undo();

		INFO("Checks possibility of redo");
		REQUIRE(document.CanRedo());
		INFO("Checks items count");
		REQUIRE(document.GetItemsCount() == 0);
		INFO("Ñhecks for the absence of an item");
		REQUIRE_THROWS(document.GetItem(0));
	}

	WHEN("redo insert image")
	{
		document.InsertImage("folder/recent/r.png", 200, 300);

		document.Undo();
		document.Redo();

		INFO("Checks items count");
		REQUIRE(document.GetItemsCount() == 1);
		INFO("Checks image width");
		REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 200);
		INFO("Checks image height");
		REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 300);
		INFO("Checks fileName");
		REQUIRE(document.GetItem(0).GetImage()->GetPath().filename() != "r");
		INFO("Checks file extension");
		REQUIRE(document.GetItem(0).GetImage()->GetPath().extension() == ".png");
		INFO("Checks parent path");
		REQUIRE(document.GetItem(0).GetImage()->GetPath().parent_path() == "images");
	}

	WHEN("insert paragraph")
	{
		document.InsertParagraph("new world");

		INFO("Checks items count");
		REQUIRE(document.GetItemsCount() == 1);
		INFO("Checks text content");
		REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "new world");
	}

	WHEN("undo insert paragraph")
	{
		document.InsertParagraph("new world");

		document.Undo();
		
		INFO("Checks possibility of redo");
		REQUIRE(document.CanRedo());
		INFO("Checks items count");
		REQUIRE(document.GetItemsCount() == 0);
		INFO("Ñhecks for the absence of an item");
		REQUIRE_THROWS(document.GetItem(0));
	}

	WHEN("redo insert paragraph")
	{
		document.InsertParagraph("new world");

		document.Undo();
		document.Redo();

		INFO("Checks items count");
		REQUIRE(document.GetItemsCount() == 1);
		INFO("Checks text content");
		REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "new world");
	}

	WHEN("set title")
	{
		document.SetTitle("new");

		INFO("Checks document title content");
		REQUIRE(document.GetTitle() == "new");
	}

	WHEN("undo set title")
	{
		document.SetTitle("new");

		document.Undo();

		INFO("Checks possibility of redo");
		REQUIRE(document.CanRedo());
		INFO("Checks document title content");
		REQUIRE(document.GetTitle() == "");
	}

	WHEN("set title")
	{
		document.SetTitle("new");

		document.Undo();
		document.Redo();

		INFO("Checks document title content");
		REQUIRE(document.GetTitle() == "new");
	}

	GIVEN("a document with image")
	{
		document.InsertImage("folder/recent/r.png", 200, 300);

		WHEN("resize image")
		{
			document.GetItem(0).GetImage()->Resize(150, 900);
			INFO("Checks image width");
			REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 150);
			INFO("Checks image height");
			REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 900);
		}

		WHEN("undo resize image")
		{
			document.GetItem(0).GetImage()->Resize(150, 900);

			document.Undo();

			INFO("Checks image width");
			REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 200);
			INFO("Checks image height");
			REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 300);
		}
	}

	GIVEN("a document with paragraph")
	{
		document.InsertParagraph("new world");

		WHEN("replace text")
		{
			document.GetItem(0).GetParagraph()->SetText("old world");

			INFO("Checks item text content");
			REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "old world");
		}

		WHEN("replace text")
		{
			document.GetItem(0).GetParagraph()->SetText("old world");

			document.Undo();

			INFO("Checks item text content");
			REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "new world");
		}
	}

	GIVEN("a document with image and paragraph")
	{
		document.InsertImage("folder/recent/r.png", 200, 300);
		document.InsertParagraph("new world");

		WHEN("delete image")
		{
			document.DeleteItem(0);

			INFO("Checks items count");
			REQUIRE(document.GetItemsCount() == 1);
			INFO("Checks item text content");
			REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "new world");
			INFO("Ñhecks for the absence of an item");
			REQUIRE_THROWS(document.GetItem(1));
		}

		WHEN("undo delete image")
		{
			std::string insertedImageRelativePath =
				document.GetItem(0).GetImage()->GetPath().string();
			document.DeleteItem(0);

			document.Undo();

			INFO("Checks items count");
			REQUIRE(document.GetItemsCount() == 2);
			INFO("Checks item text content");
			REQUIRE(document.GetItem(0).GetImage()->GetPath() == insertedImageRelativePath);
			INFO("Checks item text content");
			REQUIRE(document.GetItem(1).GetParagraph()->GetText() == "new world");
		}

		WHEN("delete paragraph")
		{
			std::string insertedImageRelativePath =
				document.GetItem(0).GetImage()->GetPath().string();

			document.DeleteItem(1);

			INFO("Checks items count");
			REQUIRE(document.GetItemsCount() == 1);
			INFO("Checks image path");
			REQUIRE(document.GetItem(0).GetImage()->GetPath() == insertedImageRelativePath);
			INFO("Ñhecks for the absence of an item");
			REQUIRE_THROWS(document.GetItem(1));
		}

		WHEN("undo delete paragraph")
		{
			std::string insertedImageRelativePath =
				document.GetItem(0).GetImage()->GetPath().string();
			document.DeleteItem(1);

			document.Undo();

			INFO("Checks items count");
			REQUIRE(document.GetItemsCount() == 2);
			INFO("Checks image item path");
			REQUIRE(document.GetItem(0).GetImage()->GetPath() == insertedImageRelativePath);
			INFO("Checks paragraph item text");
			REQUIRE(document.GetItem(1).GetParagraph()->GetText() == "new world");
		}

		WHEN("save")
		{
			document.SetTitle("Test");
			document.Save("folder/file.html");

			std::string imagePath = document.GetItem(0).GetImage()->GetPath().string();
			std::string context = "<!DOCTYPE html><html><head>"
				"<title>Test</title></head><body>"
				"<img src=\"" + imagePath + "\" width=\"200\" height=\"300\" >"
				"<p>new world</p>"
				"</body></html>";

			INFO("Checks invoke of writeToFile method");
			REQUIRE_NOTHROW(fakeit::Verify(Method(fileSystemServices, WriteToFile).Using("folder/file.html", context)));
		}
	}
}

SCENARIO("hard delete image")
{
	fakeit::Mock<IFileSystemServices> fileSystemServices;

	CHtmlDocument document(std::shared_ptr<IFileSystemServices>(&fileSystemServices.get()));

	fakeit::Fake(Method(fileSystemServices, CreateDirectoryIfNotExists));
	fakeit::Fake(Method(fileSystemServices, CopyFileByPath));
	fakeit::Fake(Method(fileSystemServices, DeleteFileByPath));
	fakeit::Fake(Dtor(fileSystemServices));

	WHEN("executing new command after undo InsertingImage command")
	{
		document.SetTitle("first");
		document.SetTitle("second");
		document.SetTitle("third");
		document.InsertImage("folder/recent/r.png", 200, 300);
		std::string insertedImageRelativePath =
			document.GetItem(0).GetImage()->GetPath().string();

		document.Undo();
		document.Undo();
		document.InsertParagraph("new world");

		REQUIRE_NOTHROW(fakeit::Verify(Method(fileSystemServices, DeleteFileByPath).Using(insertedImageRelativePath)));
	}

	WHEN("file hard deleted cuz deleting DeleteItem command due history max size")
	{
		document.InsertImage("folder/recent/r.png", 200, 300);
		std::string insertedImageRelativePath =
			document.GetItem(0).GetImage()->GetPath().string();

		document.InsertParagraph("new");
		document.InsertParagraph("old");
		document.DeleteItem(0);
		document.SetTitle("1");
		document.SetTitle("2");
		document.SetTitle("3");
		document.SetTitle("4");
		document.SetTitle("5");
		document.SetTitle("6");
		document.SetTitle("7");
		document.SetTitle("8");
		document.SetTitle("9");
		document.SetTitle("10");

		REQUIRE_NOTHROW(fakeit::Verify(Method(fileSystemServices, DeleteFileByPath).Using(insertedImageRelativePath)));
	}
}