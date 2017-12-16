//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# define SIV3D_SERIALIZE		siv3d_serialize
# define SIV3D_SERIALIZE_LOAD	siv3d_serialize_save
# define SIV3D_SERIALIZE_SAVE	siv3d_serialize_load

# define CEREAL_SERIALIZE_FUNCTION_NAME SIV3D_SERIALIZE
# define CEREAL_LOAD_FUNCTION_NAME	SIV3D_SERIALIZE_LOAD
# define CEREAL_SAVE_FUNCTION_NAME	SIV3D_SERIALIZE_SAVE

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

# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Line.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Rectangle.hpp>

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
			: OutputArchive<Serializer<Writer>, cereal::AllowEmptyClassElision>(this)
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
			: InputArchive<Deserializer<Reader>, cereal::AllowEmptyClassElision>(this)
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
	//	Line
	//
	template <class Archive>
	inline void SIV3D_SERIALIZE(Archive& archive, Line& value)
	{
		archive(value.begin, value.end);
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
}

CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::BinaryWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::BinaryReader>)
CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::MemoryWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::ByteArray>)
