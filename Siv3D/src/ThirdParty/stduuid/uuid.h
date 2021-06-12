#pragma once

#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <array>
#include <string_view>
#include <iterator>
#include <random>
#include <memory>
#include <functional>
#include <type_traits>
#include <optional>
#include <chrono>
#include <numeric>
#include <atomic>

# if defined(__cpp_lib_span) && __has_include(<span>)
#	include <span>
# else
#   include <gsl/span>
# endif

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef UUID_SYSTEM_GENERATOR
#include <objbase.h>
#endif

#include <windows.h>
#include <intrin.h>       
#include <iphlpapi.h> 
#pragma comment(lib, "IPHLPAPI.lib")

#elif defined(__linux__) || defined(__unix__)

#ifdef UUID_SYSTEM_GENERATOR
#include <uuid/uuid.h>
#endif

#elif defined(__APPLE__)

#ifdef UUID_SYSTEM_GENERATOR
#include <CoreFoundation/CFUUID.h>
#endif

#endif

namespace uuids
{
#ifdef __cpp_lib_span
   template <class ElementType, std::size_t Extent>
   using span = std::span<ElementType, Extent>;
#else
   template <class ElementType, std::ptrdiff_t Extent>
   using span = gsl::span<ElementType, Extent>;
#endif

   namespace detail
   {
      template <typename TChar>
      constexpr inline unsigned char hex2char(TChar const ch)
      {
         if (ch >= static_cast<TChar>('0') && ch <= static_cast<TChar>('9'))
            return ch - static_cast<TChar>('0');
         if (ch >= static_cast<TChar>('a') && ch <= static_cast<TChar>('f'))
            return 10 + ch - static_cast<TChar>('a');
         if (ch >= static_cast<TChar>('A') && ch <= static_cast<TChar>('F'))
            return 10 + ch - static_cast<TChar>('A');
         return 0;
      }

      template <typename TChar>
      constexpr inline bool is_hex(TChar const ch)
      {
         return
            (ch >= static_cast<TChar>('0') && ch <= static_cast<TChar>('9')) ||
            (ch >= static_cast<TChar>('a') && ch <= static_cast<TChar>('f')) ||
            (ch >= static_cast<TChar>('A') && ch <= static_cast<TChar>('F'));
      }

      template <typename TChar>
      constexpr inline unsigned char hexpair2char(TChar const a, TChar const b)
      {
         return (hex2char(a) << 4) | hex2char(b);
      }

      class sha1
      {
      public:
         using digest32_t = uint32_t[5];
         using digest8_t = uint8_t[20];

         static constexpr unsigned int block_bytes = 64;

         inline static uint32_t left_rotate(uint32_t value, size_t const count) 
         {
            return (value << count) ^ (value >> (32 - count));
         }

         sha1() { reset(); }

         void reset() 
         {
            m_digest[0] = 0x67452301;
            m_digest[1] = 0xEFCDAB89;
            m_digest[2] = 0x98BADCFE;
            m_digest[3] = 0x10325476;
            m_digest[4] = 0xC3D2E1F0;
            m_blockByteIndex = 0;
            m_byteCount = 0;
         }

         void process_byte(uint8_t octet) 
         {
            this->m_block[this->m_blockByteIndex++] = octet;
            ++this->m_byteCount;
            if (m_blockByteIndex == block_bytes)
            {
               this->m_blockByteIndex = 0;
               process_block();
            }
         }

         void process_block(void const * const start, void const * const end) 
         {
            const uint8_t* begin = static_cast<const uint8_t*>(start);
            const uint8_t* finish = static_cast<const uint8_t*>(end);
            while (begin != finish) 
            {
               process_byte(*begin);
               begin++;
            }
         }

         void process_bytes(void const * const data, size_t const len)
         {
            const uint8_t* block = static_cast<const uint8_t*>(data);
            process_block(block, block + len);
         }

         uint32_t const * get_digest(digest32_t digest) 
         {
            size_t const bitCount = this->m_byteCount * 8;
            process_byte(0x80);
            if (this->m_blockByteIndex > 56) {
               while (m_blockByteIndex != 0) {
                  process_byte(0);
               }
               while (m_blockByteIndex < 56) {
                  process_byte(0);
               }
            }
            else {
               while (m_blockByteIndex < 56) {
                  process_byte(0);
               }
            }
            process_byte(0);
            process_byte(0);
            process_byte(0);
            process_byte(0);
            process_byte(static_cast<unsigned char>((bitCount >> 24) & 0xFF));
            process_byte(static_cast<unsigned char>((bitCount >> 16) & 0xFF));
            process_byte(static_cast<unsigned char>((bitCount >> 8) & 0xFF));
            process_byte(static_cast<unsigned char>((bitCount) & 0xFF));

            memcpy(digest, m_digest, 5 * sizeof(uint32_t));
            return digest;
         }

         uint8_t const * get_digest_bytes(digest8_t digest) 
         {
            digest32_t d32;
            get_digest(d32);
            size_t di = 0;
            digest[di++] = (uint8_t)(d32[0] >> 24);
            digest[di++] = (uint8_t)(d32[0] >> 16);
            digest[di++] = (uint8_t)(d32[0] >>  8);
            digest[di++] = (uint8_t)(d32[0] >>  0);

            digest[di++] = (uint8_t)(d32[1] >> 24);
            digest[di++] = (uint8_t)(d32[1] >> 16);
            digest[di++] = (uint8_t)(d32[1] >>  8);
            digest[di++] = (uint8_t)(d32[1] >>  0);

            digest[di++] = (uint8_t)(d32[2] >> 24);
            digest[di++] = (uint8_t)(d32[2] >> 16);
            digest[di++] = (uint8_t)(d32[2] >>  8);
            digest[di++] = (uint8_t)(d32[2] >>  0);

            digest[di++] = (uint8_t)(d32[3] >> 24);
            digest[di++] = (uint8_t)(d32[3] >> 16);
            digest[di++] = (uint8_t)(d32[3] >>  8);
            digest[di++] = (uint8_t)(d32[3] >>  0);

            digest[di++] = (uint8_t)(d32[4] >> 24);
            digest[di++] = (uint8_t)(d32[4] >> 16);
            digest[di++] = (uint8_t)(d32[4] >>  8);
            digest[di++] = (uint8_t)(d32[4] >>  0);

            return digest;
         }

      private:
         void process_block() 
         {
            uint32_t w[80];
            for (size_t i = 0; i < 16; i++) {
               w[i] = (m_block[i * 4 + 0] << 24);
               w[i] |= (m_block[i * 4 + 1] << 16);
               w[i] |= (m_block[i * 4 + 2] << 8);
               w[i] |= (m_block[i * 4 + 3]);
            }
            for (size_t i = 16; i < 80; i++) {
               w[i] = left_rotate((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]), 1);
            }

            uint32_t a = m_digest[0];
            uint32_t b = m_digest[1];
            uint32_t c = m_digest[2];
            uint32_t d = m_digest[3];
            uint32_t e = m_digest[4];

            for (std::size_t i = 0; i < 80; ++i) 
            {
               uint32_t f = 0;
               uint32_t k = 0;

               if (i < 20) {
                  f = (b & c) | (~b & d);
                  k = 0x5A827999;
               }
               else if (i < 40) {
                  f = b ^ c ^ d;
                  k = 0x6ED9EBA1;
               }
               else if (i < 60) {
                  f = (b & c) | (b & d) | (c & d);
                  k = 0x8F1BBCDC;
               }
               else {
                  f = b ^ c ^ d;
                  k = 0xCA62C1D6;
               }
               uint32_t temp = left_rotate(a, 5) + f + e + k + w[i];
               e = d;
               d = c;
               c = left_rotate(b, 30);
               b = a;
               a = temp;
            }

            m_digest[0] += a;
            m_digest[1] += b;
            m_digest[2] += c;
            m_digest[3] += d;
            m_digest[4] += e;
         }

      private:
         digest32_t m_digest;
         uint8_t m_block[64];
         size_t m_blockByteIndex;
         size_t m_byteCount;
      };

      static std::mt19937 clock_gen(std::random_device{}());
      static std::uniform_int_distribution<short> clock_dis{ -32768, 32767 };
      static std::atomic_short clock_sequence = clock_dis(clock_gen);
   }

   // --------------------------------------------------------------------------------------------------------------------------
   // UUID format https://tools.ietf.org/html/rfc4122
   // --------------------------------------------------------------------------------------------------------------------------

   // --------------------------------------------------------------------------------------------------------------------------
   // Field	                     NDR Data Type	   Octet #	Note
   // --------------------------------------------------------------------------------------------------------------------------
   // time_low	                  unsigned long	   0 - 3	   The low field of the timestamp.
   // time_mid	                  unsigned short	   4 - 5	   The middle field of the timestamp.
   // time_hi_and_version	      unsigned short	   6 - 7	   The high field of the timestamp multiplexed with the version number.
   // clock_seq_hi_and_reserved	unsigned small	   8	      The high field of the clock sequence multiplexed with the variant.
   // clock_seq_low	            unsigned small	   9	      The low field of the clock sequence.
   // node	                     character	      10 - 15	The spatially unique node identifier.
   // --------------------------------------------------------------------------------------------------------------------------
   // 0                   1                   2                   3
   //  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   // |                          time_low                             |
   // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   // |       time_mid                |         time_hi_and_version   |
   // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   // |clk_seq_hi_res |  clk_seq_low  |         node (0-1)            |
   // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   // |                         node (2-5)                            |
   // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   // --------------------------------------------------------------------------------------------------------------------------
   // enumerations
   // --------------------------------------------------------------------------------------------------------------------------

   // indicated by a bit pattern in octet 8, marked with N in xxxxxxxx-xxxx-xxxx-Nxxx-xxxxxxxxxxxx
   enum class uuid_variant
   {
      // NCS backward compatibility (with the obsolete Apollo Network Computing System 1.5 UUID format)
      // N bit pattern: 0xxx
      // > the first 6 octets of the UUID are a 48-bit timestamp (the number of 4 microsecond units of time since 1 Jan 1980 UTC);
      // > the next 2 octets are reserved;
      // > the next octet is the "address family"; 
      // > the final 7 octets are a 56-bit host ID in the form specified by the address family
      ncs,
      
      // RFC 4122/DCE 1.1 
      // N bit pattern: 10xx
      // > big-endian byte order
      rfc,
      
      // Microsoft Corporation backward compatibility
      // N bit pattern: 110x
      // > little endian byte order
      // > formely used in the Component Object Model (COM) library      
      microsoft,
      
      // reserved for possible future definition
      // N bit pattern: 111x      
      reserved
   };

   // indicated by a bit pattern in octet 6, marked with M in xxxxxxxx-xxxx-Mxxx-xxxx-xxxxxxxxxxxx   
   enum class uuid_version
   {
      none = 0, // only possible for nil or invalid uuids
      time_based = 1,  // The time-based version specified in RFC 4122
      dce_security = 2,  // DCE Security version, with embedded POSIX UIDs.
      name_based_md5 = 3,  // The name-based version specified in RFS 4122 with MD5 hashing
      random_number_based = 4,  // The randomly or pseudo-randomly generated version specified in RFS 4122
      name_based_sha1 = 5   // The name-based version specified in RFS 4122 with SHA1 hashing
   };

   // --------------------------------------------------------------------------------------------------------------------------
   // uuid class
   // --------------------------------------------------------------------------------------------------------------------------
   class uuid
   {
   public:
      using value_type = uint8_t;

      constexpr uuid() noexcept : data({}) {};

      uuid(value_type(&arr)[16]) noexcept
      {
         std::copy(std::cbegin(arr), std::cend(arr), std::begin(data));
      }

      uuid(std::array<value_type, 16> const & arr) noexcept
      {
         std::copy(std::cbegin(arr), std::cend(arr), std::begin(data));
      }

      explicit uuid(span<value_type, 16> bytes)
      {
         std::copy(std::cbegin(bytes), std::cend(bytes), std::begin(data));
      }
      
      template<typename ForwardIterator>
      explicit uuid(ForwardIterator first, ForwardIterator last)
      {
         if (std::distance(first, last) == 16)
            std::copy(first, last, std::begin(data));
      }
      
      constexpr uuid_variant variant() const noexcept
      {
         if ((data[8] & 0x80) == 0x00)
            return uuid_variant::ncs;
         else if ((data[8] & 0xC0) == 0x80)
            return uuid_variant::rfc;
         else if ((data[8] & 0xE0) == 0xC0)
            return uuid_variant::microsoft;
         else
            return uuid_variant::reserved;
      }

      constexpr uuid_version version() const noexcept
      {
         if ((data[6] & 0xF0) == 0x10)
            return uuid_version::time_based;
         else if ((data[6] & 0xF0) == 0x20)
            return uuid_version::dce_security;
         else if ((data[6] & 0xF0) == 0x30)
            return uuid_version::name_based_md5;
         else if ((data[6] & 0xF0) == 0x40)
            return uuid_version::random_number_based;
         else if ((data[6] & 0xF0) == 0x50)
            return uuid_version::name_based_sha1;
         else
            return uuid_version::none;
      }

      constexpr bool is_nil() const noexcept
      {
         for (size_t i = 0; i < data.size(); ++i) if (data[i] != 0) return false;
         return true;
      }

      void swap(uuid & other) noexcept
      {
         data.swap(other.data);
      }

      inline span<std::byte const, 16> as_bytes() const
      {
         return span<std::byte const, 16>(reinterpret_cast<std::byte const*>(data.data()), 16);
      }

      template<class CharT = char>
      static bool is_valid_uuid(CharT const * str) noexcept
      {
         bool firstDigit = true;
         int hasBraces = 0;
         size_t index = 0;
         size_t size = 0;
         if constexpr(std::is_same_v<CharT, char>)
            size = strlen(str);
         else
            size = wcslen(str);

         if (str == nullptr || size == 0) 
            return false;

         if (str[0] == static_cast<CharT>('{'))
            hasBraces = 1;
         if (hasBraces && str[size - 1] != static_cast<CharT>('}'))
            return false;

         for (size_t i = hasBraces; i < size - hasBraces; ++i)
         {
            if (str[i] == static_cast<CharT>('-')) continue;

            if (index >= 16 || !detail::is_hex(str[i]))
            {
               return false;
            }

            if (firstDigit)
            {
               firstDigit = false;
            }
            else
            {
               index++;
               firstDigit = true;
            }
         }

         if (index < 16)
         {
            return false;
         }

         return true;
      }

      template<class CharT = char,
         class Traits = std::char_traits<CharT>,
         class Allocator = std::allocator<CharT>>
      static bool is_valid_uuid(std::basic_string<CharT, Traits, Allocator> const & str) noexcept
      {
         return is_valid_uuid(str.c_str());
      }

      template<class CharT = char>
      static std::optional<uuid> from_string(CharT const * str) noexcept
      {
         CharT digit = 0;
         bool firstDigit = true;
         int hasBraces = 0;
         size_t index = 0;
         size_t size = 0;
         if constexpr(std::is_same_v<CharT, char>)
            size = strlen(str);
         else
            size = wcslen(str);

         std::array<uint8_t, 16> data{ { 0 } };

         if (str == nullptr || size == 0) return {};

         if (str[0] == static_cast<CharT>('{'))
            hasBraces = 1;
         if (hasBraces && str[size - 1] != static_cast<CharT>('}'))
            return {};

         for (size_t i = hasBraces; i < size - hasBraces; ++i)
         {
            if (str[i] == static_cast<CharT>('-')) continue;

            if (index >= 16 || !detail::is_hex(str[i]))
            {
               return {};
            }

            if (firstDigit)
            {
               digit = str[i];
               firstDigit = false;
            }
            else
            {
               data[index++] = detail::hexpair2char(digit, str[i]);
               firstDigit = true;
            }
         }

         if (index < 16)
         {
            return {};
         }

         return uuid{ std::cbegin(data), std::cend(data) };
      }

      template<class CharT = char, 
               class Traits = std::char_traits<CharT>,
               class Allocator = std::allocator<CharT>>
      static std::optional<uuid> from_string(std::basic_string<CharT, Traits, Allocator> const & str) noexcept
      {
         return from_string(str.c_str());
      }

   private:
      std::array<value_type, 16> data{ { 0 } };

      friend bool operator==(uuid const & lhs, uuid const & rhs) noexcept;
      friend bool operator<(uuid const & lhs, uuid const & rhs) noexcept;

      template <class Elem, class Traits>
      friend std::basic_ostream<Elem, Traits> & operator<<(std::basic_ostream<Elem, Traits> &s, uuid const & id);  
   };

   // --------------------------------------------------------------------------------------------------------------------------
   // operators and non-member functions
   // --------------------------------------------------------------------------------------------------------------------------

   inline bool operator== (uuid const& lhs, uuid const& rhs) noexcept
   {
      return lhs.data == rhs.data;
   }

   inline bool operator!= (uuid const& lhs, uuid const& rhs) noexcept
   {
      return !(lhs == rhs);
   }

   inline bool operator< (uuid const& lhs, uuid const& rhs) noexcept
   {
      return lhs.data < rhs.data;
   }

   template <class Elem, class Traits>
   std::basic_ostream<Elem, Traits> & operator<<(std::basic_ostream<Elem, Traits> &s, uuid const & id)
   {
      // save current flags
      std::ios_base::fmtflags f(s.flags());
      
      // manipulate stream as needed
      s << std::hex << std::setfill(static_cast<Elem>('0'))
         << std::setw(2) << (int)id.data[0]
         << std::setw(2) << (int)id.data[1]
         << std::setw(2) << (int)id.data[2]
         << std::setw(2) << (int)id.data[3]
         << '-'
         << std::setw(2) << (int)id.data[4]
         << std::setw(2) << (int)id.data[5]
         << '-'
         << std::setw(2) << (int)id.data[6]
         << std::setw(2) << (int)id.data[7]
         << '-'
         << std::setw(2) << (int)id.data[8]
         << std::setw(2) << (int)id.data[9]
         << '-'
         << std::setw(2) << (int)id.data[10]
         << std::setw(2) << (int)id.data[11]
         << std::setw(2) << (int)id.data[12]
         << std::setw(2) << (int)id.data[13]
         << std::setw(2) << (int)id.data[14]
         << std::setw(2) << (int)id.data[15];

      // restore original flags
      s.flags(f);
      
      return s;
   }

   template<class CharT = char,
            class Traits = std::char_traits<CharT>,
            class Allocator = std::allocator<CharT>>
   inline std::basic_string<CharT, Traits, Allocator> to_string(uuid const & id)
   {
      std::basic_stringstream<CharT, Traits, Allocator> sstr;
      sstr << id;
      return sstr.str();
   }

   inline void swap(uuids::uuid & lhs, uuids::uuid & rhs) noexcept
   {
      lhs.swap(rhs);   
   }

   // --------------------------------------------------------------------------------------------------------------------------
   // namespace IDs that could be used for generating name-based uuids
   // --------------------------------------------------------------------------------------------------------------------------

   // Name string is a fully-qualified domain name
   static uuid uuid_namespace_dns{ {0x6b, 0xa7, 0xb8, 0x10, 0x9d, 0xad, 0x11, 0xd1, 0x80, 0xb4, 0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8} };

   // Name string is a URL
   static uuid uuid_namespace_url{ {0x6b, 0xa7, 0xb8, 0x11, 0x9d, 0xad, 0x11, 0xd1, 0x80, 0xb4, 0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8} };

   // Name string is an ISO OID (See https://oidref.com/, https://en.wikipedia.org/wiki/Object_identifier)
   static uuid uuid_namespace_oid{ {0x6b, 0xa7, 0xb8, 0x12, 0x9d, 0xad, 0x11, 0xd1, 0x80, 0xb4, 0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8} };

   // Name string is an X.500 DN, in DER or a text output format (See https://en.wikipedia.org/wiki/X.500, https://en.wikipedia.org/wiki/Abstract_Syntax_Notation_One)
   static uuid uuid_namespace_x500{ {0x6b, 0xa7, 0xb8, 0x14, 0x9d, 0xad, 0x11, 0xd1, 0x80, 0xb4, 0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8} };

   // --------------------------------------------------------------------------------------------------------------------------
   // uuid generators
   // --------------------------------------------------------------------------------------------------------------------------

#ifdef UUID_SYSTEM_GENERATOR
   class uuid_system_generator
   {
   public:
      using result_type = uuid;

      uuid operator()()
      {
#ifdef _WIN32

         GUID newId;
         ::CoCreateGuid(&newId);

         std::array<uint8_t, 16> bytes =
         { {
               (unsigned char)((newId.Data1 >> 24) & 0xFF),
               (unsigned char)((newId.Data1 >> 16) & 0xFF),
               (unsigned char)((newId.Data1 >> 8) & 0xFF),
               (unsigned char)((newId.Data1) & 0xFF),

               (unsigned char)((newId.Data2 >> 8) & 0xFF),
               (unsigned char)((newId.Data2) & 0xFF),

               (unsigned char)((newId.Data3 >> 8) & 0xFF),
               (unsigned char)((newId.Data3) & 0xFF),

               newId.Data4[0],
               newId.Data4[1],
               newId.Data4[2],
               newId.Data4[3],
               newId.Data4[4],
               newId.Data4[5],
               newId.Data4[6],
               newId.Data4[7]
            } };

         return uuid{ std::begin(bytes), std::end(bytes) };

#elif defined(__linux__) || defined(__unix__)

         uuid_t id;
         uuid_generate(id);

         std::array<uint8_t, 16> bytes =
         { {
               id[0],
               id[1],
               id[2],
               id[3],
               id[4],
               id[5],
               id[6],
               id[7],
               id[8],
               id[9],
               id[10],
               id[11],
               id[12],
               id[13],
               id[14],
               id[15]
            } };

         return uuid{ std::begin(bytes), std::end(bytes) };

#elif defined(__APPLE__)
         auto newId = CFUUIDCreate(NULL);
         auto bytes = CFUUIDGetUUIDBytes(newId);
         CFRelease(newId);

         std::array<uint8_t, 16> arrbytes =
         { {
               bytes.byte0,
               bytes.byte1,
               bytes.byte2,
               bytes.byte3,
               bytes.byte4,
               bytes.byte5,
               bytes.byte6,
               bytes.byte7,
               bytes.byte8,
               bytes.byte9,
               bytes.byte10,
               bytes.byte11,
               bytes.byte12,
               bytes.byte13,
               bytes.byte14,
               bytes.byte15
            } };
         return uuid{ std::begin(arrbytes), std::end(arrbytes) };
#else
         return uuid{};
#endif
      }
   };
#endif

   template <typename UniformRandomNumberGenerator>
   class basic_uuid_random_generator 
   {
   public:
      using engine_type = UniformRandomNumberGenerator;

      explicit basic_uuid_random_generator(engine_type& gen) :
         generator(&gen, [](auto) {}) {}
      explicit basic_uuid_random_generator(engine_type* gen) :
         generator(gen, [](auto) {}) {}

      uuid operator()()
      {
         uint8_t bytes[16];
         for (int i = 0; i < 16; i += 4)
            *reinterpret_cast<uint32_t*>(bytes + i) = distribution(*generator);

         // variant must be 10xxxxxx
         bytes[8] &= 0xBF;
         bytes[8] |= 0x80;

         // version must be 0100xxxx
         bytes[6] &= 0x4F;
         bytes[6] |= 0x40;

         return uuid{std::begin(bytes), std::end(bytes)};
      }

   private:
      std::uniform_int_distribution<uint32_t>  distribution;
      std::shared_ptr<UniformRandomNumberGenerator> generator;
   };

   using uuid_random_generator = basic_uuid_random_generator<std::mt19937>;
   
   class uuid_name_generator
   {
   public:
      explicit uuid_name_generator(uuid const& namespace_uuid) noexcept
         : nsuuid(namespace_uuid)
      {}

      template<class CharT = char>
      uuid operator()(CharT const * name)
      {
         size_t size = 0;
         if constexpr (std::is_same_v<CharT, char>)
            size = strlen(name);
         else
            size = wcslen(name);

         reset();
         process_characters(name, size);
         return make_uuid();
      }

      template<class CharT = char,
         class Traits = std::char_traits<CharT>,
         class Allocator = std::allocator<CharT>>
      uuid operator()(std::basic_string<CharT, Traits, Allocator> const & name)
      {
         reset();
         process_characters(name.data(), name.size());
         return make_uuid();
      }

   private:
      void reset() 
      {
         hasher.reset();
         std::byte bytes[16];
         auto nsbytes = nsuuid.as_bytes();
         std::copy(std::cbegin(nsbytes), std::cend(nsbytes), bytes);
         hasher.process_bytes(bytes, 16);
      }
      
      template <typename char_type,
                typename = std::enable_if_t<std::is_integral<char_type>::value>>
      void process_characters(char_type const * const characters, size_t const count)
      {
         for (size_t i = 0; i < count; i++) 
         {
            uint32_t c = characters[i];
            hasher.process_byte(static_cast<unsigned char>((c >> 0) & 0xFF));
            hasher.process_byte(static_cast<unsigned char>((c >> 8) & 0xFF));
            hasher.process_byte(static_cast<unsigned char>((c >> 16) & 0xFF));
            hasher.process_byte(static_cast<unsigned char>((c >> 24) & 0xFF));
         }
      }

      void process_characters(const char * const characters, size_t const count)
      {
         hasher.process_bytes(characters, count);
      }

      uuid make_uuid()
      {
         detail::sha1::digest8_t digest;
         hasher.get_digest_bytes(digest);

         // variant must be 0b10xxxxxx
         digest[8] &= 0xBF;
         digest[8] |= 0x80;

         // version must be 0b0101xxxx
         digest[6] &= 0x5F;
         digest[6] |= 0x50;

         return uuid{ digest, digest + 16 };
      }

   private:
      uuid nsuuid;
      detail::sha1 hasher;
   };

   // !!! DO NOT USE THIS IN PRODUCTION
   // this implementation is unreliable for good uuids
   class uuid_time_generator
   {
      using mac_address = std::array<unsigned char, 6>;

      std::optional<mac_address> device_address;

      bool get_mac_address()
      {         
         if (device_address.has_value())
         {
            return true;
         }
         
#ifdef _WIN32
         DWORD len = 0;
         auto ret = GetAdaptersInfo(nullptr, &len);
         if (ret != ERROR_BUFFER_OVERFLOW) return false;
         std::vector<unsigned char> buf(len);
         auto pips = reinterpret_cast<PIP_ADAPTER_INFO>(&buf.front());
         ret = GetAdaptersInfo(pips, &len);
         if (ret != ERROR_SUCCESS) return false;
         mac_address addr;
         std::copy(pips->Address, pips->Address + 6, std::begin(addr));
         device_address = addr;
#endif

         return device_address.has_value();
      }

      long long get_time_intervals()
      {
         auto start = std::chrono::system_clock::from_time_t(time_t(-12219292800));
         auto diff = std::chrono::system_clock::now() - start;
         auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
         return ns / 100;
      }

   public:
      uuid_time_generator()
      {
      }

      uuid operator()()
      {
         if (get_mac_address())
         {
            std::array<uuids::uuid::value_type, 16> data;

            auto tm = get_time_intervals();

            short clock_seq = detail::clock_sequence++;

            clock_seq &= 0x3FFF;

            auto ptm = reinterpret_cast<uuids::uuid::value_type*>(&tm);
            ptm[0] &= 0x0F;

            memcpy(&data[0], ptm + 4, 4);
            memcpy(&data[4], ptm + 2, 2);
            memcpy(&data[6], ptm, 2);

            memcpy(&data[8], reinterpret_cast<uuids::uuid::value_type*>(&clock_seq), 2);

            // variant must be 0b10xxxxxx
            data[8] &= 0xBF;
            data[8] |= 0x80;

            // version must be 0b0001xxxx
            data[6] &= 0x5F;
            data[6] |= 0x10;

            memcpy(&data[10], &device_address.value()[0], 6);

            return uuids::uuid{std::cbegin(data), std::cend(data)};
         }

         return {};
      }
   };
}

namespace std
{
   template <>
   struct hash<uuids::uuid>
   {
      using argument_type = uuids::uuid;
      using result_type   = std::size_t;

      result_type operator()(argument_type const &uuid) const
      {
         std::hash<std::string> hasher;
         return static_cast<result_type>(hasher(uuids::to_string(uuid)));
      }
   };
}
