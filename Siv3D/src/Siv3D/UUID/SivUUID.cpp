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
	}

	UUID::UUID(const value_type(&uuid)[16]) noexcept
	{
		std::copy(std::begin(uuid), std::end(uuid), std::begin(m_data));
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
