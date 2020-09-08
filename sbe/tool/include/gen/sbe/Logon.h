/* Generated SBE (Simple Binary Encoding) message codec */
#ifndef _SBE_LOGON_H_
#define _SBE_LOGON_H_

#if defined(SBE_HAVE_CMATH)
/* cmath needed for std::numeric_limits<double>::quiet_NaN() */
#  include <cmath>
#  define SBE_FLOAT_NAN std::numeric_limits<float>::quiet_NaN()
#  define SBE_DOUBLE_NAN std::numeric_limits<double>::quiet_NaN()
#else
/* math.h needed for NAN */
#  include <math.h>
#  define SBE_FLOAT_NAN NAN
#  define SBE_DOUBLE_NAN NAN
#endif

#if __cplusplus >= 201103L
#  define SBE_CONSTEXPR constexpr
#  define SBE_NOEXCEPT noexcept
#else
#  define SBE_CONSTEXPR
#  define SBE_NOEXCEPT
#endif

#if __cplusplus >= 201703L
#  include <string_view>
#  define SBE_NODISCARD [[nodiscard]]
#else
#  define SBE_NODISCARD
#endif

#if !defined(__STDC_LIMIT_MACROS)
#  define __STDC_LIMIT_MACROS 1
#endif

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

#if defined(WIN32) || defined(_WIN32)
#  define SBE_BIG_ENDIAN_ENCODE_16(v) _byteswap_ushort(v)
#  define SBE_BIG_ENDIAN_ENCODE_32(v) _byteswap_ulong(v)
#  define SBE_BIG_ENDIAN_ENCODE_64(v) _byteswap_uint64(v)
#  define SBE_LITTLE_ENDIAN_ENCODE_16(v) (v)
#  define SBE_LITTLE_ENDIAN_ENCODE_32(v) (v)
#  define SBE_LITTLE_ENDIAN_ENCODE_64(v) (v)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define SBE_BIG_ENDIAN_ENCODE_16(v) __builtin_bswap16(v)
#  define SBE_BIG_ENDIAN_ENCODE_32(v) __builtin_bswap32(v)
#  define SBE_BIG_ENDIAN_ENCODE_64(v) __builtin_bswap64(v)
#  define SBE_LITTLE_ENDIAN_ENCODE_16(v) (v)
#  define SBE_LITTLE_ENDIAN_ENCODE_32(v) (v)
#  define SBE_LITTLE_ENDIAN_ENCODE_64(v) (v)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define SBE_LITTLE_ENDIAN_ENCODE_16(v) __builtin_bswap16(v)
#  define SBE_LITTLE_ENDIAN_ENCODE_32(v) __builtin_bswap32(v)
#  define SBE_LITTLE_ENDIAN_ENCODE_64(v) __builtin_bswap64(v)
#  define SBE_BIG_ENDIAN_ENCODE_16(v) (v)
#  define SBE_BIG_ENDIAN_ENCODE_32(v) (v)
#  define SBE_BIG_ENDIAN_ENCODE_64(v) (v)
#else
#  error "Byte Ordering of platform not determined. Set __BYTE_ORDER__ manually before including this file."
#endif

#if defined(SBE_NO_BOUNDS_CHECK)
#  define SBE_BOUNDS_CHECK_EXPECT(exp,c) (false)
#elif defined(_MSC_VER)
#  define SBE_BOUNDS_CHECK_EXPECT(exp,c) (exp)
#else
#  define SBE_BOUNDS_CHECK_EXPECT(exp,c) (__builtin_expect(exp,c))
#endif

#define SBE_NULLVALUE_INT8 (std::numeric_limits<std::int8_t>::min)()
#define SBE_NULLVALUE_INT16 (std::numeric_limits<std::int16_t>::min)()
#define SBE_NULLVALUE_INT32 (std::numeric_limits<std::int32_t>::min)()
#define SBE_NULLVALUE_INT64 (std::numeric_limits<std::int64_t>::min)()
#define SBE_NULLVALUE_UINT8 (std::numeric_limits<std::uint8_t>::max)()
#define SBE_NULLVALUE_UINT16 (std::numeric_limits<std::uint16_t>::max)()
#define SBE_NULLVALUE_UINT32 (std::numeric_limits<std::uint32_t>::max)()
#define SBE_NULLVALUE_UINT64 (std::numeric_limits<std::uint64_t>::max)()


#include "MessageHeader.h"
#include "Boolean.h"
#include "GroupSizeEncoding.h"
#include "VarAsciiEncoding.h"
#include "VarDataEncoding.h"

namespace sbe {

class Logon
{
private:
    char *m_buffer = nullptr;
    std::uint64_t m_bufferLength = 0;
    std::uint64_t m_offset = 0;
    std::uint64_t m_position = 0;
    std::uint64_t m_actingVersion = 0;

    inline std::uint64_t *sbePositionPtr() SBE_NOEXCEPT
    {
        return &m_position;
    }

public:
    static const std::uint16_t SBE_BLOCK_LENGTH = static_cast<std::uint16_t>(12);
    static const std::uint16_t SBE_TEMPLATE_ID = static_cast<std::uint16_t>(65);
    static const std::uint16_t SBE_SCHEMA_ID = static_cast<std::uint16_t>(1);
    static const std::uint16_t SBE_SCHEMA_VERSION = static_cast<std::uint16_t>(0);

    enum MetaAttribute
    {
        EPOCH, TIME_UNIT, SEMANTIC_TYPE, PRESENCE
    };

    union sbe_float_as_uint_u
    {
        float fp_value;
        std::uint32_t uint_value;
    };

    union sbe_double_as_uint_u
    {
        double fp_value;
        std::uint64_t uint_value;
    };

    using messageHeader = MessageHeader;

    Logon() = default;

    Logon(
        char *buffer,
        const std::uint64_t offset,
        const std::uint64_t bufferLength,
        const std::uint64_t actingBlockLength,
        const std::uint64_t actingVersion) :
        m_buffer(buffer),
        m_bufferLength(bufferLength),
        m_offset(offset),
        m_position(sbeCheckPosition(offset + actingBlockLength)),
        m_actingVersion(actingVersion)
    {
    }

    Logon(char *buffer, const std::uint64_t bufferLength) :
        Logon(buffer, 0, bufferLength, sbeBlockLength(), sbeSchemaVersion())
    {
    }

    Logon(
        char *buffer,
        const std::uint64_t bufferLength,
        const std::uint64_t actingBlockLength,
        const std::uint64_t actingVersion) :
        Logon(buffer, 0, bufferLength, actingBlockLength, actingVersion)
    {
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint16_t sbeBlockLength() SBE_NOEXCEPT
    {
        return static_cast<std::uint16_t>(12);
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t sbeBlockAndHeaderLength() SBE_NOEXCEPT
    {
        return messageHeader::encodedLength() + sbeBlockLength();
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint16_t sbeTemplateId() SBE_NOEXCEPT
    {
        return static_cast<std::uint16_t>(65);
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint16_t sbeSchemaId() SBE_NOEXCEPT
    {
        return static_cast<std::uint16_t>(1);
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint16_t sbeSchemaVersion() SBE_NOEXCEPT
    {
        return static_cast<std::uint16_t>(0);
    }

    SBE_NODISCARD static SBE_CONSTEXPR const char *sbeSemanticType() SBE_NOEXCEPT
    {
        return "A";
    }

    SBE_NODISCARD std::uint64_t offset() const SBE_NOEXCEPT
    {
        return m_offset;
    }

    Logon &wrapForEncode(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        return *this = Logon(buffer, offset, bufferLength, sbeBlockLength(), sbeSchemaVersion());
    }

    Logon &wrapAndApplyHeader(char *buffer, const std::uint64_t offset, const std::uint64_t bufferLength)
    {
        messageHeader hdr(buffer, offset, bufferLength, sbeSchemaVersion());

        hdr
            .blockLength(sbeBlockLength())
            .templateId(sbeTemplateId())
            .schemaId(sbeSchemaId())
            .version(sbeSchemaVersion());

        return *this = Logon(
            buffer,
            offset + messageHeader::encodedLength(),
            bufferLength,
            sbeBlockLength(),
            sbeSchemaVersion());
    }

    Logon &wrapForDecode(
        char *buffer,
        const std::uint64_t offset,
        const std::uint64_t actingBlockLength,
        const std::uint64_t actingVersion,
        const std::uint64_t bufferLength)
    {
        return *this = Logon(buffer, offset, bufferLength, actingBlockLength, actingVersion);
    }

    SBE_NODISCARD std::uint64_t sbePosition() const SBE_NOEXCEPT
    {
        return m_position;
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    std::uint64_t sbeCheckPosition(const std::uint64_t position)
    {
        if (SBE_BOUNDS_CHECK_EXPECT((position > m_bufferLength), false))
        {
            throw std::runtime_error("buffer too short [E100]");
        }
        return position;
    }

    void sbePosition(const std::uint64_t position)
    {
        m_position = sbeCheckPosition(position);
    }

    SBE_NODISCARD std::uint64_t encodedLength() const SBE_NOEXCEPT
    {
        return sbePosition() - m_offset;
    }

    SBE_NODISCARD std::uint64_t decodeLength() const
    {
        Logon skipper(m_buffer, m_offset, m_bufferLength, sbeBlockLength(), m_actingVersion);
        skipper.skip();
        return skipper.encodedLength();
    }

    SBE_NODISCARD const char *buffer() const SBE_NOEXCEPT
    {
        return m_buffer;
    }

    SBE_NODISCARD char *buffer() SBE_NOEXCEPT
    {
        return m_buffer;
    }

    SBE_NODISCARD std::uint64_t bufferLength() const SBE_NOEXCEPT
    {
        return m_bufferLength;
    }

    SBE_NODISCARD std::uint64_t actingVersion() const SBE_NOEXCEPT
    {
        return m_actingVersion;
    }

    SBE_NODISCARD static const char *EncryptMethodMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::PRESENCE: return "required";
            default: return "";
        }
    }

    static SBE_CONSTEXPR std::uint16_t encryptMethodId() SBE_NOEXCEPT
    {
        return 98;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t encryptMethodSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    SBE_NODISCARD bool encryptMethodInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= encryptMethodSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::size_t encryptMethodEncodingOffset() SBE_NOEXCEPT
    {
        return 0;
    }

    static SBE_CONSTEXPR std::uint8_t encryptMethodNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t encryptMethodMinValue() SBE_NOEXCEPT
    {
        return static_cast<std::uint8_t>(0);
    }

    static SBE_CONSTEXPR std::uint8_t encryptMethodMaxValue() SBE_NOEXCEPT
    {
        return static_cast<std::uint8_t>(254);
    }

    static SBE_CONSTEXPR std::size_t encryptMethodEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    SBE_NODISCARD std::uint8_t encryptMethod() const SBE_NOEXCEPT
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset + 0, sizeof(std::uint8_t));
        return (val);
    }

    Logon &encryptMethod(const std::uint8_t value) SBE_NOEXCEPT
    {
        std::uint8_t val = (value);
        std::memcpy(m_buffer + m_offset + 0, &val, sizeof(std::uint8_t));
        return *this;
    }

    SBE_NODISCARD static const char *HeartBtIntMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::PRESENCE: return "required";
            default: return "";
        }
    }

    static SBE_CONSTEXPR std::uint16_t heartBtIntId() SBE_NOEXCEPT
    {
        return 108;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t heartBtIntSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    SBE_NODISCARD bool heartBtIntInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= heartBtIntSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::size_t heartBtIntEncodingOffset() SBE_NOEXCEPT
    {
        return 1;
    }

    static SBE_CONSTEXPR std::uint8_t heartBtIntNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT8;
    }

    static SBE_CONSTEXPR std::uint8_t heartBtIntMinValue() SBE_NOEXCEPT
    {
        return static_cast<std::uint8_t>(0);
    }

    static SBE_CONSTEXPR std::uint8_t heartBtIntMaxValue() SBE_NOEXCEPT
    {
        return static_cast<std::uint8_t>(254);
    }

    static SBE_CONSTEXPR std::size_t heartBtIntEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    SBE_NODISCARD std::uint8_t heartBtInt() const SBE_NOEXCEPT
    {
        std::uint8_t val;
        std::memcpy(&val, m_buffer + m_offset + 1, sizeof(std::uint8_t));
        return (val);
    }

    Logon &heartBtInt(const std::uint8_t value) SBE_NOEXCEPT
    {
        std::uint8_t val = (value);
        std::memcpy(m_buffer + m_offset + 1, &val, sizeof(std::uint8_t));
        return *this;
    }

    SBE_NODISCARD static const char *ResetSeqNumFlagMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::PRESENCE: return "required";
            default: return "";
        }
    }

    static SBE_CONSTEXPR std::uint16_t resetSeqNumFlagId() SBE_NOEXCEPT
    {
        return 141;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t resetSeqNumFlagSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    SBE_NODISCARD bool resetSeqNumFlagInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= resetSeqNumFlagSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::size_t resetSeqNumFlagEncodingOffset() SBE_NOEXCEPT
    {
        return 2;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::size_t resetSeqNumFlagEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    SBE_NODISCARD Boolean::Value resetSeqNumFlag() const
    {
        char val;
        std::memcpy(&val, m_buffer + m_offset + 2, sizeof(char));
        return Boolean::get((val));
    }

    Logon &resetSeqNumFlag(const Boolean::Value value) SBE_NOEXCEPT
    {
        char val = (value);
        std::memcpy(m_buffer + m_offset + 2, &val, sizeof(char));
        return *this;
    }

    SBE_NODISCARD static const char *NextExpectedMsgSeqNumMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::PRESENCE: return "required";
            default: return "";
        }
    }

    static SBE_CONSTEXPR std::uint16_t nextExpectedMsgSeqNumId() SBE_NOEXCEPT
    {
        return 789;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t nextExpectedMsgSeqNumSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    SBE_NODISCARD bool nextExpectedMsgSeqNumInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= nextExpectedMsgSeqNumSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::size_t nextExpectedMsgSeqNumEncodingOffset() SBE_NOEXCEPT
    {
        return 3;
    }

    static SBE_CONSTEXPR std::uint32_t nextExpectedMsgSeqNumNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t nextExpectedMsgSeqNumMinValue() SBE_NOEXCEPT
    {
        return UINT32_C(0x0);
    }

    static SBE_CONSTEXPR std::uint32_t nextExpectedMsgSeqNumMaxValue() SBE_NOEXCEPT
    {
        return UINT32_C(0xfffffffe);
    }

    static SBE_CONSTEXPR std::size_t nextExpectedMsgSeqNumEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    SBE_NODISCARD std::uint32_t nextExpectedMsgSeqNum() const SBE_NOEXCEPT
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset + 3, sizeof(std::uint32_t));
        return SBE_LITTLE_ENDIAN_ENCODE_32(val);
    }

    Logon &nextExpectedMsgSeqNum(const std::uint32_t value) SBE_NOEXCEPT
    {
        std::uint32_t val = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        std::memcpy(m_buffer + m_offset + 3, &val, sizeof(std::uint32_t));
        return *this;
    }

    SBE_NODISCARD static const char *MaxMessageSizeMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::PRESENCE: return "required";
            default: return "";
        }
    }

    static SBE_CONSTEXPR std::uint16_t maxMessageSizeId() SBE_NOEXCEPT
    {
        return 383;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t maxMessageSizeSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    SBE_NODISCARD bool maxMessageSizeInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= maxMessageSizeSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::size_t maxMessageSizeEncodingOffset() SBE_NOEXCEPT
    {
        return 7;
    }

    static SBE_CONSTEXPR std::uint32_t maxMessageSizeNullValue() SBE_NOEXCEPT
    {
        return SBE_NULLVALUE_UINT32;
    }

    static SBE_CONSTEXPR std::uint32_t maxMessageSizeMinValue() SBE_NOEXCEPT
    {
        return UINT32_C(0x0);
    }

    static SBE_CONSTEXPR std::uint32_t maxMessageSizeMaxValue() SBE_NOEXCEPT
    {
        return UINT32_C(0xfffffffe);
    }

    static SBE_CONSTEXPR std::size_t maxMessageSizeEncodingLength() SBE_NOEXCEPT
    {
        return 4;
    }

    SBE_NODISCARD std::uint32_t maxMessageSize() const SBE_NOEXCEPT
    {
        std::uint32_t val;
        std::memcpy(&val, m_buffer + m_offset + 7, sizeof(std::uint32_t));
        return SBE_LITTLE_ENDIAN_ENCODE_32(val);
    }

    Logon &maxMessageSize(const std::uint32_t value) SBE_NOEXCEPT
    {
        std::uint32_t val = SBE_LITTLE_ENDIAN_ENCODE_32(value);
        std::memcpy(m_buffer + m_offset + 7, &val, sizeof(std::uint32_t));
        return *this;
    }

    SBE_NODISCARD static const char *TestMessageIndicatorMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::PRESENCE: return "required";
            default: return "";
        }
    }

    static SBE_CONSTEXPR std::uint16_t testMessageIndicatorId() SBE_NOEXCEPT
    {
        return 464;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t testMessageIndicatorSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    SBE_NODISCARD bool testMessageIndicatorInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= testMessageIndicatorSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::size_t testMessageIndicatorEncodingOffset() SBE_NOEXCEPT
    {
        return 11;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::size_t testMessageIndicatorEncodingLength() SBE_NOEXCEPT
    {
        return 1;
    }

    SBE_NODISCARD Boolean::Value testMessageIndicator() const
    {
        char val;
        std::memcpy(&val, m_buffer + m_offset + 11, sizeof(char));
        return Boolean::get((val));
    }

    Logon &testMessageIndicator(const Boolean::Value value) SBE_NOEXCEPT
    {
        char val = (value);
        std::memcpy(m_buffer + m_offset + 11, &val, sizeof(char));
        return *this;
    }

    class NoMsgTypes
    {
    private:
        char *m_buffer = nullptr;
        std::uint64_t m_bufferLength = 0;
        std::uint64_t m_initialPosition = 0;
        std::uint64_t *m_positionPtr = nullptr;
        std::uint64_t m_blockLength = 0;
        std::uint64_t m_count = 0;
        std::uint64_t m_index = 0;
        std::uint64_t m_offset = 0;
        std::uint64_t m_actingVersion = 0;

        SBE_NODISCARD std::uint64_t *sbePositionPtr() SBE_NOEXCEPT
        {
            return m_positionPtr;
        }

    public:
        inline void wrapForDecode(
            char *buffer,
            std::uint64_t *pos,
            const std::uint64_t actingVersion,
            const std::uint64_t bufferLength)
        {
            GroupSizeEncoding dimensions(buffer, *pos, bufferLength, actingVersion);
            m_buffer = buffer;
            m_bufferLength = bufferLength;
            m_blockLength = dimensions.blockLength();
            m_count = dimensions.numInGroup();
            m_index = 0;
            m_actingVersion = actingVersion;
            m_initialPosition = *pos;
            m_positionPtr = pos;
            *m_positionPtr = *m_positionPtr + 4;
        }

        inline void wrapForEncode(
            char *buffer,
            const std::uint16_t count,
            std::uint64_t *pos,
            const std::uint64_t actingVersion,
            const std::uint64_t bufferLength)
        {
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wtype-limits"
    #endif
            if (count > 65534)
            {
                throw std::runtime_error("count outside of allowed range [E110]");
            }
    #if defined(__GNUG__) && !defined(__clang__)
    #pragma GCC diagnostic pop
    #endif
            m_buffer = buffer;
            m_bufferLength = bufferLength;
            GroupSizeEncoding dimensions(buffer, *pos, bufferLength, actingVersion);
            dimensions.blockLength(static_cast<std::uint16_t>(4));
            dimensions.numInGroup(static_cast<std::uint16_t>(count));
            m_index = 0;
            m_count = count;
            m_blockLength = 4;
            m_actingVersion = actingVersion;
            m_initialPosition = *pos;
            m_positionPtr = pos;
            *m_positionPtr = *m_positionPtr + 4;
        }

        static SBE_CONSTEXPR std::uint64_t sbeHeaderSize() SBE_NOEXCEPT
        {
            return 4;
        }

        static SBE_CONSTEXPR std::uint64_t sbeBlockLength() SBE_NOEXCEPT
        {
            return 4;
        }

        SBE_NODISCARD std::uint64_t sbePosition() const SBE_NOEXCEPT
        {
            return *m_positionPtr;
        }

        // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
        std::uint64_t sbeCheckPosition(const std::uint64_t position)
        {
            if (SBE_BOUNDS_CHECK_EXPECT((position > m_bufferLength), false))
            {
                throw std::runtime_error("buffer too short [E100]");
            }
            return position;
        }

        void sbePosition(const std::uint64_t position)
        {
            *m_positionPtr = sbeCheckPosition(position);
        }

        SBE_NODISCARD inline std::uint64_t count() const SBE_NOEXCEPT
        {
            return m_count;
        }

        SBE_NODISCARD inline bool hasNext() const SBE_NOEXCEPT
        {
            return m_index < m_count;
        }

        inline NoMsgTypes &next()
        {
            if (m_index >= m_count)
            {
                throw std::runtime_error("index >= count [E108]");
            }
            m_offset = *m_positionPtr;
            if (SBE_BOUNDS_CHECK_EXPECT(((m_offset + m_blockLength) > m_bufferLength), false))
            {
                throw std::runtime_error("buffer too short for next group index [E108]");
            }
            *m_positionPtr = m_offset + m_blockLength;
            ++m_index;

            return *this;
        }

        inline std::uint64_t resetCountToIndex() SBE_NOEXCEPT
        {
            m_count = m_index;
            GroupSizeEncoding dimensions(m_buffer, m_initialPosition, m_bufferLength, m_actingVersion);
            dimensions.numInGroup(static_cast<std::uint16_t>(m_count));
            return m_count;
        }

    #if __cplusplus < 201103L
        template<class Func> inline void forEach(Func& func)
        {
            while (hasNext())
            {
                next();
                func(*this);
            }
        }

    #else
        template<class Func> inline void forEach(Func&& func)
        {
            while (hasNext())
            {
                next();
                func(*this);
            }
        }

    #endif

        SBE_NODISCARD static const char *RefMsgTypeMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
        {
            switch (metaAttribute)
            {
                case MetaAttribute::PRESENCE: return "required";
                default: return "";
            }
        }

        static SBE_CONSTEXPR std::uint16_t refMsgTypeId() SBE_NOEXCEPT
        {
            return 372;
        }

        SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t refMsgTypeSinceVersion() SBE_NOEXCEPT
        {
            return 0;
        }

        SBE_NODISCARD bool refMsgTypeInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= refMsgTypeSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        SBE_NODISCARD static SBE_CONSTEXPR std::size_t refMsgTypeEncodingOffset() SBE_NOEXCEPT
        {
            return 0;
        }

        static SBE_CONSTEXPR char refMsgTypeNullValue() SBE_NOEXCEPT
        {
            return static_cast<char>(0);
        }

        static SBE_CONSTEXPR char refMsgTypeMinValue() SBE_NOEXCEPT
        {
            return static_cast<char>(32);
        }

        static SBE_CONSTEXPR char refMsgTypeMaxValue() SBE_NOEXCEPT
        {
            return static_cast<char>(126);
        }

        static SBE_CONSTEXPR std::size_t refMsgTypeEncodingLength() SBE_NOEXCEPT
        {
            return 3;
        }

        static SBE_CONSTEXPR std::uint64_t refMsgTypeLength() SBE_NOEXCEPT
        {
            return 3;
        }

        SBE_NODISCARD const char *refMsgType() const SBE_NOEXCEPT
        {
            return m_buffer + m_offset + 0;
        }

        SBE_NODISCARD char *refMsgType() SBE_NOEXCEPT
        {
            return m_buffer + m_offset + 0;
        }

        SBE_NODISCARD char refMsgType(const std::uint64_t index) const
        {
            if (index >= 3)
            {
                throw std::runtime_error("index out of range for refMsgType [E104]");
            }

            char val;
            std::memcpy(&val, m_buffer + m_offset + 0 + (index * 1), sizeof(char));
            return (val);
        }

        NoMsgTypes &refMsgType(const std::uint64_t index, const char value)
        {
            if (index >= 3)
            {
                throw std::runtime_error("index out of range for refMsgType [E105]");
            }

            char val = (value);
            std::memcpy(m_buffer + m_offset + 0 + (index * 1), &val, sizeof(char));
            return *this;
        }

        std::uint64_t getRefMsgType(char *const dst, const std::uint64_t length) const
        {
            if (length > 3)
            {
                throw std::runtime_error("length too large for getRefMsgType [E106]");
            }

            std::memcpy(dst, m_buffer + m_offset + 0, sizeof(char) * static_cast<size_t>(length));
            return length;
        }

        NoMsgTypes &putRefMsgType(const char *const src) SBE_NOEXCEPT
        {
            std::memcpy(m_buffer + m_offset + 0, src, sizeof(char) * 3);
            return *this;
        }

        NoMsgTypes &putRefMsgType(
            const char value0,
            const char value1,
            const char value2) SBE_NOEXCEPT
        {
            char val0 = (value0);
            std::memcpy(m_buffer + m_offset + 0, &val0, sizeof(char));
            char val1 = (value1);
            std::memcpy(m_buffer + m_offset + 1, &val1, sizeof(char));
            char val2 = (value2);
            std::memcpy(m_buffer + m_offset + 2, &val2, sizeof(char));

            return *this;
        }

        SBE_NODISCARD std::string getRefMsgTypeAsString() const
        {
            const char *buffer = m_buffer + m_offset + 0;
            size_t length = 0;

            for (; length < 3 && *(buffer + length) != '\0'; ++length);
            std::string result(buffer, length);

            return result;
        }

        std::string getRefMsgTypeAsJsonEscapedString()
        {
            std::ostringstream oss;
            std::string s = getRefMsgTypeAsString();

            for (const auto c : s)
            {
                switch (c)
                {
                    case '"': oss << "\\\""; break;
                    case '\\': oss << "\\\\"; break;
                    case '\b': oss << "\\b"; break;
                    case '\f': oss << "\\f"; break;
                    case '\n': oss << "\\n"; break;
                    case '\r': oss << "\\r"; break;
                    case '\t': oss << "\\t"; break;

                    default:
                        if ('\x00' <= c && c <= '\x1f')
                        {
                            oss << "\\u" << std::hex << std::setw(4)
                                << std::setfill('0') << (int)(c);
                        }
                        else
                        {
                            oss << c;
                        }
                }
            }

            return oss.str();
        }

        #if __cplusplus >= 201703L
        SBE_NODISCARD std::string_view getRefMsgTypeAsStringView() const SBE_NOEXCEPT
        {
            const char *buffer = m_buffer + m_offset + 0;
            size_t length = 0;

            for (; length < 3 && *(buffer + length) != '\0'; ++length);
            std::string_view result(buffer, length);

            return result;
        }
        #endif

        #if __cplusplus >= 201703L
        NoMsgTypes &putRefMsgType(const std::string_view str)
        {
            const size_t srcLength = str.length();
            if (srcLength > 3)
            {
                throw std::runtime_error("string too large for putRefMsgType [E106]");
            }

            std::memcpy(m_buffer + m_offset + 0, str.data(), srcLength);
            for (size_t start = srcLength; start < 3; ++start)
            {
                m_buffer[m_offset + 0 + start] = 0;
            }

            return *this;
        }
        #else
        NoMsgTypes &putRefMsgType(const std::string& str)
        {
            const size_t srcLength = str.length();
            if (srcLength > 3)
            {
                throw std::runtime_error("string too large for putRefMsgType [E106]");
            }

            std::memcpy(m_buffer + m_offset + 0, str.c_str(), srcLength);
            for (size_t start = srcLength; start < 3; ++start)
            {
                m_buffer[m_offset + 0 + start] = 0;
            }

            return *this;
        }
        #endif

        SBE_NODISCARD static const char *MsgDirectionMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
        {
            switch (metaAttribute)
            {
                case MetaAttribute::PRESENCE: return "required";
                default: return "";
            }
        }

        static SBE_CONSTEXPR std::uint16_t msgDirectionId() SBE_NOEXCEPT
        {
            return 385;
        }

        SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t msgDirectionSinceVersion() SBE_NOEXCEPT
        {
            return 0;
        }

        SBE_NODISCARD bool msgDirectionInActingVersion() SBE_NOEXCEPT
        {
    #if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wtautological-compare"
    #endif
            return m_actingVersion >= msgDirectionSinceVersion();
    #if defined(__clang__)
    #pragma clang diagnostic pop
    #endif
        }

        SBE_NODISCARD static SBE_CONSTEXPR std::size_t msgDirectionEncodingOffset() SBE_NOEXCEPT
        {
            return 3;
        }

        static SBE_CONSTEXPR char msgDirectionNullValue() SBE_NOEXCEPT
        {
            return static_cast<char>(0);
        }

        static SBE_CONSTEXPR char msgDirectionMinValue() SBE_NOEXCEPT
        {
            return static_cast<char>(32);
        }

        static SBE_CONSTEXPR char msgDirectionMaxValue() SBE_NOEXCEPT
        {
            return static_cast<char>(126);
        }

        static SBE_CONSTEXPR std::size_t msgDirectionEncodingLength() SBE_NOEXCEPT
        {
            return 1;
        }

        SBE_NODISCARD char msgDirection() const SBE_NOEXCEPT
        {
            char val;
            std::memcpy(&val, m_buffer + m_offset + 3, sizeof(char));
            return (val);
        }

        NoMsgTypes &msgDirection(const char value) SBE_NOEXCEPT
        {
            char val = (value);
            std::memcpy(m_buffer + m_offset + 3, &val, sizeof(char));
            return *this;
        }

        template<typename CharT, typename Traits>
        friend std::basic_ostream<CharT, Traits>& operator << (
            std::basic_ostream<CharT, Traits>& builder, NoMsgTypes writer)
        {
            builder << '{';
            builder << R"("RefMsgType": )";
            builder << '"' <<
                writer.getRefMsgTypeAsJsonEscapedString().c_str() << '"';

            builder << ", ";
            builder << R"("MsgDirection": )";
            if (std::isprint(writer.msgDirection()))
            {
                builder << '"' << (char)writer.msgDirection() << '"';
            }
            else
            {
                builder << (int)writer.msgDirection();
            }

            builder << '}';

            return builder;
        }

        void skip()
        {
        }

        SBE_NODISCARD static SBE_CONSTEXPR bool isConstLength() SBE_NOEXCEPT
        {
            return true;
        }

        SBE_NODISCARD static std::size_t computeLength()
        {
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif
            std::size_t length = sbeBlockLength();

            return length;
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
        }
    };

private:
    NoMsgTypes m_noMsgTypes;

public:
    SBE_NODISCARD static SBE_CONSTEXPR std::uint16_t NoMsgTypesId() SBE_NOEXCEPT
    {
        return 384;
    }

    SBE_NODISCARD inline NoMsgTypes &noMsgTypes()
    {
        m_noMsgTypes.wrapForDecode(m_buffer, sbePositionPtr(), m_actingVersion, m_bufferLength);
        return m_noMsgTypes;
    }

    NoMsgTypes &noMsgTypesCount(const std::uint16_t count)
    {
        m_noMsgTypes.wrapForEncode(m_buffer, count, sbePositionPtr(), m_actingVersion, m_bufferLength);
        return m_noMsgTypes;
    }

    SBE_NODISCARD static SBE_CONSTEXPR std::uint64_t noMsgTypesSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    SBE_NODISCARD bool noMsgTypesInActingVersion() const SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= noMsgTypesSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    SBE_NODISCARD static const char *UsernameMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::SEMANTIC_TYPE: return "string";
            case MetaAttribute::PRESENCE: return "required";
            default: return "";
        }
    }

    static const char *usernameCharacterEncoding() SBE_NOEXCEPT
    {
        return "ASCII";
    }

    static SBE_CONSTEXPR std::uint64_t usernameSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    bool usernameInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= usernameSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::uint16_t usernameId() SBE_NOEXCEPT
    {
        return 553;
    }

    static SBE_CONSTEXPR std::uint64_t usernameHeaderLength() SBE_NOEXCEPT
    {
        return 4;
    }

    SBE_NODISCARD std::uint32_t usernameLength() const
    {
        std::uint32_t length;
        std::memcpy(&length, m_buffer + sbePosition(), sizeof(std::uint32_t));
        return SBE_LITTLE_ENDIAN_ENCODE_32(length);
    }

    std::uint64_t skipUsername()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        sbePosition(lengthPosition + lengthOfLengthField + dataLength);
        return dataLength;
    }

    SBE_NODISCARD const char *username()
    {
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + sbePosition(), sizeof(std::uint32_t));
        const char *fieldPtr = m_buffer + sbePosition() + 4;
        sbePosition(sbePosition() + 4 + SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue));
        return fieldPtr;
    }

    std::uint64_t getUsername(char *dst, const std::uint64_t length)
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t bytesToCopy = length < dataLength ? length : dataLength;
        std::uint64_t pos = sbePosition();
        sbePosition(pos + dataLength);
        std::memcpy(dst, m_buffer + pos, static_cast<size_t>(bytesToCopy));
        return bytesToCopy;
    }

    Logon &putUsername(const char *src, const std::uint32_t length)
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        std::uint32_t lengthFieldValue = SBE_LITTLE_ENDIAN_ENCODE_32(length);
        sbePosition(lengthPosition + lengthOfLengthField);
        std::memcpy(m_buffer + lengthPosition, &lengthFieldValue, sizeof(std::uint32_t));
        if (length != std::uint32_t(0))
        {
            std::uint64_t pos = sbePosition();
            sbePosition(pos + length);
            std::memcpy(m_buffer + pos, src, length);
        }
        return *this;
    }

    std::string getUsernameAsString()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t pos = sbePosition();
        const std::string result(m_buffer + pos, dataLength);
        sbePosition(pos + dataLength);
        return result;
    }

    std::string getUsernameAsJsonEscapedString()
    {
        std::ostringstream oss;
        std::string s = getUsernameAsString();

        for (const auto c : s)
        {
            switch (c)
            {
                case '"': oss << "\\\""; break;
                case '\\': oss << "\\\\"; break;
                case '\b': oss << "\\b"; break;
                case '\f': oss << "\\f"; break;
                case '\n': oss << "\\n"; break;
                case '\r': oss << "\\r"; break;
                case '\t': oss << "\\t"; break;

                default:
                    if ('\x00' <= c && c <= '\x1f')
                    {
                        oss << "\\u" << std::hex << std::setw(4)
                            << std::setfill('0') << (int)(c);
                    }
                    else
                    {
                        oss << c;
                    }
            }
        }

        return oss.str();
    }

    #if __cplusplus >= 201703L
    std::string_view getUsernameAsStringView()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t pos = sbePosition();
        const std::string_view result(m_buffer + pos, dataLength);
        sbePosition(pos + dataLength);
        return result;
    }
    #endif

    Logon &putUsername(const std::string& str)
    {
        if (str.length() > 1073741824)
        {
            throw std::runtime_error("std::string too long for length type [E109]");
        }
        return putUsername(str.data(), static_cast<std::uint32_t>(str.length()));
    }

    #if __cplusplus >= 201703L
    Logon &putUsername(const std::string_view str)
    {
        if (str.length() > 1073741824)
        {
            throw std::runtime_error("std::string too long for length type [E109]");
        }
        return putUsername(str.data(), static_cast<std::uint32_t>(str.length()));
    }
    #endif

    SBE_NODISCARD static const char *PasswordMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::SEMANTIC_TYPE: return "string";
            case MetaAttribute::PRESENCE: return "required";
            default: return "";
        }
    }

    static const char *passwordCharacterEncoding() SBE_NOEXCEPT
    {
        return "ASCII";
    }

    static SBE_CONSTEXPR std::uint64_t passwordSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    bool passwordInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= passwordSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::uint16_t passwordId() SBE_NOEXCEPT
    {
        return 554;
    }

    static SBE_CONSTEXPR std::uint64_t passwordHeaderLength() SBE_NOEXCEPT
    {
        return 4;
    }

    SBE_NODISCARD std::uint32_t passwordLength() const
    {
        std::uint32_t length;
        std::memcpy(&length, m_buffer + sbePosition(), sizeof(std::uint32_t));
        return SBE_LITTLE_ENDIAN_ENCODE_32(length);
    }

    std::uint64_t skipPassword()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        sbePosition(lengthPosition + lengthOfLengthField + dataLength);
        return dataLength;
    }

    SBE_NODISCARD const char *password()
    {
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + sbePosition(), sizeof(std::uint32_t));
        const char *fieldPtr = m_buffer + sbePosition() + 4;
        sbePosition(sbePosition() + 4 + SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue));
        return fieldPtr;
    }

    std::uint64_t getPassword(char *dst, const std::uint64_t length)
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t bytesToCopy = length < dataLength ? length : dataLength;
        std::uint64_t pos = sbePosition();
        sbePosition(pos + dataLength);
        std::memcpy(dst, m_buffer + pos, static_cast<size_t>(bytesToCopy));
        return bytesToCopy;
    }

    Logon &putPassword(const char *src, const std::uint32_t length)
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        std::uint32_t lengthFieldValue = SBE_LITTLE_ENDIAN_ENCODE_32(length);
        sbePosition(lengthPosition + lengthOfLengthField);
        std::memcpy(m_buffer + lengthPosition, &lengthFieldValue, sizeof(std::uint32_t));
        if (length != std::uint32_t(0))
        {
            std::uint64_t pos = sbePosition();
            sbePosition(pos + length);
            std::memcpy(m_buffer + pos, src, length);
        }
        return *this;
    }

    std::string getPasswordAsString()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t pos = sbePosition();
        const std::string result(m_buffer + pos, dataLength);
        sbePosition(pos + dataLength);
        return result;
    }

    std::string getPasswordAsJsonEscapedString()
    {
        std::ostringstream oss;
        std::string s = getPasswordAsString();

        for (const auto c : s)
        {
            switch (c)
            {
                case '"': oss << "\\\""; break;
                case '\\': oss << "\\\\"; break;
                case '\b': oss << "\\b"; break;
                case '\f': oss << "\\f"; break;
                case '\n': oss << "\\n"; break;
                case '\r': oss << "\\r"; break;
                case '\t': oss << "\\t"; break;

                default:
                    if ('\x00' <= c && c <= '\x1f')
                    {
                        oss << "\\u" << std::hex << std::setw(4)
                            << std::setfill('0') << (int)(c);
                    }
                    else
                    {
                        oss << c;
                    }
            }
        }

        return oss.str();
    }

    #if __cplusplus >= 201703L
    std::string_view getPasswordAsStringView()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t pos = sbePosition();
        const std::string_view result(m_buffer + pos, dataLength);
        sbePosition(pos + dataLength);
        return result;
    }
    #endif

    Logon &putPassword(const std::string& str)
    {
        if (str.length() > 1073741824)
        {
            throw std::runtime_error("std::string too long for length type [E109]");
        }
        return putPassword(str.data(), static_cast<std::uint32_t>(str.length()));
    }

    #if __cplusplus >= 201703L
    Logon &putPassword(const std::string_view str)
    {
        if (str.length() > 1073741824)
        {
            throw std::runtime_error("std::string too long for length type [E109]");
        }
        return putPassword(str.data(), static_cast<std::uint32_t>(str.length()));
    }
    #endif

    SBE_NODISCARD static const char *RawDataMetaAttribute(const MetaAttribute metaAttribute) SBE_NOEXCEPT
    {
        switch (metaAttribute)
        {
            case MetaAttribute::SEMANTIC_TYPE: return "data";
            case MetaAttribute::PRESENCE: return "required";
            default: return "";
        }
    }

    static const char *rawDataCharacterEncoding() SBE_NOEXCEPT
    {
        return "null";
    }

    static SBE_CONSTEXPR std::uint64_t rawDataSinceVersion() SBE_NOEXCEPT
    {
        return 0;
    }

    bool rawDataInActingVersion() SBE_NOEXCEPT
    {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-compare"
#endif
        return m_actingVersion >= rawDataSinceVersion();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    }

    static SBE_CONSTEXPR std::uint16_t rawDataId() SBE_NOEXCEPT
    {
        return 96;
    }

    static SBE_CONSTEXPR std::uint64_t rawDataHeaderLength() SBE_NOEXCEPT
    {
        return 4;
    }

    SBE_NODISCARD std::uint32_t rawDataLength() const
    {
        std::uint32_t length;
        std::memcpy(&length, m_buffer + sbePosition(), sizeof(std::uint32_t));
        return SBE_LITTLE_ENDIAN_ENCODE_32(length);
    }

    std::uint64_t skipRawData()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        sbePosition(lengthPosition + lengthOfLengthField + dataLength);
        return dataLength;
    }

    SBE_NODISCARD const char *rawData()
    {
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + sbePosition(), sizeof(std::uint32_t));
        const char *fieldPtr = m_buffer + sbePosition() + 4;
        sbePosition(sbePosition() + 4 + SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue));
        return fieldPtr;
    }

    std::uint64_t getRawData(char *dst, const std::uint64_t length)
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t bytesToCopy = length < dataLength ? length : dataLength;
        std::uint64_t pos = sbePosition();
        sbePosition(pos + dataLength);
        std::memcpy(dst, m_buffer + pos, static_cast<size_t>(bytesToCopy));
        return bytesToCopy;
    }

    Logon &putRawData(const char *src, const std::uint32_t length)
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        std::uint32_t lengthFieldValue = SBE_LITTLE_ENDIAN_ENCODE_32(length);
        sbePosition(lengthPosition + lengthOfLengthField);
        std::memcpy(m_buffer + lengthPosition, &lengthFieldValue, sizeof(std::uint32_t));
        if (length != std::uint32_t(0))
        {
            std::uint64_t pos = sbePosition();
            sbePosition(pos + length);
            std::memcpy(m_buffer + pos, src, length);
        }
        return *this;
    }

    std::string getRawDataAsString()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t pos = sbePosition();
        const std::string result(m_buffer + pos, dataLength);
        sbePosition(pos + dataLength);
        return result;
    }

    std::string getRawDataAsJsonEscapedString()
    {
        std::ostringstream oss;
        std::string s = getRawDataAsString();

        for (const auto c : s)
        {
            switch (c)
            {
                case '"': oss << "\\\""; break;
                case '\\': oss << "\\\\"; break;
                case '\b': oss << "\\b"; break;
                case '\f': oss << "\\f"; break;
                case '\n': oss << "\\n"; break;
                case '\r': oss << "\\r"; break;
                case '\t': oss << "\\t"; break;

                default:
                    if ('\x00' <= c && c <= '\x1f')
                    {
                        oss << "\\u" << std::hex << std::setw(4)
                            << std::setfill('0') << (int)(c);
                    }
                    else
                    {
                        oss << c;
                    }
            }
        }

        return oss.str();
    }

    #if __cplusplus >= 201703L
    std::string_view getRawDataAsStringView()
    {
        std::uint64_t lengthOfLengthField = 4;
        std::uint64_t lengthPosition = sbePosition();
        sbePosition(lengthPosition + lengthOfLengthField);
        std::uint32_t lengthFieldValue;
        std::memcpy(&lengthFieldValue, m_buffer + lengthPosition, sizeof(std::uint32_t));
        std::uint64_t dataLength = SBE_LITTLE_ENDIAN_ENCODE_32(lengthFieldValue);
        std::uint64_t pos = sbePosition();
        const std::string_view result(m_buffer + pos, dataLength);
        sbePosition(pos + dataLength);
        return result;
    }
    #endif

    Logon &putRawData(const std::string& str)
    {
        if (str.length() > 1073741824)
        {
            throw std::runtime_error("std::string too long for length type [E109]");
        }
        return putRawData(str.data(), static_cast<std::uint32_t>(str.length()));
    }

    #if __cplusplus >= 201703L
    Logon &putRawData(const std::string_view str)
    {
        if (str.length() > 1073741824)
        {
            throw std::runtime_error("std::string too long for length type [E109]");
        }
        return putRawData(str.data(), static_cast<std::uint32_t>(str.length()));
    }
    #endif

template<typename CharT, typename Traits>
friend std::basic_ostream<CharT, Traits>& operator << (
    std::basic_ostream<CharT, Traits>& builder, Logon _writer)
{
    Logon writer(_writer.m_buffer, _writer.m_offset,
        _writer.m_bufferLength, _writer.sbeBlockLength(), _writer.m_actingVersion);
    builder << '{';
    builder << R"("Name": "Logon", )";
    builder << R"("sbeTemplateId": )";
    builder << writer.sbeTemplateId();
    builder << ", ";

    builder << R"("EncryptMethod": )";
    builder << +writer.encryptMethod();

    builder << ", ";
    builder << R"("HeartBtInt": )";
    builder << +writer.heartBtInt();

    builder << ", ";
    builder << R"("ResetSeqNumFlag": )";
    builder << '"' << writer.resetSeqNumFlag() << '"';

    builder << ", ";
    builder << R"("NextExpectedMsgSeqNum": )";
    builder << +writer.nextExpectedMsgSeqNum();

    builder << ", ";
    builder << R"("MaxMessageSize": )";
    builder << +writer.maxMessageSize();

    builder << ", ";
    builder << R"("TestMessageIndicator": )";
    builder << '"' << writer.testMessageIndicator() << '"';

    builder << ", ";
    {
        bool atLeastOne = false;
        builder << R"("NoMsgTypes": [)";
        writer.noMsgTypes().forEach([&](NoMsgTypes& noMsgTypes)
        {
            if (atLeastOne)
            {
                builder << ", ";
            }
            atLeastOne = true;
            builder << noMsgTypes;
        });
        builder << ']';
    }

    builder << ", ";
    builder << R"("Username": )";
    builder << '"' <<
        writer.getUsernameAsJsonEscapedString().c_str() << '"';

    builder << ", ";
    builder << R"("Password": )";
    builder << '"' <<
        writer.getPasswordAsJsonEscapedString().c_str() << '"';

    builder << ", ";
    builder << R"("RawData": )";
    builder << '"' <<
        writer.skipRawData() << " bytes of raw data\"";
    builder << '}';

    return builder;
}

void skip()
{
    noMsgTypes().forEach([](NoMsgTypes e)
    {
        e.skip();
    });
    skipUsername();
    skipPassword();
    skipRawData();
}

SBE_NODISCARD static SBE_CONSTEXPR bool isConstLength() SBE_NOEXCEPT
{
    return false;
}

SBE_NODISCARD static std::size_t computeLength(
    std::size_t noMsgTypesLength = 0,
    std::size_t usernameLength = 0,
    std::size_t passwordLength = 0,
    std::size_t rawDataLength = 0)
{
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif
    std::size_t length = sbeBlockLength();

    length += NoMsgTypes::sbeHeaderSize();
    if (noMsgTypesLength > 65534LL)
    {
        throw std::runtime_error("noMsgTypesLength outside of allowed range [E110]");
    }
    length += noMsgTypesLength *NoMsgTypes::sbeBlockLength();

    length += usernameHeaderLength();
    if (usernameLength > 1073741824LL)
    {
        throw std::runtime_error("usernameLength too long for length type [E109]");
    }
    length += usernameLength;

    length += passwordHeaderLength();
    if (passwordLength > 1073741824LL)
    {
        throw std::runtime_error("passwordLength too long for length type [E109]");
    }
    length += passwordLength;

    length += rawDataHeaderLength();
    if (rawDataLength > 1073741824LL)
    {
        throw std::runtime_error("rawDataLength too long for length type [E109]");
    }
    length += rawDataLength;

    return length;
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
}
};
}
#endif
