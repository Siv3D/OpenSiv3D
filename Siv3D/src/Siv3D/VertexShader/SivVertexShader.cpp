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

# include "../Siv3DEngine.hpp"
# include "../Shader/IShader.hpp"
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/ByteArrayView.hpp>

namespace s3d
{
	template <>
	AssetHandle<VertexShader::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetShader())
		{
			p->releaseVS(m_id);
		}
	}

	VertexShader::VertexShader()
		: m_handle(std::make_shared<VertexShaderHandle>())
	{

	}

	VertexShader::VertexShader(const FilePath& path, const Array<BindingPoint>& bindingPoints)
		: m_handle(std::make_shared<VertexShaderHandle>(Siv3DEngine::GetShader()->createVSFromFile(std::move(path), bindingPoints)))
	{

	}
	
	VertexShader::VertexShader(Arg::source_<String> source, const Array<BindingPoint>& bindingPoints)
		: m_handle(std::make_shared<VertexShaderHandle>(Siv3DEngine::GetShader()->createVSFromSource(source.value(), bindingPoints)))
	{
		
	}

	VertexShader::~VertexShader()
	{

	}

	void VertexShader::release()
	{
		m_handle = std::make_shared<VertexShaderHandle>();
	}

	bool VertexShader::isEmpty() const
	{
		return m_handle->id().isNullAsset();
	}

	VertexShaderID VertexShader::id() const
	{
		return m_handle->id();
	}

	bool VertexShader::operator ==(const VertexShader& shader) const
	{
		return m_handle->id() == shader.m_handle->id();
	}

	bool VertexShader::operator !=(const VertexShader& shader) const
	{
		return m_handle->id() != shader.m_handle->id();
	}

	ByteArrayView VertexShader::getBinaryView() const
	{
		return Siv3DEngine::GetShader()->getBinaryViewVS(m_handle->id());
	}
}
