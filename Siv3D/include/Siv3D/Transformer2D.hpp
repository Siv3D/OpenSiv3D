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
# include "Uncopyable.hpp"
# include "Optional.hpp"
# include "Mat3x2.hpp"
# include "Graphics2D.hpp"
# include "Cursor.hpp"

namespace s3d
{
	class Transformer2D : Uncopyable
	{
	public:

		enum class Target
		{
			PushLocal,
			
			PushCamera,
			
			SetLocal,
			
			SetCamera,
		};

		SIV3D_NODISCARD_CXX20
		Transformer2D() = default;

		SIV3D_NODISCARD_CXX20
		Transformer2D(const Mat3x2& transform, Target target);

		SIV3D_NODISCARD_CXX20
		explicit Transformer2D(const Mat3x2& transform, bool transformCursor = false, Target target = Target::PushLocal);

		SIV3D_NODISCARD_CXX20
		Transformer2D(const Mat3x2& graphics2DTransform, const Mat3x2& cursorTransform, Target target = Target::PushLocal);

		SIV3D_NODISCARD_CXX20
		Transformer2D(Transformer2D&& other) noexcept;

		~Transformer2D();

		//Transformer2D& operator =(Transformer2D&& other);

	private:

		Target m_target = Target::PushLocal;

		Optional<Mat3x2> m_oldTransform;
		
		Optional<Mat3x2> m_oldCursorTransform;

		void clear() noexcept;

		bool isPush() const noexcept;

		bool isLocal() const noexcept;

		bool isCamera() const noexcept;

		const Mat3x2& getGraphics2DTransform() const noexcept;

		const Mat3x2& getCursorTransform() const noexcept;

		void setGraphics2DTransform(const Mat3x2& transform) const;

		void setCursorTransform(const Mat3x2& transform) const;
	};
}

# include "detail/Transformer2D.ipp"
