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
# include "Array.hpp"
# include "Grid.hpp"
# include "Blob.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "NamedParameter.hpp"
# include "PredefinedNamedParameter.hpp"
# include "ImageFormat.hpp"
# include "ImageAddressMode.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "IReader.hpp"
# include "PNGFilter.hpp"
# include "PPMType.hpp"
# include "WebPMethod.hpp"
# include "BorderType.hpp"
# include "AdaptiveThresholdMethod.hpp"
# include "FloodFillConnectivity.hpp"
# include "InterpolationAlgorithm.hpp"
# include "PredefinedYesNo.hpp"
# include "ImageFormat/PNGEncoder.hpp"
# include "ImageFormat/JPEGEncoder.hpp"
# include "ImageFormat/PPMEncoder.hpp"
# include "ImageFormat/WebPEncoder.hpp"

namespace s3d
{
	struct Emoji;
	struct Icon;
	struct ImageROI;
	struct ImageConstROI;
	struct Mat3x2;

	class Image
	{
	public:

		/// @brief 作成可能な最大の画像の幅
		static constexpr int32 MaxWidth		= 16384;

		/// @brief 作成可能な最大の画像の高さ
		static constexpr int32 MaxHeight	= 16384;

		using base_type					= Array<Color>;
		using iterator					= base_type::iterator;
		using const_iterator			= base_type::const_iterator;
		using reverse_iterator			= base_type::reverse_iterator;
		using const_reverse_iterator	= base_type::const_reverse_iterator;

		SIV3D_NODISCARD_CXX20
		Image() = default;

		SIV3D_NODISCARD_CXX20
		Image(const Image&) = default;

		SIV3D_NODISCARD_CXX20
		Image(Image&& image) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit Image(size_t size);

		SIV3D_NODISCARD_CXX20
		explicit Image(size_t size, Color color);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(size_t size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(size_t size, Arg::generator0_1_<Fty> generator);

		SIV3D_NODISCARD_CXX20
		Image(size_t width, size_t height);

		SIV3D_NODISCARD_CXX20
		Image(size_t width, size_t height, Color color);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(size_t width, size_t height, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(size_t width, size_t height, Arg::generator0_1_<Fty> generator);

		SIV3D_NODISCARD_CXX20
		explicit Image(Size size);

		SIV3D_NODISCARD_CXX20
		Image(Size size, Color color);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(Size size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(Size size, Arg::generator0_1_<Fty> generator);

		SIV3D_NODISCARD_CXX20
		explicit Image(FilePathView path, ImageFormat format = ImageFormat::Unspecified);

		SIV3D_NODISCARD_CXX20
		explicit Image(IReader&& reader, ImageFormat format = ImageFormat::Unspecified);

		SIV3D_NODISCARD_CXX20
		Image(FilePathView rgb, FilePathView alpha);

		SIV3D_NODISCARD_CXX20
		Image(Color rgb, FilePathView alpha);

		SIV3D_NODISCARD_CXX20
		explicit Image(const Emoji& emoji);

		SIV3D_NODISCARD_CXX20
		explicit Image(const Icon& icon, int32 size);

		SIV3D_NODISCARD_CXX20
		explicit Image(const Grid<Color>& grid);

		SIV3D_NODISCARD_CXX20
		explicit Image(const Grid<ColorF>& grid);

		template <class Type, class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty, Type>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit Image(const Grid<Type>& grid, Fty converter);

		Image& operator =(const Image&) = default;

		Image& operator =(Image && image) noexcept;

		/// @brief 画像の幅（ピクセル）を返します。
		/// @return 画像の幅（ピクセル）
		[[nodiscard]]
		int32 width() const noexcept;

		/// @brief 画像の高さ（ピクセル）を返します。
		/// @return 画像の高さ（ピクセル）
		[[nodiscard]]
		int32 height() const noexcept;

		/// @brief 画像の幅と高さ（ピクセル）を返します。
		/// @return 画像の幅と高さ（ピクセル）		
		[[nodiscard]]
		Size size() const noexcept;

		/// @brief 画像の各行のサイズ（バイト）を返します。
		/// @remark `(width() * sizeof(Color))` です。
		/// @return 画像の各行のサイズ（バイト）
		[[nodiscard]]
		uint32 stride() const noexcept;

		/// @brief 画像の総ピクセル数を返します。
		/// @remark `(width() * height())` です。
		/// @return 画像の総ピクセル数
		[[nodiscard]]
		uint32 num_pixels() const noexcept;

		/// @brief 画像のデータサイズ（バイト）を返します。
		/// @remark `(stride() * height())` です。
		/// @return 画像のデータサイズ（バイト）
		[[nodiscard]]
		size_t size_bytes() const noexcept;

		/// @brief 画像が空であるかを返します。
		/// @return 画像が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief 画像が空でないかを返します。
		/// @return 画像が空でない場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		template <class Type = double>
		[[nodiscard]]
		Type horizontalAspectRatio() const noexcept;

		/// @brief 使用するメモリ量を現在のサイズまで切り詰めます。
		void shrink_to_fit();

		/// @brief 画像を消去し、空の画像にします。
		/// @remark メモリを解放したい場合は、さらに shrink_to_fit() を呼びます。
		void clear() noexcept;

		/// @brief 画像を消去して空の画像にし、使用するメモリ量を切り詰めます。
		/// @remark `clear()` + `shrink_to_fit()` と同じです。
		void release();

		/// @brief 画像を別の画像と交換します。
		/// @param image 交換する画像
		void swap(Image& image) noexcept;

		/// @brief 内容をコピーした新しい画像を作成して返します。
		/// @return 内容をコピーした新しい画像
		[[nodiscard]]
		Image cloned() const;

		/// @brief 指定した行の先頭ポインタを返します。
		/// @param y 位置（行）
		/// @remark image[y][x] で指定したピクセルにアクセスします。
		/// @return 指定した行の先頭ポインタ
		[[nodiscard]]
		Color* operator [](size_t y);

		/// @brief 指定した位置のピクセルの参照を返します。
		/// @param pos 位置
		/// @return 指定した位置のピクセルの参照
		[[nodiscard]]
		Color& operator [](Point pos);

		/// @brief 指定した行の先頭ポインタを返します。
		/// @param y 位置（行）
		/// @remark image[y][x] で指定したピクセルにアクセスします。
		/// @return 指定した行の先頭ポインタ
		[[nodiscard]]
		const Color* operator [](size_t y) const;

		/// @brief 指定した位置のピクセルの参照を返します。
		/// @param pos 位置
		/// @return 指定した位置のピクセルの参照
		[[nodiscard]]
		const Color& operator [](Point pos) const;

		/// @brief 画像データの先頭のポインタを返します。
		/// @return 画像データの先頭のポインタ
		[[nodiscard]]
		Color* data();

		/// @brief 画像データの先頭のポインタを返します。
		/// @return 画像データの先頭のポインタ
		[[nodiscard]]
		const Color* data() const;

		/// @brief 画像データの先頭のポインタを uint8* 型で返します。
		/// @return 画像データの先頭のポインタ
		[[nodiscard]]
		uint8* dataAsUint8();

		/// @brief 画像データの先頭のポインタを uint8* 型で返します。
		/// @return 画像データの先頭のポインタ
		[[nodiscard]]
		const uint8* dataAsUint8() const;

		[[nodiscard]]
		const Array<Color>& asArray() const&;

		[[nodiscard]]
		Array<Color> asArray()&&;

		[[nodiscard]]
		iterator begin() noexcept;

		[[nodiscard]]
		iterator end() noexcept;

		[[nodiscard]]
		const_iterator begin() const noexcept;

		[[nodiscard]]
		const_iterator end() const noexcept;

		[[nodiscard]]
		const_iterator cbegin() const noexcept;

		[[nodiscard]]
		const_iterator cend() const noexcept;

		[[nodiscard]]
		reverse_iterator rbegin() noexcept;

		[[nodiscard]]
		reverse_iterator rend() noexcept;

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept;

		/// @brief 画像を指定した色で塗りつぶします。
		/// @param color 塗りつぶしの色
		void fill(Color color) noexcept;

		void resize(size_t width, size_t height);

		void resize(Size size);

		void resize(size_t width, size_t height, Color fillColor);

		void resize(Size size, Color fillColor);

		void resizeRows(size_t rows, Color fillColor);

		[[nodiscard]]
		Color getPixel(int32 x, int32 y, ImageAddressMode addressMode) const;

		[[nodiscard]]
		Color getPixel(Point pos, ImageAddressMode addressMode) const;

		[[nodiscard]]
		ColorF samplePixel(double x, double y, ImageAddressMode addressMode) const;

		[[nodiscard]]
		ColorF samplePixel(Vec2 pos, ImageAddressMode addressMode) const;

		[[nodiscard]]
		Image clipped(const Rect& rect) const;

		[[nodiscard]]
		Image clipped(int32 x, int32 y, int32 w, int32 h) const;

		[[nodiscard]]
		Image clipped(const Point& pos, int32 w, int32 h) const;

		[[nodiscard]]
		Image clipped(int32 x, int32 y, const Size& size) const;

		[[nodiscard]]
		Image clipped(const Point& pos, const Size& size) const;

		[[nodiscard]]
		Image squareClipped() const;

		template <class Fty>
		Image& forEach(Fty f);

		template <class Fty>
		const Image& forEach(Fty f) const;

		/// @brief 画像の R 成分と B 成分を入れ替えます。
		/// @return *this
		Image& RGBAtoBGRA();

		bool applyAlphaFromRChannel(FilePathView alpha);

		/// @brief 画像をファイルに保存します。
		/// @param path 保存するファイルパス
		/// @param format 保存時のフォーマット。`ImageFormat::Unspecified` の場合拡張子から判断
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(FilePathView path, ImageFormat format = ImageFormat::Unspecified) const;

		[[nodiscard]]
		Blob encode(ImageFormat format) const;

		bool saveWithDialog() const;

		bool savePNG(FilePathView path, PNGFilter filter = PNGEncoder::DefaultFilter) const;

		[[nodiscard]]
		Blob encodePNG(PNGFilter filter = PNGEncoder::DefaultFilter) const;

		bool saveJPEG(FilePathView path, int32 quality = JPEGEncoder::DefaultQuality) const;

		[[nodiscard]]
		Blob encodeJPEG(int32 quality = JPEGEncoder::DefaultQuality) const;

		bool savePPM(FilePathView path, PPMType format = PPMEncoder::DefaultFromat) const;

		[[nodiscard]]
		Blob encodePPM(PPMType format = PPMEncoder::DefaultFromat) const;

		bool saveWebP(FilePathView path, Lossless lossless = Lossless::No, double quality = WebPEncoder::DefaultQuality, WebPMethod method = WebPMethod::Default) const;

		[[nodiscard]]
		Blob encodeWebP(Lossless lossless = Lossless::No, double quality = WebPEncoder::DefaultQuality, WebPMethod method = WebPMethod::Default) const;

		/// @brief 画像の色を反転します。
		/// @return *this
		Image& negate();

		[[nodiscard]]
		Image negated() const;

		/// @brief 画像をグレイスケール画像に変換します。
		/// @return *this
		Image& grayscale();

		[[nodiscard]]
		Image grayscaled() const;

		/// @brief 画像をセピア画像に変換します。
		/// @return *this
		Image& sepia();

		[[nodiscard]]
		Image sepiaed() const;

		Image& posterize(int32 level);

		[[nodiscard]]
		Image posterized(int32 level) const;

		Image& brighten(int32 level);

		[[nodiscard]]
		Image brightened(int32 level) const;

		/// @brief 画像を左右反転します。
		/// @return *this
		Image& mirror();

		[[nodiscard]]
		Image mirrored() const;

		/// @brief 画像を上下反転します。
		/// @return *this
		Image& flip();

		[[nodiscard]]
		Image flipped() const;

		/// @brief 画像を時計回りに 90° 回転します。
		/// @return *this
		Image& rotate90();

		[[nodiscard]]
		Image rotated90() const;

		/// @brief 画像を時計回りに 180° 回転します。
		/// @return *this
		Image& rotate180();

		[[nodiscard]]
		Image rotated180() const;

		/// @brief 画像を時計回りに 270° 回転します。
		/// @return *this
		Image& rotate270();

		[[nodiscard]]
		Image rotated270() const;

		Image& gammaCorrect(double gamma);

		[[nodiscard]]
		Image gammaCorrected(double gamma) const;

		Image& threshold(uint8 threshold, InvertColor invertColor = InvertColor::No);

		[[nodiscard]]
		Image thresholded(uint8 threshold, InvertColor invertColor = InvertColor::No) const;

		Image& threshold_Otsu(InvertColor invertColor = InvertColor::No);

		[[nodiscard]]
		Image thresholded_Otsu(InvertColor invertColor = InvertColor::No) const;

		Image& adaptiveThreshold(AdaptiveThresholdMethod method, int32 blockSize, double c, InvertColor invertColor = InvertColor::No);

		[[nodiscard]]
		Image adaptiveThresholded(AdaptiveThresholdMethod method, int32 blockSize, double c, InvertColor invertColor = InvertColor::No) const;

		Image& mosaic(int32 size);

		Image& mosaic(int32 horizontal, int32 vertical);

		[[nodiscard]]
		Image mosaiced(int32 size) const;

		[[nodiscard]]
		Image mosaiced(int32 horizontal, int32 vertical) const;

		Image& spread(int32 size);

		Image& spread(int32 horizontal, int32 vertical);

		[[nodiscard]]
		Image spreaded(int32 size) const;

		[[nodiscard]]
		Image spreaded(int32 horizontal, int32 vertical) const;

		Image& blur(int32 size, BorderType borderType = BorderType::Reflect_101);

		Image& blur(int32 horizontal, int32 vertical, BorderType borderType = BorderType::Reflect_101);

		[[nodiscard]]
		Image blurred(int32 size, BorderType borderType = BorderType::Reflect_101) const;

		[[nodiscard]]
		Image blurred(int32 horizontal, int32 vertical, BorderType borderType = BorderType::Reflect_101) const;

		Image& medianBlur(int32 apertureSize);

		[[nodiscard]]
		Image medianBlurred(int32 apertureSize) const;

		Image& gaussianBlur(int32 size, BorderType borderType = BorderType::Reflect_101);

		Image& gaussianBlur(int32 horizontal, int32 vertical, BorderType borderType = BorderType::Reflect_101);

		[[nodiscard]]
		Image gaussianBlurred(int32 size, BorderType borderType = BorderType::Reflect_101) const;

		[[nodiscard]]
		Image gaussianBlurred(int32 horizontal, int32 vertical, BorderType borderType = BorderType::Reflect_101) const;

		Image& bilateralFilter(int32 d, double sigmaColor, double sigmaSpace, BorderType borderType = BorderType::Reflect_101);

		[[nodiscard]]
		Image bilateralFiltered(int32 d, double sigmaColor, double sigmaSpace, BorderType borderType = BorderType::Reflect_101) const;

		Image& dilate(int32 iterations = 1);

		[[nodiscard]]
		Image dilated(int32 iterations = 1) const;

		Image& erode(int32 iterations = 1);

		[[nodiscard]]
		Image eroded(int32 iterations = 1) const;

		Image& floodFill(const Point& pos, const Color& color, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0);

		[[nodiscard]]
		Image floodFilled(const Point& pos, const Color& color, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0) const;

		Image& scale(int32 width, int32 height, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto);

		[[nodiscard]]
		Image scaled(int32 width, int32 height, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const;

		Image& scale(const Size& size, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto);

		[[nodiscard]]
		Image scaled(const Size& size, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const;

		Image& scale(double scaling, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto);

		[[nodiscard]]
		Image scaled(double scaling, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const;

		Image& fit(int32 width, int32 height, AllowScaleUp allowScaleUp = AllowScaleUp::Yes, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto);

		[[nodiscard]]
		Image fitted(int32 width, int32 height, AllowScaleUp allowScaleUp = AllowScaleUp::Yes, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const;

		Image& fit(const Size& size, AllowScaleUp allowScaleUp = AllowScaleUp::Yes, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto);

		[[nodiscard]]
		Image fitted(const Size& size, AllowScaleUp allowScaleUp = AllowScaleUp::Yes, InterpolationAlgorithm interpolation = InterpolationAlgorithm::Auto) const;

		Image& border(int32 thickness, const Color& color = Palette::White);

		[[nodiscard]]
		Image bordered(int32 thickness, const Color& color = Palette::White) const;

		Image& border(int32 top, int32 right, int32 bottom, int32 left, const Color& color = Palette::White);

		[[nodiscard]]
		Image bordered(int32 top, int32 right, int32 bottom, int32 left, const Color& color = Palette::White) const;

		[[nodiscard]]
		Image warpAffine(const Mat3x2& mat, const Color& background = Color{ 0, 0 }) const;

		[[nodiscard]]
		Image rotated(double angle, const Color& background = Color{ 0, 0 }) const;

		[[nodiscard]]
		Image warpPerspective(const Quad& quad, const Color& background = Color{ 0, 0 }) const;

		void paint(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void paint(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void stamp(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void stamp(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void overwrite(Image& dst, int32 x, int32 y) const;

		void overwrite(Image& dst, Point pos) const;

		void paintAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void paintAt(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void stampAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void stampAt(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void overwriteAt(Image& dst, int32 x, int32 y) const;

		void overwriteAt(Image& dst, Point pos) const;

		[[nodiscard]]
		ImageROI operator ()(int32 x, int32 y, int32 w, int32 h);

		[[nodiscard]]
		ImageROI operator ()(const Point& pos, int32 w, int32 h);

		[[nodiscard]]
		ImageROI operator ()(int32 x, int32 y, const Size& size);

		[[nodiscard]]
		ImageROI operator ()(const Point& pos, const Size& size);

		[[nodiscard]]
		ImageROI operator ()(const Rect& rect);

		[[nodiscard]]
		ImageConstROI operator ()(int32 x, int32 y, int32 w, int32 h) const;

		[[nodiscard]]
		ImageConstROI operator ()(const Point& pos, int32 w, int32 h) const;

		[[nodiscard]]
		ImageConstROI operator ()(int32 x, int32 y, const Size& size) const;

		[[nodiscard]]
		ImageConstROI operator ()(const Point& pos, const Size& size) const;

		[[nodiscard]]
		ImageConstROI operator ()(const Rect& rect) const;

		[[nodiscard]]
		Polygon alphaToPolygon(uint32 threshold = 160, AllowHoles allowHoles = AllowHoles::Yes) const;

		[[nodiscard]]
		Polygon alphaToPolygonCentered(uint32 threshold = 160, AllowHoles allowHoles = AllowHoles::Yes) const;

		[[nodiscard]]
		MultiPolygon alphaToPolygons(uint32 threshold = 160, AllowHoles allowHoles = AllowHoles::Yes) const;

		[[nodiscard]]
		MultiPolygon alphaToPolygonsCentered(uint32 threshold = 160, AllowHoles allowHoles = AllowHoles::Yes) const;

		[[nodiscard]]
		Polygon grayscaleToPolygon(uint32 threshold = 160, AllowHoles allowHoles = AllowHoles::Yes) const;

		[[nodiscard]]
		Polygon grayscaleToPolygonCentered(uint32 threshold = 160, AllowHoles allowHoles = AllowHoles::Yes) const;

		[[nodiscard]]
		MultiPolygon grayscaleToPolygons(uint32 threshold = 160, AllowHoles allowHoles = AllowHoles::Yes) const;

		[[nodiscard]]
		MultiPolygon grayscaleToPolygonsCentered(uint32 threshold = 160, AllowHoles allowHoles = AllowHoles::Yes) const;

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>* = nullptr>
		static Image Generate(Size size, Fty generator);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>* = nullptr>
		static Image Generate0_1(Size size, Fty generator);
	
	private:

		base_type m_data;

		uint32 m_width = 0;

		uint32 m_height = 0;
	};

	inline void swap(Image& a, Image& b) noexcept;
}

template <>
inline void std::swap(s3d::Image& a, s3d::Image& b) noexcept;

# include "detail/Image.ipp"
