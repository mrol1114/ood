#define CATCH_CONFIG_MAIN
#include "../../../../../../lib/catch.hpp"

#include <vector>

#include "../Command/lib/Document/DocumentItem/Image/CImage.h"
#include "../Command/lib/History/CCommandHistory.h"
#include "../Command/lib/System/IFileSystemServices.h"
#include "../Command/lib/Document/CHtmlDocument.h"

class MockFileSystem : public IFileSystemServices
{
public:
	MockFileSystem(std::shared_ptr<std::vector<std::string>> executedCommands)
		: m_executedCommands(executedCommands)
	{
	}

	void CreateDirectoryIfNotExists(const std::string& directoryName)override
	{
		m_executedCommands->push_back("CreateDirectoryIfNotExists " + directoryName);
	}

	void CopyFileByPath(
		const std::filesystem::path& fromPath,
		const std::filesystem::path& toPath
	)override
	{
		m_executedCommands->push_back("CopyFile " + fromPath.string() + " " + toPath.string());
	}

	void DeleteFileByPath(
		const std::filesystem::path& pathToFile
	)override
	{
		m_executedCommands->push_back("DeleteFile " + pathToFile.string());
	}

	void WriteToFile(const std::filesystem::path& path, const std::string& text)override
	{
		m_executedCommands->push_back("WriteToFile " + path.string() + " " + text);
	}

private:
	std::shared_ptr<std::vector<std::string>> m_executedCommands;
};

class MockCommand : public CDocumentCommand
{
public:
	MockCommand(std::shared_ptr<std::vector<std::string>> array, unsigned int index)
		: m_array(array)
		, m_index(index)
	{
	}

	~MockCommand()
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
			history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 1));
			history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 2));

			REQUIRE(array->size() == 2);
			REQUIRE(array->at(0) == "execute1");
			REQUIRE(array->at(1) == "execute2");
		}
	}

	GIVEN("history with 3 mock unexecuted commands")
	{
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 1));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 2));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 3));

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
			history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 4));

			REQUIRE(array->at(4) == "execute4");
			REQUIRE(array->at(5) == "delete3");
			REQUIRE(!history.CanRedo());
			REQUIRE(history.CanUndo());

		}
	}

	GIVEN("history with 3 mock executed  commands")
	{
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 1));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 2));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 3));

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
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 1));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 2));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 3));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 4));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 5));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 6));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 7));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 8));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 9));
		history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 10));

		REQUIRE(!history.CanRedo());
		REQUIRE(history.CanUndo());

		WHEN("adding new command")
		{
			history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 11));

			REQUIRE(array->at(10) == "execute11");
			REQUIRE(array->at(11) == "delete1");
		}

		WHEN("adding new command after undo 2 commands")
		{
			history.Undo();
			history.Undo();
			history.ExecuteAndAddCommand(std::make_unique<MockCommand>(array, 11));

			REQUIRE(array->at(12) == "execute11");
			REQUIRE(array->at(13) == "delete10");
			REQUIRE(array->at(14) == "delete9");
		}
	}
}

SCENARIO("executing document commands")
{
	std::shared_ptr<std::vector<std::string>> executedFileSystemCommands 
		= std::make_shared<std::vector<std::string>>();
	IFileSystemServicesPtr fileSystemServices 
		= std::make_shared<MockFileSystem>(executedFileSystemCommands);
	CHtmlDocument document(fileSystemServices);

	GIVEN("empty document")
	{
		WHEN("inserting image")
		{
			document.InsertImage("folder/recent/r.png", 200, 300);

			REQUIRE(document.GetItemsCount() == 1);
			REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 200);
			REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 300);
			REQUIRE(document.GetItem(0).GetImage()->GetPath().filename() != "r");
			REQUIRE(document.GetItem(0).GetImage()->GetPath().extension() == ".png");
			REQUIRE(document.GetItem(0).GetImage()->GetPath().parent_path() == "images");
			REQUIRE(executedFileSystemCommands->size() == 2);
			REQUIRE(executedFileSystemCommands->at(0) == "CreateDirectoryIfNotExists images");
			REQUIRE(executedFileSystemCommands->at(1) 
				== "CopyFile folder/recent/r.png " 
				+ document.GetItem(0).GetImage()->GetPath().string());

			document.Undo();
			REQUIRE(document.GetItemsCount() == 0);
			REQUIRE_THROWS(document.GetItem(0));
			REQUIRE(executedFileSystemCommands->size() == 2);
		}

		WHEN("inserting paragraph")
		{
			document.InsertParagraph("new world");
			REQUIRE(document.GetItemsCount() == 1);
			REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "new world");

			document.Undo();
			REQUIRE(document.GetItemsCount() == 0);
			REQUIRE_THROWS(document.GetItem(0));
		}

		WHEN("setting title")
		{
			document.SetTitle("new");
			REQUIRE(document.GetTitle() == "new");

			document.Undo();
			REQUIRE(document.GetTitle() == "");
		}
	}

	GIVEN("a document with image")
	{
		document.InsertImage("folder/recent/r.png", 200, 300);

		WHEN("resizing image")
		{
			document.GetItem(0).GetImage()->Resize(150, 900);
			REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 150);
			REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 900);

			document.Undo();
			REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 200);
			REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 300);
		}
	}

	GIVEN("a document with paragraph")
	{
		document.InsertParagraph("new world");

		WHEN("replacing text")
		{
			document.GetItem(0).GetParagraph()->SetText("old world");
			REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "old world");

			document.Undo();
			REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "new world");
		}
	}

	GIVEN("a document with image and paragraph")
	{
		document.InsertImage("folder/recent/r.png", 200, 300);
		document.InsertParagraph("new world");

		REQUIRE(document.GetItemsCount() == 2);
		REQUIRE(document.GetItem(0).GetImage());
		REQUIRE(!document.GetItem(0).GetParagraph());
		REQUIRE(document.GetItem(1).GetParagraph());
		REQUIRE(!document.GetItem(1).GetImage());

		WHEN("deleting image")
		{
			std::string insertedImageRelativePath = 
				document.GetItem(0).GetImage()->GetPath().string();

			document.DeleteItem(0);

			REQUIRE(document.GetItemsCount() == 1);
			REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "new world");
			REQUIRE_THROWS(document.GetItem(1));

			document.Undo();
			REQUIRE(document.GetItemsCount() == 2);
			REQUIRE(document.GetItem(0).GetImage()->GetPath() == insertedImageRelativePath);
			REQUIRE(document.GetItem(1).GetParagraph()->GetText() == "new world");
		}

		WHEN("deleting paragraph")
		{
			std::string insertedImageRelativePath =
				document.GetItem(0).GetImage()->GetPath().string();
			document.DeleteItem(1);

			REQUIRE(document.GetItemsCount() == 1);
			REQUIRE(document.GetItem(0).GetImage()->GetPath() == insertedImageRelativePath);
			REQUIRE_THROWS(document.GetItem(1));

			document.Undo();
			REQUIRE(document.GetItemsCount() == 2);
			REQUIRE(document.GetItem(0).GetImage()->GetPath() == insertedImageRelativePath);
			REQUIRE(document.GetItem(1).GetParagraph()->GetText() == "new world");
		}
	}
}

SCENARIO("hard delete image when executing DeleteItem command")
{
	std::shared_ptr<std::vector<std::string>> executedFileSystemCommands
		= std::make_shared<std::vector<std::string>>();
	IFileSystemServicesPtr fileSystemServices
		= std::make_shared<MockFileSystem>(executedFileSystemCommands);
	CHtmlDocument document(fileSystemServices);

	GIVEN("a document with 3 executed commands")
	{
		document.SetTitle("first");
		document.SetTitle("second");
		document.SetTitle("third");

		WHEN("executing new command after undone InsertingImage command")
		{
			document.InsertImage("folder/recent/r.png", 200, 300);
			std::string insertedImageRelativePath =
				document.GetItem(0).GetImage()->GetPath().string();
			REQUIRE(executedFileSystemCommands->size() == 2);

			document.Undo();
			document.Undo();
			REQUIRE(executedFileSystemCommands->size() == 2);

			document.InsertParagraph("new world");

			REQUIRE(executedFileSystemCommands->size() == 3);
			REQUIRE(executedFileSystemCommands->at(2) == "DeleteFile " + insertedImageRelativePath);
		}
	}
}

SCENARIO("hard delete image, when executing Deleteitem command")
{
	std::shared_ptr<std::vector<std::string>> executedFileSystemCommands
		= std::make_shared<std::vector<std::string>>();
	IFileSystemServicesPtr fileSystemServices
		= std::make_shared<MockFileSystem>(executedFileSystemCommands);
	CHtmlDocument document(fileSystemServices);

	GIVEN("an empty document")
	{
		WHEN("file hard deleted cuz deleting DeleteItem command due history max size")
		{
			document.InsertImage("folder/recent/r.png", 200, 300);
			std::string insertedImageRelativePath =
				document.GetItem(0).GetImage()->GetPath().string();

			REQUIRE(executedFileSystemCommands->size() == 2);

			document.InsertParagraph("new");
			document.InsertParagraph("old");
			document.DeleteItem(0);

			REQUIRE(document.GetItemsCount() == 2);
			REQUIRE(executedFileSystemCommands->size() == 2);

			document.SetTitle("1");
			document.SetTitle("2");
			document.SetTitle("3");
			document.SetTitle("4");
			document.SetTitle("5");
			document.SetTitle("6");
			document.SetTitle("7");
			document.SetTitle("8");
			document.SetTitle("9");

			REQUIRE(executedFileSystemCommands->size() == 2);

			document.SetTitle("10");

			REQUIRE(executedFileSystemCommands->size() == 3);
			REQUIRE(executedFileSystemCommands->at(2) == "DeleteFile " + insertedImageRelativePath);
		}
	}
}

SCENARIO("testing command InsertItem")
{
	WHEN("")
	{

	}
}

SCENARIO("testing DeleteItem command")
{
	WHEN("")
	{

	}
}

// проверить удаление файла классом команды