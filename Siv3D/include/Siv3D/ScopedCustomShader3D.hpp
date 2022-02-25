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
# include "VertexShader.hpp"
# include "PixelShader.hpp"

namespace s3d
{
	class ScopedCustomShader3D : Uncopyable
	{
	public:

		SIV3D_NODISCARD_CXX20
		ScopedCustomShader3D();

		SIV3D_NODISCARD_CXX20
		explicit ScopedCustomShader3D(const VertexShader& vs);

		SIV3D_NODISCARD_CXX20
		explicit ScopedCustomShader3D(const PixelShader& ps);

		SIV3D_NODISCARD_CXX20
		ScopedCustomShader3D(const VertexShader& vs, const PixelShader& ps);

		SIV3D_NODISCARD_CXX20
		ScopedCustomShader3D(const PixelShader& ps, const VertexShader& vs);

		SIV3D_NODISCARD_CXX20
		ScopedCustomShader3D(ScopedCustomShader3D&& other) noexcept;

		~ScopedCustomShader3D();

		//ScopedCustomShader3D& operator =(ScopedCustomShader3D&& other) noexcept;

	private:

		Optional<Optional<VertexShader>> m_oldVS;

		Optional<Optional<PixelShader>> m_oldPS;

		void clear() noexcept;
	};
}
