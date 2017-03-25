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
# include <cassert>
# include <array>
# include "Fwd.hpp"
# include "Number.hpp"

namespace s3d
{
	/// <summary>
	/// 乱数生成エンジン xorshift64* (周期 2^64-1, メモリ消費 8B)
	/// </summary>
	class Xorshift64Star
	{
	private:

		uint64 m_seed;

	public:

		using result_type = uint64;

		explicit Xorshift64Star(uint64 _seed = 1)
		{
			seed(_seed);
		}

		void seed(const uint64 _seed)
		{
			assert(_seed != 0);

			m_seed = _seed;
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		static constexpr uint64 min()
		{
			return Smallest<uint64>();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		static constexpr uint64 max()
		{
			return Largest<uint64>();
		}

		uint64 operator()()
		{
			m_seed ^= m_seed >> 12; // a
			m_seed ^= m_seed << 25; // b
			m_seed ^= m_seed >> 27; // c
			return m_seed * 2685821657736338717LL;
		}

		uint64 currentSeed() const
		{
			return m_seed;
		}
	};

	/// <summary>
	/// 乱数生成エンジン xorshift128+ (周期 2^128-1, メモリ消費 16B)
	/// </summary>
	class Xorshift128Plus
	{
	private:

		std::array<uint64, 2> m_seeds;

	public:

		using result_type = uint64;

		explicit Xorshift128Plus(uint64 _seed = 1)
		{
			seed(_seed);
		}

		Xorshift128Plus(uint64 seed0, uint64 seed1)
		{
			seed(seed0, seed1);
		}

		void seed(const uint64 _seed)
		{
			m_seeds[0] = _seed;
			m_seeds[1] = 1;
		}

		void seed(const uint64 seed0, const uint64 seed1)
		{
			assert(seed0 != 0 || seed1 != 0);
			m_seeds[0] = seed0;
			m_seeds[1] = seed1;
		}

		void seed(const std::array<uint64, 2>& seeds)
		{
			assert(seeds[0] != 0 || seeds[1] != 0);
			m_seeds = seeds;
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		static constexpr uint64 min()
		{
			return Smallest<uint64>();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		static constexpr uint64 max()
		{
			return Largest<uint64>();
		}

		uint64 operator()()
		{
			uint64 s1 = m_seeds[0];
			const uint64 s0 = m_seeds[1];
			m_seeds[0] = s0;
			s1 ^= s1 << 23; // a
			return (m_seeds[1] = (s1 ^ s0 ^ (s1 >> 17) ^ (s0 >> 26))) + s0; // b, c
		}

		std::array<uint64, 2> currentSeed() const
		{
			return m_seeds;
		}
	};

	/// <summary>
	/// 乱数生成エンジン xorshift1024* (周期 2^1024-1, メモリ消費 132B)
	/// </summary>
	class Xorshift1024Star
	{
	private:

		std::array<uint64, 16> m_seeds;

		uint32 p = 0;

	public:

		using result_type = uint64;

		explicit Xorshift1024Star(uint64 _seed = 1)
		{
			seed(_seed);
		}

		explicit Xorshift1024Star(const std::array<uint64, 16>& seeds)
		{
			seed(seeds);
		}

		void seed(const uint64 _seed)
		{
			assert(_seed != 0);

			Xorshift64Star x(_seed);

			for (auto& s : m_seeds)
			{
				s = x();
			}
		}

		void seed(const std::array<uint64, 16>& seeds)
		{
			m_seeds = seeds;
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		static constexpr uint64 min()
		{
			return Smallest<uint64>();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		static constexpr uint64 max()
		{
			return Largest<uint64>();
		}

		/// <summary>
		/// 乱数を生成します。
		/// </summary>
		/// <returns>
		/// 乱数
		/// </returns>
		uint64 operator()()
		{
			uint64 s0 = m_seeds[p];
			uint64 s1 = m_seeds[p = (p + 1) & 15];
			s1 ^= s1 << 31; // a
			s1 ^= s1 >> 11; // b
			s0 ^= s0 >> 30; // c
			return (m_seeds[p] = s0 ^ s1) * 1181783497276652981LL;
		}

		std::array<uint64, 16> currentSeed() const
		{
			return m_seeds;
		}
	};
}
