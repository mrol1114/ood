#pragma once

#include <list>

#include "./IDocument.h"
#include "../Command/IDocumentCommand.h"
#include "./DocumentItem/CDocumentItem.h"
#include "../History/ICommandHistory.h"
#include "./Commands/InsertImageDocumentCommand.h"
#include "./Commands/InsertParagraphDocumentCommand.h"
#include "./Commands/SetTitleDocumentCommand.h"
#include "./Commands/DeleteItemDocumentCommand.h"
#include "../System/CFileSystemServices.h"
#include "../History/CCommandHistory.h"

class CHtmlDocument : public IDocument
{
public:
    CHtmlDocument(IFileSystemServicesPtr fileSystemServices)
        : m_history(std::make_unique<CCommandHistory>())
        , m_fileSystemServices(fileSystemServices)
    {
    }

    using DocumentItems = std::list<CDocumentItem>;

    void InsertParagraph(const std::string& text,
        std::optional<size_t> position = std::nullopt)override
    {
        if (position != std::nullopt)
        {
            EnsureIndexDoesNotExceedsItemsBoudaries(position.value());
        }
        m_history->ExecuteAndAddCommand(
            std::make_unique<InsertParagraphDocumentCommand>(
                text, m_items, *m_history.get(), position
            )
        );
    }

    void InsertImage(const std::filesystem::path& path, int width, int height,
        std::optional<size_t> position = std::nullopt)override
    {
        if (position != std::nullopt)
        {
            EnsureIndexDoesNotExceedsItemsBoudaries(position.value());
        }
        m_history->ExecuteAndAddCommand(
            std::make_unique<InsertImageDocumentCommand>(
                path, width, height, m_items, m_fileSystemServices, *m_history.get(), position
            )
        );
    }

    size_t GetItemsCount()const override
    {
        return m_items.size();
    }

    CConstDocumentItem GetItem(size_t index)const override
    {
        EnsureIndexDoesNotExceedsItemsBoudaries(index);
        return DoGetItem(index);
    }

    CDocumentItem GetItem(size_t index)override
    {
        EnsureIndexDoesNotExceedsItemsBoudaries(index);
        return DoGetItem(index);
    }

    void DeleteItem(size_t index)override
    {
        EnsureIndexDoesNotExceedsItemsBoudaries(index);
        m_history->ExecuteAndAddCommand(
            std::make_unique<DeleteItemDocumentCommand>(m_items, index, m_fileSystemServices)
        );
    }

    std::string GetTitle()const override
    {
        return m_title;
    }

    void SetTitle(const std::string& title)override
    {
        m_history->ExecuteAndAddCommand(
            std::make_unique<SetTitleDocumentCommand>(m_title, title)
        );
    }

    bool CanUndo()const override
    {
        return m_history->CanUndo();
    }

    void Undo()override
    {
        m_history->Undo();
    }

    bool CanRedo()const override
    {
        return m_history->CanRedo();
    }

    void Redo()override
    {
        m_history->Redo();
    }

    void Save(const std::filesystem::path& path)const override
    {
        std::string htmlText;

        htmlText += m_PRE_HEAD_TAGS;
        htmlText += CreateTitleTag(m_title);
        htmlText += m_HEAD_CLOSING_TAG;
        htmlText += m_BODY_OPENING_TAG;

        for (const CConstDocumentItem& item : m_items)
        {
            htmlText += item.GetImage() 
                ? CreateImageTagFromItem(item)
                : CreateParagraphTagFromItem(item);
        }

        htmlText += m_CLOSING_TAGS;
        m_fileSystemServices->WriteToFile(path, htmlText);
    }

private:
    inline static const std::string m_PRE_HEAD_TAGS = "<!DOCTYPE html><html><head>";
    inline static const std::string m_HEAD_CLOSING_TAG = "</head>";
    inline static const std::string m_BODY_OPENING_TAG = "<body>";
    inline static const std::string m_CLOSING_TAGS = "</body></html>";
    inline static const std::string m_PX = "px";

    static std::string CreateImageTagFromItem(const CConstDocumentItem& item)
    {
        return "<img src=\"" + item.GetImage()->GetPath().string() + "\" "
            + "width=\"" + std::to_string(item.GetImage()->GetWidth()) + m_PX + "\" "
            + "height=\"" + std::to_string(item.GetImage()->GetHeight()) + m_PX + "\" >";
    }

    static std::string CreateParagraphTagFromItem(const CConstDocumentItem& item)
    {
        return "<p>" + item.GetParagraph()->GetText() + "</p>";
    }

    static std::string CreateTitleTag(const std::string& text)
    {
        return "<title>" + text + "</title>";
    }

    CDocumentItem DoGetItem(size_t index)const
    {
        EnsureIndexDoesNotExceedsItemsBoudaries(index);
        auto it = m_items.begin();
        advance(it, index);
        return *it;
    }

    void EnsureIndexDoesNotExceedsItemsBoudaries(size_t index)const
    {
        if (index >= m_items.size())
        {
            throw std::runtime_error("Boundaries exceeds");
        }
    }

    std::string m_title;
    DocumentItems m_items;
    ICommandHistoryPtr m_history;
    IFileSystemServicesPtr m_fileSystemServices;
};