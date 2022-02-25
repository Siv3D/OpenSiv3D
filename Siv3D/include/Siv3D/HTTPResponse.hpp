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
# include "Common.hpp"
# include "HTTPStatusCode.hpp"
# include "String.hpp"

namespace s3d
{
	/// @brief HTTP レスポンス
	class HTTPResponse
	{
	public:

		/// @brief デフォルトコンストラクタ
		/// @remark 無効な HTTP レスポンスを作成します。 
		SIV3D_NODISCARD_CXX20
		HTTPResponse() = default;

		/// @brief HTTP レスポンスからステータスとヘッダを取得します。
		/// @param response HTTP レスポンス
		SIV3D_NODISCARD_CXX20
		explicit HTTPResponse(const std::string& response);

		/// @brief ステータスコードを返します。
		/// @return ステータスコード
		[[nodiscard]]
		HTTPStatusCode getStatusCode() const noexcept;

		/// @brief ステータス行を返します。
		/// @return ステータス行
		[[nodiscard]]
		const String& getStatusLine() const noexcept;

		/// @brief ヘッダーを返します。
		/// @return ヘッダー
		[[nodiscard]]
		const String& getHeader() const noexcept;

		/// @brief 有効な HTTP レスポンスであるかを返します。
		/// @return 有効な HTTP レスポンスである場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 無効な HTTP レスポンスであるかを返します。
		/// @return 無効な HTTP レスポンスである場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isInvalid() const noexcept;

		/// @brief ステータスコードが 1xx (情報レスポンス) であるかを返します。
		/// @return ステータスコードが 1xx (情報レスポンス) である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isInformational() const noexcept;

		/// @brief ステータスコードが 2xx (成功レスポンス) であるかを返します。
		/// @return ステータスコードが 2xx (成功レスポンス) である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isSuccessful() const noexcept;

		/// @brief ステータスコードが 3xx (リダイレクト) であるかを返します。
		/// @return ステータスコードが 3xx (リダイレクト) である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isRedirection() const noexcept;

		/// @brief ステータスコードが 4xx (クライアントエラー) であるかを返します。
		/// @return ステータスコードが 4xx (クライアントエラー) である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isClientError() const noexcept;

		/// @brief ステータスコードが 5xx (サーバエラー) であるかを返します。
		/// @return ステータスコードが 5xx (サーバエラー) である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isServerError() const noexcept;

		/// @brief ステータスコードが 200 (OK) であるかを返します。
		/// @return ステータスコードが 200 (OK) である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOK() const noexcept;

		/// @brief ステータスコードが 404 (NotFound) であるかを返します。
		/// @return ステータスコードが 404 (NotFound) である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isNotFound() const noexcept;

	private:

		String m_statusLine;

		String m_header;

		HTTPStatusCode m_statusCode = HTTPStatusCode::Invalid;
	};
}