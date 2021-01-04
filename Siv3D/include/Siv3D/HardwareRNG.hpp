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
# include <random>
# include "Common.hpp"

namespace s3d
{
	/// <summary>
	/// 乱数生成エンジン
	/// </summary>
	class HardwareRNG
	{
	public:

		using engine_type = std::random_device;

		using result_type = engine_type::result_type;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		SIV3D_NODISCARD_CXX20
		HardwareRNG() = default;

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		[[nodiscard]]
		static constexpr result_type min() noexcept;

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		[[nodiscard]]
		static constexpr result_type max() noexcept;

		/// <summary>
		/// 乱数を生成します。
		/// </summary>
		/// <returns>
		/// 乱数
		/// </returns>
		result_type operator()();

		template <size_t N>
		std::array<result_type, N> generateSeeds() noexcept;

	private:

		engine_type m_engine;
	};
}

# include "detail/HardwareRNG.ipp"
