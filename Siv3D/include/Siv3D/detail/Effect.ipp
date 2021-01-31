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

namespace s3d
{
	template <class IEffectType, class... Args, std::enable_if_t<std::is_base_of_v<IEffect, IEffectType>>*>
	inline void Effect::add(Args&&... args) const
	{
		add(std::make_unique<IEffectType>(std::forward<Args>(args)...));
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, double>>*>
	inline void Effect::add(Fty f) const
	{
		struct AnonymousEffect : IEffect
		{
			Fty m_function;

			explicit AnonymousEffect(Fty _function)
				: m_function{ _function } {}

			bool update(double timeSec) override
			{
				return m_function(timeSec);
			}
		};

		add(std::make_unique<AnonymousEffect>(f));
	}
}
