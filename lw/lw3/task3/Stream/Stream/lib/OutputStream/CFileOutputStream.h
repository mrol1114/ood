#pragma once

#include <fstream>
#include "./IOutputDataStream.h"

class CFileOutputStream : public IOutputDataStream
{
public:
    CFileOutputStream(const std::string& fileName)
    {
        m_file.open(fileName, std::ios::binary | std::ios::out);

        try
        {
            m_file << "";
        }
        catch (std::exception& ex)
        {
            throw std::runtime_error("Can not open file on write");
        }
    }

    void WriteByte(uint8_t data)override
    {
        EnsureStreamIsOpen();
        m_file << data;
    }

    void WriteBlock(const void* srcData, std::streamsize size)override
    {
        uint8_t* buffer = (uint8_t*)(srcData);
        for (std::streamsize addedSize = 0; addedSize < size; addedSize++)
        {
            WriteByte(*buffer);
            buffer++;
        }
    }

    void Close()override
    {
        m_isOpen = false;
    }

private:
    void EnsureStreamIsOpen()
    {
        if (!m_isOpen)
        {
            throw std::logic_error("Stream is closed");
        }
    }

    std::ofstream m_file;
    bool m_isOpen = true;
};