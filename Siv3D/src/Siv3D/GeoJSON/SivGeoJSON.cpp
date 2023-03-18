//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------
// Original author: torin (yurkth)
//-----------------------------------------------

# include <Siv3D/GeoJSON.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr StringView GeoJSONTypeNameTable[] = {
			U"Point",
			U"MultiPoint",
			U"LineString",
			U"MultiLineString",
			U"Polygon",
			U"MultiPolygon",
			U"GeometryCollection",
			U"Feature",
			U"FeatureCollection"
		};

		[[nodiscard]]
		static GeoJSONType GetGeoJSONType(const JSON& object)
		{
			if (object.isEmpty())
			{
				throw Error{ U"detail::GetGeoJSONType(): JSON object is empty" };
			}

			const String typeString = object.getString();

			if (typeString == U"Point")
			{
				return GeoJSONType::Point;
			}
			else if (typeString == U"MultiPoint")
			{
				return GeoJSONType::MultiPoint;
			}
			else if (typeString == U"LineString")
			{
				return GeoJSONType::LineString;
			}
			else if (typeString == U"MultiLineString")
			{
				return GeoJSONType::MultiLineString;
			}
			else if (typeString == U"Polygon")
			{
				return GeoJSONType::Polygon;
			}
			else if (typeString == U"MultiPolygon")
			{
				return GeoJSONType::MultiPolygon;
			}
			else if (typeString == U"GeometryCollection")
			{
				return GeoJSONType::GeometryCollection;
			}
			else if (typeString == U"Feature")
			{
				return GeoJSONType::Feature;
			}
			else if (typeString == U"FeatureCollection")
			{
				return GeoJSONType::FeatureCollection;
			}
			else
			{
				throw Error{ U"detail::GetGeoJSONType(): \"type\" value is wrong" };
			}
		}

		template <class Type, class Fty>
		[[nodiscard]]
		inline Array<Type> GetArray(const JSON& arr, Fty convert, const CloseRing closeRing = CloseRing::Yes)
		{
			assert(arr.isArray());
			assert(1 <= arr.size());

			const size_t num_elements = (arr.size() - (closeRing ? 0 : 1));
			Array<Type> result(Arg::reserve = num_elements);

			for (size_t i = 0; i < num_elements; ++i)
			{
				result << convert(arr[i]);
			}

			return result;
		}

		template <bool FlipY>
		[[nodiscard]]
		inline Vec2 GetVec2(const JSON& arr)
		{
			assert(arr.isArray());
			assert(2 <= arr.size());

			if constexpr (FlipY)
			{
				return{ arr[0].get<double>(), -arr[1].get<double>() };
			}
			else
			{
				return{ arr[0].get<double>(), arr[1].get<double>() };
			}
		}

		template <bool FlipY>
		[[nodiscard]]
		inline Polygon GetPolygon(const JSON& arr)
		{
			Array<Vec2> outer = GetArray<Vec2>(arr[0], GetVec2<FlipY>, CloseRing::No);
			{
				if (not Geometry2D::IsClockwise(outer))
				{
					outer.reverse();
				}
			}

			Array<Array<Vec2>> inners(Arg::reserve = (arr.size() - 1));
			{
				for (size_t i = 1; i < arr.size(); i++)
				{
					Array<Vec2> inner = GetArray<Vec2>(arr[i], GetVec2<FlipY>, CloseRing::No);
					{
						if (Geometry2D::IsClockwise(inner))
						{
							inner.reverse();
						}
					}

					inners << std::move(inner);
				}
			}

			Polygon polygon{ outer, inners };

			if (not polygon)
			{
				polygon = Polygon::CorrectOne(outer, inners);

				if (not polygon)
				{
					throw Error{ U"detail::GetPolygon(): Incorrect Polygon" };
				}
			}

			return polygon;
		}

		template <bool FlipY>
		inline GeoJSONGeometry::GeometryVariant MakeCache(const GeoJSONType type, const JSON& coordinates)
		{
			switch (type)
			{
			case GeoJSONType::Point:
				return detail::GetVec2<FlipY>(coordinates);
			case GeoJSONType::MultiPoint:
				return detail::GetArray<Vec2>(coordinates, detail::GetVec2<FlipY>);
			case GeoJSONType::LineString:
				return LineString{ detail::GetArray<Vec2>(coordinates, detail::GetVec2<FlipY>) };
			case GeoJSONType::MultiLineString:
				return detail::GetArray<LineString>(
					coordinates,
					[](const JSON& element) { return LineString{ detail::GetArray<Vec2>(element, detail::GetVec2<FlipY>) }; });
			case GeoJSONType::Polygon:
				return detail::GetPolygon<FlipY>(coordinates);
			case GeoJSONType::MultiPolygon:
				return detail::GetArray<Polygon>(coordinates, detail::GetPolygon<FlipY>);
			case GeoJSONType::GeometryCollection:
				return detail::GetArray<GeoJSONGeometry>(
					coordinates,
					[](const JSON& element) { return GeoJSONGeometry{ element, s3d::FlipY{ FlipY } }; });
			default:
				throw Error{ U"GeoJSONGeometry MakeCache(): Invalid GeoJSONType" };
			}
		}
	}

	void Formatter(FormatData& formatData, const GeoJSONType& type)
	{
		formatData.string.append(detail::GeoJSONTypeNameTable[FromEnum(type)]);
	}

	//////////////////////////////////////////////////
	//
	//	GeoJSONBase
	//
	//////////////////////////////////////////////////

	GeoJSONBase::GeoJSONBase(const JSON& object)
	{
		if (not object)
		{
			throw Error{ U"GeoJSONBase::GeoJSONBase(): Failed to load file" };
		}
		
		if (object.hasElement(U"type"))
		{
			m_type = detail::GetGeoJSONType(object[U"type"]);
		}

		if (object.hasElement(U"bbox"))
		{
			m_bbox = detail::GetArray<double>(object[U"bbox"], [](const JSON& element) { return element.get<double>(); }, CloseRing::No);
		}
	}

	const Array<double>& GeoJSONBase::getBBox() const noexcept
	{
		return m_bbox;
	}

	GeoJSONType GeoJSONBase::getType() const noexcept
	{
		return m_type;
	}

	//////////////////////////////////////////////////
	//
	//	GeoJSONGeometry
	//
	//////////////////////////////////////////////////

	GeoJSONGeometry::GeoJSONGeometry(const JSON& object, const FlipY flipY)
		: GeoJSONBase({ object })
		, m_flipY{ flipY }
	{
		if (not InRange(m_type, GeoJSONType::Point, GeoJSONType::GeometryCollection))
		{
			throw Error{ U"GeoJSONGeometry::GeoJSONGeometry(): Invalid GeoJSONType" };
		}

		if (not object.hasElement(U"coordinates"))
		{
			throw Error{ U"GeoJSONGeometry::GeoJSONGeometry(): Geometry does not have coordinates" };
		}

		m_coordinates = object[U"coordinates"];
	}

	MultiPolygon GeoJSONGeometry::getPolygons() const
	{
		const auto& cache = getCache();

		if (std::holds_alternative<Array<Polygon>>(cache))
		{
			return MultiPolygon(std::get<Array<Polygon>>(cache));
		}
		else if (std::holds_alternative<Polygon>(cache))
		{
			return MultiPolygon({ std::get<Polygon>(cache) });
		}
		else
		{
			return{};
		}
	}

	const GeoJSONGeometry::GeometryVariant& GeoJSONGeometry::getCache() const
	{
		if (std::holds_alternative<MonoState>(m_cache))
		{
			if (m_flipY)
			{
				m_cache = detail::MakeCache<true>(m_type, m_coordinates);
			}
			else
			{
				m_cache = detail::MakeCache<false>(m_type, m_coordinates);
			}
		}

		return m_cache;
	}

	void Formatter(FormatData& formatData, const GeoJSONGeometry& geometry)
	{
		Formatter(formatData, geometry.getType());

		geometry.visit([&formatData](const auto& g) { Formatter(formatData, g); });
	}

	//////////////////////////////////////////////////
	//
	//	GeoJSONFeature
	//
	//////////////////////////////////////////////////

	GeoJSONFeature::GeoJSONFeature(const JSON& object, const FlipY flipY)
		: GeoJSONBase({ object })
	{
		if (m_type != GeoJSONType::Feature)
		{
			throw Error{ U"GeoJSONFeature::GeoJSONFeature(): \"type\" must be \"Feature\"" };
		}

		if (not object.hasElement(U"geometry"))
		{
			throw Error{ U"GeoJSONFeature::GeoJSONFeature(): \"Feature\" does not have \"geometry\"" };
		}

		m_geometry = GeoJSONGeometry{ object[U"geometry"], flipY };

		if (object.hasElement(U"properties")) // 本来必須だが、properties を持たない GeoJSON ファイルもある
		{
			m_properties = object[U"properties"];
		}

		if (object.hasElement(U"id"))
		{
			switch (object[U"id"].getType())
			{
			case JSONValueType::String:
				m_id = object[U"id"].getString();
				break;
			case JSONValueType::Number:
				m_id = object[U"id"].get<double>();
				break;
			default:
				throw Error{ U"GeoJSONFeature::GeoJSONFeature(): \"id\" must be either String type or Number type" };
			}
		}
	}

	const GeoJSONGeometry& GeoJSONFeature::getGeometry() const noexcept
	{
		return m_geometry;
	}

	const JSON& GeoJSONFeature::getProperties() const noexcept
	{
		return m_properties;
	}

	const std::variant<std::monostate, String, double>& GeoJSONFeature::getID() const noexcept
	{
		return m_id;
	}

	void Formatter(FormatData& formatData, const GeoJSONFeature& feature)
	{
		Formatter(formatData, feature.getType());

		formatData.string.append(U": ");

		Formatter(formatData, feature.getGeometry());
	}

	//////////////////////////////////////////////////
	//
	//	GeoJSONFeatureCollection
	//
	//////////////////////////////////////////////////

	GeoJSONFeatureCollection::GeoJSONFeatureCollection(const JSON& object, const FlipY flipY)
		: GeoJSONBase({ object })
	{
		if (m_type != GeoJSONType::FeatureCollection)
		{
			throw Error{ U"GeoJSONFeatureCollection::GeoJSONFeatureCollection(): \"type\" must be \"FeatureCollection\"" };
		}

		if (not object.hasElement(U"features"))
		{
			throw Error{ U"GeoJSONFeatureCollection::GeoJSONFeatureCollection(): \"FeatureCollection\" does not have \"features\"" };
		}

		m_features = detail::GetArray<GeoJSONFeature>(object[U"features"], [flipY](const JSON& element) { return GeoJSONFeature{ element, flipY }; });
	}

	const Array<GeoJSONFeature>& GeoJSONFeatureCollection::getFeatures() const noexcept
	{
		return m_features;
	}

	void Formatter(FormatData& formatData, const GeoJSONFeatureCollection& featureCollection)
	{
		Formatter(formatData, featureCollection.getType());

		formatData.string.append(U":");

		for (const auto& feature : featureCollection.getFeatures())
		{
			formatData.string.append(U"\n  ");

			Formatter(formatData, feature);
		}
	}
}
