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

namespace s3d
{
	template <class Writer>
	template <class ...Args>
	inline Serializer<Writer>::Serializer(Args&& ... args)
		: cereal::OutputArchive<Serializer<Writer>, cereal::AllowEmptyClassElision>{ this }
		, m_writer{ std::make_shared<Writer>(std::forward<Args>(args)...) } {}

	template <class Writer>
	inline void Serializer<Writer>::saveBinary(const void* data, const size_t size)
	{
		const size_t writeSize = static_cast<size_t>(m_writer->write(data, size));

		if (writeSize != size)
		{
			throw cereal::Exception{ "Failed to write " + std::to_string(size) + " bytes to output stream! Wrote " + std::to_string(writeSize) };
		}
	}

	template <class Writer>
	inline Serializer<Writer>::operator bool() const noexcept
	{
		return (m_writer && m_writer->isOpen());
	}

	template <class Writer>
	inline std::shared_ptr<Writer> Serializer<Writer>::operator ->()
	{
		return std::dynamic_pointer_cast<Writer>(m_writer);
	}

	template <class Writer>
	inline std::shared_ptr<const Writer> Serializer<Writer>::operator ->() const
	{
		return std::dynamic_pointer_cast<const Writer>(m_writer);
	}

	template <class Reader>
	template <class ...Args>
	inline Deserializer<Reader>::Deserializer(Args&& ... args)
		: cereal::InputArchive<Deserializer<Reader>, cereal::AllowEmptyClassElision>(this)
		, m_reader(std::make_shared<Reader>(std::forward<Args>(args)...)) {}

	template <class Reader>
	inline void Deserializer<Reader>::loadBinary(void* const data, const size_t size)
	{
		const size_t readSize = static_cast<size_t>(m_reader->read(data, size));

		if (readSize != size)
		{
			throw cereal::Exception{ "Failed to read " + std::to_string(size) + " bytes from input stream! Read " + std::to_string(readSize) };
		}
	}

	template <class Reader>
	inline Deserializer<Reader>::operator bool() const noexcept
	{
		return (m_reader && m_reader->isOpen());
	}

	template <class Reader>
	inline std::shared_ptr<Reader> Deserializer<Reader>::operator ->()
	{
		return std::dynamic_pointer_cast<Reader>(m_reader);
	}

	template <class Reader>
	inline std::shared_ptr<const Reader> Deserializer<Reader>::operator ->() const
	{
		return std::dynamic_pointer_cast<const Reader>(m_reader);
	}

	//////////////////////////////////////////////////////
	//
	//	arithmetic types
	//
	template <class Type, class Writer, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_SAVE(Serializer<Writer>& archive, const Type& value)
	{
		archive.saveBinary(std::addressof(value), sizeof(value));
	}

	template <class Type, class Reader, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_LOAD(Deserializer<Reader>& archive, Type& value)
	{
		archive.loadBinary(std::addressof(value), sizeof(value));
	}

	//////////////////////////////////////////////////////
	//
	//	cereal::NameValuePair
	//
	template <class Archive, class Type>
	inline void SIV3D_SERIALIZE(Archive& archive, cereal::NameValuePair<Type>& value)
	{
		archive(value.value);
	}

	//////////////////////////////////////////////////////
	//
	//	cereal::SizeTag
	//
	template <class Archive, class Type>
	inline void SIV3D_SERIALIZE(Archive& archive, cereal::SizeTag<Type>& value)
	{
		archive(value.size);
	}

	//////////////////////////////////////////////////////
	//
	//	cereal::BinaryData
	//
	template <class Type, class Writer>
	inline void SIV3D_SERIALIZE_SAVE(Serializer<Writer>& archive, const cereal::BinaryData<Type>& value)
	{
		archive.saveBinary(value.data, static_cast<size_t>(value.size));
	}

	template <class Type, class Reader>
	inline void SIV3D_SERIALIZE_LOAD(Deserializer<Reader>& archive, cereal::BinaryData<Type>& value)
	{
		archive.loadBinary(value.data, static_cast<size_t>(value.size));
	}

	//////////////////////////////////////////////////////
	//
	//	Byte
	//
	template <class Archive>
	inline uint8 SIV3D_SERIALIZE_LOAD_M(const Archive&, const Byte& value)
	{
		return static_cast<uint8>(value);
	}

	template <class Archive>
	inline void SIV3D_SERIALIZE_SAVE_M(const Archive&, Byte& value, const uint8& data)
	{
		value = Byte{ data };
	}

	//////////////////////////////////////////////////////
	//
	//	Array
	//
	template <class Archive, class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Array<Type>& value)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.size())));
		archive(cereal::binary_data(value.data(), value.size_bytes()));
	}

	template <class Archive, class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Array<Type>& value)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));
		value.resize(static_cast<size_t>(size));
		archive(cereal::binary_data(value.data(), value.size_bytes()));
	}

	template <class Archive, class Type, std::enable_if_t<!std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Array<Type>& value)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.size())));

		for (auto&& v : value)
		{
			archive(v);
		}
	}

	template <class Archive, class Type, std::enable_if_t<!std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Array<Type>& value)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));
		value.resize(static_cast<size_t>(size));

		for (auto&& v : value)
		{
			archive(v);
		}
	}

	//////////////////////////////////////////////////////
	//
	//	Grid
	//
	template <class Archive, class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Grid<Type>& value)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.width())));
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.height())));
		archive(cereal::binary_data(value.data(), value.size_bytes()));
	}

	template <class Archive, class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Grid<Type>& value)
	{
		cereal::size_type width, height;
		archive(cereal::make_size_tag(width));
		archive(cereal::make_size_tag(height));
		value.resize(static_cast<size_t>(width), static_cast<size_t>(height));
		archive(cereal::binary_data(value.data(), value.size_bytes()));
	}

	template <class Archive, class Type, std::enable_if_t<!std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Grid<Type>& value)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.width())));
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.height())));

		for (auto&& v : value)
		{
			archive(v);
		}
	}

	template <class Archive, class Type, std::enable_if_t<!std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Grid<Type>& value)
	{
		cereal::size_type width, height;
		archive(cereal::make_size_tag(width));
		archive(cereal::make_size_tag(height));
		value.resize(static_cast<size_t>(width), static_cast<size_t>(height));

		for (auto&& v : value)
		{
			archive(v);
		}
	}

	//////////////////////////////////////////////////////
	//
	//	HashTable
	//
	template <class Archive, class Key, class Value>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const HashTable<Key, Value>& table)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(table.size())));

		for (const auto& p : table)
		{
			archive(cereal::make_map_item(p.first, p.second));
		}
	}

	template <class Archive, class Key, class Value>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, HashTable<Key, Value>& table)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));

		table.clear();
		auto hint = table.begin();

		for (size_t i = 0; i < size; ++i)
		{
			Key key;
			Value value;
			archive(cereal::make_map_item(key, value));
			hint = table.emplace_hint(hint, std::move(key), std::move(value));
		}
	}

	//////////////////////////////////////////////////////
	//
	//	HashSet
	//
	template <class Archive, class Key>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const HashSet<Key>& set)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(set.size())));

		for (const auto& key : set)
		{
			archive(key);
		}
	}

	template <class Archive, class Key>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, HashSet<Key>& set)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));

		set.clear();
		set.reserve(static_cast<std::size_t>(size));

		for (size_t i = 0; i < size; ++i)
		{
			Key key;
			archive(key);
			set.emplace(std::move(key));
		}
	}

	//////////////////////////////////////////////////////
	//
	//	Optional
	//
	template <class Archive, class Type>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Optional<Type>& value)
	{
		if (value)
		{
			archive(true);
			archive(*value);
		}
		else
		{
			archive(false);
		}
	}

	template <class Archive, class Type>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Optional<Type>& value)
	{
		bool hasValue = false;
		archive(hasValue);

		if (hasValue)
		{
			if (value)
			{
				archive(*value);
			}
			else
			{
				Type t;
				archive(t);
				value = std::move(t);
			}
		}
		else
		{
			value.reset();
		}
	}

	//////////////////////////////////////////////////////
	//
	//	String
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const String& value)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.length())));
		archive(cereal::binary_data(value.data(), value.size_bytes()));
	}

	template <class Archive>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, String& value)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));
		value.resize(static_cast<size_t>(size));
		archive(cereal::binary_data(value.data(), value.size_bytes()));
	}

	//////////////////////////////////////////////////////
	//
	//	Date
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Date& value)
	{
		archive(value.year, value.month, value.day);
	}

	//////////////////////////////////////////////////////
	//
	//	DateTime
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, DateTime& value)
	{
		archive(value.year, value.month, value.day, value.hour, value.minute, value.second, value.milliseconds);
	}

	//////////////////////////////////////////////////////
	//
	//	MD5Value
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, MD5Value& value)
	{
		archive(value.value);
	}

	//////////////////////////////////////////////////////
	//
	//	Color
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Color& value)
	{
		archive(value.r, value.g, value.b, value.a);
	}

	//////////////////////////////////////////////////////
	//
	//	ColorF
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, ColorF& value)
	{
		archive(value.r, value.g, value.b, value.a);
	}

	//////////////////////////////////////////////////////
	//
	//	HSV
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, HSV& value)
	{
		archive(value.h, value.s, value.v, value.a);
	}

	//////////////////////////////////////////////////////
	//
	//	Point
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Point& value)
	{
		archive(value.x, value.y);
	}

	//////////////////////////////////////////////////////
	//
	//	Float2
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Float2& value)
	{
		archive(value.x, value.y);
	}

	//////////////////////////////////////////////////////
	//
	//	Vec2
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Vec2& value)
	{
		archive(value.x, value.y);
	}

	//////////////////////////////////////////////////////
	//
	//	Float3
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Float3& value)
	{
		archive(value.x, value.y, value.z);
	}

	//////////////////////////////////////////////////////
	//
	//	Vec3
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Vec3& value)
	{
		archive(value.x, value.y, value.z);
	}

	//////////////////////////////////////////////////////
	//
	//	Float4
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Float4& value)
	{
		archive(value.x, value.y, value.z, value.w);
	}

	//////////////////////////////////////////////////////
	//
	//	Vec4
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Vec4& value)
	{
		archive(value.x, value.y, value.z, value.w);
	}

	//////////////////////////////////////////////////////
	//
	//	CircularBase
	//
	template <class Archive, class Float, int32 Oclock>
	inline void SIV3D_SERIALIZE(Archive& archive, CircularBase<Float, Oclock>& value)
	{
		archive(value.r, value.theta);
	}

	//////////////////////////////////////////////////////
	//
	//	OffsetCircularBase
	//
	template <class Archive, class Float, int32 Oclock>
	inline void SIV3D_SERIALIZE(Archive& archive, OffsetCircularBase<Float, Oclock>& value)
	{
		archive(value.center, value.r, value.theta);
	}

	//////////////////////////////////////////////////////
	//
	//	CylindricalBase
	//
	template <class Archive, class Float>
	inline void SIV3D_SERIALIZE(Archive& archive, CylindricalBase<Float>& value)
	{
		archive(value.r, value.phi, value.y);
	}

	//////////////////////////////////////////////////////
	//
	//	SphericalBase
	//
	template <class Archive, class Float>
	inline void SIV3D_SERIALIZE(Archive& archive, SphericalBase<Float>& value)
	{
		archive(value.r, value.theta, value.phi);
	}

	//////////////////////////////////////////////////////
	//
	//	Mat3x2
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Mat3x2& value)
	{
		archive(cereal::binary_data(&value, sizeof(value)));
	}

	//////////////////////////////////////////////////////
	//
	//	Mat3x3
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Mat3x3& value)
	{
		archive(cereal::binary_data(&value, sizeof(value)));
	}

	//////////////////////////////////////////////////////
	//
	//	TriangleIndex
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, TriangleIndex& value)
	{
		archive(value.i0, value.i1, value.i2);
	}

	//////////////////////////////////////////////////////
	//
	//	Line
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Line& value)
	{
		archive(value.begin, value.end);
	}

	//////////////////////////////////////////////////////
	//
	//	Rect
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Rect& value)
	{
		archive(value.pos, value.size);
	}

	//////////////////////////////////////////////////////
	//
	//	RectF
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, RectF& value)
	{
		archive(value.pos, value.size);
	}

	//////////////////////////////////////////////////////
	//
	//	Circle
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Circle& value)
	{
		archive(value.center, value.r);
	}

	//////////////////////////////////////////////////////
	//
	//	Ellipse
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Ellipse& value)
	{
		archive(value.center, value.a, value.b);
	}

	//////////////////////////////////////////////////////
	//
	//	Triangle
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Triangle& value)
	{
		archive(value.p0, value.p1, value.p2);
	}

	//////////////////////////////////////////////////////
	//
	//	Quad
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Quad& value)
	{
		archive(value.p0, value.p1, value.p2, value.p3);
	}

	//////////////////////////////////////////////////////
	//
	//	RoundRect
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, RoundRect& value)
	{
		archive(value.rect, value.r);
	}

	//////////////////////////////////////////////////////
	//
	//	LineString
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const LineString& value)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.size())));
		archive(cereal::binary_data(value.data(), value.size_bytes()));
	}

	template <class Archive>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, LineString& value)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));
		value.resize(static_cast<size_t>(size));
		archive(cereal::binary_data(value.data(), value.size_bytes()));
	}

	//////////////////////////////////////////////////////
	//
	//	Polygon
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Polygon& value)
	{
		archive(value.outer());
		archive(value.inners());
		archive(value.vertices());
		archive(value.indices());
		archive(value.boundingRect());
	}

	template <class Archive>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Polygon& value)
	{
		Array<Vec2> outer;
		Array<Array<Vec2>> holes;
		Array<Float2> vertices;
		Array<TriangleIndex> indices;
		RectF boundingRect;
		archive(outer);
		archive(holes);
		archive(vertices);
		archive(indices);
		archive(boundingRect);
		value = Polygon{ outer, holes, vertices, indices, boundingRect };
	}

	//////////////////////////////////////////////////////
	//
	//	Bezier2
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Bezier2& value)
	{
		archive(value.p0, value.p1, value.p2);
	}

	//////////////////////////////////////////////////////
	//
	//	Bezier3
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Bezier3& value)
	{
		archive(value.p0, value.p1, value.p2, value.p3);
	}

	//////////////////////////////////////////////////////
	//
	//	Vertex2D
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Vertex2D& value)
	{
		archive(value.pos, value.tex, value.color);
	}

	//////////////////////////////////////////////////////
	//
	//	Shape2D
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Shape2D& value)
	{
		archive(value.vertices());
		archive(value.indices());
	}

	template <class Archive>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Shape2D& value)
	{
		Array<Float2> vertices;
		Array<TriangleIndex> indices;
		archive(vertices);
		archive(indices);
		value = Shape2D{ std::move(vertices), std::move(indices) };
	}

	//////////////////////////////////////////////////////
	//
	//	Image
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Image& image)
	{
		const auto encoded = image.encodePNG();
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(encoded.size())));
		archive(cereal::binary_data(encoded.data(), encoded.size()));
	}

	template <class Archive>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Image& image)
	{
		cereal::size_type binarySize;
		archive(cereal::make_size_tag(binarySize));
		Blob binary(static_cast<size_t>(binarySize));
		archive(cereal::binary_data(binary.data(), binary.size()));
		image = Image{ MemoryReader{ std::move(binary) } };
	}
}
