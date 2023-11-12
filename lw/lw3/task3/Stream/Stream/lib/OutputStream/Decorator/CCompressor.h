#pragma once

#include "./COutputDataStreamDecorator.h"

class CCompressor : public COutputDataStreamDecorator
{
public:
	CCompressor(IOutputDataStreamPtr&& stream)
		: COutputDataStreamDecorator(std::move(stream))
	{
	}

private:
	void ActionBeforeClose()override
	{
		if (m_count != 0)
		{
			m_stream->WriteByte(m_count);
			m_stream->WriteByte(m_symbol);
		}
	}

	void DoWriteByte(uint8_t data)override
	{
		if (m_count == 0)
		{
			m_symbol = data;
		}

		if (m_symbol != data || m_count == m_BYTE_MAX_COUNT)
		{
			m_stream->WriteByte(m_count);
			m_stream->WriteByte(m_symbol);
			m_count = 0;
			m_symbol = data;
		}

		m_count++;
		return;
	}

	static constexpr uint8_t m_BYTE_MAX_COUNT = 255;
	uint8_t m_count = 0;
	uint8_t m_symbol = 0;
};