#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "./COutputDataStreamDecorator.h"

class CEncrypter : public COutputDataStreamDecorator
{
public:
	CEncrypter(IOutputDataStreamPtr&& stream, unsigned int key)
		: COutputDataStreamDecorator(std::move(stream))
	{
		InitializeCipher(key);
	}

private:
	void DoWriteByte(uint8_t data)override
	{
		m_stream->WriteByte(m_cipher.at(data));
	}

	void InitializeCipher(unsigned int key)
	{
		for (unsigned int i = 0; i < m_CIPHER_SIZE; i++)
		{
			m_cipher[i] = i;
		}

		std::shuffle(m_cipher.begin(), m_cipher.end(), std::default_random_engine(key));
	}

	const unsigned int m_CIPHER_SIZE = 256;
	bool m_isOpen = true;
	std::vector<uint8_t> m_cipher = std::vector<uint8_t>(m_CIPHER_SIZE, 0);
};