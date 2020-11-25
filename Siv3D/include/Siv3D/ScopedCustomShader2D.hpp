//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Uncopyable.hpp"
# include "Graphics2D.hpp"

namespace s3d
{
	class ScopedCustomShader2D : Uncopyable
	{
	public:

		ScopedCustomShader2D() = default;

		explicit ScopedCustomShader2D(const VertexShader& vs);

		explicit ScopedCustomShader2D(const PixelShader& ps);

		ScopedCustomShader2D(const VertexShader& vs, const PixelShader& ps);

		ScopedCustomShader2D(const PixelShader& ps, const VertexShader& vs);

		ScopedCustomShader2D(ScopedCustomShader2D&& other) noexcept;

		~ScopedCustomShader2D();

		//ScopedCustomShader2D& operator =(ScopedCustomShader2D&& other) noexcept;

	private:

		Optional<Optional<VertexShader>> m_oldVS;

		Optional<Optional<PixelShader>> m_oldPS;

		void clear() noexcept;
	};
}

# include "detail/ScopedCustomShader2D.ipp"
