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
# include "../Common.hpp"
# include "../LineString.hpp"
# include "P2Fwd.hpp"
# include "P2Shape.hpp"

namespace s3d
{
	class P2LineString : public P2Shape
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2LineString(b2Body& body, const LineString& lines, CloseRing closeRing, OneSided oneSided, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2ShapeType getShapeType() const noexcept override;

		[[nodiscard]]
		bool isClosed() const noexcept;

		[[nodiscard]]
		bool isOneSided() const noexcept;

		const P2Shape& draw(const ColorF& color = Palette::White) const override;

		const P2Shape& drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		const P2Shape& drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]]
		const LineString& getLineString() const;

	private:

		std::unique_ptr<b2ChainShape> m_pShape;

		mutable LineString m_lineString;

		bool m_closeRing = false;

		bool m_oneSided = true;
	};
}
