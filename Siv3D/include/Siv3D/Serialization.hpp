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
		SIV3D_NODISCARD_CXX20
		Serializer(Args&& ... args);

		void saveBinary(const void* data, size_t size);

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		std::shared_ptr<Writer> operator ->();

		[[nodiscard]]
		std::shared_ptr<const Writer> operator ->() const;

	private:

		std::shared_ptr<IWriter> m_writer;
	};

	template <class Reader>
	class Deserializer : public cereal::InputArchive<Deserializer<Reader>, cereal::AllowEmptyClassElision>
	{
	public:

		template <class ...Args>
		SIV3D_NODISCARD_CXX20
		Deserializer(Args&& ... args);

		void loadBinary(void* const data, size_t size);

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		std::shared_ptr<Reader> operator ->();

		[[nodiscard]]
		std::shared_ptr<const Reader> operator ->() const;

	private:

		std::shared_ptr<IReader> m_reader;
	};
}

# include "detail/Serialization.ipp"

CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::BinaryWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::BinaryReader>)
CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::MemoryWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::MemoryReader>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::MemoryViewReader>)

CEREAL_SETUP_ARCHIVE_TRAITS(s3d::Deserializer<s3d::BinaryReader>, s3d::Serializer<s3d::BinaryWriter>)
CEREAL_SETUP_ARCHIVE_TRAITS(s3d::Deserializer<s3d::MemoryReader>, s3d::Serializer<s3d::MemoryWriter>)
