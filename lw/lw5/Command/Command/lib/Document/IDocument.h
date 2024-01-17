#pragma once

#include <memory>
#include <optional>
#include <filesystem>

#include "./DocumentItem/CDocumentItem.h"

/*
��������� ���������
*/
class IDocument
{
public:
    // ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
    // ���� �������� position �� ������, ������� ���������� � ����� ���������
    virtual void InsertParagraph(const std::string& text,
        std::optional<size_t> position = std::nullopt) = 0;
    // ��������� ����������� � ��������� ������� (������� ����������� ��������)
    // �������� path ������ ���� � ������������ �����������
    // ��� ������� ����������� ������ ������������ � ���������� images
    // ��� ������������� ��������������� ������
    virtual void InsertImage(const std::filesystem::path& path, int width, int height,
        std::optional<size_t> position = std::nullopt) = 0;
    // ���������� ���������� ��������� � ���������
    virtual size_t GetItemsCount()const = 0;
    // ������ � ��������� �����������
    virtual CConstDocumentItem GetItem(size_t index)const = 0;
    virtual CDocumentItem GetItem(size_t index) = 0;
    // ������� ������� �� ���������
    virtual void DeleteItem(size_t index) = 0;
    // ���������� ��������� ���������
    virtual std::string GetTitle()const = 0;
    // �������� ��������� ���������
    virtual void SetTitle(const std::string& title) = 0;
    // �������� � ����������� �������� Undo
    virtual bool CanUndo()const = 0;
    // �������� ������� ��������������
    virtual void Undo() = 0;
    // �������� � ����������� �������� Redo
    virtual bool CanRedo()const = 0;
    // ��������� ���������� ������� ��������������
    virtual void Redo() = 0;
    // ��������� �������� � ������� html. ����������� ����������� � ���������� images.
    // ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
    virtual void Save(const std::filesystem::path& path)const = 0;
    virtual ~IDocument() = default;
};

using IDocumentPtr = std::shared_ptr<IDocument>;