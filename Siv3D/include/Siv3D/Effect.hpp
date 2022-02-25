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
# include "Common.hpp"
# include "IEffect.hpp"
# include "Duration.hpp"
# include "AssetHandle.hpp"

namespace s3d
{
	/// @brief エフェクトグループ
	class Effect : public AssetHandle<Effect>
	{
	public:

		/// @brief エフェクトグループを作成します。
		/// @param maxLifeTimeSec このエフェクトグループでのエフェクトの最大継続時間（秒）
		SIV3D_NODISCARD_CXX20
		Effect(double maxLifeTimeSec = 10.0);

		/// @brief エフェクトグループを作成します。
		/// @param maxLifeTimeSec このエフェクトグループでのエフェクトの最大継続時間（秒）
		SIV3D_NODISCARD_CXX20
		Effect(const Duration& maxLifeTimeSec);

		/// @brief デストラクタ
		virtual ~Effect();

		/// @brief エフェクトグループに新しいエフェクトを追加します
		/// @param effect 追加するエフェクト
		const Effect& add(std::unique_ptr<IEffect>&& effect) const;

		/// @brief エフェクトグループに新しいエフェクトを追加します
		/// @tparam IEffectType 追加するエフェクトの型
		/// @tparam ...Args コンストラクタ引数の型
		/// @param ...args コンストラクタ引数
		template <class IEffectType, class... Args, std::enable_if_t<std::is_base_of_v<IEffect, IEffectType>>* = nullptr>
		const Effect& add(Args&&... args) const;

		/// @brief エフェクトグループに新しいエフェクトを追加します
		/// @remark 関数オブジェクトは double 型を受け取り bool 型を返す必要があります。
		/// @tparam Fty エフェクト（関数オブジェクト）の型
		/// @param f エフェクトの関数オブジェクト
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, double>>* = nullptr>
		const Effect& add(Fty f) const;

		/// @brief エフェクトグループがアクティブなエフェクトを持っているかを返します。
		/// @remark `Effect::hasEffects()` と同じ結果を返します。
		/// @return アクティブなエフェクトがある場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const;

		/// @brief エフェクトグループがアクティブなエフェクトを持っていないかを返します。
		/// @return アクティブなエフェクトがない場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const;

		/// @brief エフェクトグループがアクティブなエフェクトを持っているかを返します。
		/// @return アクティブなエフェクトがある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasEffects() const;

		/// @brief エフェクトグループでアクティブなエフェクトの個数を返します。
		/// @return アクティブなエフェクトの個数
		[[nodiscard]]
		size_t num_effects() const;

		/// @brief このエフェクトグループの時間経過を一時停止します。
		void pause() const;

		/// @brief このエフェクトグループの時間経過が一時停止されているかを返します。
		/// @return 一時停止されている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isPaused() const;

		/// @brief このエフェクトグループの時間経過が一時停止されている場合、再開します。
		void resume() const;

		/// @brief このエフェクトグループの時間経過の速さを、実時間に対する倍率 (2.0 で 2 倍早く経過）で設定します。
		/// @param speed 時間経過の速さ
		const Effect& setSpeed(double speed) const;

		/// @brief このエフェクトグループの時間経過の速さを返します。
		/// @return 時間経過の速さ
		[[nodiscard]]
		double getSpeed() const;

		/// @brief このエフェクトグループでのエフェクトの最大継続時間（秒）を設定します。
		/// @param maxLifeTimeSec このエフェクトグループでのエフェクトの最大継続時間（秒）
		const Effect& setMaxLifeTime(double maxLifeTimeSec);

		/// @brief このエフェクトグループでのエフェクトの最大継続時間（秒）を設定します。
		/// @param maxLifeTimeSec このエフェクトグループでのエフェクトの最大継続時間（秒）
		void setMaxLifeTime(const Duration& maxLifeTimeSec);

		/// @brief このエフェクトグループでのエフェクトの最大継続時間（秒）を返します。
		/// @return このエフェクトグループでのエフェクトの最大継続時間（秒）
		[[nodiscard]]
		double getMaxLifeTime() const;

		/// @brief このエフェクトグループ内のエフェクトの `update()` を実行します。
		void update() const;

		/// @brief このエフェクトグループ内の全てのエフェクトを、経過時間に関わらず消去します。
		void clear() const;

		void swap(Effect& other) noexcept;
	};
}

template <>
inline void std::swap(s3d::Effect& a, s3d::Effect& b) noexcept;

# include "detail/Effect.ipp"
