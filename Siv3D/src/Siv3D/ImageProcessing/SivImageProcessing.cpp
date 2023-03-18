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

# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	namespace detail
	{
		static Image GenerateMip(const Image& src)
		{
			if (not src)
			{
				return{};
			}

			const Color* pSrc = src.data();
			const int32 srcW = src.width();
			const int32 srcH = src.height();

			const int32 targetWidth = Max(src.width() / 2, 1);
			const int32 targetHeight = Max(src.height() / 2, 1);
			
			if ((targetWidth <= 4) && (targetHeight <= 4))
			{
				return src.scaled(targetWidth, targetHeight, InterpolationAlgorithm::Area);
			}
			
			Image result(targetWidth, targetHeight);
			Color* pDst = result.data();

			const float sddx = (srcW - 1.0f) / Max(targetWidth - 1, 1);
			const float sddy = (srcH - 1.0f) / Max(targetHeight - 1, 1);

			for (int32 y = 0; y < targetHeight; ++y)
			{
				float sy = y * sddy;

				const int32 dy = static_cast<int32>(sy);

				sy -= dy;

				const int32 dyO = Min(dy + 1, srcH - 1);

				for (int32 x = 0; x < targetWidth; ++x)
				{
					float sx = x * sddx;

					const int32 dx = static_cast<int32>(sx);

					sx -= dx;

					const int32 dxO = Min(dx + 1, srcW - 1);

					const Color& c0 = pSrc[dy * srcW + dx];
					const Color& c1 = pSrc[dy * srcW + dxO];
					const Color& c2 = pSrc[dyO * srcW + dx];
					const Color& c3 = pSrc[dyO * srcW + dxO];

					const uint8 r = static_cast<uint8>((c0.r * (1 - sx) + c1.r * sx) * (1 - sy) + (c2.r * (1 - sx) + c3.r * sx) * sy);
					const uint8 g = static_cast<uint8>((c0.g * (1 - sx) + c1.g * sx) * (1 - sy) + (c2.g * (1 - sx) + c3.g * sx) * sy);
					const uint8 b = static_cast<uint8>((c0.b * (1 - sx) + c1.b * sx) * (1 - sy) + (c2.b * (1 - sx) + c3.b * sx) * sy);
					const uint8 a = static_cast<uint8>((c0.a * (1 - sx) + c1.a * sx) * (1 - sy) + (c2.a * (1 - sx) + c3.a * sx) * sy);

					(pDst++)->set(r, g, b, a);
				}
			}

			return result;
		}
	}

	namespace ImageProcessing
	{
		Array<Image> GenerateMips(const Image& src)
		{
			return GenerateMips(src, Largest<size_t>);
		}

		Array<Image> GenerateMips(const Image& src, const size_t maxLevel)
		{
			const size_t mipCount = std::min(maxLevel, (CalculateMipCount(src.width(), src.height()) - 1));

			if (mipCount < 1)
			{
				return{};
			}

			Array<Image> mipImages(mipCount);

			mipImages[0] = detail::GenerateMip(src);

			for (size_t i = 1; i < mipCount; ++i)
			{
				mipImages[i] = detail::GenerateMip(mipImages[i - 1]);
			}

			return mipImages;
		}

		void Sobel(const Image& src, Image& dst, const int32 dx, const int32 dy, int32 apertureSize)
		{
			// 1. パラメータチェック
			{
				if (not src)
				{
					return;
				}

				if (&src == &dst)
				{
					return;
				}

				if (IsEven(apertureSize))
				{
					++apertureSize;
				}
			}

			// 2. 出力画像のサイズ変更
			{
				dst.resize(src.size());
				std::memcpy(dst.data(), src.data(), dst.size_bytes());
			}

			// 3. 処理
			{
				const cv::Mat_<uint8> gray = OpenCV_Bridge::ToGrayScale(src);
				cv::Mat_<uint8> detected_edges;
				cv::Sobel(gray, detected_edges, CV_8U, dx, dy, apertureSize);
				OpenCV_Bridge::FromGrayScale(detected_edges, dst, OverwriteAlpha::No);
			}
		}

		void Laplacian(const Image& src, Image& dst, int32 apertureSize)
		{
			// 1. パラメータチェック
			{
				if (not src)
				{
					return;
				}

				if (&src == &dst)
				{
					return;
				}

				if (IsEven(apertureSize))
				{
					++apertureSize;
				}
			}

			// 2. 出力画像のサイズ変更
			{
				dst.resize(src.size());
				std::memcpy(dst.data(), src.data(), dst.size_bytes());
			}

			// 3. 処理
			{
				const cv::Mat_<uint8> gray = OpenCV_Bridge::ToGrayScale(src);
				cv::Mat_<uint8> detected_edges;
				cv::Laplacian(gray, detected_edges, CV_8U, apertureSize);
				OpenCV_Bridge::FromGrayScale(detected_edges, dst, OverwriteAlpha::No);
			}
		}

		void Canny(const Image& src, Image& dst, const uint8 lowThreshold, const uint8 highThreshold, int32 apertureSize, const bool useL2Gradient)
		{
			// 1. パラメータチェック
			{
				if (not src)
				{
					return;
				}

				if (&src == &dst)
				{
					return;
				}

				if (IsEven(apertureSize))
				{
					++apertureSize;
				}
			}

			// 2. 出力画像のサイズ変更
			{
				dst.resize(src.size());
				std::memcpy(dst.data(), src.data(), dst.size_bytes());
			}

			// 3. 処理
			{
				const cv::Mat_<uint8> gray = OpenCV_Bridge::ToGrayScale(src);
				cv::Mat_<uint8> detected_edges;
				cv::blur(gray, detected_edges, cv::Size(3, 3));
				cv::Canny(detected_edges, detected_edges, lowThreshold, highThreshold, apertureSize, useL2Gradient);
				OpenCV_Bridge::FromGrayScale(detected_edges, dst, OverwriteAlpha::No);
			}
		}

		void EdgePreservingFilter(const Image& src, Image& dst, EdgePreservingFilterType filterType, double sigma_s, double sigma_r)
		{
			// 1. パラメータチェック
			{
				if (not src)
				{
					return dst.clear();
				}
			}

			// 2. 出力画像のサイズ変更
			{
				dst.resize(src.size());
				std::memcpy(dst.data(), src.data(), dst.size_bytes());
			}

			// 3. 処理
			{
				const cv::Mat_<cv::Vec3b> matSrc = OpenCV_Bridge::ToMatVec3bBGR(src);
				cv::Mat_<cv::Vec3b> matDst;
				cv::edgePreservingFilter(matSrc, matDst,
					(filterType == EdgePreservingFilterType::Recursive)
					? cv::RECURS_FILTER : cv::NORMCONV_FILTER,
					static_cast<float>(sigma_s), static_cast<float>(sigma_r));
				OpenCV_Bridge::FromMatVec3b(matDst, dst, OverwriteAlpha::No);
			}
		}

		void DetailEnhance(const Image& src, Image& dst, double sigma_s, double sigma_r)
		{
			// 1. パラメータチェック
			{
				if (not src)
				{
					return dst.clear();
				}
			}

			// 2. 出力画像のサイズ変更
			{
				dst.resize(src.size());
				std::memcpy(dst.data(), src.data(), dst.size_bytes());
			}

			// 3. 処理
			{
				cv::Mat_<cv::Vec3b> matSrc = OpenCV_Bridge::ToMatVec3bBGR(src);
				cv::Mat_<cv::Vec3b> matDst;
				cv::detailEnhance(matSrc, matDst, static_cast<float>(sigma_s), static_cast<float>(sigma_r));
				OpenCV_Bridge::FromMatVec3b(matDst, dst, OverwriteAlpha::No);
			}
		}

		void Stylization(const Image& src, Image& dst, double sigma_s, double sigma_r)
		{
			// 1. パラメータチェック
			{
				if (not src)
				{
					return dst.clear();
				}
			}

			// 2. 出力画像のサイズ変更
			{
				dst.resize(src.size());
				std::memcpy(dst.data(), src.data(), dst.size_bytes());
			}

			// 3. 処理
			{
				cv::Mat_<cv::Vec3b> matSrc = OpenCV_Bridge::ToMatVec3bBGR(src);
				cv::Mat_<cv::Vec3b> matDst;
				cv::stylization(matSrc, matDst, static_cast<float>(sigma_s), static_cast<float>(sigma_r));
				OpenCV_Bridge::FromMatVec3b(matDst, dst, OverwriteAlpha::No);
			}
		}

		ColorF SSIM(const Image& image1, const Image& image2)
		{
			if (image1.size() != image2.size())
			{
				return ColorF{ 1.0 };
			}

			const double C1 = 6.5025, C2 = 58.5225;
			const int32 x = image1.width(), y = image1.height();

			cv::Mat_<cv::Vec3f> I1(y, x), I2(y, x);
			OpenCV_Bridge::ToMatVec3f255(image1, I1);
			OpenCV_Bridge::ToMatVec3f255(image2, I2);

			cv::Mat I2_2 = I2.mul(I2);        // I2^2
			cv::Mat I1_2 = I1.mul(I1);        // I1^2
			cv::Mat I1_I2 = I1.mul(I2);        // I1 * I2

			/*************************** END INITS **********************************/

			cv::Mat mu1, mu2;   // PRELIMINARY COMPUTING
			cv::GaussianBlur(I1, mu1, cv::Size(11, 11), 1.5);
			cv::GaussianBlur(I2, mu2, cv::Size(11, 11), 1.5);


			cv::Mat mu1_2 = mu1.mul(mu1);
			cv::Mat mu2_2 = mu2.mul(mu2);
			cv::Mat mu1_mu2 = mu1.mul(mu2);

			cv::Mat sigma1_2, sigma2_2, sigma12;

			cv::GaussianBlur(I1_2, sigma1_2, cv::Size(11, 11), 1.5);
			sigma1_2 -= mu1_2;

			cv::GaussianBlur(I2_2, sigma2_2, cv::Size(11, 11), 1.5);
			sigma2_2 -= mu2_2;

			cv::GaussianBlur(I1_I2, sigma12, cv::Size(11, 11), 1.5);
			sigma12 -= mu1_mu2;

			///////////////////////////////// FORMULA ////////////////////////////////
			cv::Mat t1, t2, t3;

			t1 = 2 * mu1_mu2 + C1;
			t2 = 2 * sigma12 + C2;
			t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

			t1 = mu1_2 + mu2_2 + C1;
			t2 = sigma1_2 + sigma2_2 + C2;
			t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

			cv::Mat ssim_map;
			cv::divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;

			cv::Scalar mssim = cv::mean(ssim_map); // mssim = average of ssim map
			return{ mssim[2], mssim[1], mssim[0], 1.0 };
		}

		void Inpaint(const Image& image, const Image& maskImage, const Color& maskColor, Image& result, int32 radius)
		{
			// 1. パラメータチェック
			{
				if ((not image) || (not maskImage))
				{
					return;
				}

				if (image.size() != maskImage.size())
				{
					return;
				}

				radius = Max(radius, 0);
			}

			// 2. 処理
			{
				cv::Mat_<cv::Vec3b> matSrc = OpenCV_Bridge::ToMatVec3bBGR(image);

				cv::Mat_<uint8> matMask(image.height(), image.width());
				OpenCV_Bridge::MaskByColor(maskImage, matMask, maskColor);

				cv::Mat_<cv::Vec3b> matDst;
				cv::inpaint(matSrc, matMask, matDst, radius, cv::INPAINT_TELEA);
				OpenCV_Bridge::FromMatVec3b(matDst, result, OverwriteAlpha::Yes);
			}
		}

		void Inpaint(const Image& image, const Grid<uint8>& maskImage, Image& result, int32 radius)
		{
			// 1. パラメータチェック
			{
				if ((not image) || (not maskImage))
				{
					return;
				}

				if (image.size() != maskImage.size())
				{
					return;
				}

				radius = Max(radius, 0);
			}

			// 2. 処理
			{
				cv::Mat_<cv::Vec3b> matSrc = OpenCV_Bridge::ToMatVec3bBGR(image);
				cv::Mat_<uint8> matMask(static_cast<int32>(maskImage.height()), static_cast<int32>(maskImage.width()), const_cast<uint8*>(maskImage.data()), static_cast<int32>(maskImage.width()));
				cv::Mat_<cv::Vec3b> matDst;
				cv::inpaint(matSrc, matMask, matDst, radius, cv::INPAINT_TELEA);
				OpenCV_Bridge::FromMatVec3b(matDst, result, OverwriteAlpha::Yes);
			}
		}
	}
}
