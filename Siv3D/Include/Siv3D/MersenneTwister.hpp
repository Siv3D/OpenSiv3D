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
# include <sstream>
# include <random>
# include <array>
# include "Fwd.hpp"
# include "HardwareRNG.hpp"

namespace s3d
{
	/// <summary>
	/// 乱数生成エンジン MT 11213b (周期 2^11213-1, メモリ消費 2816B)
	/// </summary>
	class MT11213b
	{
	private:

		using engine_type = std::mersenne_twister_engine<unsigned, 32, 351, 175, 19, 0xccab8ee7,
			11, 0xffffffff, 7, 0x31b6ab00, 15, 0xffe50000, 17, 1812433253>;

		engine_type m_engine;

	public:

		using result_type = engine_type::result_type;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		/// <remarks>
		/// シードはランダムに設定されます。
		/// </remarks>
		MT11213b()
		{
			HardwareRNG rng;

			std::seed_seq seeds{ rng(), rng(), rng(), rng(), rng(), rng(), rng(), rng() };

			m_engine.seed(seeds);
		}

		/// <summary>
		/// シードを指定して乱数生成器を作成します。
		/// </summary>
		/// <param name="seed">
		/// シード
		/// </param>
		explicit MT11213b(uint32 seed)
			: m_engine(seed) {}

		/// <summary>
		/// シードを指定して乱数生成器を作成します。
		/// </summary>
		/// <param name="seeds">
		/// シード
		/// </param>
		explicit MT11213b(const std::array<uint32, 8>& seeds)
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
		void seed(const uint32 seed)
		{
			m_engine.seed(seed);
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
		void seed(const std::array<uint32, 8>& seeds)
		{
			std::seed_seq seq(std::begin(seeds), std::end(seeds));

			m_engine.seed(seq);
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		static constexpr result_type min()
		{
			return engine_type::min();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		static constexpr result_type max()
		{
			return engine_type::max();
		}

		/// <summary>
		/// 乱数を生成します。
		/// </summary>
		/// <returns>
		/// 乱数
		/// </returns>
		result_type operator()()
		{
			return m_engine();
		}

		std::string serialize() const
		{
			std::ostringstream os;
			os << m_engine;
			return os.str();
		}

		void deserialize(const std::string& representation)
		{
			std::istringstream(representation) >> m_engine;
		}
	};

	/// <summary>
	/// 乱数生成エンジン MT 19937 (周期 2^19937-1, メモリ消費 5000B)
	/// </summary>
	class MT19937
	{
	private:

		using engine_type = std::mt19937;

		engine_type m_engine;

	public:

		using result_type = engine_type::result_type;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		/// <remarks>
		/// シードはランダムに設定されます。
		/// </remarks>
		MT19937()
		{
			HardwareRNG rng;

			std::seed_seq seeds{ rng(), rng(), rng(), rng(), rng(), rng(), rng(), rng() };

			m_engine.seed(seeds);
		}

		/// <summary>
		/// シードを指定して乱数生成器を作成します。
		/// </summary>
		/// <param name="seed">
		/// シード
		/// </param>
		explicit MT19937(uint32 seed)
			: m_engine(seed) {}

		/// <summary>
		/// シードを指定して乱数生成器を作成します。
		/// </summary>
		/// <param name="seeds">
		/// シード
		/// </param>
		explicit MT19937(const std::array<uint32, 8>& seeds)
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
		void seed(const uint32 seed)
		{
			m_engine.seed(seed);
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
		void seed(const std::array<uint32, 8>& seeds)
		{
			std::seed_seq seq(std::begin(seeds), std::end(seeds));

			m_engine.seed(seq);
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		static constexpr result_type min()
		{
			return engine_type::min();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		static constexpr result_type max()
		{
			return engine_type::max();
		}

		/// <summary>
		/// 乱数を生成します。
		/// </summary>
		/// <returns>
		/// 乱数
		/// </returns>
		result_type operator()()
		{
			return m_engine();
		}

		std::string serialize() const
		{
			std::ostringstream os;
			os << m_engine;
			return os.str();
		}

		void deserialize(const std::string& representation)
		{
			std::istringstream(representation) >> m_engine;
		}
	};

	/// <summary>
	/// 乱数生成エンジン MT 19937-64 (周期 2^19937-1, メモリ消費 5008B)
	/// </summary>
	class MT19937_64
	{
	private:

		using engine_type = std::mt19937_64;

		engine_type m_engine;

	public:

		using result_type = engine_type::result_type;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		/// <remarks>
		/// シードはランダムに設定されます。
		/// </remarks>
		MT19937_64()
		{
			uint64 seeds[8];

			HardwareRNG rng;

			for (auto& seed : seeds)
			{
				seed = (static_cast<uint64>(rng()) << 32) | rng();
			}

			std::seed_seq seq(std::begin(seeds), std::end(seeds));

			m_engine.seed(seq);
		}

		/// <summary>
		/// シードを指定して乱数生成器を作成します。
		/// </summary>
		/// <param name="seed">
		/// シード
		/// </param>
		explicit MT19937_64(const uint64 seed)
			: m_engine(seed) {}

		/// <summary>
		/// シードを指定して乱数生成器を作成します。
		/// </summary>
		/// <param name="seeds">
		/// シード
		/// </param>
		explicit MT19937_64(const std::array<uint64, 8>& seeds)
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
			m_engine.seed(seed);
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
			std::seed_seq seq(std::begin(seeds), std::end(seeds));

			m_engine.seed(seq);
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		static constexpr result_type min()
		{
			return engine_type::min();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		static constexpr result_type max()
		{
			return engine_type::max();
		}

		/// <summary>
		/// 乱数を生成します。
		/// </summary>
		/// <returns>
		/// 乱数
		/// </returns>
		result_type operator()()
		{
			return m_engine();
		}

		std::string serialize() const
		{
			std::ostringstream os;
			os << m_engine;
			return os.str();
		}

		void deserialize(const std::string& representation)
		{
			std::istringstream(representation) >> m_engine;
		}
	};
}
