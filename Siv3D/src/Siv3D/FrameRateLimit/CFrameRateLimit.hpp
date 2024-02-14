//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "IFrameRateLimit.hpp"

namespace s3d
{
	class CFrameRateLimit final : public ISiv3DFrameRateLimit
	{
	public:

		using clock_type = std::chrono::steady_clock;

		/// @brief フレームレート制限を実行します。
		void update() override;

		/// @brief 目標フレームレートを設定します。
		/// @param fps 目標フレームレート（FPS）。フレームレート制限を無効にする場合は none
		void setTargetFrameRate(const Optional<double>& fps) override;

		/// @brief 目標フレームレートを取得します。
		/// @return 目標フレームレート（FPS）。フレームレート制限が無効の場合は none
		SIV3D_NODISCARD_CXX20
		Optional<double> getTargetFrameRate() const override;

	private:

		class Limiter
		{
		public:

			/// @brief コンストラクタ
			/// @param fps 目標フレームレート（FPS）
			/// @throw Error fps が無効な値の場合
			SIV3D_NODISCARD_CXX20
			explicit Limiter(double fps);

			/// @brief sleepを実行し、フレームを次に進めます。
			void doSleep();

			/// @brief 目標フレームレートを設定します。
			/// @param targetFrameRate 目標フレームレート（FPS）
			/// @throw Error fps が無効な値の場合
			void setTargetFrameRate(double fps);

			/// @brief 目標フレームレートを取得します。
			/// @return 目標フレームレート（FPS）
			SIV3D_NODISCARD_CXX20
			double getTargetFrameRate() const noexcept { return m_fps; }

		private:

			/// @brief 1秒間
			static constexpr clock_type::duration OneSecond = std::chrono::seconds{ 1 };

			/// @brief 目標フレームレート（FPS）
			double m_fps;

			/// @brief 1フレームあたりの時間
			clock_type::duration m_oneFrameDuration;

			/// @brief 目標sleep時刻
			clock_type::time_point m_sleepUntil;
			
			/// @brief フレームレートから1フレームあたりの時間の長さを計算します。
			/// @param fps フレームレート（FPS）
			/// @return 1フレームあたりの時間の長さ
			/// @throw Error fps が無効な値の場合
			SIV3D_NODISCARD_CXX20
			static clock_type::duration FPSToOneFrameDuration(double fps);
		};

		/// @brief フレームレート制限
		/// @remark フレームレート制限が無効の場合は nullptr
		std::unique_ptr<Limiter> m_limiter;
	};
}
