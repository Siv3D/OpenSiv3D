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
# include <memory>
# include "../Common.hpp"
# include "../PointVector.hpp"
# include "../HashTable.hpp"
# include "../Scene.hpp"
# include "P2Fwd.hpp"
# include "P2BodyType.hpp"
# include "P2Material.hpp"
# include "P2Filter.hpp"
# include "P2Body.hpp"
# include "P2PivotJoint.hpp"
# include "P2DistanceJoint.hpp"
# include "P2SliderJoint.hpp"
# include "P2WheelJoint.hpp"
# include "P2MouseJoint.hpp"

namespace s3d
{
	/// @brief 2D 物理演算を行うワールド
	class P2World
	{
	public:

		/// @brief 2D 物理演算を行うワールドを作成します。
		/// @param gravity 重力加速度 (cm/s^2)
		SIV3D_NODISCARD_CXX20
		explicit P2World(double gravity = 980);

		/// @brief 2D 物理演算を行うワールドを作成します。
		/// @param gravity 重力加速度のベクトル (cm/s^2)
		SIV3D_NODISCARD_CXX20
		explicit P2World(Vec2 gravity);

		/// @brief 2D 物理演算のワールドの状態を更新します。
		/// @param timeStep タイムステップ（秒）
		/// @param velocityIterations 物体の衝突時の速度の補正の回数
		/// @param positionIterations 物体の衝突時の位置の補正の回数
		void update(double timeStep = Scene::DeltaTime(), int32 velocityIterations = 6, int32 positionIterations = 2) const;

		/// @brief ワールド内の物体がスリープ状態になることを許可・不許可を設定します（デフォルトでは許可）。
		/// @param enabled 許可する場合 true, 許可しない場合 false
		void setSleepEnabled(bool enabled);

		/// @brief ワールド内の物体がスリープ状態になることを許可しているかの現在の設定を返します。
		/// @return スリープを許可している場合 true, 許可していない場合 false
		[[nodiscard]]
		bool getSleepEnabled() const;

		/// @brief 重力加速度 (cm/s^2) を設定します。
		/// @remark `setGravity(Vec2{ 0, gravity })` と同じです。
		/// @param gravity 重力加速度 (cm/s^2)
		void setGravity(double gravity);

		/// @brief 重力加速度 (cm/s^2) を設定します。
		/// @param gravity 重力加速度のベクトル (cm/s^2)
		void setGravity(const Vec2& gravity);

		/// @brief 現在の重力加速度の設定を返します。
		/// @return 現在の重力加速度の設定 (cm/s^2)
		[[nodiscard]]
		Vec2 getGravity() const;

		/// @brief ワールドの物体全ての座標 (cm) をシフトします。
		/// @param newOrigin シフト量 (cm) 
		void shiftOrigin(const Vec2& newOrigin);

		/// @brief プレースホルダーとなる物体を作成します。
		/// @remark プレースホルダーは、部品を持っていない状態の物体です。何もないところにジョイントを作ったり、あとから部品を追加する目的で使います。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createPlaceholder(P2BodyType bodyType, const Vec2& worldPos);

		/// @brief 線分を部品として持つ物体を作成します。
		/// @remark 物体は `P2Line` の部品を持ちます。
		/// @param bodyType 物体の種類（P2BodyType::Dynamic は指定不可）
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param localPos `worldPos` から見たローカルでの形状の座標 (cm) 
		/// @param oneSided 線分の片側（右に向かうときの上側）のみ干渉するか
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createLine(P2BodyType bodyType, const Vec2& worldPos, const Line& localPos, OneSided oneSided = OneSided::No, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 連続する複数の線分を部品として持つ物体を作成します。
		/// @remark 物体は `P2LineString` の部品を持ちます。
		/// @param bodyType 物体の種類（P2BodyType::Dynamic は指定不可）
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param localPos `worldPos` から見たローカルでの形状の座標 (cm) 
		/// @param oneSided 線分の片側（右に向かうときの上側）のみ干渉するか
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createLineString(P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, OneSided oneSided = OneSided::No, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 連続する複数の線分（終点と始点を結ぶ）を部品として持つ物体を作成します。
		/// @remark 物体は `P2LineString` の部品を持ちます。
		/// @param bodyType 物体の種類（P2BodyType::Dynamic は指定不可）
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param localPos `worldPos` から見たローカルでの形状の座標 (cm) 
		/// @param oneSided 線分の片側（右に向かうときの上側）のみ干渉するか
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createClosedLineString(P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, OneSided oneSided = OneSided::No, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 円を部品として持つ物体を作成します。
		/// @remark 物体は `P2Circle` の部品を持ちます。
		/// @remark 円の中心座標は `worldPos` です。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param r 円形の部品の半径 (cm) 
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createCircle(P2BodyType bodyType, const Vec2& worldPos, double r, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 円を部品として持つ物体を作成します。
		/// @remark 物体は `P2Circle` の部品を持ちます。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param localPos `worldPos` から見たローカルでの形状の座標 (cm) 
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createCircle(P2BodyType bodyType, const Vec2& worldPos, const Circle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 円形のセンサー部品を持つ物体を作成します。
		/// @remark 物体は `P2Circle` の部品を持ちます。
		/// @remark センサーは他の物体と干渉しませんが接触情報は発生します。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param r センサーの半径 (cm) 
		/// @param filter センサーの干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createCircleSensor(P2BodyType bodyType, const Vec2& worldPos, double r, const P2Filter& filter = {});

		/// @brief 正方形を部品として持つ物体を作成します。
		/// @remark 物体は `P2Rect` の部品を持ちます。
		/// @remark 正方形の中心座標は `worldPos` です。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param size 正方形の一辺の長さ (cm) 
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createRect(P2BodyType bodyType, const Vec2& worldPos, double size, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 長方形を部品として持つ物体を作成します。
		/// @remark 物体は `P2Rect` の部品を持ちます。
		/// @remark 長方形の中心座標は `worldPos` です。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param size 長方形の幅と高さ (cm) 
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createRect(P2BodyType bodyType, const Vec2& worldPos, const SizeF& size, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 長方形を部品として持つ物体を作成します。
		/// @remark 物体は `P2Rect` の部品を持ちます。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param localPos `worldPos` から見たローカルでの形状の座標 (cm) 
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createRect(P2BodyType bodyType, const Vec2& worldPos, const RectF& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 三角形を部品として持つ物体を作成します。
		/// @remark 物体は `P2Triangle` の部品を持ちます。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param localPos `worldPos` から見たローカルでの形状の座標 (cm) 
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createTriangle(P2BodyType bodyType, const Vec2& worldPos, const Triangle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 凸な四角形を部品として持つ物体を作成します。
		/// @remark 物体は `P2Quad` の部品を持ちます。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param localPos `worldPos` から見たローカルでの形状の座標 (cm) 
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createQuad(P2BodyType bodyType, const Vec2& worldPos, const Quad& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 多角形を部品として持つ物体を作成します。
		/// @remark 物体は `P2Polygon` の部品を持ちます。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param localPos `worldPos` から見たローカルでの形状の座標 (cm) 
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createPolygon(P2BodyType bodyType, const Vec2& worldPos, const Polygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 複数の多角形を部品として持つ物体を作成します。
		/// @remark 物体は複数の `P2Polygon` の部品を持ちます。
		/// @param bodyType 物体の種類
		/// @param worldPos 物体のワールド座標 (cm) 
		/// @param localPos `worldPos` から見たローカルでの形状の座標 (cm) 
		/// @param material 部品の材質
		/// @param filter 部品の干渉フィルタ
		/// @return 作成した物体
		[[nodiscard]]
		P2Body createPolygons(P2BodyType bodyType, const Vec2& worldPos, const MultiPolygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		/// @brief 回転ジョイントを作成します。
		/// @param bodyA 接続する物体
		/// @param bodyB 接続する物体
		/// @param worldAnchorPos ジョイントのワールド座標 (cm) 
		/// @param enableCollision 接続した物体どうしの衝突を有効にするか
		/// @return 作成したジョイント
		[[nodiscard]]
		P2PivotJoint createPivotJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, EnableCollision enableCollision = EnableCollision::No);

		/// @brief 距離ジョイントを作成します。
		/// @param bodyA 接続する物体 A
		/// @param worldAnchorPosA 物体 A のジョイントのワールド座標 (cm) 
		/// @param bodyB 接続する物体 B
		/// @param worldAnchorPosB 物体 B のジョイントのワールド座標 (cm) 
		/// @param length ジョイントの静止長 (cm)
		/// @param enableCollision 接続した物体どうしの衝突を有効にするか
		/// @return 作成したジョイント
		[[nodiscard]]
		P2DistanceJoint createDistanceJoint(const P2Body& bodyA, const Vec2& worldAnchorPosA, const P2Body& bodyB, const Vec2& worldAnchorPosB, double length, EnableCollision enableCollision = EnableCollision::No);

		/// @brief スライダージョイントを作成します。
		/// @param bodyA 接続する物体 A
		/// @param bodyB 接続する物体 B
		/// @param worldAnchorPos ジョイントのワールド座標 (cm) 
		/// @param normalizedAxis スライダーの方向の単位ベクトル
		/// @param enableCollision 接続した物体どうしの衝突を有効にするか
		/// @return 作成したジョイント
		[[nodiscard]]
		P2SliderJoint createSliderJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, EnableCollision enableCollision = EnableCollision::No);

		/// @brief ホイールジョイントを作成します。
		/// @param bodyA 接続する物体 A
		/// @param bodyB 接続する物体 B
		/// @param worldAnchorPos ジョイントのワールド座標 (cm) 
		/// @param normalizedAxis 軸の方向の単位ベクトル
		/// @param enableCollision 接続した物体どうしの衝突を有効にするか
		/// @return 作成したジョイント
		[[nodiscard]]
		P2WheelJoint createWheelJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, EnableCollision enableCollision = EnableCollision::No);

		/// @brief マウスジョイントを作成します。
		/// @param body 接続する物体
		/// @param worldTargetPos ターゲットのワールド座標 (cm) 
		/// @return 作成したジョイント
		[[nodiscard]]
		P2MouseJoint createMouseJoint(const P2Body& body, const Vec2& worldTargetPos);

		/// @brief 物体の接触情報の一覧を返します。
		/// @return 物体の接触情報の一覧
		[[nodiscard]]
		const HashTable<P2ContactPair, P2Collision>& getCollisions() const noexcept;

	private:

		std::shared_ptr<detail::P2WorldDetail> pImpl;
	};
}
