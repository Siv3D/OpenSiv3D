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
# include <memory>
# include "../Common.hpp"
# include "../2DShapesFwd.hpp"
# include "../ColorHSV.hpp"
# include "../PredefinedYesNo.hpp"
# include "P2Fwd.hpp"
# include "P2Material.hpp"
# include "P2Filter.hpp"

namespace s3d
{
	/// @brief 2D 物理演算のワールドに存在する物体
	/// @remark 0 個以上（通常は 1 個以上）の部品 (`P2Shape`) から構成されます。
	class P2Body
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		P2Body();

		/// @brief 物体の ID を返します。
		/// @return 物体の ID
		[[nodiscard]]
		P2BodyID id() const noexcept;

		/// @brief 物体がワールドに存在しないかを返します
		/// @return 物体がワールドに存在しない場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief 物体がワールドに存在するかを返します。
		/// @return 物体がワールドに存在する場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 物体をワールドから明示的に削除します。
		/// @remark デストラクタで自動的に削除されるため、必須ではありません。
		void release();

		/// @brief 線分の部品を物体に追加します。
		/// @param localPos 
		/// @param oneSided 
		/// @param material 
		/// @param filter 
		/// @return 
		P2Body& addLine(const Line& localPos, OneSided oneSided, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 連続する複数の線分の部品を物体に追加します。
		/// @param localPos 
		/// @param oneSided 
		/// @param material 
		/// @param filter 
		/// @return 
		P2Body& addLineString(const LineString& localPos, OneSided oneSided, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 
		/// @param localPos 
		/// @param oneSided 
		/// @param material 
		/// @param filter 
		/// @return 
		P2Body& addClosedLineString(const LineString& localPos, OneSided oneSided, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 
		/// @param localPos 
		/// @param material 
		/// @param filter 
		/// @return 
		P2Body& addCircle(const Circle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 
		/// @param localPos 
		/// @param filter 
		/// @return 
		P2Body& addCircleSensor(const Circle& localPos, const P2Filter& filter = {});

		/// @brief 
		/// @param localPos 
		/// @param material 
		/// @param filter 
		/// @return 
		P2Body& addRect(const RectF& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 
		/// @param localPos 
		/// @param material 
		/// @param filter 
		/// @return 
		P2Body& addTriangle(const Triangle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 
		/// @param localPos 
		/// @param material 
		/// @param filter 
		/// @return 
		P2Body& addQuad(const Quad& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 
		/// @param localPos 
		/// @param material 
		/// @param filter 
		/// @return 
		P2Body& addPolygon(const Polygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 
		/// @param localPos 
		/// @param material 
		/// @param filter 
		/// @return 
		P2Body& addPolygons(const MultiPolygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 
		/// @param enabled 
		/// @return 
		P2Body& setSleepEnabled(bool enabled) noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		bool getSleepEnabled() const noexcept;

		/// @brief 
		/// @param awake 
		/// @return 
		P2Body& setAwake(bool awake) noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		bool isAwake() const noexcept;

		/// @brief 
		/// @param x 
		/// @param y 
		/// @return 
		P2Body& setPos(double x, double y) noexcept;

		/// @brief 
		/// @param pos 
		/// @return 
		P2Body& setPos(Vec2 pos) noexcept;

		/// @brief 
		/// @param x 
		/// @param y 
		/// @return 
		P2Body& moveBy(double x, double y) noexcept;

		/// @brief 
		/// @param v 
		/// @return 
		P2Body& moveBy(Vec2 v) noexcept;

		/// @brief 
		/// @param angle 
		/// @return 
		P2Body& setAngle(double angle) noexcept;

		/// @brief 
		/// @param angle 
		/// @return 
		P2Body& rotateBy(double angle) noexcept;

		/// @brief 
		/// @param x 
		/// @param y 
		/// @param angle 
		/// @return 
		P2Body& setTransform(double x, double y, double angle) noexcept;

		/// @brief 
		/// @param pos 
		/// @param angle 
		/// @return 
		P2Body& setTransform(Vec2 pos, double angle) noexcept;

		/// @brief 
		/// @param force 
		/// @return 
		P2Body& applyForce(Vec2 force) noexcept;

		/// @brief 
		/// @param force 
		/// @param offset 
		/// @return 
		P2Body& applyForce(Vec2 force, Vec2 offset) noexcept;

		/// @brief 
		/// @param force 
		/// @param pos 
		/// @return 
		P2Body& applyForceAt(Vec2 force, Vec2 pos) noexcept;

		/// @brief 
		/// @param force 
		/// @return 
		P2Body& applyLinearImpulse(Vec2 force) noexcept;

		/// @brief 
		/// @param force 
		/// @param offset 
		/// @return 
		P2Body& applyLinearImpulse(Vec2 force, Vec2 offset) noexcept;

		/// @brief 
		/// @param force 
		/// @param pos 
		/// @return 
		P2Body& applyLinearImpulseAt(Vec2 force, Vec2 pos) noexcept;

		/// @brief 
		/// @param torque 
		/// @return 
		P2Body& applyTorque(double torque) noexcept;

		/// @brief 
		/// @param torque 
		/// @return 
		P2Body& applyAngularImpulse(double torque) noexcept;

		/// @brief 物体のワールド座標 (cm) を返します。
		/// @return 物体のワールド座標 (cm) 
		[[nodiscard]]
		Vec2 getPos() const noexcept;

		/// @brief 物体の回転角度（ラジアン）を返します。
		/// @return 物体の回転角度（ラジアン）
		[[nodiscard]]
		double getAngle() const noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		std::pair<Vec2, double> getTransform() const noexcept;

		/// @brief 
		/// @param v 
		/// @return 
		P2Body& setVelocity(Vec2 v) noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		Vec2 getVelocity() const noexcept;

		/// @brief 
		/// @param omega 
		/// @return 
		P2Body& setAngularVelocity(double omega) noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		double getAngularVelocity() const noexcept;

		/// @brief 
		/// @param damping 
		/// @return 
		P2Body& setDamping(double damping) noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		double getDamping() const noexcept;

		/// @brief 
		/// @param damping 
		/// @return 
		P2Body& setAngularDamping(double damping) noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		double getAngularDamping() const noexcept;

		/// @brief 
		/// @param scale 
		/// @return 
		P2Body& setGravityScale(double scale) noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		double getGravityScale() const noexcept;

		/// @brief 物体の重量 (kg) を返します。
		/// @return 物体の重量 (kg)
		[[nodiscard]]
		double getMass() const noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		double getInertia() const noexcept;

		/// @brief 
		/// @param bodyType 
		/// @return 
		P2Body& setBodyType(P2BodyType bodyType) noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		P2BodyType getBodyType() const noexcept;

		/// @brief 
		/// @param fixedRotation 
		/// @return 
		P2Body& setFixedRotation(bool fixedRotation) noexcept;

		/// @brief 
		/// @return 
		[[nodiscard]]
		bool isFixedRotation() const noexcept;

		/// @brief 
		/// @param color 
		/// @return 
		const P2Body& draw(const ColorF& color = Palette::White) const;

		/// @brief 
		/// @param thickness 
		/// @param color 
		/// @return 
		const P2Body& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		/// @brief 
		/// @param thickness 
		/// @param color 
		/// @return 
		const P2Body& drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		/// @brief 
		/// @return 
		[[nodiscard]]
		size_t num_shapes() const noexcept;

		/// @brief 
		/// @param index 
		/// @return 
		[[nodiscard]]
		P2Shape& shape(size_t index);

		/// @brief 
		/// @param index 
		/// @return 
		[[nodiscard]]
		const P2Shape& shape(size_t index) const;

		/// @brief 
		/// @param index 
		/// @return 
		[[nodiscard]]
		const std::shared_ptr<P2Shape>& getPtr(size_t index) const noexcept;

		/// @brief 
		/// @tparam PShape 
		/// @param index 
		/// @return 
		template <class PShape, std::enable_if_t<std::is_base_of_v<P2Shape, PShape>>* = nullptr>
		std::shared_ptr<PShape> as(size_t index) const;

	private:

		class P2BodyDetail;

		std::shared_ptr<P2BodyDetail> pImpl;

		friend class detail::P2WorldDetail;
		friend class detail::P2ContactListener;
		friend class detail::P2PivotJointDetail;
		friend class detail::P2DistanceJointDetail;
		friend class detail::P2SliderJointDetail;
		friend class detail::P2WheelJointDetail;
		friend class detail::P2MouseJointDetail;

		SIV3D_NODISCARD_CXX20
		P2Body(const std::shared_ptr<detail::P2WorldDetail>& world, P2BodyID id, const Vec2& center, P2BodyType bodyType);

		[[nodiscard]]
		std::weak_ptr<P2BodyDetail> getWeakPtr() const;
	};
}

# include "detail/P2Body.ipp"
