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
# include <memory>
# include "Common.hpp"
# include "Optional.hpp"
# include "DynamicTexture.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief Web カメラ
	class Webcam
	{
	public:

		enum class Permission
		{
			Allowed,

			Denied,
		};

		SIV3D_NODISCARD_CXX20
		Webcam();

		SIV3D_NODISCARD_CXX20
		explicit Webcam(uint32 cameraIndex, StartImmediately startImmediately = StartImmediately::No);

		SIV3D_NODISCARD_CXX20
		Webcam(uint32 cameraIndex, const Size& targetResolution, StartImmediately startImmediately = StartImmediately::No);

		~Webcam();

		/// @brief Web カメラの使用権限を返します。
		/// @return 許可されている場合 `Permission::Allowed`, 拒否されている場合 `Permission::Denied`, 権限をリクエスト中である場合 `none`
		[[nodiscard]]
		Optional<Permission> getPermission() const;

		/// @brief Web カメラを起動します。
		/// @param cameraIndex カメラのデバイスインデックス
		/// @return 
		bool open(uint32 cameraIndex);

		/// @brief Web カメラをオフにします。
		void close();

		/// @brief Web カメラが起動しているかを返します。
		/// @return Web カメラが起動している場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const;

		/// @brief Web カメラが起動しているかを返します。
		/// @remark `Webcam::isOpen()` と同じです。
		/// @return Web カメラが起動している場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const;

		/// @brief Web カメラによる撮影を開始します。
		/// @return すでに撮影中であるか、撮影の開始に成功した場合 true, それ以外の場合は false
		bool start();

		/// @brief Web カメラが撮影中であるかを返します。
		/// @return  Web カメラが撮影中である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isActive() const;

		/// @brief Web カメラのデバイスインデックスを返します。
		/// @return Web カメラのデバイスインデックス
		[[nodiscard]]
		uint32 cameraIndex() const;

		/// @brief Web カメラの撮影解像度を返します。
		/// @return Web カメラの撮影解像度
		[[nodiscard]]
		Size getResolution() const;

		/// @brief Web カメラの撮影解像度の変更をリクエストします。
		/// @param width 幅（ピクセル）
		/// @param height 高さ（ピクセル）
		/// @return リクエストした解像度に変更できた場合 true, それ以外の場合は false
		bool setResolution(int32 width, int32 height);

		/// @brief Web カメラの撮影解像度の変更をリクエストします。
		/// @param resolution 解像度
		/// @return リクエストした解像度に変更できた場合 true, それ以外の場合は false
		bool setResolution(Size resolution);

		/// @brief 新しく撮影された画像があるかを返します。
		/// @return 新しく撮影された画像がある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasNewFrame() const;

		/// @brief 最新の撮影された画像を取得します。
		/// @param image 画像の格納先
		/// @return 画像の取得に成功した場合 true, それ以外の場合は false
		bool getFrame(Image& image);

		/// @brief 最新の撮影された画像を取得します。
		/// @param texture 画像の格納先
		/// @return 画像の取得に成功した場合 true, それ以外の場合は false
		bool getFrame(DynamicTexture& texture);

	private:

		class WebcamDetail;

		std::shared_ptr<WebcamDetail> pImpl;
	};
}
