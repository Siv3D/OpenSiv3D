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
