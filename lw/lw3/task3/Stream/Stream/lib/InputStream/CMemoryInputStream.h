#pragma once

#include <vector>

#include "./IInputDataStream.h"

class CMemoryInputStream: public IInputDataStream
{
public:
    CMemoryInputStream(const std::vector<uint8_t>& data)
        : m_bytes(data)
    {
    }

    bool IsEOF()const override
    {
        return m_currPosition == m_bytes.size();
    }

    uint8_t ReadByte()override
    {
        if (IsEOF())
        {
            throw std::ios_base::failure("Exceeds boudaries");
        }

        return m_bytes[m_currPosition++];
    }

    std::streamsize ReadBlock(void* dstBuffer, std::streamsize size)override
    {
        uint8_t* buffer = (uint8_t*)(dstBuffer);
        std::streamsize count = 0;

        while (!IsEOF() && count < size)
        {
            buffer[count] = ReadByte();
            count++;
        }

        return count;
    }

private:
    std::vector<uint8_t> m_bytes;
    size_t m_currPosition = 0;
};
