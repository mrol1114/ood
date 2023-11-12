#pragma once

#include "./CInputDataStreamDecorator.h"

class CDecompressor : public CInputDataStreamDecorator
{
public:
	CDecompressor(IInputDataStreamPtr&& stream)
		: CInputDataStreamDecorator(std::move(stream))
	{
	}

private:
	uint8_t DoReadByte()override
	{
		if (m_count == 0)
		{
			m_count = m_stream->ReadByte();
			m_symbol = m_stream->ReadByte();
		}

		m_count--;
		return m_symbol;
	}

	bool AdditionalEOFCondition()const override
	{
		return m_count == 0;
	}

	uint8_t m_count = 0;
	uint8_t m_symbol = 0;
};