#include <fstream>
#include <memory>

#include "./FileAssembler.h"
#include "./InputStream/IInputDataStream.h"
#include "./InputStream/CFileInputStream.h"
#include "./InputStream/Decorator/CDecompressor.h"
#include "./InputStream/Decorator/CDecrypter.h"
#include "./OutputStream/IOutputDataStream.h"
#include "./OutputStream/CFileOutputStream.h"
#include "./OutputStream/Decorator/CCompressor.h"
#include "./OutputStream/Decorator/CEncrypter.h"

template <typename StreamDecorator, typename... Args>
auto MakeStreamDecorator(const Args&...args)
{
	return [=](auto&& b) {
		return make_unique<StreamDecorator>(forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator << (Component&& component, const Decorator& decorate)
{
	return decorate(forward<Component>(component));
}

IInputDataStreamPtr CreateFileInputStream(const Params& params)
{
	IInputDataStreamPtr inputStream = std::make_unique<CFileInputStream>(params.inFileName);

	if (params.isNeedToDecompress)
	{
		inputStream = std::move(inputStream) << MakeStreamDecorator<CDecompressor>();
	}

	if (params.processMode == ProcessModeType::Assemble)
	{
		for (auto option : params.options)
		{
			inputStream = std::move(inputStream) << MakeStreamDecorator<CDecrypter>(option.key);
		}
	}

	return inputStream;
}

IOutputDataStreamPtr CreateFileOutputStream(const Params& params)
{
	IOutputDataStreamPtr outputStream = std::make_unique<CFileOutputStream>(params.outFileName);

	if (params.isNeedToCompress)
	{
		outputStream = std::move(outputStream) << MakeStreamDecorator<CCompressor>();
	}

	if (params.processMode == ProcessModeType::Disassemble)
	{
		for (auto option : params.options)
		{
			outputStream = std::move(outputStream) << MakeStreamDecorator<CEncrypter>(option.key);
		}
	}

	return outputStream;
}

void AssembleFile(const Params& params)
{
	auto inputStream = CreateFileInputStream(params);
	auto outputStream = CreateFileOutputStream(params);

	while (!inputStream->IsEOF())
	{
		outputStream->WriteByte(inputStream->ReadByte());
	}
	outputStream->Close();
}