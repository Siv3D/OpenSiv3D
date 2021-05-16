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
// # include "../ThirdParty/cereal/types/atomic.hpp"
# include "../ThirdParty/cereal/types/base_class.hpp"
// # include "../ThirdParty/cereal/types/bitset.hpp"
# include "../ThirdParty/cereal/types/chrono.hpp"
# include "../ThirdParty/cereal/types/common.hpp"
// # include "../ThirdParty/cereal/types/complex.hpp"
// # include "../ThirdParty/cereal/types/deque.hpp"
// # include "../ThirdParty/cereal/types/forward_list.hpp"
// # include "../ThirdParty/cereal/types/functional.hpp"
// # include "../ThirdParty/cereal/types/list.hpp"
// # include "../ThirdParty/cereal/types/map.hpp"
# include "../ThirdParty/cereal/types/memory.hpp"
// # include "../ThirdParty/cereal/types/optional.hpp"
# include "../ThirdParty/cereal/types/polymorphic.hpp"
// #include "../ThirdParty/cereal/types/queue.hpp"
// # include "../ThirdParty/cereal/types/set.hpp"
// # include "../ThirdParty/cereal/types/stack.hpp"
# include "../ThirdParty/cereal/types/string.hpp"
# include "../ThirdParty/cereal/types/tuple.hpp"
// # include "../ThirdParty/cereal/types/unordered_map.hpp"
// # include "../ThirdParty/cereal/types/unordered_set.hpp"
# include "../ThirdParty/cereal/types/utility.hpp"
// # include "../ThirdParty/cereal/types/valarray.hpp"
// # include "../ThirdParty/cereal/types/variant.hpp"
# include "../ThirdParty/cereal/types/vector.hpp"

namespace s3d
{
	template <class Writer>
	class Serializer : public cereal::OutputArchive<Serializer<Writer>, cereal::AllowEmptyClassElision>
	{
	public:

		template <class ...Args>
		Serializer(Args&& ... args)
			: cereal::OutputArchive<Serializer<Writer>, cereal::AllowEmptyClassElision>(this)
			, m_writer(std::make_shared<Writer>(std::forward<Args>(args)...)) {}

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

	private:

		std::shared_ptr<IWriter> m_writer;
	};

	template <class Reader>
	class Deserializer : public cereal::InputArchive<Deserializer<Reader>, cereal::AllowEmptyClassElision>
	{
	public:

		template <class ...Args>
		Deserializer(Args&& ... args)
			: cereal::InputArchive<Deserializer<Reader>, cereal::AllowEmptyClassElision>(this)
			, m_reader(std::make_shared<Reader>(std::forward<Args>(args)...)) {}

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

	private:

		std::shared_ptr<IReader> m_reader;
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
}

CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::BinaryWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::BinaryReader>)
CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::BlobWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::MemoryReader>)

CEREAL_SETUP_ARCHIVE_TRAITS(s3d::Deserializer<s3d::BinaryReader>, s3d::Serializer<s3d::BinaryWriter>)
CEREAL_SETUP_ARCHIVE_TRAITS(s3d::Deserializer<s3d::MemoryReader>, s3d::Serializer<s3d::BlobWriter>)
