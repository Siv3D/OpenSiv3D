//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/UUID.hpp>

# define UUID_SYSTEM_GENERATOR
# include <ThirdParty/stduuid/uuid.h>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static UUID ToUUID(const uuids::uuid& id)
		{
			std::array<uint8, 16> data;

			std::memcpy(data.data(), id.as_bytes().data(), sizeof(data));

			return UUID{ data };
		}

		void ToHex(char32* dst, const uint8 value) noexcept
		{
			constexpr char s[16] =
			{
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
			};

			dst[0] = static_cast<char32>(s[value >> 4]);
			dst[1] = static_cast<char32>(s[value & 0xF]);
		}
	}

	UUID::UUID(const value_type(&uuid)[16]) noexcept
	{
		std::copy(std::begin(uuid), std::end(uuid), std::begin(m_data));
	}

	UUID::Variant UUID::variant() const noexcept
	{
		return UUID::Variant{ FromEnum(uuids::uuid{ m_data }.variant()) };
	}

	UUID::Version UUID::version() const noexcept
	{
		return UUID::Version{ FromEnum(uuids::uuid{ m_data }.version()) };
	}

	String UUID::toStr() const
	{
		String s(36, U'-');
		detail::ToHex(&s[0], m_data[0]);
		detail::ToHex(&s[2], m_data[1]);
		detail::ToHex(&s[4], m_data[2]);
		detail::ToHex(&s[6], m_data[3]);

		detail::ToHex(&s[9], m_data[4]);
		detail::ToHex(&s[11], m_data[5]);

		detail::ToHex(&s[14], m_data[6]);
		detail::ToHex(&s[16], m_data[7]);

		detail::ToHex(&s[19], m_data[8]);
		detail::ToHex(&s[21], m_data[9]);

		detail::ToHex(&s[24], m_data[10]);
		detail::ToHex(&s[26], m_data[11]);
		detail::ToHex(&s[28], m_data[12]);
		detail::ToHex(&s[30], m_data[13]);
		detail::ToHex(&s[32], m_data[14]);
		detail::ToHex(&s[34], m_data[15]);

		return s;
	}

	UUID UUID::Generate()
	{
		const uuids::uuid id = uuids::uuid_system_generator{}();

		return detail::ToUUID(id);
	}

	UUID UUID::FromRNG()
	{
		const uuids::uuid id = uuids::basic_uuid_random_generator{ GetDefaultRNG() }();

		return detail::ToUUID(id);
	}

	Optional<UUID> UUID::Parse(const std::string_view uuid)
	{
		if (auto result = uuids::uuid::from_string(std::string(uuid)))
		{
			return detail::ToUUID(*result);
		}
		else
		{
			return none;
		}
	}

	Optional<UUID> UUID::Parse(const StringView uuid)
	{
		if (auto result = uuids::uuid::from_string(uuid.toUTF8()))
		{
			return detail::ToUUID(*result);
		}
		else
		{
			return none;
		}
	}
}
