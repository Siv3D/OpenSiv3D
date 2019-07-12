//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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

		Webcam();

		explicit Webcam(size_t index);

		~Webcam();

		[[nodiscard]] bool isAvailable() const;

		[[nodiscard]] explicit operator bool() const;

		bool start();

		void stop();

		[[nodiscard]] bool isActive() const;

		[[nodiscard]] size_t index() const;

		[[nodiscard]] Size getResolution() const;

		bool setResolution(const Size& resolution);
		
		bool setResolution(int32 width, int32 height);

		[[nodiscard]] bool hasNewFrame() const;

		bool getFrame(Image& image);

		bool getFrame(DynamicTexture& texture);
	};

	namespace System
	{
		[[nodiscard]] Array<WebcamInfo> EnumerateWebcams();
	}
}
