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
# include <array>
# include "Fwd.hpp"
# include "HardwareRNG.hpp"
# include "ThirdParty/SFMT/SFMT.hpp"

namespace s3d
{
	/// <summary>
	/// 乱数生成エンジン SFMT 19937 (周期 2^19937-1, メモリ消費 2,512 bytes)
	/// </summary>
	class SFMT19937_64
	{
	private:

		detail::SFMT_T m_sfmt;

	public:

		using result_type = uint64;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		/// <remarks>
		/// シードはランダムに設定されます。
		/// </remarks>
		SFMT19937_64()
		{
			uint32 keys[16];

			HardwareRNG rng;

			for (auto& key : keys)
			{
				key = rng();
			}

			detail::sfmt_init_by_array(&m_sfmt, keys, 16);
		}

		/// <summary>
		/// シードを指定して乱数生成器を作成します。
		/// </summary>
		/// <param name="seed">
		/// シード
		/// </param>
		explicit SFMT19937_64(const uint64 seed)
		{
			this->seed(seed);
		}

		/// <summary>
		/// シードを指定して乱数生成器を作成します。
		/// </summary>
		/// <param name="seeds">
		/// シード
		/// </param>
		explicit SFMT19937_64(const std::array<uint64, 8>& seeds)
		{
			seed(seeds);
		}

		/// <summary>
		/// シードを設定しなおします。
		/// </summary>
		/// <param name="seed">
		/// シード
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void seed(uint64 seed)
		{
			uint32 keys[2] = { static_cast<uint32>(seed >> 32), static_cast<uint32>(seed & 0xffFFffFF) };

			detail::sfmt_init_by_array(&m_sfmt, keys, 2);
		}

		/// <summary>
		/// シードを設定しなおします。
		/// </summary>
		/// <param name="seeds">
		/// シード
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void seed(const std::array<uint64, 8>& seeds)
		{
			uint32 keys[16];

			for (size_t i = 0; i < 8; ++i)
			{
				keys[i * 2] = static_cast<uint32>(seeds[i] >> 32);
				
				keys[i * 2 + 1] = static_cast<uint32>(seeds[i] & 0xffFFffFF);
			}

			detail::sfmt_init_by_array(&m_sfmt, keys, 16);
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		[[nodiscard]] static constexpr result_type min()
		{
			return std::numeric_limits<result_type>::min();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		[[nodiscard]] static constexpr result_type max()
		{
			return std::numeric_limits<result_type>::max();
		}

		/// <summary>
		/// 乱数を生成します。
		/// </summary>
		/// <returns>
		/// 乱数
		/// </returns>
		result_type operator()()
		{
			return detail::sfmt_genrand_uint64(&m_sfmt);
		}

		/// <summary>
		/// [0, 1) の範囲の乱数を生成します。
		/// </summary>
		/// <returns>
		/// [0, 1) の範囲の乱数
		/// </returns>
		double generateReal()
		{
			return detail::sfmt_genrand_res53(&m_sfmt);
		}
	};
}
