#pragma once

#include <memory>

class IImage
{
public:
	// ���������� ���� ������������ �������� ���������
	virtual const std::filesystem::path& GetPath()const = 0;
	// ������ ����������� � ��������
	virtual unsigned int GetWidth()const = 0;
	// ������ ����������� � ��������
	virtual unsigned int GetHeight()const = 0;
	// �������� ������ �����������
	virtual void Resize(unsigned int width, unsigned int height) = 0;
	virtual ~IImage() = default;
};

using IImagePtr = std::shared_ptr<IImage>;