//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/Common/D3D11.hpp>

namespace s3d
{
	class D3D11VertexShader
	{
	private:

		Blob m_binary;

		ComPtr<ID3D11VertexShader> m_shader;

		bool m_initialized = false;

	public:

		struct Null {};

		D3D11VertexShader() = default;

		D3D11VertexShader(Null);

		D3D11VertexShader(Blob&& binary, ID3D11Device* device);

		bool isInitialized() const noexcept;

		ID3D11VertexShader* getShader() const;

		const Blob& getBinary() const noexcept;
	};
}
