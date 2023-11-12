#pragma once

#include <list>

#include "./IDocument.h"
#include "../Command/ICommand.h"
#include "./DocumentItem/CDocumentItem.h"

class CDocument : public IDocument
{
public:
    using DocumentItems = std::list<CDocumentItem>;

    void InsertParagraph(const std::string& text,
        std::optional<size_t> position = std::nullopt)override
    {

    }

    void InsertImage(const std::filesystem::path& path, int width, int height,
        std::optional<size_t> position = std::nullopt)override
    {

    }

    size_t GetItemsCount()const override
    {
        return m_items.size();
    }

    CConstDocumentItem GetItem(size_t index)const override
    {
        EnsureIndexDoesNotExceedsItemsBoudaries(index);
        auto it = m_items.begin();
        advance(it, index);
        return *it;
    }

    CDocumentItem GetItem(size_t index)override
    {
        EnsureIndexDoesNotExceedsItemsBoudaries(index);
        auto it = m_items.begin();
        advance(it, index);
        return *it;
    }

    void DeleteItem(size_t index)override
    {
        EnsureIndexDoesNotExceedsItemsBoudaries(index);
    }

    std::string GetTitle()const override
    {
        return m_title;
    }

    void SetTitle(const std::string& title)override
    {
        
    }

    bool CanUndo()const override
    {
        return m_currentCommandIndex >= 0;
    }

    void Undo()override
    {
        if (!CanUndo())
        {
            throw std::logic_error("Command can not be undone");
        }

        m_commands[m_currentCommandIndex]->Unexecute();
    }

    bool CanRedo()const override
    {
        return m_currentCommandIndex < m_commands.size();
    }

    void Redo()override
    {
        if (!CanRedo())
        {
            throw std::logic_error("Command can not be redone");
        }

        m_commands[m_currentCommandIndex]->Execute();
    }

    void Save(const std::filesystem::path& path)const override
    {

    }

private:
    void EnsureIndexDoesNotExceedsItemsBoudaries(size_t index)const
    {
        if (index >= m_items.size())
        {
            throw std::runtime_error("Boundaries exceeds");
        }
    }

    void ExecuteAndAddCommand(ICommandPtr&& command)
    {
        command->Execute();
        m_commands.push_back(std::move(command));
    }

    void ResizeCommandsToCurrentIndex()
    {
        if (m_commands.size() == m_currentCommandIndex)
        {
            return;
        }

        m_commands.resize(m_currentCommandIndex + 1);
    }

    std::string m_title;
    DocumentItems m_items;
    std::vector<ICommandPtr> m_commands;

    int m_currentCommandIndex = -1;
};