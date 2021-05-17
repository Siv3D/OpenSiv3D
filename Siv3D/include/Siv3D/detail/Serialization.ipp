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
}
