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

# include <Siv3D/Blob.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/MD5.hpp>
# include <Siv3D/Base64.hpp>

namespace s3d
{
	Blob::Blob(const size_t sizeBytes)
		: m_data(sizeBytes) {}

	Blob::Blob(const Arg::reserve_<size_t> resrveSizeBytes)
		: m_data(resrveSizeBytes) {}

	Blob::Blob(const FilePathView path)
	{
		createFromFile(path);
	}

	Blob::Blob(IReader& reader)
		: m_data(reader.size())
	{
		reader.read(m_data.data(), m_data.size());
	}

	Blob::Blob(const void* src, const size_t sizeBytes)
		: m_data(static_cast<const Byte*>(src), (static_cast<const Byte*>(src) + sizeBytes)) {}

	Blob::Blob(const Array<Byte>& data)
		: m_data(data) {}

	Blob::Blob(Array<Byte>&& data)
		: m_data(std::move(data)) {}

	Blob& Blob::operator =(const Array<Byte>& other)
	{
		m_data = other;

		return *this;
	}

	Blob& Blob::operator =(Array<Byte>&& other) noexcept
	{
		m_data = std::move(other);

		return *this;
	}

	Blob& Blob::operator =(const Blob& other)
	{
		m_data = other.m_data;

		return *this;
	}

	Blob& Blob::operator =(Blob&& other) noexcept
	{
		m_data = std::move(other.m_data);

		return *this;
	}

	void Blob::create(const Blob& other)
	{
		m_data = other.m_data;
	}

	void Blob::create(Blob&& other)
	{
		m_data = std::move(other.m_data);
	}

	void Blob::create(const void* src, const size_t sizeBytes)
	{
		m_data.assign(static_cast<const Byte*>(src), (static_cast<const Byte*>(src) + sizeBytes));
	}

	void Blob::create(const Array<Byte>& data)
	{
		m_data = data;
	}

	void Blob::create(Array<Byte>&& data)
	{
		m_data = std::move(data);
	}

	bool Blob::createFromFile(const FilePathView path)
	{
		BinaryReader reader{ path };

		if (not reader)
		{
			return false;
		}

		m_data.resize(reader.size());

		const bool result = (static_cast<int64>(m_data.size_bytes()) == reader.read(m_data.data(), m_data.size_bytes()));

		return result;
	}

	void Blob::reserve(const size_t sizeBytes)
	{
		m_data.reserve(sizeBytes);
	}

	void Blob::resize(const size_t sizeBytes)
	{
		m_data.resize(sizeBytes, Byte{ 0 });
	}

	void Blob::shrink_to_fit()
	{
		m_data.shrink_to_fit();
	}

	void Blob::clear()
	{
		m_data.clear();
	}

	void Blob::release()
	{
		m_data.release();
	}

	void Blob::append(const void* src, const size_t sizeBytes)
	{
		m_data.insert(m_data.end(), static_cast<const Byte*>(src), (static_cast<const Byte*>(src) + sizeBytes));
	}

	bool Blob::save(const FilePathView path) const
	{
		BinaryWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		const bool result = (static_cast<int64>(m_data.size_bytes()) == writer.write(m_data.data(), m_data.size_bytes()));

		return result;
	}

	MD5Value Blob::md5() const
	{
		return MD5::FromBinary(m_data.data(), m_data.size_bytes());
	}

	std::string Blob::base64() const
	{
		std::string result;
		Base64::Encode(m_data.data(), m_data.size_bytes(), result);
		return result;
	}

	String Blob::base64Str() const
	{
		String result;
		Base64::Encode(m_data.data(), m_data.size_bytes(), result);
		return result;
	}

	void Blob::base64(std::string& dst) const
	{
		Base64::Encode(m_data.data(), m_data.size_bytes(), dst);
	}

	void Blob::base64(String& dst) const
	{
		Base64::Encode(m_data.data(), m_data.size_bytes(), dst);
	}
}
