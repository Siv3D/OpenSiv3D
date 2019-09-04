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
# include "Fwd.hpp"
# include "Graphics2D.hpp"
# include "Uncopyable.hpp"

namespace s3d
{
	class ScopedCustomShader2D : Uncopyable
	{
	private:

		Optional<Optional<PixelShader>> m_oldPS;

		void clear() noexcept;

	public:

		ScopedCustomShader2D() = default;

		explicit ScopedCustomShader2D(const Optional<PixelShader>& ps);

		ScopedCustomShader2D(ScopedCustomShader2D&& other) noexcept;

		~ScopedCustomShader2D();

		ScopedCustomShader2D& operator =(ScopedCustomShader2D&& other) noexcept;
	};
}
