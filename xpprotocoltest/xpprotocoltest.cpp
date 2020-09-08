#include "pch.h"
#include"XPProtocol.hpp"

#include <cstring>
#include <string>


TEST(XPProtocol, EncodeMagicNumber)
{
	char buffer[2048];
	XP::Protocol message;
	
	const std::uint32_t magic_number = 0xC0CADA;

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.setMagicNumber(magic_number);

	EXPECT_EQ(magic_number, message.getMagicNumber());
}

TEST(XPProtocol, EncodeVersion) {

	char buffer[2048];
	XP::Protocol message;
	
	const std::uint8_t version = 0x9;

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.cleanVersionAndProtocolID()
		.setVersion(version);

	EXPECT_EQ(version, message.getVersion());
}

TEST(XPProtocol, EncodeProtocolID) {

	char buffer[2048];
	XP::Protocol message;
	
	const std::uint8_t protocolID = 0x9;

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.cleanVersionAndProtocolID()
		.setProtocolID(protocolID);

	EXPECT_EQ(protocolID, message.getProtocolID());
}


TEST(XPProtocol, EncodeVersionAndProtocolID)
{
	char buffer[2048];
	XP::Protocol message;
	
	const std::uint8_t protocolID = 0x9;
	const std::uint8_t version = 0xD;

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.cleanVersionAndProtocolID()
		.setProtocolID(protocolID)
		.setVersion(version);

	EXPECT_EQ(protocolID, message.getProtocolID());
	EXPECT_EQ(version, message.getVersion());
}

TEST(XPProtocol, EncodeCompressTrue)
{
	char buffer[2048];
	XP::Protocol message;
	

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.clearSettings()
		.setCompress(true);

	EXPECT_TRUE(message.isCompressed());
}

TEST(XPProtocol, EncodeCompressFalse)
{
	char buffer[2048];
	XP::Protocol message;
	

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.clearSettings()
		.setCompress(false);

	EXPECT_FALSE(message.isCompressed());
}

TEST(XPProtocol, EncodeLastFragmentTrue)
{
	char buffer[2048];
	XP::Protocol message;
	

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.clearSettings()
		.setLastFragment(true);

	EXPECT_TRUE(message.isLastFragment());
}

TEST(XPProtocol, EncodeLastFragmentFalse)
{

	char buffer[2048];
	XP::Protocol message;
	

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.clearSettings()
		.setLastFragment(false);

	EXPECT_FALSE(message.isLastFragment());
}

TEST(XPProtocol, EncodeCompressAndLastFragmentTrue)
{
	char buffer[2048];
	XP::Protocol message;
	

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.clearSettings()
		.setCompress(true)
		.setLastFragment(true);

	EXPECT_TRUE(message.isLastFragment());
	EXPECT_TRUE(message.isCompressed());
}

TEST(XPProtocol, EncodeCompressAndLastFragmentFalse)
{

	char buffer[2048];
	XP::Protocol message;
	

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.clearSettings()
		.setCompress(false)
		.setLastFragment(false);

	EXPECT_FALSE(message.isLastFragment());
	EXPECT_FALSE(message.isCompressed());
}

TEST(XPProtocol, EncondeCompressTrueLastFragmentFalse)
{
	char buffer[2048];
	XP::Protocol message;
	

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.clearSettings()
		.setCompress(true)
		.setLastFragment(false);

	EXPECT_FALSE(message.isLastFragment());
	EXPECT_TRUE(message.isCompressed());
}

TEST(XPProtocol, EncondeCompressFalseLastFragmentTrue)
{
	char buffer[2048];
	XP::Protocol message;
	

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.clearSettings()
		.setCompress(false)
		.setLastFragment(true);

	EXPECT_TRUE(message.isLastFragment());
	EXPECT_FALSE(message.isCompressed());
}

TEST(XPProtocol, EncodeBodySize)
{
	char buffer[2048];
	XP::Protocol message;
	
	std::uint32_t bodySize = 300;

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.setBodySize(bodySize);

	EXPECT_EQ(bodySize, message.getBodySize());
}

TEST(XPProtocol, EncodeBody)
{
	char buffer[2048];
	XP::Protocol message;
	
	std::string body = "encoding body";

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.setBody(body.c_str(), body.size() + 1);

	EXPECT_EQ(body.size() + 1, message.getBodySize());

	char* result = new char[message.getBodySize() + 1];

	message.getBody(result);

	EXPECT_STREQ(body.c_str(), result);
}

TEST(XPProtocol, EncodeBodyConst)
{
	char buffer[2048];
	XP::Protocol message;
	
	std::string body = "encoding body";

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.setBody(body.c_str(), body.size() + 1);


	std::uint32_t size = 0;

	const char* result = message.getBody(size);
	
	EXPECT_EQ(body.size() + 1, size);
	EXPECT_STREQ(body.c_str(), result);
}

TEST(XPProtocol, ProtocolSizeWithEmptyBody)
{
	char buffer[2048];
	XP::Protocol message;

	message.wrapForDecodeAndEncode(buffer, 2048, 0);
	
	EXPECT_EQ(message.getBufferSize(), XP::Protocol::HEADER_SIZE);
}

TEST(XPProtocol, ProtocolSizeWithBody)
{
	char buffer[2048];
	XP::Protocol message;
	
	std::string body = "encoding body";

	message.wrapForDecodeAndEncode(buffer, 2048, 0)
		.setBody(body.c_str(), body.size() + 1);


	std::uint32_t size = 0;

	const char* result = message.getBody(size);
	
	EXPECT_EQ(message.getBufferSize(), XP::Protocol::HEADER_SIZE + size);
}
