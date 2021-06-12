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

# pragma once
# include <array>
# include "Common.hpp"
# include "StringView.hpp"
# include "Optional.hpp"

namespace s3d
{
	class UUID
	{
	public:

		using value_type = uint8;

		SIV3D_NODISCARD_CXX20
		UUID() = default;

		SIV3D_NODISCARD_CXX20
		explicit UUID(const value_type(&uuid)[16]) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr UUID(const std::array<value_type, 16>& uuid) noexcept;

		template <class Iterator>
		SIV3D_NODISCARD_CXX20
		explicit UUID(Iterator first, Iterator last);

		[[nodiscard]]
		constexpr bool isNil() const noexcept;

		//variant

		//version

		void swap(UUID& other);

		//String toStr() const;

		[[nodiscard]]
		friend constexpr bool operator ==(const UUID& lhs, const UUID& rhs) noexcept
		{
			return (lhs.m_data == rhs.m_data);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const UUID& lhs, const UUID& rhs) noexcept
		{
			return (lhs.m_data != rhs.m_data);
		}

		[[nodiscard]]
		friend constexpr bool operator <(const UUID& lhs, const UUID& rhs) noexcept
		{
			return (lhs.m_data < rhs.m_data);
		}

		[[nodiscard]]
		static UUID Generate();

		[[nodiscard]]
		static UUID FromRNG();

		[[nodiscard]]
		static Optional<UUID> Parse(std::string_view uuid);

		[[nodiscard]]
		static Optional<UUID> Parse(StringView uuid);

	private:

		std::array<uint8, 16> m_data{};
	};
}

# include "detail/UUID.ipp"
