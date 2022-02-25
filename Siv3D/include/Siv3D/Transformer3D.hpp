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
# include "Uncopyable.hpp"
# include "Optional.hpp"
# include "Mat4x4.hpp"
# include "Graphics3D.hpp"
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4324)

namespace s3d
{
	class Transformer3D : Uncopyable
	{
	public:

		enum class Target : uint8
		{
			PushLocal,

			SetLocal,
		};

		SIV3D_NODISCARD_CXX20
		Transformer3D() = default;

		SIV3D_NODISCARD_CXX20
		explicit Transformer3D(const Mat4x4& transform, Target target = Target::PushLocal);

		SIV3D_NODISCARD_CXX20
		Transformer3D(Transformer3D&& other) noexcept;

		~Transformer3D();

		//Transformer3D& operator =(Transformer2D&& other);

	private:

		Optional<Mat4x4> m_oldTransform;

		Target m_target = Target::PushLocal;

		void clear() noexcept;

		bool isPush() const noexcept;
	};
}

SIV3D_DISABLE_MSVC_WARNINGS_POP()

# include "detail/Transformer3D.ipp"
