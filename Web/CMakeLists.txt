cmake_minimum_required(VERSION 3.5)

project(Siv6 CXX)
enable_language(C)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-missing-field-initializers")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -DMUPARSER_STATIC -D_UNICODE")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

add_library(
  Siv3D STATIC
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Siv3DMain.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Common/OpenGL.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Cursor/CCursor.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/FileSystem/SivFileSystem_Platform.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer/GLES3/CRenderer_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer/RendererFactory.cpp

  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer2D/Renderer2DFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Resource/CResource.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Resource/SivResource_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/System/CSystem.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Time/SivTime.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Window/CWindow.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Window/WindowFactory.cpp

  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/BinaryReader/BinaryReaderDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/BinaryWriter/BinaryWriterDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Console/CConsole.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Date/SivDate_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/DateTime/SivDateTime_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/EnvironmentVariable/SivEnvironmentVariable.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Logger/CLogger.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/System/SivSystem_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Unicode/SivUnicode_macOS_Linux.cpp

  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer2D/GLES3/CRenderer2D_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer2D/GLES3/Vertex2DBatch_GLES3.cpp

  ../Siv3D/src/Siv3D/ApplicationOptions/SivApplicationOptions.cpp
  # ../Siv3D/src/Siv3D/BigFloat/SivBigFloat.cpp
  # ../Siv3D/src/Siv3D/BigInt/SivBigInt.cpp
  ../Siv3D/src/Siv3D/Blob/SivBlob.cpp
  ../Siv3D/src/Siv3D/Byte/SivByte.cpp
  ../Siv3D/src/Siv3D/BinaryReader/SivBinaryReader.cpp
  ../Siv3D/src/Siv3D/BinaryWriter/SivBinaryWriter.cpp
  ../Siv3D/src/Siv3D/Color/SivColor.cpp
  ../Siv3D/src/Siv3D/Common/Siv3DEngine.cpp
  ../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp
  ../Siv3D/src/Siv3D/Console/SivConsole.cpp
  ../Siv3D/src/Siv3D/Cursor/CCursor_Null.cpp
  ../Siv3D/src/Siv3D/Cursor/CursorFactory.cpp
  ../Siv3D/src/Siv3D/Cursor/SivCursor.cpp
  # ../Siv3D/src/Siv3D/CPUInfo/SivCPUInfo.cpp
  ../Siv3D/src/Siv3D/DateTime/SivDateTime.cpp
  ../Siv3D/src/Siv3D/Dummy/CDummy.cpp
  ../Siv3D/src/Siv3D/Dummy/DummyFactory.cpp
  ../Siv3D/src/Siv3D/Duration/SivDuration.cpp
  ../Siv3D/src/Siv3D/EngineLog/SivEngineLog.cpp
  ../Siv3D/src/Siv3D/Error/SivError.cpp
  ../Siv3D/src/Siv3D/FileSystem/SivFileSystem.cpp
  ../Siv3D/src/Siv3D/FormatFloat/SivFormatFloat.cpp
  ../Siv3D/src/Siv3D/FormatInt/SivFormatInt.cpp
  ../Siv3D/src/Siv3D/Formatter/SivFormatter.cpp
  ../Siv3D/src/Siv3D/FormatUtility/SivFormatUtility.cpp
  ../Siv3D/src/Siv3D/Hash/SivHash.cpp
  ../Siv3D/src/Siv3D/Image/SivImage.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/CImageDecoder.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/ImageDecoderFactory.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/SivImageDecoder.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/CImageEncoder.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/ImageEncoderFactory.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/SivImageEncoder.cpp 
  ../Siv3D/src/Siv3D/ImageFormat/BMPDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/BMPEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PNGDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PNGEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/SVGDecoder.cpp
  ../Siv3D/src/Siv3D/INIData/SivINIData.cpp
  ../Siv3D/src/Siv3D/Int128/SivInt128.cpp
  ../Siv3D/src/Siv3D/IntFormatter/SivIntFormatter.cpp
  ../Siv3D/src/Siv3D/LicenseManager/CLicenseManager.cpp
  ../Siv3D/src/Siv3D/LicenseManager/LicenseManagerFactory.cpp
  ../Siv3D/src/Siv3D/LicenseManager/SivLicenseManager.cpp
  ../Siv3D/src/Siv3D/Logger/LoggerFactory.cpp
  ../Siv3D/src/Siv3D/Logger/SivLogger.cpp
  ../Siv3D/src/Siv3D/MathParser/MathParserDetail.cpp
  ../Siv3D/src/Siv3D/MathParser/SivMathParser.cpp
  ../Siv3D/src/Siv3D/Point/SivPoint.cpp
  # ../Siv3D/src/Siv3D/PrimeNumber/SivPrimeNumber.cpp
  ../Siv3D/src/Siv3D/Profiler/CProfiler.cpp
  ../Siv3D/src/Siv3D/Profiler/ProfilerFactory.cpp
  ../Siv3D/src/Siv3D/Profiler/SivProfiler.cpp
  ../Siv3D/src/Siv3D/QR/SivQR.cpp
  ../Siv3D/src/Siv3D/Random/SivRandom.cpp
  ../Siv3D/src/Siv3D/Rectangle/SivRectangle.cpp
  ../Siv3D/src/Siv3D/RegExp/RegExpDetail.cpp
  ../Siv3D/src/Siv3D/RegExp/SivRegExp.cpp
  ../Siv3D/src/Siv3D/Renderer/Null/CRenderer_Null.cpp
  ../Siv3D/src/Siv3D/Renderer2D/Null/CRenderer2D_Null.cpp
  ../Siv3D/src/Siv3D/Resource/ResourceFactory.cpp
  ../Siv3D/src/Siv3D/Resource/SivResource.cpp
  ../Siv3D/src/Siv3D/Scene/CScene.cpp
  ../Siv3D/src/Siv3D/Scene/SceneFactory.cpp
  ../Siv3D/src/Siv3D/Scene/SivScene.cpp
  ../Siv3D/src/Siv3D/String/SivString.cpp
  # ../Siv3D/src/Siv3D/String/Levenshtein.cpp
  ../Siv3D/src/Siv3D/StringView/SivStringView.cpp
  ../Siv3D/src/Siv3D/System/SivSystem.cpp
  ../Siv3D/src/Siv3D/System/SystemFactory.cpp
  ../Siv3D/src/Siv3D/System/SystemLog.cpp
  ../Siv3D/src/Siv3D/System/SystemMisc.cpp
  ../Siv3D/src/Siv3D/TextEncoding/SivTextEncoding.cpp
  ../Siv3D/src/Siv3D/TextReader/SivTextReader.cpp
  ../Siv3D/src/Siv3D/TextReader/TextReaderDetail.cpp
  ../Siv3D/src/Siv3D/TextWriter/SivTextWriter.cpp
  ../Siv3D/src/Siv3D/TextWriter/TextWriterDetail.cpp  
  ../Siv3D/src/Siv3D/Threading/SivThreading.cpp
  ../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp
  ../Siv3D/src/Siv3D/UnicodeConverter/SivUnicodeConverter.cpp
  ../Siv3D/src/Siv3D/Unicode/UnicodeUtility.cpp
  ../Siv3D/src/Siv3D/UserAction/CUserAction.cpp
  ../Siv3D/src/Siv3D/UserAction/UserActionFactory.cpp
  ../Siv3D/src/Siv3D/Vector2D/SivVector2D.cpp
  ../Siv3D/src/Siv3D/Vector3D/SivVector3D.cpp
  ../Siv3D/src/Siv3D/Vector4D/SivVector4D.cpp
  ../Siv3D/src/Siv3D/Window/SivWindow.cpp
  ../Siv3D/src/Siv3D/Window/Null/CWindow_Null.cpp

  ../Siv3D/src/ThirdParty/absl/numeric/int128.cc

  ../Siv3D/src/ThirdParty/agg/agg_arc.cpp
  ../Siv3D/src/ThirdParty/agg/agg_arrowhead.cpp
  ../Siv3D/src/ThirdParty/agg/agg_bezier_arc.cpp
  ../Siv3D/src/ThirdParty/agg/agg_bspline.cpp
  ../Siv3D/src/ThirdParty/agg/agg_color_rgba.cpp
  ../Siv3D/src/ThirdParty/agg/agg_curves.cpp
  ../Siv3D/src/ThirdParty/agg/agg_embedded_raster_fonts.cpp
  ../Siv3D/src/ThirdParty/agg/agg_gsv_text.cpp
  ../Siv3D/src/ThirdParty/agg/agg_image_filters.cpp
  ../Siv3D/src/ThirdParty/agg/agg_line_aa_basics.cpp
  ../Siv3D/src/ThirdParty/agg/agg_line_profile_aa.cpp
  ../Siv3D/src/ThirdParty/agg/agg_rounded_rect.cpp
  ../Siv3D/src/ThirdParty/agg/agg_sqrt_tables.cpp
  ../Siv3D/src/ThirdParty/agg/agg_trans_affine.cpp
  ../Siv3D/src/ThirdParty/agg/agg_trans_double_path.cpp
  ../Siv3D/src/ThirdParty/agg/agg_trans_single_path.cpp
  ../Siv3D/src/ThirdParty/agg/agg_trans_warp_magnifier.cpp
  ../Siv3D/src/ThirdParty/agg/agg_vcgen_bspline.cpp
  ../Siv3D/src/ThirdParty/agg/agg_vcgen_contour.cpp
  ../Siv3D/src/ThirdParty/agg/agg_vcgen_dash.cpp
  ../Siv3D/src/ThirdParty/agg/agg_vcgen_markers_term.cpp
  ../Siv3D/src/ThirdParty/agg/agg_vcgen_smooth_poly1.cpp
  ../Siv3D/src/ThirdParty/agg/agg_vcgen_stroke.cpp
  ../Siv3D/src/ThirdParty/agg/agg_vpgen_clip_polygon.cpp
  ../Siv3D/src/ThirdParty/agg/agg_vpgen_clip_polyline.cpp
  ../Siv3D/src/ThirdParty/agg/agg_vpgen_segmentator.cpp
  
  # ../Siv3D/src/ThirdParty/cpu_features/cpuinfo_x86.c

  ../Siv3D/src/ThirdParty/double-conversion/bignum-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/bignum.cc
  ../Siv3D/src/ThirdParty/double-conversion/cached-powers.cc
  ../Siv3D/src/ThirdParty/double-conversion/double-to-string.cc
  ../Siv3D/src/ThirdParty/double-conversion/fast-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/fixed-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/string-to-double.cc
  ../Siv3D/src/ThirdParty/double-conversion/strtod.cc

  ../Siv3D/src/ThirdParty/fmt/format.cc
  
  ../Siv3D/src/ThirdParty/lunasvg/affinetransform.cpp
  ../Siv3D/src/ThirdParty/lunasvg/canvas.cpp
  ../Siv3D/src/ThirdParty/lunasvg/canvasimpl.cpp
  ../Siv3D/src/ThirdParty/lunasvg/cssproperty.cpp
  ../Siv3D/src/ThirdParty/lunasvg/flatteningpathiterator.cpp
  ../Siv3D/src/ThirdParty/lunasvg/gradient.cpp
  ../Siv3D/src/ThirdParty/lunasvg/paint.cpp
  ../Siv3D/src/ThirdParty/lunasvg/path.cpp
  ../Siv3D/src/ThirdParty/lunasvg/pathiterator.cpp
  ../Siv3D/src/ThirdParty/lunasvg/pathutils.cpp
  ../Siv3D/src/ThirdParty/lunasvg/pattern.cpp
  ../Siv3D/src/ThirdParty/lunasvg/rendercontext.cpp
  ../Siv3D/src/ThirdParty/lunasvg/rgb.cpp
  ../Siv3D/src/ThirdParty/lunasvg/strokedata.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgcircleelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgclippathelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgcolor.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgdefselement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgdocument.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgdocumentimpl.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelementhead.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelementimpl.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelementiter.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelementtail.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelementtext.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelementutils.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgellipseelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgenumeration.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgfittoviewbox.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svggelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svggeometryelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svggradientelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svggraphicselement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svglength.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svglengthlist.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svglineargradientelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svglineelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgmaskelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgnumber.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgnumberlist.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpaintelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgparser.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpath.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpathelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpatternelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpoint.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpointlist.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpolyelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpolygonelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpolylineelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpreserveaspectratio.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgproperty.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpropertyutils.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgradialgradientelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgrect.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgrectelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgrootelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgsolidcolorelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgstopelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgstring.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgstringlist.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgstyledelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgsvgelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgsymbolelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgtransform.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgurireference.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svguseelement.cpp

  ../Siv3D/src/ThirdParty/muparser/muParser.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserBase.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserBytecode.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserCallback.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserDLL.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserError.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserInt.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserTest.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserTokenReader.cpp
  
  ../Siv3D/src/ThirdParty/Oniguruma/ascii.c
  ../Siv3D/src/ThirdParty/Oniguruma/big5.c
  ../Siv3D/src/ThirdParty/Oniguruma/cp1251.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_jp.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_jp_prop.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_kr.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_tw.c
  ../Siv3D/src/ThirdParty/Oniguruma/gb18030.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_1.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_10.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_11.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_13.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_14.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_15.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_16.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_2.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_3.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_4.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_5.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_6.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_7.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_8.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_9.c
  ../Siv3D/src/ThirdParty/Oniguruma/koi8.c
  ../Siv3D/src/ThirdParty/Oniguruma/koi8_r.c
  ../Siv3D/src/ThirdParty/Oniguruma/onig_init.c
  ../Siv3D/src/ThirdParty/Oniguruma/regcomp.c
  ../Siv3D/src/ThirdParty/Oniguruma/regenc.c
  ../Siv3D/src/ThirdParty/Oniguruma/regerror.c
  ../Siv3D/src/ThirdParty/Oniguruma/regexec.c
  ../Siv3D/src/ThirdParty/Oniguruma/reggnu.c
  ../Siv3D/src/ThirdParty/Oniguruma/regparse.c
  ../Siv3D/src/ThirdParty/Oniguruma/regsyntax.c
  ../Siv3D/src/ThirdParty/Oniguruma/regtrav.c
  ../Siv3D/src/ThirdParty/Oniguruma/regversion.c
  ../Siv3D/src/ThirdParty/Oniguruma/sjis.c
  ../Siv3D/src/ThirdParty/Oniguruma/sjis_prop.c
  ../Siv3D/src/ThirdParty/Oniguruma/st.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_fold1_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_fold2_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_fold3_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_unfold_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf16_be.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf16_le.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf32_be.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf32_le.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf8.c

  ../Siv3D/src/ThirdParty/qr-code-generator-library/QrCode.cpp

  ../Siv3D/src/ThirdParty/xxHash/xxhash.c
  )

target_include_directories(
  Siv3D
  PUBLIC
  ../Siv3D/include
  ../Siv3D/include/ThirdParty
  ../Siv3D/src
  ../Siv3D/src/Siv3D-Platform/macOS_Linux
  ../Siv3D/src/Siv3D-Platform/Web
  ../Siv3D/src/Siv3D-Platform/OpenGLES3
  ../Siv3D/src/ThirdParty
  ${LIBSIV3D_INCLUDE_DIRS}
  )
