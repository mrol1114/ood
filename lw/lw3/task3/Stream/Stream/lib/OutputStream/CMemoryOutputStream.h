#pragma once

#include <vector>

#include "./IOutputDataStream.h"

class CMemoryOutputStream : public IOutputDataStream
{
public:
    CMemoryOutputStream(std::shared_ptr<std::vector<uint8_t>> source)
        : m_bytes(source)
    {
    }

    void WriteByte(uint8_t data)override
    {
        EnsureStreamIsOpen();
        m_bytes->push_back(data);
    }

    void WriteBlock(const void* srcData, std::streamsize size)override
    {
        EnsureStreamIsOpen();

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

    std::shared_ptr<std::vector<uint8_t>> m_bytes;
    bool m_isOpen = true;
};