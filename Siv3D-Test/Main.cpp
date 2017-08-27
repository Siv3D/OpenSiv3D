# include <Siv3D.hpp> // OpenSiv3D v0.1.7
# include <HamFramework.hpp>
# include "Test/Siv3DTest.hpp"

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

			detail::sfmt_init_by_array(&m_sfmt, keys, std::size(keys));
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

			detail::sfmt_init_by_array(&m_sfmt, keys, std::size(keys));
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

			detail::sfmt_init_by_array(&m_sfmt, keys, std::size(seeds));
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		static constexpr result_type min()
		{
			return std::numeric_limits<uint64>::min();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		static constexpr result_type max()
		{
			return std::numeric_limits<uint64>::max();
		}

		/// <summary>
		/// 乱数を生成します。
		/// </summary>
		/// <returns>
		/// 乱数
		/// </returns>
		result_type operator()()
		{
			return sfmt_genrand_uint64(&m_sfmt);
		}
	};
}


void Main()
{
	constexpr size_t s = sizeof(MT11213b);

	constexpr size_t s2 = sizeof(SFMT19937_64);

	detail::SFMT_T sfmt;
	
	detail::sfmt_init_gen_rand(&sfmt, 1234);
	
	for (auto i : step(5))
	{
		Print << detail::sfmt_genrand_uint32(&sfmt);
	}

	
	//SFMT19937_64 rng;

	//for (auto i : step(5))
	//{
	//	Print << rng();
	//}

	//rng.seed(1234);

	//Print << L"---";

	//for (auto i : step(5))
	//{
	//	Print << rng();
	//}

	//rng.seed(1234);

	//Print << L"---";

	//for (auto i : step(5))
	//{
	//	Print << rng();
	//}
	

	while (System::Update())
	{

		if (MouseL.down())
		{
			Window::SetTitle(L"My Game");
		}
	}
}