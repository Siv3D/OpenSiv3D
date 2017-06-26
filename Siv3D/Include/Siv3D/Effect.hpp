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

		class Handle {};

		using EffectHandle = AssetHandle<Handle>;

		friend EffectHandle::~AssetHandle();

		std::shared_ptr<EffectHandle> m_handle;

	public:

		using IDType = EffectHandle::IDType;

		static constexpr IDType NullHandleID = EffectHandle::NullID;

		Effect();

		~Effect();

		void release();

		/// <summary>
		/// エフェクトハンドルの ID を示します。
		/// </summary>
		IDType id() const;

		/// <summary>
		/// 2 つの Effect が同じかどうかを返します。
		/// </summary>
		/// <param name="effect">
		/// 比較する Effect
		/// </param>
		/// <returns>
		/// 2 つの Effect が同じ場合 true, それ以外の場合は false
		/// </returns>
		bool operator ==(const Effect& effect) const;

		/// <summary>
		/// 2 つの Effect が異なるかどうかを返します。
		/// </summary>
		/// <param name="effect">
		/// 比較する Effect
		/// </param>
		/// <returns>
		/// 2 つの Effect が異なる場合 true, それ以外の場合は false
		/// </returns>
		bool operator !=(const Effect& effect) const;

		explicit operator bool() const
		{
			return hasEffects();
		}

		/// <summary>
		/// エフェクトが空かどうかを示します。
		/// </summary>
		bool isEmpty() const
		{
			return !hasEffects();
		}

		bool hasEffects() const
		{
			return num_effects() > 0;
		}

		size_t num_effects() const;

		void add(std::unique_ptr<IEffect>&& effect) const;

		template <class EffectElement, class... Args>
		void add(Args&&... args) const
		{
			add(std::make_unique<EffectElement>(std::forward<Args>(args)...));
		}

		void add(std::function<bool(double)> f) const
		{
			struct AnonymousEffect : IEffect
			{
				std::function<bool(double)> function;

				explicit AnonymousEffect(std::function<bool(double)> _function)
					: function(_function) {}

				bool update(double timeSec) override
				{
					return function(timeSec);
				}
			};

			add(std::make_unique<AnonymousEffect>(f));
		}

		void pause() const;

		bool isPaused() const;

		void resume() const;

		void setSpeed(double speed) const;

		double getSpeed() const;

		void update() const;

		void clear() const;
	};
}
