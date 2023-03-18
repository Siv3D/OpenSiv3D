//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/UUIDValue.hpp>

# define UUID_SYSTEM_GENERATOR
# include <ThirdParty/stduuid/uuid.h>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static UUIDValue ToUUIDValue(const uuids::uuid& id) noexcept
		{
			std::array<uint8, 16> data;

			std::memcpy(data.data(), id.as_bytes().data(), sizeof(data));

			return UUIDValue{ data };
		}

		template <class CharType>
		void ToHex(CharType* dst, const uint8 value) noexcept
		{
			constexpr char s[16] =
			{
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
			};

			dst[0] = static_cast<CharType>(s[value >> 4]);
			dst[1] = static_cast<CharType>(s[value & 0xF]);
		}
	}

	UUIDValue::UUIDValue(const value_type(&uuid)[16]) noexcept
	{
		std::copy(std::begin(uuid), std::end(uuid), std::begin(m_data));
	}

	UUIDValue::Variant UUIDValue::variant() const noexcept
	{
		return UUIDValue::Variant{ FromEnum(uuids::uuid{ m_data }.variant()) };
	}

	UUIDValue::Version UUIDValue::version() const noexcept
	{
		return UUIDValue::Version{ FromEnum(uuids::uuid{ m_data }.version()) };
	}

	std::string UUIDValue::to_string() const
	{
		std::string s(36, '-');
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

	String UUIDValue::str() const
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

	UUIDValue UUIDValue::Generate()
	{
		const uuids::uuid id = uuids::uuid_system_generator{}();

		return detail::ToUUIDValue(id);
	}

	UUIDValue UUIDValue::GenerateFromRNG(DefaultRNG& rng)
	{
		const uuids::uuid id = uuids::basic_uuid_random_generator{ rng }();

		return detail::ToUUIDValue(id);
	}

	UUIDValue UUIDValue::GenerateFromName(const UUIDValue& namespaceUUID, const std::string& name)
	{
		const uuids::uuid id = uuids::uuid_name_generator{ namespaceUUID.m_data }(name);

		return detail::ToUUIDValue(id);
	}

	UUIDValue UUIDValue::GenerateFromName(const UUIDValue& namespaceUUID, const String& name)
	{
		const uuids::uuid id = uuids::uuid_name_generator{ namespaceUUID.m_data }(name.toUTF8());

		return detail::ToUUIDValue(id);
	}

	UUIDValue UUIDValue::Nil()
	{
		return{};
	}

	UUIDValue UUIDValue::NamespaceDNS() noexcept
	{
		return detail::ToUUIDValue(uuids::uuid_namespace_dns);
	}

	UUIDValue UUIDValue::NamespaceURL() noexcept
	{
		return detail::ToUUIDValue(uuids::uuid_namespace_url);
	}

	UUIDValue UUIDValue::NamespaceOID() noexcept
	{
		return detail::ToUUIDValue(uuids::uuid_namespace_oid);
	}

	UUIDValue UUIDValue::NamespaceX500() noexcept
	{
		return detail::ToUUIDValue(uuids::uuid_namespace_x500);
	}

	bool UUIDValue::IsValid(const std::string_view uuid)
	{
		return uuids::uuid::is_valid_uuid(std::string(uuid));
	}

	bool UUIDValue::IsValid(const StringView uuid)
	{
		return uuids::uuid::is_valid_uuid(uuid.toUTF8());
	}

	Optional<UUIDValue> UUIDValue::Parse(const std::string_view uuid)
	{
		if (auto result = uuids::uuid::from_string(std::string(uuid)))
		{
			return detail::ToUUIDValue(*result);
		}
		else
		{
			return none;
		}
	}

	Optional<UUIDValue> UUIDValue::Parse(const StringView uuid)
	{
		if (auto result = uuids::uuid::from_string(uuid.toUTF8()))
		{
			return detail::ToUUIDValue(*result);
		}
		else
		{
			return none;
		}
	}

	void Formatter(FormatData& formatData, const UUIDValue& value)
	{
		formatData.string.append(value.str());
	}
}
