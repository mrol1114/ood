#pragma once

#include <fstream>

#include "./IInputDataStream.h"

class CFileInputStream : public IInputDataStream
{
public:
    CFileInputStream(const std::string& fileName)
    {
        m_file.open(fileName, std::ios::binary | std::ios::in);
        if (!m_file.is_open())
        {
            throw std::runtime_error("Can not open stream");
        }
        m_file.read(readedByte, 1);
    }

    bool IsEOF()const override
    {
        return m_file.eof(); 
    }

    uint8_t ReadByte()override
    {
        if (IsEOF())
        {
            throw std::ios_base::failure("Exceeds boudaries");
        }

        char byte = *readedByte;
        m_file.read(readedByte, 1);
        return byte;
    }

    std::streamsize ReadBlock(void* dstBuffer, std::streamsize size)override
    {
        uint8_t* buffer = (uint8_t*)(dstBuffer);
        std::streamsize count = 0;

        while (!IsEOF() && count < size)
        {
            buffer[count++] = ReadByte();
        }

        return count;
    }

private:
    char* readedByte = new char;
    std::ifstream m_file;
};
