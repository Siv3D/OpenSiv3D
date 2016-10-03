//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace Arg
	{
		template <class ValueType, class ArgType>
		struct NamedParameter
		{
			using base = NamedParameter;

			ValueType value;

			constexpr NamedParameter()
				: value() {}

			constexpr NamedParameter(ValueType _val)
				: value(_val) {}

			constexpr ArgType operator =(ValueType val) const
			{
				return ArgType{ val };
			}

			operator ValueType() const
			{
				return value;
			}
		};

		constexpr struct r_ : NamedParameter<double, r_>
		{
			using base::base;
			using base::operator=;
        } r{};

		constexpr struct theta_ : NamedParameter<double, theta_>
		{
			using base::base;
			using base::operator=;
        } theta{};
	}
}
