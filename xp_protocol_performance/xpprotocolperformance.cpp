#include <benchmark/benchmark.h>

#include "XPProtocol.hpp"
#include <string>

static void BM_EncodeXPProtocolPreAllocateBody(benchmark::State& state)
{
	
	for (auto _ : state)
	{
		char buffer[2048];
		XP::Protocol message;

		message.wrapForDecodeAndEncode(buffer, 2048, 0)
			.setMagicNumber(0xC0CADA)
			.cleanVersionAndProtocolID()
			.setVersion(1)
			.setProtocolID(1)
			.clearSettings()
			.setCompress(true)
			.setLastFragment(false)
			.setBodySize(500);
	}
}


static void BM_EncodeXPProtocolWihtSetBodyCopy512k(benchmark::State& state)
{
	std::uint32_t size = 512000;

	char* buffer = new char[size + 12];
	char* body = new char[size];
	
	for (auto _ : state)
	{
		XP::Protocol message;

		message.wrapForDecodeAndEncode(buffer, size + 12, 0)
			.setMagicNumber(0xC0CADA)
			.cleanVersionAndProtocolID()
			.setVersion(1)
			.setProtocolID(1)
			.clearSettings()
			.setCompress(true)
			.setLastFragment(false)
			.setBody(body, size);
	}
}

static void BM_DecodeXPProtocol(benchmark::State& state)
{

	char buffer[2048];
	XP::Protocol message;

	std::string body = "Ecoding Message";

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.setMagicNumber(0xC0CADA)
		.cleanVersionAndProtocolID()
		.setVersion(1)
		.setProtocolID(1)
		.clearSettings()
		.setCompress(true)
		.setLastFragment(false)
		.setBody(body.c_str(), body.size() + 1);
	
	auto buffersize = message.getBufferSize();

	for (auto _ : state)
	{
		message.wrapForDecodeAndEncode(buffer, buffersize, 0);
		auto magic = message.getMagicNumber();
		auto version = message.getVersion();
		auto protocolID = message.getProtocolID();
		auto isCompress = message.isCompressed();
		auto isLasFragment = message.isLastFragment();
		std::uint32_t size = 0;
		auto body = message.getBody(size);
	}

}

static void BM_DecodeXPProtocolAndCopyBody512k(benchmark::State& state)
{

	std::uint32_t size = 512000;

	char* buffer = new char[size + 12];
	char* body = new char[size];

	XP::Protocol message;

	message.wrapForDecodeAndEncode(buffer, size + 12, 0)
		.setMagicNumber(0xC0CADA)
		.cleanVersionAndProtocolID()
		.setVersion(1)
		.setProtocolID(1)
		.clearSettings()
		.setCompress(true)
		.setLastFragment(false)
		.setBody(body, size);

	for (auto _ : state)
	{
		message.wrapForDecodeAndEncode(buffer, size + 12, 0);
		auto magic = message.getMagicNumber();
		auto version = message.getVersion();
		auto protocolID = message.getProtocolID();
		auto isCompress = message.isCompressed();
		auto isLasFragment = message.isLastFragment();
		std::uint32_t size = 0;
		message.getBody(body);
	}

}

BENCHMARK(BM_EncodeXPProtocolPreAllocateBody);
BENCHMARK(BM_EncodeXPProtocolWihtSetBodyCopy512k);
BENCHMARK(BM_DecodeXPProtocol);
BENCHMARK(BM_DecodeXPProtocolAndCopyBody512k);

BENCHMARK_MAIN();