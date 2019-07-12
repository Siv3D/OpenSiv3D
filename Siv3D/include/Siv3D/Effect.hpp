//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include <functional>
# include "Fwd.hpp"
# include "AssetHandle.hpp"
# include "Uncopyable.hpp"

namespace s3d
{
	struct IEffect : private Uncopyable
	{
		virtual ~IEffect() = default;

		virtual bool update(double timeSec) = 0;
	};

	class Effect
	{
	private:

		class Tag {};

		using EffectHandle = AssetHandle<Tag>;

		friend EffectHandle::AssetHandle();
		
		friend EffectHandle::AssetHandle(const IDWrapperType id) noexcept;
		
		friend EffectHandle::~AssetHandle();

		std::shared_ptr<EffectHandle> m_handle;

	public:

		using IDType = EffectHandle::IDWrapperType;

		Effect();

		~Effect();

		void release();

		/// <summary>
		/// エフェクトハンドルの ID を示します。
		/// </summary>
		[[nodiscard]] IDType id() const;

		/// <summary>
		/// 2 つの Effect が同じかどうかを返します。
		/// </summary>
		/// <param name="effect">
		/// 比較する Effect
		/// </param>
		/// <returns>
		/// 2 つの Effect が同じ場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool operator ==(const Effect& effect) const;

		/// <summary>
		/// 2 つの Effect が異なるかどうかを返します。
		/// </summary>
		/// <param name="effect">
		/// 比較する Effect
		/// </param>
		/// <returns>
		/// 2 つの Effect が異なる場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool operator !=(const Effect& effect) const;

		[[nodiscard]] explicit operator bool() const;

		/// <summary>
		/// エフェクトが空かどうかを示します。
		/// </summary>
		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] bool hasEffects() const;

		[[nodiscard]] size_t num_effects() const;

		void add(std::unique_ptr<IEffect>&& effect) const;

		template <class EffectElement, class... Args>
		void add(Args&&... args) const
		{
			add(std::make_unique<EffectElement>(std::forward<Args>(args)...));
		}

		void add(std::function<bool(double)> f) const;

		void pause() const;

		[[nodiscard]] bool isPaused() const;

		void resume() const;

		void setSpeed(double speed) const;

		[[nodiscard]] double getSpeed() const;

		void update() const;

		void clear() const;
	};

	using EffectID = Effect::IDType;
}
