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
// Original author: torin (yurkth)
//-----------------------------------------------

# pragma once
# include <variant>
# include "Common.hpp"
# include "FormatData.hpp"
# include "JSON.hpp"
# include "LineString.hpp"
# include "Polygon.hpp"
# include "MultiPolygon.hpp"

namespace s3d
{
	/// @brief GeoJSONで定義されているオブジェクトの型
	/// @details https://tools.ietf.org/html/rfc7946#section-1.4
	enum class GeoJSONType : uint8
	{
		Point,

		MultiPoint,

		LineString,

		MultiLineString,

		Polygon,

		MultiPolygon,

		GeometryCollection,

		Feature,

		FeatureCollection
	};

	void Formatter(FormatData& formatData, const GeoJSONType& type);

	/// @brief GeoJSON オブジェクトの基本クラス
	/// @details https://tools.ietf.org/html/rfc7946#section-3
	class GeoJSONBase
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		GeoJSONBase() = default;

		/// @brief GeoJSON オブジェクトを作成します。
		/// @param object JSON データ
		SIV3D_NODISCARD_CXX20
		GeoJSONBase(const JSON& object);

		/// @brief バウンディングボックスデータを返します。
		/// @return バウンディングボックスデータ
		[[nodiscard]]
		const Array<double>& getBBox() const noexcept;

		/// @brief GeoJSON type を返します。
		/// @return このオブジェクトの GeoJSON type
		[[nodiscard]]
		GeoJSONType getType() const noexcept;

	protected:

		/// @brief バウンディングボックス
		/// @details https://tools.ietf.org/html/rfc7946#section-5
		Array<double> m_bbox;

		/// @brief GeoJSON type
		GeoJSONType m_type = GeoJSONType::Feature;
	};

	/// @brief GeoJSON Geometry オブジェクト
	/// @details https://tools.ietf.org/html/rfc7946#section-3.1
	class GeoJSONGeometry : public GeoJSONBase
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		GeoJSONGeometry() = default;

		/// @brief Geometry オブジェクトを作成します。
		/// @param object JSON データ
		SIV3D_NODISCARD_CXX20
		GeoJSONGeometry(const JSON& object, FlipY flipY = FlipY::Yes);

		/// @brief 形状データを取得します。
		/// @tparam Type 形状データの型
		/// @return 形状データ
		template <class Type>
		[[nodiscard]]
		Type get() const;

		/// @brief 形状データをもとに MultiPolygon を作成して返します。
		/// @return 形状データをもとに作成した　MultiPolygon
		[[nodiscard]]
		MultiPolygon getPolygons() const;

		/// @brief 図形を引数にして関数を呼び出します。
		/// @tparam Visitor Visitor オブジェクトの型
		/// @param visitor Visitor オブジェクト
		template <class Visitor>
		void visit(Visitor&& visitor) const
		{
			return std::visit(std::forward<Visitor>(visitor), getCache());
		}

		friend void Formatter(FormatData& formatData, const GeoJSONGeometry& geometry);

		using MonoState = int32; // std::visit で Format できるように。

		using GeometryVariant = std::variant<
			MonoState,
			Vec2,
			Array<Vec2>,
			LineString,
			Array<LineString>,
			Polygon,
			Array<Polygon>,
			Array<GeoJSONGeometry>>;

	private:

		JSON m_coordinates;

		mutable GeometryVariant m_cache;

		bool m_flipY = false;

		const GeometryVariant& getCache() const;
	};

	/// @brief GeoJSON Feature オブジェクト
	/// @details https://tools.ietf.org/html/rfc7946#section-3.2
	class GeoJSONFeature : public GeoJSONBase
	{
	public:

		/// @brief GeoJSON Feature オブジェクトを作成します。
		/// @param object JSON データ
		SIV3D_NODISCARD_CXX20
		GeoJSONFeature(const JSON& object, FlipY flipY = FlipY::Yes);

		/// @brief GeoJSONGeometry データを返します。
		/// @return GeoJSONGeometry データ
		[[nodiscard]]
		const GeoJSONGeometry& getGeometry() const noexcept;

		/// @brief GeoJSON Feature の properties を返します。
		/// @return GeoJSON Feature の properties
		[[nodiscard]]
		const JSON& getProperties() const noexcept;

		/// @brief GeoJSON Feature の id を返します。
		/// @return GeoJSON Feature の id
		[[nodiscard]]
		const std::variant<std::monostate, String, double>& getID() const noexcept;

		friend void Formatter(FormatData& formatData, const GeoJSONFeature& feature);

	private:

		/// @brief Geometry オブジェクト
		GeoJSONGeometry m_geometry;

		/// @brief プロパティオブジェクト
		JSON m_properties;

		/// @brief 識別子
		std::variant<std::monostate, String, double> m_id;
	};

	/// @brief GeoJSON FeatureCollection オブジェクト
	/// @details https://tools.ietf.org/html/rfc7946#section-3.3
	class GeoJSONFeatureCollection : public GeoJSONBase
	{
	public:

		/// @brief FeatureCollection オブジェクトを作成します。
		/// @param object JSON データ
		SIV3D_NODISCARD_CXX20
		GeoJSONFeatureCollection(const JSON& object, FlipY flipY = FlipY::Yes);

		/// @brief GeoJSON Feature の一覧を返します。
		/// @return GeoJSON Feature の一覧
		[[nodiscard]]
		const Array<GeoJSONFeature>& getFeatures() const noexcept;

		friend void Formatter(FormatData& formatData, const GeoJSONFeatureCollection& featureCollection);

	private:

		/// @brief Featureの配列
		Array<GeoJSONFeature> m_features;
	};
}
