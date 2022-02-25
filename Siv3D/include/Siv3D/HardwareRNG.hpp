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
# include <array>
# include <random>
# include "Common.hpp"

namespace s3d
{
	/// @brief ハードウェア情報に基づく非決定的な乱数エンジン
	class HardwareRNG
	{
	public:

		using engine_type = std::random_device;

		/// @brief 生成される乱数の型
		using result_type = engine_type::result_type;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		HardwareRNG() = default;

		/// @brief この乱数生成器で生成される乱数の最小値を返します。
		/// @return 乱数の最小値
		[[nodiscard]]
		static constexpr result_type min() noexcept;

		/// @brief この乱数生成器で生成される乱数の最大値を返します。
		/// @return 乱数の最大値
		[[nodiscard]]
		static constexpr result_type max() noexcept;

		/// @brief 乱数を生成します。
		/// @return 生成された乱数
		result_type operator ()();

		/// @brief 疑似乱数生成エンジンで使うための乱数シード列を作成します。
		/// @return 乱数シード列
		template <size_t N>
		std::array<result_type, N> generateSeeds() noexcept;

	private:

		engine_type m_engine;
	};
}

# include "detail/HardwareRNG.ipp"
