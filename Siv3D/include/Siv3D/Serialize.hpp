//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# define SIV3D_SERIALIZE		siv3d_serialize
# define SIV3D_SERIALIZE_LOAD	siv3d_serialize_save
# define SIV3D_SERIALIZE_SAVE	siv3d_serialize_load
# define SIV3D_SERIALIZE_LOAD_M	siv3d_serialize_save_minimal
# define SIV3D_SERIALIZE_SAVE_M	siv3d_serialize_load_minimal

# define CEREAL_SERIALIZE_FUNCTION_NAME		SIV3D_SERIALIZE
# define CEREAL_LOAD_FUNCTION_NAME			SIV3D_SERIALIZE_LOAD
# define CEREAL_SAVE_FUNCTION_NAME			SIV3D_SERIALIZE_SAVE
# define CEREAL_SAVE_MINIMAL_FUNCTION_NAME	SIV3D_SERIALIZE_LOAD_M
# define CEREAL_LOAD_MINIMAL_FUNCTION_NAME	SIV3D_SERIALIZE_SAVE_M

# include "../ThirdParty/cereal/cereal.hpp"
# include "../ThirdParty/cereal/archives/binary.hpp"
# include "../ThirdParty/cereal/types/array.hpp"
# include "../ThirdParty/cereal/types/base_class.hpp"
// # include "../ThirdParty/cereal/types/bitset.hpp"
# include "../ThirdParty/cereal/types/chrono.hpp"
# include "../ThirdParty/cereal/types/common.hpp"
# include "../ThirdParty/cereal/types/complex.hpp"
// # include "../ThirdParty/cereal/types/deque.hpp"
// # include "../ThirdParty/cereal/types/forward_list.hpp"
// # include "../ThirdParty/cereal/types/functional.hpp"
// # include "../ThirdParty/cereal/types/list.hpp"
// # include "../ThirdParty/cereal/types/map.hpp"
# include "../ThirdParty/cereal/types/memory.hpp"
# include "../ThirdParty/cereal/types/polymorphic.hpp"
// include "../ThirdParty/cereal/types/queue.hpp"
// # include "../ThirdParty/cereal/types/set.hpp"
// # include "../ThirdParty/cereal/types/stack.hpp"
# include "../ThirdParty/cereal/types/string.hpp"
# include "../ThirdParty/cereal/types/tuple.hpp"
# include "../ThirdParty/cereal/types/unordered_map.hpp"
# include "../ThirdParty/cereal/types/unordered_set.hpp"
# include "../ThirdParty/cereal/types/utility.hpp"
// # include "../ThirdParty/cereal/types/valarray.hpp"
# include "../ThirdParty/cereal/types/vector.hpp"

namespace s3d
{
	template <class Writer>
	class Serializer : public cereal::OutputArchive<Serializer<Writer>, cereal::AllowEmptyClassElision>
	{
	private:

		std::shared_ptr<IWriter> m_writer;

	public:

		template <class ...Args>
		Serializer(Args&&... args)
			: cereal::OutputArchive<Serializer<Writer>, cereal::AllowEmptyClassElision>(this)
			, m_writer(std::make_shared<Writer>(std::forward<Args>(args)...))
		{

		}

		void saveBinary(const void* data, const size_t size)
		{
			const size_t writtenSize = static_cast<size_t>(m_writer->write(data, size));

			if (writtenSize != size)
			{
				throw cereal::Exception("Failed to write " + std::to_string(size) + " bytes to output stream! Wrote " + std::to_string(writtenSize));
			}
		}

		Writer& getWriter()
		{
			return *std::dynamic_pointer_cast<Writer>(m_writer);
		}
	};

	template <class Reader>
	class Deserializer : public cereal::InputArchive<Deserializer<Reader>, cereal::AllowEmptyClassElision>
	{
	private:

		std::shared_ptr<IReader> m_reader;

	public:

		template <class ...Args>
		Deserializer(Args&&... args)
			: cereal::InputArchive<Deserializer<Reader>, cereal::AllowEmptyClassElision>(this)
			, m_reader(std::make_shared<Reader>(std::forward<Args>(args)...))
		{

		}

		void loadBinary(void* const data, const size_t size)
		{
			const size_t readSize = static_cast<size_t>(m_reader->read(data, size));

			if (readSize != size)
			{
				throw cereal::Exception("Failed to read " + std::to_string(size) + " bytes from input stream! Read " + std::to_string(readSize));
			}
		}

		Reader& getReader()
		{
			return *std::dynamic_pointer_cast<Reader>(m_reader);
		}
	};

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
		archive(cereal::binary_data(value.data(), value.size() * sizeof(Array<Type>::value_type)));
	}

	template <class Archive, class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Array<Type>& value)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));
		value.resize(static_cast<size_t>(size));
		archive(cereal::binary_data(value.data(), static_cast<size_t>(size * sizeof(Array<Type>::value_type))));
	}

	template <class Archive, class Type, std::enable_if_t<!std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Array<Type>& value)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.size())));

		for (auto && v : value)
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

		for (auto && v : value)
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
		archive(cereal::binary_data(value.data(), value.size_elements() * sizeof(Array<Type>::value_type)));
	}

	template <class Archive, class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, Grid<Type>& value)
	{
		cereal::size_type width, height;
		archive(cereal::make_size_tag(width));
		archive(cereal::make_size_tag(height));
		value.resize(static_cast<size_t>(width), static_cast<size_t>(height));
		archive(cereal::binary_data(value.data(), static_cast<size_t>(width * height * sizeof(Array<Type>::value_type))));
	}

	template <class Archive, class Type, std::enable_if_t<!std::is_trivially_copyable_v<Type>>* = nullptr>
	inline void SIV3D_SERIALIZE_SAVE(Archive& archive, const Grid<Type>& value)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.width())));
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(value.height())));

		for (auto && v : value)
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

		for (auto && v : value)
		{
			archive(v);
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
				archive(value.value());
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
		archive(cereal::binary_data(value.data(), value.length() * sizeof(String::value_type)));
	}

	template <class Archive>
	inline void SIV3D_SERIALIZE_LOAD(Archive& archive, String& value)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));
		value.resize(static_cast<size_t>(size));
		archive(cereal::binary_data(value.data(), static_cast<size_t>(size * sizeof(String::value_type))));
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
	template <class Archive, int Oclock>
	inline void SIV3D_SERIALIZE(Archive& archive, CircularBase<Oclock>& value)
	{
		archive(value.r, value.theta);
	}

	//////////////////////////////////////////////////////
	//
	//	OffsetCircularBase
	//
	template <class Archive, int Oclock>
	inline void SIV3D_SERIALIZE(Archive& archive, OffsetCircularBase<Oclock>& value)
	{
		archive(value.center, value.r, value.theta);
	}

	//////////////////////////////////////////////////////
	//
	//	Cylindrical
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Cylindrical& value)
	{
		archive(value.r, value.phi, value.y);
	}

	//////////////////////////////////////////////////////
	//
	//	Spherical
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Spherical& value)
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
}

CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::BinaryWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::BinaryReader>)
CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::MemoryWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::ByteArray>)

CEREAL_SETUP_ARCHIVE_TRAITS(s3d::Deserializer<s3d::BinaryReader>, s3d::Serializer<s3d::BinaryWriter>)
CEREAL_SETUP_ARCHIVE_TRAITS(s3d::Deserializer<s3d::ByteArray>, s3d::Serializer<s3d::MemoryWriter>)
