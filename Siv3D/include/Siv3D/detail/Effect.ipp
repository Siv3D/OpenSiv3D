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

namespace s3d
{
	template <class IEffectType, class... Args, std::enable_if_t<std::is_base_of_v<IEffect, IEffectType>>*>
	inline const Effect& Effect::add(Args&&... args) const
	{
		return add(std::make_unique<IEffectType>(std::forward<Args>(args)...));
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, double>>*>
	inline const Effect& Effect::add(Fty f) const
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

		return add(std::make_unique<AnonymousEffect>(f));
	}
}

template <>
inline void std::swap(s3d::Effect& a, s3d::Effect& b) noexcept
{
	a.swap(b);
}
