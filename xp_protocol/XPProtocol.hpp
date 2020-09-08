#ifndef _XP_PROTOCOL_
#define _XP_PROTOCOL_

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

/*************************************************************************************************************************************************************
                ******************************************************************************************************************************************
                * magic number *    version       *   protocol id *   compression *   lastfragment * buffer_size  *  buffer              *   checksum    *
                *   bytes<4>   *    bits<4>MSB    *   bits<4>LSB  *   bit 7       *   bit 6        * bytes<4>     *  bytes<buffer_size>  *   bytes<1>    *
                ******************************************************************************************************************************************
array position        0                 4                  4             5                5             6                   9               9 + buffer_size
 *************************************************************************************************************************************************************/

namespace XP {

    struct ProtocolID
    {
        static const std::uint8_t SBE = 0x01;
    };

    struct ProtocolMask
    {
        static const std::uint8_t VERSION_MASK = 0xF0;
        static const std::uint8_t PROTOCOL_ID_MASK = 0x0F;
        static const std::uint8_t COMPRESSION_MASK = 0x80;
        static const std::uint8_t LAST_FRAGMENT_MASK = 0x40;

        static const std::uint8_t SET_COMPRESSION_TRUE = 0x80;
        static const std::uint8_t SET_COMPRESSION_FALSE = 0xBF;

        static const std::uint8_t SET_LAST_FRAGMENT_TRUE = 0x40;
        static const std::uint8_t SET_LAST_FRAGMENT_FALSE = 0xDF;
    };

    class Protocol
    {

    private:

        char* m_buffer = nullptr;
        std::uint32_t m_buffer_size = 0;
        std::uint32_t m_offset = 0;
        std::uint32_t m_protocolSize = 11;

    public:

        static const std::uint32_t MAGIC_NUMBER = 0xC0CADA;
        static const std::uint8_t VERSION = 1;
        static const std::uint32_t HEADER_SIZE = 11;

    public:

        Protocol() = default;

        Protocol(char* buffer, const std::uint32_t& buffer_size, const std::uint32_t& offset) : m_buffer(buffer),
            m_buffer_size(buffer_size),
            m_offset(offset)
        {}

        Protocol& wrapForDecodeAndEncode(char* buffer, std::uint32_t buffer_size, std::uint32_t offset)
        {
            return *this = Protocol(buffer, buffer_size, offset);
        }

        Protocol& cleanVersionAndProtocolID()
        {
            *(std::uint8_t*)(m_buffer + m_offset + 4) = (std::uint8_t)(0);
            return *this;
        }

        Protocol& clearSettings()
        {
            *(std::uint8_t*)(m_buffer + m_offset + 5) = (std::uint8_t)(0);
            return *this;
        }

        Protocol& setMagicNumber(const std::uint32_t& mgknum)
        {
            std::memcpy(m_buffer + m_offset, &mgknum, sizeof(std::uint32_t));
            return *this;
        }

        std::uint32_t getMagicNumber()
        {
            std::uint32_t val = 0;
            std::memcpy(&val, m_buffer + m_offset, sizeof(std::uint32_t));
            return val;
        }

        Protocol& setVersion(const std::uint8_t& version)
        {
            std::uint8_t val = version;
            val <<= 4;
            *(std::uint8_t*)(m_buffer + m_offset + 4) |= val;
            return *this;
        }

        std::uint8_t getVersion()
        {
            std::uint8_t val = 0;
            std::memcpy(&val, m_buffer + m_offset + 4, sizeof(std::uint8_t));
            val = (val & ProtocolMask::VERSION_MASK) >> 4;
            return val;
        }

        Protocol& setProtocolID(const std::uint8_t& protocolID)
        {
            *(std::uint8_t*)(m_buffer + m_offset + 4) |= protocolID;
            return *this;
        }

        std::uint8_t getProtocolID()
        {
            std::uint8_t val = 0;
            std::memcpy(&val, m_buffer + m_offset + 4, sizeof(std::uint8_t));
            val &= ProtocolMask::PROTOCOL_ID_MASK;
            return val;
        }

        Protocol& setBodySize(const std::uint32_t size)
        {
            m_protocolSize = HEADER_SIZE + size;
            std::memcpy(m_buffer + m_offset + 6,&size, sizeof(std::uint32_t));
            return *this;
        }

        std::uint32_t getBodySize()
        {
            std::uint32_t val = 0;
            std::memcpy(&val, m_buffer + m_offset + 6, sizeof(std::uint32_t));
            return val;
        }

        Protocol& setBody(char* buffer, const std::uint32_t& size)
        {
            m_protocolSize = HEADER_SIZE + size;

            std::memcpy(m_buffer + m_offset + 9, buffer, sizeof(char) * size);
            std::memcpy(m_buffer + m_offset + 6, &size, sizeof(std::uint32_t));
            return *this;
        }

        Protocol& setBody(const char* buffer, const std::uint32_t& size)
        {
            m_protocolSize = HEADER_SIZE + size;

            std::memcpy(m_buffer + m_offset + 10, buffer, sizeof(char) * size);
            std::memcpy(m_buffer + m_offset + 6, &size, sizeof(std::uint32_t));
            return *this;
        }

        const char* getBody(std::uint32_t& size)
        {
            std::memcpy(&size, m_buffer + m_offset + 6, sizeof(std::uint32_t));
            return (m_buffer + m_offset + 10);
        }

        void getBody(char* body)
        {
            std::uint32_t size = 0;
            std::memcpy(&size, m_buffer + m_offset + 6, sizeof(std::uint32_t));
            std::memcpy(body, m_buffer + m_offset + 10, sizeof(char) * size);
        }

        Protocol& setCompress(const bool& val)
        {
            if (val)
            {
                *(std::uint8_t*)(m_buffer + m_offset + 5) |= ProtocolMask::SET_COMPRESSION_TRUE;
            }
            else
            {
                *(std::uint8_t*)(m_buffer + m_offset + 5) &= ProtocolMask::SET_COMPRESSION_FALSE;
            }
            return *this;
        }

        bool isCompressed()
        {
            return *(std::uint8_t *)(m_buffer + m_offset + 5) & ProtocolMask::COMPRESSION_MASK;
        }

		Protocol& setLastFragment(const bool& val)
		{
			if (val)
			{
				*(std::uint8_t*)(m_buffer + m_offset + 5) |= ProtocolMask::SET_LAST_FRAGMENT_TRUE;
			}
			else
			{
				*(std::uint8_t*)(m_buffer + m_offset + 5) &= ProtocolMask::SET_LAST_FRAGMENT_FALSE;
			}
			return *this;
		}

        bool isLastFragment()
        {
            return *(std::uint8_t *)(m_buffer + m_offset + 5) & ProtocolMask::LAST_FRAGMENT_MASK;
        }

        bool compareMagicNumber()
        {
            return  *(std::uint32_t*)(m_buffer + m_offset) == MAGIC_NUMBER;
        }

        std::uint32_t getBufferSize()
        {
            return m_protocolSize;
        }
    };
};
#endif //_XP_PROTOCOL_