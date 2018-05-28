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

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// Webcam device information
	/// </summary>
	struct WebcamInfo
	{
		/// <summary>
		/// Webcam index
		/// </summary>
		uint32 index = 0;

		/// <summary>
		/// Name of the device
		/// </summary>
		String name;

		/// <summary>
		/// Unique name
		/// </summary>
		String uniqueName;
	};

	class Webcam
	{
	private:

		class WebcamDetail;

		std::shared_ptr<WebcamDetail> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Webcam(size_t index = 0);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Webcam();

		bool isAvailable() const;

		explicit operator bool() const;

		bool start();

		void stop();

		bool isActive() const;

		size_t index() const;

		Size getResolution() const;

		bool setResolution(const Size& resolution);

		bool hasNewFrame() const;

		bool getFrame(Image& image);

		bool getFrame(DynamicTexture& texture);
	};

	namespace System
	{
		Array<WebcamInfo> EnumerateWebcams();
	}
}
