#define CATCH_CONFIG_MAIN
#include "../../../../../lib/catch.hpp"

#include <string>

#include "../Stream/lib/InputStream/CFileInputStream.h"
#include "../Stream/lib/InputStream/CMemoryInputStream.h"
#include "../Stream/lib/InputStream/Decorator/CDecompressor.h"
#include "../Stream/lib/InputStream/Decorator/CDecrypter.h"

#include "../Stream/lib/OutputStream/CMemoryOutputStream.h"
#include "../Stream/lib/OutputStream/CFileOutputStream.h"
#include "../Stream/lib/OutputStream/Decorator/CEncrypter.h"
#include "../Stream/lib/OutputStream/Decorator/CCompressor.h"

SCENARIO("Reading from CMemoryInputStream")
{
	WHEN("reading byte")
	{
		CMemoryInputStream stream(
			std::vector<uint8_t>{'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'}
		);

		REQUIRE(stream.ReadByte() == 'H');
		REQUIRE(stream.ReadByte() == 'e');
	}
	WHEN("reading byte block")
	{
		CMemoryInputStream stream(
			std::vector<uint8_t>{'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'}
		);
		char str[3] = "";

		REQUIRE(stream.ReadBlock(&str, 2) == 2);
		REQUIRE(std::string(str) == "He");
	}
	WHEN("reading byte block to end of stream")
	{
		CMemoryInputStream stream(std::vector<uint8_t>{'H', 'e', 'l', 'l', 'o'});
		char str[8] = "";

		REQUIRE(stream.ReadBlock(str, 7) == 5);
		REQUIRE(std::string(str) == "Hello");
	}
	WHEN("reading byte from empty stream")
	{
		CMemoryInputStream stream(std::vector<uint8_t>{});
		REQUIRE_THROWS(stream.ReadByte());
	}
	WHEN("reading block from empty stream")
	{
		CMemoryInputStream stream(std::vector<uint8_t>{});
		char str[3] = "";

		REQUIRE(stream.ReadBlock(str, 2) == 0);
		REQUIRE(std::string(str) == "");
	}
}

SCENARIO("Writing to CMemoryOutputStream")
{
	std::shared_ptr<std::vector<uint8_t>> source = std::make_shared<std::vector<uint8_t>>();
	CMemoryOutputStream stream(source);

	WHEN("writing byte")
	{
		stream.WriteByte('H');
		stream.WriteByte('E');
		stream.WriteByte('l');
		stream.WriteByte('l');
		stream.WriteByte('o');

		REQUIRE(*source == std::vector<uint8_t>({'H', 'E', 'l', 'l', 'o'}));
	}
	WHEN("writing byte block")
	{
		char str[6] = "Hello";

		stream.WriteBlock(&str, 5);

		REQUIRE(*source == std::vector<uint8_t>({ 'H', 'e', 'l', 'l', 'o' }));
		REQUIRE(std::string(str) == "Hello");
	}
	WHEN("writing byte to closed stream")
	{
		stream.Close();

		REQUIRE_THROWS(stream.WriteByte('A'));
		REQUIRE(*source == std::vector<uint8_t>({}));
	}
	WHEN("writing byte block to closed stream")
	{
		char str[4] = "str";

		stream.Close();

		REQUIRE_THROWS(stream.WriteBlock(&str, 3));
		REQUIRE(std::string(str) == "str");
		REQUIRE(*source == std::vector<uint8_t>({}));
	}
}

std::vector<uint8_t> CreateCipher(unsigned int key)
{
	std::vector<uint8_t> cipher(256, 0);
	for (unsigned int i = 0; i < 256; i++)
	{
		cipher[i] = i;
	}

	std::shuffle(cipher.begin(), cipher.end(), std::default_random_engine(key));

	return cipher;
}

SCENARIO("Encrypting memory stream")
{
	std::shared_ptr<std::vector<uint8_t>> source = std::make_shared<std::vector<uint8_t>>();
	CEncrypter encrypter(
		std::make_unique<CMemoryOutputStream>(source), 123
	);
	auto cipher = CreateCipher(123);

	WHEN("encrypting by bytes")
	{
		encrypter.WriteByte('Q');
		encrypter.WriteByte('Q');
		encrypter.WriteByte('W');
		encrypter.WriteByte('E');

		auto byte = cipher['Q'];
		REQUIRE(*source == std::vector<uint8_t>({
			cipher['Q'],
			cipher['Q'],
			cipher['W'],
			cipher['E']
		}));
	}
	WHEN("encrypting byte block")
	{
		char str[5] = "QQWE";

		encrypter.WriteBlock(&str, 4);

		REQUIRE(*source == std::vector<uint8_t>({
			cipher['Q'],
			cipher['Q'],
			cipher['W'],
			cipher['E']
		}));
	}
}

SCENARIO("Compressing memory stream")
{
	std::shared_ptr<std::vector<uint8_t>> source = std::make_shared<std::vector<uint8_t>>();
	CCompressor compressor(
		std::make_unique<CMemoryOutputStream>(source)
	);

	WHEN("compressing by byte")
	{
		compressor.WriteByte('A');
		compressor.WriteByte('A');
		compressor.WriteByte('B');
		compressor.Close();

		REQUIRE(*source == std::vector<uint8_t>({ 2, 'A', 1, 'B' }));
	}
	WHEN("compressing different bytes")
	{
		char str[13] = "AA   1ffAAAB";

		compressor.WriteBlock(&str, 12);
		compressor.Close();

		REQUIRE(
			*source == std::vector<uint8_t>({ 2, 'A', 3, ' ', 1, '1', 2, 'f', 3, 'A', 1, 'B'})
		);
		REQUIRE(std::string(str) == "AA   1ffAAAB");
	}
	WHEN("compressing bytes more then 256 size")
	{
		std::string str(520, 'a');
		str += 'b';

		compressor.WriteBlock(str.c_str(), 521);
		compressor.Close();

		REQUIRE(
			*source == std::vector<uint8_t>({ 255, 'a', 255, 'a', 10, 'a', 1, 'b' })
		);
	}
}

SCENARIO("Decrypting memory stream")
{
	std::shared_ptr<std::vector<uint8_t>> source = std::make_shared<std::vector<uint8_t>>();
	CEncrypter encrypter(
		std::make_unique<CMemoryOutputStream>(source), 123
	);
	char initStr[5] = "QQWE";
	encrypter.WriteBlock(&initStr, 4);
	CDecrypter decrypter(
		std::make_unique<CMemoryInputStream>(*source), 123
	);

	WHEN("decrypting bytes")
	{
		REQUIRE(decrypter.ReadByte() == 'Q');
		REQUIRE(decrypter.ReadByte() == 'Q');
		REQUIRE(decrypter.ReadByte() == 'W');
		REQUIRE(decrypter.ReadByte() == 'E');
	}
	WHEN("decrypting byte block")
	{
		char dstStr[5] = "";
		decrypter.ReadBlock(&dstStr, 4);

		REQUIRE(std::string(dstStr) == std::string(initStr));
	}
}

SCENARIO("Decompressing memory stream")
{
	CDecompressor decompressor(
		std::make_unique<CMemoryInputStream>(std::vector<uint8_t>{2, 'A', 13, 'B', 12, 'C'})
	);

	WHEN("decompressing bytes")
	{
		REQUIRE(decompressor.ReadByte() == 'A');
		REQUIRE(decompressor.ReadByte() == 'A');
		REQUIRE(decompressor.ReadByte() == 'B');
		REQUIRE(!decompressor.IsEOF());
	}
	WHEN("decompressing byte block")
	{
		char str[28] = "";
		REQUIRE(decompressor.ReadBlock(&str, 30) == 27);
		REQUIRE(std::string(str) == "AABBBBBBBBBBBBBCCCCCCCCCCCC");
		REQUIRE(decompressor.IsEOF());
	}
}