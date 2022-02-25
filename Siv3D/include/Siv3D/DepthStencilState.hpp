//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# if  __has_include(<bit>)
#	include <bit>
# endif
# include <cstring>
# include <functional>
# include "Common.hpp"
# include "Utility.hpp"

# ifdef Always
#	undef Always
# endif

namespace s3d
{
	enum class DepthFunc : uint8
	{
		Never			= 1,
		Less			= 2,
		Equal			= 3,
		LessEqual		= 4,
		Greater			= 5,
		NotEqual		= 6,
		GreaterEqual	= 7,
		Always			= 8
	};

	/// @brief デプス・ステンシルステート
	struct DepthStencilState
	{
	private:

		enum class Predefined
		{
			Disbaled,

			DepthTest,

			DepthTestWrite,
		};

	public:

		using storage_type = uint32;

		bool depthEnable = false;

		bool depthWriteEnable = false;

		DepthFunc depthFunc = DepthFunc::Always;

		uint8 _unused = false;

		SIV3D_NODISCARD_CXX20
		explicit constexpr DepthStencilState(
			bool _depthEnable = false,
			bool _depthWriteEnable = false,
			DepthFunc _depthFunc = DepthFunc::Always
		);

		SIV3D_NODISCARD_CXX20
		constexpr DepthStencilState(Predefined predefined) noexcept;

		[[nodiscard]]
		storage_type asValue() const noexcept;

		[[nodiscard]]
		bool operator ==(const DepthStencilState& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const DepthStencilState& other) const noexcept;

		/// @remark DepthStencilState{ false, false, DepthFunc::Always }
		static const Predefined Disbaled = Predefined::Disbaled;

		/// @remark DepthStencilState{ true, false, DepthFunc::GreaterEqual }
		static const Predefined DepthTest = Predefined::DepthTest;

		/// @remark DepthStencilState{ true, true, DepthFunc::GreaterEqual }
		static const Predefined DepthTestWrite = Predefined::DepthTestWrite;

		/// @brief 2D 描画時のデフォルト
		/// @remark DepthStencilState::SolidNone
		static const Predefined Default2D = Predefined::Disbaled;

		/// @brief 3D 描画時のデフォルト
		/// @remark DepthStencilState::SolidBack
		static const Predefined Default3D = Predefined::DepthTestWrite;
	};
	static_assert(sizeof(DepthStencilState) == sizeof(DepthStencilState::storage_type));
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::DepthStencilState>
{
	[[nodiscard]]
	size_t operator ()(const s3d::DepthStencilState& value) const noexcept
	{
		return hash<s3d::DepthStencilState::storage_type>()(value.asValue());
	}
};

# include "detail/DepthStencilState.ipp"
