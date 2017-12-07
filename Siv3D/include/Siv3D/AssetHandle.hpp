//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	template <class Type>
	class AssetHandle
	{
	public:

		using IDType = uint32;

		enum : IDType { NullID = 0 };

	private:

		IDType m_id = NullID;

	public:

		AssetHandle() = default;

		constexpr AssetHandle(IDType id) noexcept
			: m_id(id) {}

		~AssetHandle();

		constexpr IDType getID() const noexcept
		{
			return m_id;
		}
	};
}
