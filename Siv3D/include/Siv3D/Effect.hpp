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
# include "Common.hpp"
# include "IEffect.hpp"
# include "Duration.hpp"

namespace s3d
{
	class Effect : public AssetHandle<Effect>
	{
	public:

		Effect(double maxLifeTimeSec = 10.0);

		Effect(const Duration& maxLifeTimeSec);

		virtual ~Effect();

		void add(std::unique_ptr<IEffect>&& effect) const;

		template <class IEffectType, class... Args, std::enable_if_t<std::is_base_of_v<IEffect, IEffectType>>* = nullptr>
		void add(Args&&... args) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<double, Fty, double>>* = nullptr>
		void add(Fty f) const;

		[[nodiscard]]
		explicit operator bool() const;

		[[nodiscard]]
		bool isEmpty() const;

		[[nodiscard]]
		bool hasEffects() const;

		[[nodiscard]]
		size_t num_effects() const;

		void pause() const;

		[[nodiscard]]
		bool isPaused() const;

		void resume() const;

		void setSpeed(double speed) const;

		[[nodiscard]]
		double getSpeed() const;

		void setMaxLifeTime(double maxLifeTimeSec);

		void setMaxLifeTime(const Duration& maxLifeTimeSec);

		[[nodiscard]]
		double getMaxLifeTime() const;

		void update() const;

		void clear() const;
	};
}

# include "detail/Effect.ipp"
