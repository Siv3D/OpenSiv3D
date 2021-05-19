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
		explicit Webcam(size_t cameraIndex, StartImmediately startImmediately = StartImmediately::No);

		SIV3D_NODISCARD_CXX20
		Webcam(size_t cameraIndex, const Size& targetResolution, StartImmediately startImmediately = StartImmediately::No);

		~Webcam();

		/// @brief Web カメラの使用権限を返します。
		/// @return 許可されている場合 `Permission::Allowed`, 拒否されている場合 `Permission::Denied`, 権限をリクエスト中である場合 `none`
		[[nodiscard]]
		Optional<Permission> getPermission() const;

		bool open(size_t cameraIndex);

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

		bool start();

		[[nodiscard]]
		bool isActive() const;

		[[nodiscard]]
		size_t cameraIndex() const;

		[[nodiscard]]
		Size getResolution() const;

		bool setResolution(int32 width, int32 height);

		bool setResolution(Size resolution);

		[[nodiscard]]
		bool hasNewFrame() const;

		bool getFrame(Image& image);

		bool getFrame(DynamicTexture& texture);

	private:

		class WebcamDetail;

		std::shared_ptr<WebcamDetail> pImpl;
	};
}
