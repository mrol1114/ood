#pragma once

#include "../IInputDataStream.h"

class CInputDataStreamDecorator : public IInputDataStream
{
public:
	bool IsEOF()const override
	{
		return m_stream->IsEOF() && AdditionalEOFCondition();
	}

	uint8_t ReadByte()override
	{
		EnsureStreamIsNotEnded();
		return DoReadByte();
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size)override
	{
		std::streamsize readedSize = 0;
		uint8_t* buffer = (uint8_t*)(dstBuffer);
		while (!IsEOF() && readedSize < size)
		{
			buffer[readedSize] = ReadByte();
			readedSize++;
		}

		return readedSize;
	}

protected:
	CInputDataStreamDecorator(IInputDataStreamPtr&& stream)
		: m_stream(std::move(stream))
	{
	}

	virtual uint8_t DoReadByte() = 0;
	virtual bool AdditionalEOFCondition()const
	{
		return true;
	}

	IInputDataStreamPtr m_stream;

private:
	void EnsureStreamIsNotEnded()
	{
		if (IsEOF())
		{
			throw std::logic_error("Stream is ended, nothing to read");
		}
	}
};