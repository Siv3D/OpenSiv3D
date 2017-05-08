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

# include "../Siv3DEngine.hpp"
# include "../Shader/IShader.hpp"
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/ByteArrayView.hpp>

namespace s3d
{
	template <>
	AssetHandle<PixelShader::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetShader())
		{
			p->releasePS(m_id);
		}
	}

	PixelShader::PixelShader()
		: m_handle(std::make_shared<PixelShaderHandle>())
	{

	}

	PixelShader::PixelShader(const FilePath& path, const Array<BindingPoint>& bindingPoints)
		: m_handle(std::make_shared<PixelShaderHandle>(Siv3DEngine::GetShader()->createPSFromFile(std::move(path), bindingPoints)))
	{

	}
	
	PixelShader::PixelShader(Arg::source_<String> source, const Array<BindingPoint>& bindingPoints)
		: m_handle(std::make_shared<PixelShaderHandle>(Siv3DEngine::GetShader()->createPSFromSource(source.value(), bindingPoints)))
	{
		
	}

	PixelShader::~PixelShader()
	{

	}

	void PixelShader::release()
	{
		m_handle = std::make_shared<PixelShaderHandle>();
	}

	bool PixelShader::isEmpty() const
	{
		return m_handle->getID() == PixelShaderHandle::NullID;
	}

	PixelShader::IDType PixelShader::id() const
	{
		return m_handle->getID();
	}

	bool PixelShader::operator ==(const PixelShader& shader) const
	{
		return m_handle->getID() == shader.m_handle->getID();
	}

	bool PixelShader::operator !=(const PixelShader& shader) const
	{
		return m_handle->getID() != shader.m_handle->getID();
	}

	ByteArrayView PixelShader::getBinaryView() const
	{
		return Siv3DEngine::GetShader()->getBinaryViewPS(m_handle->getID());
	}
}
