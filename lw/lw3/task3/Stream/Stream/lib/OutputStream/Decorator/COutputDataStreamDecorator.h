#pragma once

#include "../IOutputDataStream.h"

class COutputDataStreamDecorator : public IOutputDataStream
{
public:
	void WriteByte(uint8_t data)override
	{
		DoWriteByte(data);
	}

	void WriteBlock(const void* srcData, std::streamsize size)override
	{
		std::streamsize writtenSize = 0;
		auto buffer = static_cast<const uint8_t*>(srcData);
		while (writtenSize++ < size)
		{
			WriteByte(*buffer);
			buffer++;
		}
	}

	void Close()override
	{
		ActionBeforeClose();
		m_stream->Close();
	}

protected:
	COutputDataStreamDecorator(IOutputDataStreamPtr&& stream)
		: m_stream(std::move(stream))
	{
	}

	virtual void ActionBeforeClose()
	{
		//Do nothing
	}

	virtual void DoWriteByte(uint8_t data) = 0;

	IOutputDataStreamPtr m_stream;
};