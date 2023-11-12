#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <map>

#include "./CInputDataStreamDecorator.h"

class CDecrypter : public CInputDataStreamDecorator
{
public:
	CDecrypter(IInputDataStreamPtr&& stream, unsigned int key)
		: CInputDataStreamDecorator(std::move(stream))
	{
		InitializeCipher(key);
	}

private:
	uint8_t DoReadByte()override
	{
		return m_cipher[m_stream->ReadByte()];
	}

	uint8_t ChangeByte(uint8_t byte) 
	{
		return m_cipher[byte];
	}

	void InitializeCipher(unsigned int key)
	{
		std::vector<uint8_t> orderedCipher = std::vector<uint8_t>(m_CIPHER_SIZE, 0);
		for (unsigned int i = 0; i < m_CIPHER_SIZE; i++)
		{
			orderedCipher[i] = i;
		}
		std::shuffle(orderedCipher.begin(), orderedCipher.end(), std::default_random_engine(key));

		for (unsigned int index : orderedCipher)
		{
			m_cipher[orderedCipher[index]] = index;
		}
	}

	const unsigned int m_CIPHER_SIZE = 256;
	std::map<uint8_t, uint8_t> m_cipher;
};