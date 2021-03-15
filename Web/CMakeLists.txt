cmake_minimum_required(VERSION 3.5)

project(OpenSiv3D_Web CXX C)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-missing-field-initializers")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -DMUPARSER_STATIC -D_UNICODE")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

if (NOT CMAKE_CONFIGURATION_TYPES AND 
    NOT CMAKE_NO_BUILD_TYPE AND
    NOT CMAKE_BUILD_TYPE AND
    CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "[!] Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options ("-fcolor-diagnostics")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options ("-fdiagnostics-color=always")
endif()


add_library(
  OpenSiv3D_Web STATIC
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Siv3DMain.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Common/OpenGL.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/ConstantBuffer/ConstantBufferDetailFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Cursor/CCursor.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/DirectoryWatcher/DirectoryWatcherDetail.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/FileSystem/SivFileSystem_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/FreestandingMessageBox/FreestandingMessageBox_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Monitor/SivMonitor_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer/GLES3/CRenderer_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer/RendererFactory.cpp

  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer2D/Renderer2DFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Resource/CResource.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Resource/SivResource_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Shader/ShaderFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/System/CSystem.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/System/SivSystem_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Texture/TextureFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Time/SivTime.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Window/CWindow.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Window/WindowFactory.cpp

  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/BinaryReader/BinaryReaderDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/BinaryWriter/BinaryWriterDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Console/CConsole.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Date/SivDate_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/DateTime/SivDateTime_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/EnvironmentVariable/SivEnvironmentVariable.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Keyboard/CKeyboard.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Logger/CLogger.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Monitor/SivMonitor_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Mouse/CMouse.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/System/SivSystem_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Unicode/SivUnicode_macOS_Linux.cpp

  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/BackBuffer/GLES3BackBuffer.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/BackBuffer/GLES3InternalTexture2D.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/BlendState/GLES3BlendState.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/RasterizerState/GLES3RasterizerState.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/SamplerState/GLES3SamplerState.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/ConstantBuffer/GLES3/ConstantBufferDetail_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer2D/GLES3/CRenderer2D_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer2D/GLES3/GLES3Renderer2DCommand.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer2D/GLES3/GLES3Vertex2DBatch.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Shader/GLES3/CShader_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Shader/GLES3/PixelShader/GLES3PixelShader.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Shader/GLES3/VertexShader/GLES3VertexShader.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Shader/GLES3/ShaderPipeline/GLES3ShaderPipeline.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Texture/GLES3/CTexture_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Texture/GLES3/GLES3Texture.cpp

  ../Siv3D/src/Siv3D/Addon/AddonFactory.cpp
  ../Siv3D/src/Siv3D/Addon/CAddon.cpp
  ../Siv3D/src/Siv3D/Addon/SivAddon.cpp
  ../Siv3D/src/Siv3D/ApplicationOptions/SivApplicationOptions.cpp
  ../Siv3D/src/Siv3D/AssetMonitor/AssetMonitorFactory.cpp
  ../Siv3D/src/Siv3D/AssetMonitor/CAssetMonitor.cpp
  ../Siv3D/src/Siv3D/Base64/SivBase64.cpp
  ../Siv3D/src/Siv3D/Bezier2/SivBezier2.cpp
  ../Siv3D/src/Siv3D/Bezier3/SivBezier3.cpp
  ../Siv3D/src/Siv3D/BigFloat/SivBigFloat.cpp
  ../Siv3D/src/Siv3D/BigInt/SivBigInt.cpp
  ../Siv3D/src/Siv3D/BinaryReader/SivBinaryReader.cpp
  ../Siv3D/src/Siv3D/BinaryWriter/SivBinaryWriter.cpp
  ../Siv3D/src/Siv3D/Blob/SivBlob.cpp
  ../Siv3D/src/Siv3D/Buffer2D/SivBuffer2D.cpp
  ../Siv3D/src/Siv3D/Byte/SivByte.cpp
  ../Siv3D/src/Siv3D/CacheDirectory/CacheDirectory.cpp
  ../Siv3D/src/Siv3D/Camera2D/SivCamera2D.cpp
  ../Siv3D/src/Siv3D/Circle/SivCircle.cpp
  ../Siv3D/src/Siv3D/Color/SivColor.cpp
  ../Siv3D/src/Siv3D/Colormap/SivColormap.cpp
  ../Siv3D/src/Siv3D/CommandLine/SivCommandLine.cpp
  ../Siv3D/src/Siv3D/Common/Siv3DEngine.cpp
  ../Siv3D/src/Siv3D/Compression/SivCompression.cpp
  ../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp
  ../Siv3D/src/Siv3D/Console/SivConsole.cpp
  ../Siv3D/src/Siv3D/ConstantBuffer/Null/ConstantBufferDetail_Null.cpp
  ../Siv3D/src/Siv3D/ConstantBuffer/SivConstantBuffer.cpp
  # ../Siv3D/src/Siv3D/CPUInfo/SivCPUInfo.cpp
  ../Siv3D/src/Siv3D/CSV/SivCSV.cpp
  ../Siv3D/src/Siv3D/Cursor/CCursor_Null.cpp
  ../Siv3D/src/Siv3D/Cursor/CursorFactory.cpp
  ../Siv3D/src/Siv3D/Cursor/SivCursor.cpp
  ../Siv3D/src/Siv3D/DateTime/SivDateTime.cpp
  ../Siv3D/src/Siv3D/DirectoryWatcher/SivDirectoryWatcher.cpp
  ../Siv3D/src/Siv3D/DrawableText/SivDrawableText.cpp
  ../Siv3D/src/Siv3D/Dummy/CDummy.cpp
  ../Siv3D/src/Siv3D/Dummy/DummyFactory.cpp
  ../Siv3D/src/Siv3D/Duration/SivDuration.cpp
  ../Siv3D/src/Siv3D/DynamicTexture/SivDynamicTexture.cpp
  ../Siv3D/src/Siv3D/Effect/CEffect.cpp
  ../Siv3D/src/Siv3D/Effect/EffectData.cpp
  ../Siv3D/src/Siv3D/Effect/EffectFactory.cpp
  ../Siv3D/src/Siv3D/Effect/SivEffect.cpp
  ../Siv3D/src/Siv3D/Ellipse/SivEllipse.cpp
  ../Siv3D/src/Siv3D/Emoji/SivEmoji.cpp
  ../Siv3D/src/Siv3D/EngineLog/SivEngineLog.cpp
  ../Siv3D/src/Siv3D/Error/SivError.cpp
  ../Siv3D/src/Siv3D/Exif/SivExif.cpp
  ../Siv3D/src/Siv3D/FileSystem/SivFileSystem.cpp
  ../Siv3D/src/Siv3D/Font/CFont.cpp
  ../Siv3D/src/Siv3D/Font/CFont_Headless.cpp
  ../Siv3D/src/Siv3D/Font/EmojiData.cpp
  ../Siv3D/src/Siv3D/Font/FontCommon.cpp
  ../Siv3D/src/Siv3D/Font/GlyphCache/BitmapGlyphCache.cpp
  ../Siv3D/src/Siv3D/Font/GlyphCache/GlyphCacheCommon.cpp
  ../Siv3D/src/Siv3D/Font/GlyphCache/MSDFGlyphCache.cpp
  ../Siv3D/src/Siv3D/Font/GlyphCache/SDFGlyphCache.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/agg/agg.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/GlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/BitmapGlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/MSDFGlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/OutlineGlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/SDFGlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/FontData.cpp
  ../Siv3D/src/Siv3D/Font/FontFace.cpp
  ../Siv3D/src/Siv3D/Font/FontFactory.cpp
  ../Siv3D/src/Siv3D/Font/IconData.cpp
  ../Siv3D/src/Siv3D/Font/SivFont.cpp
  ../Siv3D/src/Siv3D/FormatFloat/SivFormatFloat.cpp
  ../Siv3D/src/Siv3D/FormatInt/SivFormatInt.cpp
  ../Siv3D/src/Siv3D/Formatter/SivFormatter.cpp
  ../Siv3D/src/Siv3D/FormatUtility/SivFormatUtility.cpp
  ../Siv3D/src/Siv3D/Geometry2D/SivGeometry2D.cpp
  ../Siv3D/src/Siv3D/GrabCut/GrabCutDetail.cpp
  ../Siv3D/src/Siv3D/GrabCut/SivGrabCut.cpp
  ../Siv3D/src/Siv3D/Graphics2D/SivGraphics2D.cpp
  ../Siv3D/src/Siv3D/GUI/CGUI.cpp
  ../Siv3D/src/Siv3D/GUI/GUIFactory.cpp
  ../Siv3D/src/Siv3D/Hash/SivHash.cpp
  ../Siv3D/src/Siv3D/Icon/SivIcon.cpp
  ../Siv3D/src/Siv3D/Image/ImagePainting.cpp
  ../Siv3D/src/Siv3D/Image/ShapePainting.cpp
  ../Siv3D/src/Siv3D/Image/SivImage.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/CImageDecoder.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/ImageDecoderFactory.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/SivImageDecoder.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/CImageEncoder.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/ImageEncoderFactory.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/SivImageEncoder.cpp 
  ../Siv3D/src/Siv3D/ImageFormat/BMP/BMPDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/BMP/BMPEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/JPEG/JPEGDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/JPEG/JPEGEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PNG/PNGDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PNG/PNGEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/SVG/SVGDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/TGA/TGADecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/TGA/TGAEncoder.cpp
  ../Siv3D/src/Siv3D/ImageProcessing/SivImageProcessing.cpp
  ../Siv3D/src/Siv3D/ImageROI/SivImageROI.cpp
  ../Siv3D/src/Siv3D/INI/SivINI.cpp
  ../Siv3D/src/Siv3D/Input/InputState.cpp
  ../Siv3D/src/Siv3D/Input/SivInput.cpp
  ../Siv3D/src/Siv3D/InputCombination/SivInputCombination.cpp
  ../Siv3D/src/Siv3D/InputGroup/SivInputGroup.cpp
  ../Siv3D/src/Siv3D/Int128/SivInt128.cpp
  ../Siv3D/src/Siv3D/Interpolation/SivInterpolation.cpp
  ../Siv3D/src/Siv3D/IntFormatter/SivIntFormatter.cpp
  ../Siv3D/src/Siv3D/JSON/SivJSON.cpp
  ../Siv3D/src/Siv3D/Keyboard/KeyboardFactory.cpp
  ../Siv3D/src/Siv3D/Keyboard/SivKeyboard.cpp
  ../Siv3D/src/Siv3D/LicenseManager/CLicenseManager.cpp
  ../Siv3D/src/Siv3D/LicenseManager/LicenseManagerFactory.cpp
  ../Siv3D/src/Siv3D/LicenseManager/SivLicenseManager.cpp
  ../Siv3D/src/Siv3D/Line/SivLine.cpp
  ../Siv3D/src/Siv3D/LineString/SivLineString.cpp
  ../Siv3D/src/Siv3D/Logger/LoggerFactory.cpp
  ../Siv3D/src/Siv3D/Logger/SivLogger.cpp
  ../Siv3D/src/Siv3D/Mat3x3/SivMat3x3.cpp
  ../Siv3D/src/Siv3D/MathParser/MathParserDetail.cpp
  ../Siv3D/src/Siv3D/MathParser/SivMathParser.cpp
  ../Siv3D/src/Siv3D/MD5/SivMD5.cpp
  ../Siv3D/src/Siv3D/MD5Value/SivMD5Value.cpp
  ../Siv3D/src/Siv3D/Monitor/SivMonitor.cpp
  ../Siv3D/src/Siv3D/Mouse/MouseFactory.cpp
  ../Siv3D/src/Siv3D/Mouse/SivMouse.cpp
  ../Siv3D/src/Siv3D/MultiPolygon/SivMultiPolygon.cpp
  ../Siv3D/src/Siv3D/NavMesh/NavMeshDetail.cpp
  ../Siv3D/src/Siv3D/NavMesh/SivNavMesh.cpp
  ../Siv3D/src/Siv3D/OpenCV_Bridge/SivOpenCV_Bridge.cpp
  ../Siv3D/src/Siv3D/ParseBool/SivParseBool.cpp
  ../Siv3D/src/Siv3D/ParseFloat/SivParseFloat.cpp
  ../Siv3D/src/Siv3D/ParseInt/SivParseInt.cpp
  ../Siv3D/src/Siv3D/PixelShader/SivPixelShader.cpp
  ../Siv3D/src/Siv3D/Point/SivPoint.cpp
  ../Siv3D/src/Siv3D/Polygon/PolygonDetail.cpp
  ../Siv3D/src/Siv3D/Polygon/SivPolygon.cpp
  ../Siv3D/src/Siv3D/Polygon/Triangulation.cpp
  ../Siv3D/src/Siv3D/PrimeNumber/SivPrimeNumber.cpp
  ../Siv3D/src/Siv3D/Print/CPrint.cpp
  ../Siv3D/src/Siv3D/Print/PrintFactory.cpp
  ../Siv3D/src/Siv3D/Print/SivPrint.cpp
  ../Siv3D/src/Siv3D/Profiler/CProfiler.cpp
  ../Siv3D/src/Siv3D/Profiler/ProfilerFactory.cpp
  ../Siv3D/src/Siv3D/Profiler/SivProfiler.cpp
  ../Siv3D/src/Siv3D/PutText/SivPutText.cpp
  ../Siv3D/src/Siv3D/QR/SivQR.cpp
  ../Siv3D/src/Siv3D/Quad/SivQuad.cpp
  ../Siv3D/src/Siv3D/Random/SivRandom.cpp
  ../Siv3D/src/Siv3D/Rect/SivRect.cpp
  ../Siv3D/src/Siv3D/RectanglePacking/SivRectanglePacking.cpp
  ../Siv3D/src/Siv3D/RectF/SivRectF.cpp
  ../Siv3D/src/Siv3D/RegExp/RegExpDetail.cpp
  ../Siv3D/src/Siv3D/RegExp/SivRegExp.cpp
  ../Siv3D/src/Siv3D/Renderer/Null/CRenderer_Null.cpp
  ../Siv3D/src/Siv3D/Renderer2D/Null/CRenderer2D_Null.cpp
  ../Siv3D/src/Siv3D/Renderer2D/Vertex2DBuilder.cpp
  ../Siv3D/src/Siv3D/Resource/ResourceFactory.cpp
  ../Siv3D/src/Siv3D/Resource/SivResource.cpp
  ../Siv3D/src/Siv3D/RoundRect/SivRoundRect.cpp
  ../Siv3D/src/Siv3D/Scene/CScene.cpp
  ../Siv3D/src/Siv3D/Scene/FrameCounter.cpp
  ../Siv3D/src/Siv3D/Scene/FrameTimer.cpp
  ../Siv3D/src/Siv3D/Scene/SceneFactory.cpp
  ../Siv3D/src/Siv3D/Scene/SivScene.cpp
  ../Siv3D/src/Siv3D/ScreenCapture/CScreenCapture.cpp
  ../Siv3D/src/Siv3D/ScreenCapture/ScreenCaptureFactory.cpp
  ../Siv3D/src/Siv3D/ScreenCapture/SivScreenCapture.cpp
  ../Siv3D/src/Siv3D/SerialPortInfo/SivSerialPortInfo.cpp
  ../Siv3D/src/Siv3D/Serial/SerialDetail.cpp
  ../Siv3D/src/Siv3D/Serial/SivSerial.cpp
  ../Siv3D/src/Siv3D/Shader/Null/CShader_Null.cpp
  ../Siv3D/src/Siv3D/Shape2D/SivShape2D.cpp
  ../Siv3D/src/Siv3D/SimpleGUI/SivSimpleGUI.cpp
  ../Siv3D/src/Siv3D/Spline2D/SivSpline2D.cpp
  ../Siv3D/src/Siv3D/String/SivString.cpp
  # ../Siv3D/src/Siv3D/String/Levenshtein.cpp
  ../Siv3D/src/Siv3D/StringView/SivStringView.cpp
  ../Siv3D/src/Siv3D/Subdivision2D/SivSubdivision2D.cpp
  ../Siv3D/src/Siv3D/SVG/SivSVG.cpp
  ../Siv3D/src/Siv3D/SVG/SVGDetail.cpp
  ../Siv3D/src/Siv3D/System/SivSystem.cpp
  ../Siv3D/src/Siv3D/System/SystemFactory.cpp
  ../Siv3D/src/Siv3D/System/SystemLog.cpp
  ../Siv3D/src/Siv3D/System/SystemMisc.cpp
  ../Siv3D/src/Siv3D/TextEncoding/SivTextEncoding.cpp
  ../Siv3D/src/Siv3D/TextReader/SivTextReader.cpp
  ../Siv3D/src/Siv3D/TextReader/TextReaderDetail.cpp
  ../Siv3D/src/Siv3D/Texture/Null/CTexture_Null.cpp
  ../Siv3D/src/Siv3D/Texture/SivTexture.cpp
  ../Siv3D/src/Siv3D/Texture/TextureCommon.cpp
  ../Siv3D/src/Siv3D/TexturedCircle/SivTexturedCircle.cpp
  ../Siv3D/src/Siv3D/TexturedQuad/SivTexturedQuad.cpp
  ../Siv3D/src/Siv3D/TexturedRoundRect/SivTexturedRoundRect.cpp
  ../Siv3D/src/Siv3D/TextureFormat/SivTextureFormat.cpp
  ../Siv3D/src/Siv3D/TextureRegion/SivTextureRegion.cpp
  ../Siv3D/src/Siv3D/TextWriter/SivTextWriter.cpp
  ../Siv3D/src/Siv3D/TextWriter/TextWriterDetail.cpp  
  ../Siv3D/src/Siv3D/Threading/SivThreading.cpp
  ../Siv3D/src/Siv3D/Triangle/SivTriangle.cpp
  ../Siv3D/src/Siv3D/Twitter/SivTwitter.cpp
  ../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp
  ../Siv3D/src/Siv3D/Unicode/UnicodeUtility.cpp
  ../Siv3D/src/Siv3D/UnicodeConverter/SivUnicodeConverter.cpp
  ../Siv3D/src/Siv3D/UserAction/CUserAction.cpp
  ../Siv3D/src/Siv3D/UserAction/UserActionFactory.cpp
  ../Siv3D/src/Siv3D/Vector2D/SivVector2D.cpp
  ../Siv3D/src/Siv3D/Vector3D/SivVector3D.cpp
  ../Siv3D/src/Siv3D/Vector4D/SivVector4D.cpp
  ../Siv3D/src/Siv3D/VertexShader/SivVertexShader.cpp
  ../Siv3D/src/Siv3D/VideoReader/SivVideoReader.cpp
  ../Siv3D/src/Siv3D/VideoReader/VideoReaderDetail.cpp
  ../Siv3D/src/Siv3D/VideoWriter/SivVideoWriter.cpp
  ../Siv3D/src/Siv3D/VideoWriter/VideoWriterDetail.cpp
  ../Siv3D/src/Siv3D/VideoTexture/SivVideoTexture.cpp
  ../Siv3D/src/Siv3D/VideoTexture/VideoTextureDetail.cpp
  ../Siv3D/src/Siv3D/Window/SivWindow.cpp
  ../Siv3D/src/Siv3D/Window/Null/CWindow_Null.cpp

  ../Siv3D/src/ThirdParty/absl/numeric/int128.cc
  ../Siv3D/src/ThirdParty/absl/random/discrete_distribution.cc

  # ../Siv3D/src/ThirdParty/cpu_features/cpuinfo_x86.c
  ../Siv3D/src/ThirdParty/cpu_features/filesystem.c
  ../Siv3D/src/ThirdParty/cpu_features/stack_line_reader.c
  ../Siv3D/src/ThirdParty/cpu_features/string_view.c

  ../Siv3D/src/ThirdParty/double-conversion/bignum-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/bignum.cc
  ../Siv3D/src/ThirdParty/double-conversion/cached-powers.cc
  ../Siv3D/src/ThirdParty/double-conversion/double-to-string.cc
  ../Siv3D/src/ThirdParty/double-conversion/fast-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/fixed-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/string-to-double.cc
  ../Siv3D/src/ThirdParty/double-conversion/strtod.cc

  ../Siv3D/src/ThirdParty/easyexif/exif.cpp

  ../Siv3D/src/ThirdParty/fmt/format.cc
  
  ../Siv3D/src/ThirdParty/lua/lapi.c
  ../Siv3D/src/ThirdParty/lua/lauxlib.c
  ../Siv3D/src/ThirdParty/lua/lbaselib.c
  ../Siv3D/src/ThirdParty/lua/lcode.c
  ../Siv3D/src/ThirdParty/lua/lcorolib.c
  ../Siv3D/src/ThirdParty/lua/lctype.c
  ../Siv3D/src/ThirdParty/lua/ldblib.c
  ../Siv3D/src/ThirdParty/lua/ldebug.c
  ../Siv3D/src/ThirdParty/lua/ldo.c
  ../Siv3D/src/ThirdParty/lua/ldump.c
  ../Siv3D/src/ThirdParty/lua/lfunc.c
  ../Siv3D/src/ThirdParty/lua/lgc.c
  ../Siv3D/src/ThirdParty/lua/linit.c
  ../Siv3D/src/ThirdParty/lua/liolib.c
  ../Siv3D/src/ThirdParty/lua/llex.c
  ../Siv3D/src/ThirdParty/lua/lmathlib.c
  ../Siv3D/src/ThirdParty/lua/lmem.c
  ../Siv3D/src/ThirdParty/lua/loadlib.c
  ../Siv3D/src/ThirdParty/lua/lobject.c
  ../Siv3D/src/ThirdParty/lua/lopcodes.c
  ../Siv3D/src/ThirdParty/lua/loslib.c
  ../Siv3D/src/ThirdParty/lua/lparser.c
  ../Siv3D/src/ThirdParty/lua/lstate.c
  ../Siv3D/src/ThirdParty/lua/lstring.c
  ../Siv3D/src/ThirdParty/lua/lstrlib.c
  ../Siv3D/src/ThirdParty/lua/ltable.c
  ../Siv3D/src/ThirdParty/lua/ltablib.c
  ../Siv3D/src/ThirdParty/lua/ltm.c
  ../Siv3D/src/ThirdParty/lua/lua.c
  ../Siv3D/src/ThirdParty/lua/lundump.c
  ../Siv3D/src/ThirdParty/lua/lutf8lib.c
  ../Siv3D/src/ThirdParty/lua/lvm.c
  ../Siv3D/src/ThirdParty/lua/lzio.c

  ../Siv3D/src/ThirdParty/lunasvg/affinetransform.cpp
  ../Siv3D/src/ThirdParty/lunasvg/canvas.cpp
  ../Siv3D/src/ThirdParty/lunasvg/canvasimpl.cpp
  ../Siv3D/src/ThirdParty/lunasvg/cssproperty.cpp
  ../Siv3D/src/ThirdParty/lunasvg/font.cpp
  ../Siv3D/src/ThirdParty/lunasvg/paint.cpp
  ../Siv3D/src/ThirdParty/lunasvg/path.cpp
  ../Siv3D/src/ThirdParty/lunasvg/pathiterator.cpp
  ../Siv3D/src/ThirdParty/lunasvg/rendercontext.cpp
  ../Siv3D/src/ThirdParty/lunasvg/strokedata.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgangle.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgclippathelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgcolor.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgcontentutils.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgdefselement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgdocument.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgdocumentimpl.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelementimpl.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelementiter.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgenumeration.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgfittoviewbox.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svggelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svggeometryelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svggraphicselement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svglength.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgmarkerelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgmaskelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgnumber.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpaintelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgparser.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpath.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpoint.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgpreserveaspectratio.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgproperty.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgrect.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgstopelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgstring.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgstyledelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgsvgelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgsymbolelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgtextelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgtransform.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgurireference.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svguseelement.cpp

  ../Siv3D/src/ThirdParty/msdfgen/core/contour-combiners.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/Contour.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/edge-coloring.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/edge-segments.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/edge-selectors.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/EdgeHolder.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/equation-solver.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/msdf-edge-artifact-patcher.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/msdf-error-correction.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/msdfgen.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/rasterization.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/render-sdf.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/save-bmp.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/save-tiff.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/Scanline.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/sdf-error-estimation.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/shape-description.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/Shape.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/SignedDistance.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/Vector2.cpp

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

  ../Siv3D/src/ThirdParty/plutovg/plutovg-blend.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg-dash.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg-geometry.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg-paint.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg-rle.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg.c
  ../Siv3D/src/ThirdParty/plutovg/sw_ft_math.c
  ../Siv3D/src/ThirdParty/plutovg/sw_ft_raster.c
  ../Siv3D/src/ThirdParty/plutovg/sw_ft_stroker.c

  ../Siv3D/src/ThirdParty/qr-code-generator-library/QrCode.cpp

  ../Siv3D/src/ThirdParty/RecastDetour/DetourAlloc.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourAssert.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourCommon.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourNavMesh.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourNavMeshBuilder.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourNavMeshQuery.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourNode.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/Recast.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastAlloc.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastArea.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastAssert.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastContour.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastFilter.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastLayers.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastMesh.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastMeshDetail.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastRasterization.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastRegion.cpp

  ../Siv3D/src/ThirdParty/serial/impl/list_ports/list_ports_linux.cc
  ../Siv3D/src/ThirdParty/serial/impl/unix.cc
  ../Siv3D/src/ThirdParty/serial/serial.cc

  ../Siv3D/src/ThirdParty/SplineLib/Splines.cpp

  ../Siv3D/src/ThirdParty/zstd/common/debug.c
  ../Siv3D/src/ThirdParty/zstd/common/entropy_common.c
  ../Siv3D/src/ThirdParty/zstd/common/error_private.c
  ../Siv3D/src/ThirdParty/zstd/common/fse_decompress.c
  ../Siv3D/src/ThirdParty/zstd/common/pool.c
  ../Siv3D/src/ThirdParty/zstd/common/threading.c
  ../Siv3D/src/ThirdParty/zstd/common/xxhash.c
  ../Siv3D/src/ThirdParty/zstd/common/zstd_common.c
  ../Siv3D/src/ThirdParty/zstd/compress/fse_compress.c
  ../Siv3D/src/ThirdParty/zstd/compress/hist.c
  ../Siv3D/src/ThirdParty/zstd/compress/huf_compress.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstdmt_compress.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_compress.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_compress_literals.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_compress_sequences.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_compress_superblock.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_double_fast.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_fast.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_lazy.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_ldm.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_opt.c
  ../Siv3D/src/ThirdParty/zstd/decompress/huf_decompress.c
  ../Siv3D/src/ThirdParty/zstd/decompress/zstd_ddict.c
  ../Siv3D/src/ThirdParty/zstd/decompress/zstd_decompress.c
  ../Siv3D/src/ThirdParty/zstd/decompress/zstd_decompress_block.c
  ../Siv3D/src/ThirdParty/zstd/dictBuilder/cover.c
  ../Siv3D/src/ThirdParty/zstd/dictBuilder/divsufsort.c
  ../Siv3D/src/ThirdParty/zstd/dictBuilder/fastcover.c
  ../Siv3D/src/ThirdParty/zstd/dictBuilder/zdict.c
  )

set_target_properties(OpenSiv3D_Web 
  PROPERTIES 
    OUTPUT_NAME "Siv3D"
)

target_include_directories(
  OpenSiv3D_Web
  PUBLIC
  ../Siv3D/include
  ../Siv3D/include/ThirdParty
  ../Siv3D/src
  ../Siv3D/src/Siv3D-Platform/macOS_Linux
  ../Siv3D/src/Siv3D-Platform/Web
  ../Siv3D/src/Siv3D-Platform/OpenGLES3
  ../Siv3D/src/ThirdParty
  ../Siv3D/src/ThirdParty/freetype
  ../Siv3D/src/ThirdParty-prebuilt
  ../Siv3D/src/ThirdParty-prebuilt/harfbuzz
  ../Siv3D/src/ThirdParty-prebuilt/libjpeg-turbo
  ../Siv3D/src/ThirdParty-prebuilt/libpng
  ../Dependencies/boost_1_73_0
  ${LIBSIV3D_INCLUDE_DIRS}
  )
