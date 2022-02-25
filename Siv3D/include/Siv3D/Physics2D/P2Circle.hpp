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
# include "../2DShapes.hpp"
# include "P2Fwd.hpp"
# include "P2Shape.hpp"

namespace s3d
{
	/// @brief 円形の部品です。
	class P2Circle : public P2Shape
	{
	public:

		/// @brief 円形の部品を作成します。（この関数は内部実装向けで、通常は使用しません）
		/// @param body 
		/// @param circle 
		/// @param material 
		/// @param filter 
		/// @param isSensor 
		SIV3D_NODISCARD_CXX20
		P2Circle(b2Body& body, const Circle& circle, const P2Material& material, const P2Filter& filter, bool isSensor);

		/// @brief `P2ShapeType::Circle` を返します。
		/// @return `P2ShapeType::Circle`
		[[nodiscard]]
		P2ShapeType getShapeType() const noexcept override;

		/// @brief 部品を描画します。
		/// @param color 色
		/// @return *this
		const P2Shape& draw(const ColorF& color = Palette::White) const override;

		const P2Shape& drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		const P2Shape& drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]]
		Circle getCircle() const;

	private:

		std::unique_ptr<b2CircleShape> m_pShape;
	};
}
