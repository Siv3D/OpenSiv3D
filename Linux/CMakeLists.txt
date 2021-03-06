cmake_minimum_required (VERSION 3.0)

find_package(PkgConfig)

project(OpenSiv3D_Linux CXX)
enable_language(C)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Wno-unknown-pragmas -fPIC -msse4.1 -D_GLFW_X11")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-unknown-pragmas -fPIC -msse4.1 -D_GLFW_X11")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	add_compile_options ("-fcolor-diagnostics")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	add_compile_options ("-fdiagnostics-color=always")
endif()

#set(CMAKE_BUILD_TYPE Release)

pkg_check_modules(LIBSIV3D REQUIRED glib-2.0 gobject-2.0 gio-2.0 gl libpng libturbojpeg x11 xi xinerama xcursor xrandr gl glu freetype2 openal opencv4 ogg vorbis zlib)
include_directories(
	"/usr/include"

	"."
	"../Siv3D/include"
	"../Siv3D/src/Siv3D"
	"../Siv3D/src/Siv3D-Platform/Linux"
	"../Siv3D/include/ThirdParty"
	"../Siv3D/src/ThirdParty"

	"../Siv3D/src/ThirdParty/asio"
	"../Siv3D/src/ThirdParty/zstd"
	"../Siv3D/src/ThirdParty/zstd/common"

	${LIBSIV3D_INCLUDE_DIRS}
)

set(SOURCE_FILES
	"../Siv3D/src/Siv3D/AABB/SivAABB.cpp"
	"../Siv3D/src/Siv3D/AnimatedGIFReader/AnimatedGIFReaderDetail.cpp"
	"../Siv3D/src/Siv3D/AnimatedGIFReader/SivAnimatedGIFReader.cpp"	
	"../Siv3D/src/Siv3D/AnimatedGIFWriter/AnimatedGIFWriterDetail.cpp"
	"../Siv3D/src/Siv3D/AnimatedGIFWriter/SivAnimatedGIFWriter.cpp"
	"../Siv3D/src/Siv3D/Asset/AssetFactory.cpp"
	"../Siv3D/src/Siv3D/Asset/CAsset.cpp"
	"../Siv3D/src/Siv3D/Asset/IAssetDetail.cpp"
	"../Siv3D/src/Siv3D/Asset/SivAsset.cpp"
	"../Siv3D/src/Siv3D/AssetHandleManager/AssetReport.cpp"
	"../Siv3D/src/Siv3D/Audio/Null/CAudio_Null.cpp"
	"../Siv3D/src/Siv3D/Audio/SivAudio.cpp"
	"../Siv3D/src/Siv3D/AudioAsset/SivAudioAsset.cpp"
	"../Siv3D/src/Siv3D/AudioFormat/AudioFormatFactory.cpp"
	"../Siv3D/src/Siv3D/AudioFormat/CAudioFormat.cpp"
	"../Siv3D/src/Siv3D/AudioFormat/SivAudioFormat.cpp"
	"../Siv3D/src/Siv3D/AudioFormat/OggVorbis/AudioFormat_OggVorbis.cpp"
	"../Siv3D/src/Siv3D/AudioFormat/WAVE/AudioFormat_WAVE.cpp"
	"../Siv3D/src/Siv3D/Base64/SivBase64.cpp"
	"../Siv3D/src/Siv3D/Bezier2/SivBezier2.cpp"
	"../Siv3D/src/Siv3D/Bezier3/SivBezier3.cpp"
	"../Siv3D/src/Siv3D/BigFloat/SivBigFloat.cpp"
	"../Siv3D/src/Siv3D/BigInt/SivBigInt.cpp"
	"../Siv3D/src/Siv3D/BinaryReader/SivBinaryReader.cpp"
	"../Siv3D/src/Siv3D/BinaryWriter/SivBinaryWriter.cpp"
	"../Siv3D/src/Siv3D/BlendState/SivBlendState.cpp"
	"../Siv3D/src/Siv3D/BoolArray/SivBoolArray.cpp"
	"../Siv3D/src/Siv3D/Byte/SivByte.cpp"
	"../Siv3D/src/Siv3D/ByteArray/ByteArrayDetail.cpp"
	"../Siv3D/src/Siv3D/ByteArray/SivByteArray.cpp"
	"../Siv3D/src/Siv3D/ByteArrayView/SivByteArrayView.cpp"
	"../Siv3D/src/Siv3D/CPU/CCPU.cpp"
	"../Siv3D/src/Siv3D/CPU/CPUFactory.cpp"
	"../Siv3D/src/Siv3D/CPU/SivCPU.cpp"
	"../Siv3D/src/Siv3D/CSVData/SivCSVData.cpp"
	"../Siv3D/src/Siv3D/Camera2D/SivCamera2D.cpp"
	"../Siv3D/src/Siv3D/Camera3D/SivCamera3D.cpp"
	"../Siv3D/src/Siv3D/Circle/SivCircle.cpp"
	"../Siv3D/src/Siv3D/Clipboard/ClipboardFactory.cpp"
	"../Siv3D/src/Siv3D/Clipboard/SivClipboard.cpp"
	"../Siv3D/src/Siv3D/Codec/CodecFactory.cpp"
	"../Siv3D/src/Siv3D/Color/SivColor.cpp"
	"../Siv3D/src/Siv3D/Compression/SivCompression.cpp"
	"../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp"
	"../Siv3D/src/Siv3D/Console/SivConsole.cpp"
	"../Siv3D/src/Siv3D/Cursor/CursorFactory.cpp"
	"../Siv3D/src/Siv3D/Cursor/SivCursor.cpp"
	"../Siv3D/src/Siv3D/CustomStopwatch/SivCustomStopwatch.cpp"
	"../Siv3D/src/Siv3D/Cylindrical/SivCylindrical.cpp"
	"../Siv3D/src/Siv3D/Date/SivDate.cpp"
	"../Siv3D/src/Siv3D/DateTime/SivDateTime.cpp"
	"../Siv3D/src/Siv3D/DeadZone/SivDeadZone.cpp"
	"../Siv3D/src/Siv3D/DefaultRNG/SivDefaultRNG.cpp"
	"../Siv3D/src/Siv3D/Dialog/SivDialog.cpp"
	"../Siv3D/src/Siv3D/DirectoryWatcher/SivDirectoryWatcher.cpp"
	"../Siv3D/src/Siv3D/Distribution/SivDistribution.cpp"
	"../Siv3D/src/Siv3D/DragDrop/DragDropFactory.cpp"
	"../Siv3D/src/Siv3D/DragDrop/SivDragDrop.cpp"
	"../Siv3D/src/Siv3D/Duration/SivDuration.cpp"
	"../Siv3D/src/Siv3D/DynamicTexture/SivDynamicTexture.cpp"
	"../Siv3D/src/Siv3D/Easing/SivEasing.cpp"
	"../Siv3D/src/Siv3D/Effect/CEffect.cpp"
	"../Siv3D/src/Siv3D/Effect/EffectData.cpp"
	"../Siv3D/src/Siv3D/Effect/EffectFactory.cpp"
	"../Siv3D/src/Siv3D/Effect/SivEffect.cpp"
	"../Siv3D/src/Siv3D/Ellipse/SivEllipse.cpp"
	"../Siv3D/src/Siv3D/Emitter2D/SivEmitter2D.cpp"
	"../Siv3D/src/Siv3D/Emoji/SivEmoji.cpp"
	"../Siv3D/src/Siv3D/EmojiList/EmojiListDetail.cpp"
	"../Siv3D/src/Siv3D/EmojiList/SivEmojiList.cpp"
	"../Siv3D/src/Siv3D/EngineDirectory/EngineDirectory.cpp"
	"../Siv3D/src/Siv3D/Error/SivError.cpp"
	"../Siv3D/src/Siv3D/Exif/SivExif.cpp"
	"../Siv3D/src/Siv3D/FFT/CFFT.cpp"
	"../Siv3D/src/Siv3D/FFT/FFTFactory.cpp"
	"../Siv3D/src/Siv3D/FFT/SivFFT.cpp"
	"../Siv3D/src/Siv3D/FileFilter/SivFileFilter.cpp"
	"../Siv3D/src/Siv3D/FileSystem/SivFileSystem.cpp"
	"../Siv3D/src/Siv3D/Font/CFont.cpp"
	"../Siv3D/src/Siv3D/Font/FontFace.cpp"
	"../Siv3D/src/Siv3D/Font/FontFactory.cpp"
	"../Siv3D/src/Siv3D/Font/SivFont.cpp"
	"../Siv3D/src/Siv3D/Font/FontData.cpp"
	"../Siv3D/src/Siv3D/FontAsset/SivFontAsset.cpp"
	"../Siv3D/src/Siv3D/Format/SivFormat.cpp"
	"../Siv3D/src/Siv3D/FormatFloat/SivFormatFloat.cpp"
	"../Siv3D/src/Siv3D/FormatInt/SivFormatInt.cpp"
	"../Siv3D/src/Siv3D/FormatLiteral/SivFormatLiteral.cpp"
	"../Siv3D/src/Siv3D/FormatUtility/SivFormatUtility.cpp"
	"../Siv3D/src/Siv3D/GUI/CGUI.cpp"
	"../Siv3D/src/Siv3D/GUI/GUIFactory.cpp"
	"../Siv3D/src/Siv3D/Gamepad/GamepadFactory.cpp"
	"../Siv3D/src/Siv3D/Gamepad/SivGamepad.cpp"
	"../Siv3D/src/Siv3D/Geometry2D/SivGeometry2D.cpp"
	"../Siv3D/src/Siv3D/Graphics/SivGraphics.cpp"
	"../Siv3D/src/Siv3D/Graphics2D/SivGraphics2D.cpp"
	"../Siv3D/src/Siv3D/HSV/SivHSV.cpp"
	"../Siv3D/src/Siv3D/HTMLWriter/HTMLWriterDetail.cpp"
	"../Siv3D/src/Siv3D/HTMLWriter/SivHTMLWriter.cpp"
	"../Siv3D/src/Siv3D/HalfFloat/SivHalfFloat.cpp"
	"../Siv3D/src/Siv3D/Hash/SivHash.cpp"
	"../Siv3D/src/Siv3D/INIData/SivINIData.cpp"
	"../Siv3D/src/Siv3D/IPv4/SivIPv4.cpp"
	"../Siv3D/src/Siv3D/Icon/SivIcon.cpp"
	"../Siv3D/src/Siv3D/Image/SivImage.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/BMP/ImageFormat_BMP.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/CImageFormat.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/GIF/ImageFormat_GIF.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/ImageFormatFactory.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/JPEG/ImageFormat_JPEG.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/PNG/ImageFormat_PNG.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/PPM/ImageFormat_PPM.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/SivImageFormat.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/TGA/ImageFormat_TGA.cpp"
	"../Siv3D/src/Siv3D/ImageFormat/WebP/ImageFormat_WebP.cpp"
	"../Siv3D/src/Siv3D/ImageProcessing/SivImageProcessing.cpp"
	"../Siv3D/src/Siv3D/Interpolation/SivInterpolation.cpp"
	"../Siv3D/src/Siv3D/JSONReader/SivJSONReader.cpp"
	"../Siv3D/src/Siv3D/JSONWriter/SivJSONWriter.cpp"
	"../Siv3D/src/Siv3D/JoyCon/SivJoyCon.cpp"
	"../Siv3D/src/Siv3D/Key/SivKey.cpp"
	"../Siv3D/src/Siv3D/KeyConjunction/SivKeyConjunction.cpp"
	"../Siv3D/src/Siv3D/KeyGroup/SivKeyGroup.cpp"
	"../Siv3D/src/Siv3D/Keyboard/KeyboardFactory.cpp"
	"../Siv3D/src/Siv3D/LicenseManager/CLicenseManager.cpp"
	"../Siv3D/src/Siv3D/LicenseManager/LicenseManagerFactory.cpp"
	"../Siv3D/src/Siv3D/LicenseManager/SivLicenseManager.cpp"
	"../Siv3D/src/Siv3D/Line/SivLine.cpp"
	"../Siv3D/src/Siv3D/Line3D/SivLine3D.cpp"
	"../Siv3D/src/Siv3D/LineString/SivLineString.cpp"
	"../Siv3D/src/Siv3D/Logger/LoggerFactory.cpp"
	"../Siv3D/src/Siv3D/Logger/SivLogger.cpp"
	"../Siv3D/src/Siv3D/MD5/SivMD5.cpp"
	"../Siv3D/src/Siv3D/MSRenderTexture/SivMSRenderTexture.cpp"
	"../Siv3D/src/Siv3D/ManagedScript/ManagedScriptDetail.cpp"
	"../Siv3D/src/Siv3D/ManagedScript/SivManagedScript.cpp"
	"../Siv3D/src/Siv3D/Mat3x2/SivMat3x2.cpp"
	"../Siv3D/src/Siv3D/Mat4x4/SivMat4x4.cpp"
	"../Siv3D/src/Siv3D/Math/SivMath.cpp"
	"../Siv3D/src/Siv3D/MathParser/MathParserDetail.cpp"
	"../Siv3D/src/Siv3D/MathParser/SivMathParser.cpp"
	"../Siv3D/src/Siv3D/MemoryMapping/SivMemoryMapping.cpp"
	"../Siv3D/src/Siv3D/MemoryWriter/MemoryWriterDetail.cpp"
	"../Siv3D/src/Siv3D/MemoryWriter/SivMemoryWriter.cpp"
	"../Siv3D/src/Siv3D/MersenneTwister/SivMersenneTwister.cpp"
	"../Siv3D/src/Siv3D/Microphone/SivMicrophone.cpp"
	"../Siv3D/src/Siv3D/Mouse/MouseFactory.cpp"
	"../Siv3D/src/Siv3D/Mouse/SivMouse.cpp"
	"../Siv3D/src/Siv3D/MultiPolygon/SivMultiPolygon.cpp"
	"../Siv3D/src/Siv3D/NavMesh/NavMeshDetail.cpp"
	"../Siv3D/src/Siv3D/NavMesh/SivNavMesh.cpp"
	"../Siv3D/src/Siv3D/Network/NetworkFactory.cpp"
	"../Siv3D/src/Siv3D/Network/SivNetwork.cpp"
	"../Siv3D/src/Siv3D/NoiseGenerator/NoiseGeneratorDetail.cpp"
	"../Siv3D/src/Siv3D/NoiseGenerator/SivNoiseGenerator.cpp"
	"../Siv3D/src/Siv3D/OBB/SivOBB.cpp"
	"../Siv3D/src/Siv3D/ObjectDetection/CObjectDetection.cpp"
	"../Siv3D/src/Siv3D/ObjectDetection/ObjectDetectionFactory.cpp"
	"../Siv3D/src/Siv3D/OpenCV_Bridge/SivOpenCV_Bridge.cpp"
	"../Siv3D/src/Siv3D/OutlineGlyph/SivOutlineGlyph.cpp"
	"../Siv3D/src/Siv3D/Painting/PaintShape.cpp"
	"../Siv3D/src/Siv3D/Painting/SivPainting.cpp"
	"../Siv3D/src/Siv3D/Parse/SivParse.cpp"
	"../Siv3D/src/Siv3D/ParseBool/SivParseBool.cpp"
	"../Siv3D/src/Siv3D/ParseFloat/SivParseFloat.cpp"
	"../Siv3D/src/Siv3D/ParseInt/SivParseInt.cpp"
	"../Siv3D/src/Siv3D/Particle2D/SivParticle2D.cpp"
	"../Siv3D/src/Siv3D/ParticleSystem2D/ParticleSystem2DDetail.cpp"
	"../Siv3D/src/Siv3D/ParticleSystem2D/SivParticleSystem2D.cpp"
	"../Siv3D/src/Siv3D/PerlinNoise/SivPerlinNoise.cpp"
	"../Siv3D/src/Siv3D/Physics2D/P2BodyDetail.cpp"
	"../Siv3D/src/Siv3D/Physics2D/P2ContactListner.cpp"
	"../Siv3D/src/Siv3D/Physics2D/P2DistanceJointDetail.cpp"
	"../Siv3D/src/Siv3D/Physics2D/P2PivotJointDetail.cpp"
	"../Siv3D/src/Siv3D/Physics2D/P2RopeJointDetail.cpp"
	"../Siv3D/src/Siv3D/Physics2D/P2SliderJointDetail.cpp"
	"../Siv3D/src/Siv3D/Physics2D/P2WheelJointDetail.cpp"
	"../Siv3D/src/Siv3D/Physics2D/P2WorldDetail.cpp"
	"../Siv3D/src/Siv3D/Physics2D/SivPhysics2D.cpp"
	"../Siv3D/src/Siv3D/PixelShader/SivPixelShader.cpp"
	"../Siv3D/src/Siv3D/Point/SivPoint.cpp"
	"../Siv3D/src/Siv3D/PoissonDisk2D/SivPoissonDisk2D.cpp"
	"../Siv3D/src/Siv3D/Polygon/PolygonDetail.cpp"
	"../Siv3D/src/Siv3D/Polygon/SivPolygon.cpp"
	"../Siv3D/src/Siv3D/Print/CPrint.cpp"
	"../Siv3D/src/Siv3D/Print/PrintFactory.cpp"
	"../Siv3D/src/Siv3D/Print/SivPrint.cpp"
	"../Siv3D/src/Siv3D/ProController/SivProController.cpp"
	"../Siv3D/src/Siv3D/Profiler/CProfiler.cpp"
	"../Siv3D/src/Siv3D/Profiler/ProfilerFactory.cpp"
	"../Siv3D/src/Siv3D/Profiler/SivProfiler.cpp"
	"../Siv3D/src/Siv3D/Process/SivProcess.cpp"
	"../Siv3D/src/Siv3D/QR/QRDecoderDetail.cpp"
	"../Siv3D/src/Siv3D/QR/SivQR.cpp"
	"../Siv3D/src/Siv3D/Quad/SivQuad.cpp"
	"../Siv3D/src/Siv3D/Quaternion/SivQuaternion.cpp"
	"../Siv3D/src/Siv3D/RNG/SivRNG.cpp"
	"../Siv3D/src/Siv3D/Random/SivRandom.cpp"
	"../Siv3D/src/Siv3D/Ray/SivRay.cpp"
	"../Siv3D/src/Siv3D/RasterizerState/SivRasterizerState.cpp"
	"../Siv3D/src/Siv3D/Rectangle/SivRectangle.cpp"
	"../Siv3D/src/Siv3D/RectanglePacking/SivRectanglePacking.cpp"
	"../Siv3D/src/Siv3D/RenderTexture/SivRenderTexture.cpp"
	"../Siv3D/src/Siv3D/Renderer2D/Vertex2DBuilder.cpp"
	"../Siv3D/src/Siv3D/RoundRect/SivRoundRect.cpp"
	"../Siv3D/src/Siv3D/SDF/SivSDF.cpp"
	"../Siv3D/src/Siv3D/SDFFont/CSDFFont.cpp"
	"../Siv3D/src/Siv3D/SDFFont/SDFFontData.cpp"
	"../Siv3D/src/Siv3D/SDFFont/SDFFontFactory.cpp"
	"../Siv3D/src/Siv3D/SDFFont/SivSDFFont.cpp"
	"../Siv3D/src/Siv3D/SFMT/SivSFMT.cpp"
	"../Siv3D/src/Siv3D/SIMD_Float4/SivSIMD_Float4.cpp"
	"../Siv3D/src/Siv3D/SVM/CSVM.cpp"
	"../Siv3D/src/Siv3D/SVM/SivSVM.cpp"
	"../Siv3D/src/Siv3D/SamplerState/SivSamplerState.cpp"
	"../Siv3D/src/Siv3D/Say/SivSay.cpp"
	"../Siv3D/src/Siv3D/Scene/SivScene.cpp"
	"../Siv3D/src/Siv3D/ScopedColor2D/SivScopedColor2D.cpp"
	"../Siv3D/src/Siv3D/ScopedCustomShader2D/SivScopedCustomShader2D.cpp"
	"../Siv3D/src/Siv3D/ScopedRenderStates2D/SivScopedRenderStates2D.cpp"
	"../Siv3D/src/Siv3D/ScopedRenderTarget2D/SivScopedRenderTarget2D.cpp"
	"../Siv3D/src/Siv3D/ScopedViewport2D/SivScopedViewport2D.cpp"
	"../Siv3D/src/Siv3D/ScreenCapture/CScreenCapture.cpp"
	"../Siv3D/src/Siv3D/ScreenCapture/ScreenCaptureFactory.cpp"
	"../Siv3D/src/Siv3D/ScreenCapture/SivScreenCapture.cpp"
	"../Siv3D/src/Siv3D/Script/AngelScript/scriptarray.cpp"
	"../Siv3D/src/Siv3D/Script/AngelScript/scriptbuilder.cpp"
	"../Siv3D/src/Siv3D/Script/AngelScript/scriptgrid.cpp"
	"../Siv3D/src/Siv3D/Script/AngelScript/scriptstdstring.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Audio.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Bezier2.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Bezier3.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Circle.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Circular.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Color.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_ColorF.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Cursor.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_CustomStopwatch.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Date.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_DateTime.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Dialog.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_DrawableText.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Duration.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_DynamicTexture.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Easing.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Ellipse.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Emoji.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Float2.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_FloatRect.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Font.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Format.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Graphics.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_HSV.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Icon.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Image.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Line.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_LineString.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_LineStyle.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Mat3x2.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Math.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_MathConstants.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_MicrosecClock.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_MillisecClock.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Mouse.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_NamedArg.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_None_t.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_OffsetCircular.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Optional.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Palette.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Periodic.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Point.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Polygon.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Print.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Profiler.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Quad.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_RDTSCClock.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Random.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Rect.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_RectF.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_RoundRect.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Say.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Scene.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_ScopedViewport2D.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Shape2D.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_SoundFont.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Stopwatch.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_System.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_TextToSpeech.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Texture.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_TextureFormat.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_TextureRegion.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_TexturedCircle.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_TexturedQuad.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_TexturedRoundRect.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Time.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Timer.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Transformer2D.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Triangle.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Types.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Utility.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Vec2.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Vec3.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Vec4.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Wave.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_WaveSample.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Window.cpp"
	"../Siv3D/src/Siv3D/Script/Bind/Script_Key.cpp"
	"../Siv3D/src/Siv3D/Script/CScript.cpp"
	"../Siv3D/src/Siv3D/Script/ScriptData.cpp"
	"../Siv3D/src/Siv3D/Script/ScriptFactory.cpp"
	"../Siv3D/src/Siv3D/Script/SivScript.cpp"
	"../Siv3D/src/Siv3D/Serial/SerialDetail.cpp"
	"../Siv3D/src/Siv3D/Serial/SivSerial.cpp"
	"../Siv3D/src/Siv3D/Shader/SivShader.cpp"
	"../Siv3D/src/Siv3D/Shape2D/SivShape2D.cpp"
	"../Siv3D/src/Siv3D/SimpleGUI/SimpleGUI.cpp"
	"../Siv3D/src/Siv3D/SimpleGUIManager/SimpleGUIManagerDetail.cpp"
	"../Siv3D/src/Siv3D/SimpleGUIManager/SivSimpleGUIManager.cpp"
	"../Siv3D/src/Siv3D/Siv3DEngine.cpp"
	"../Siv3D/src/Siv3D/SoundFont/CSoundFont.cpp"
	"../Siv3D/src/Siv3D/SoundFont/SoundFontFactory.cpp"
	"../Siv3D/src/Siv3D/Sphere/SivSphere.cpp"
	"../Siv3D/src/Siv3D/Spherical/SivSpherical.cpp"
	"../Siv3D/src/Siv3D/Sprite/SivSprite.cpp"
	"../Siv3D/src/Siv3D/Step2D/SivStep2D.cpp"
	"../Siv3D/src/Siv3D/Stopwatch/SivStopwatch.cpp"
	"../Siv3D/src/Siv3D/String/SivString.cpp"
	"../Siv3D/src/Siv3D/StringView/SivStringView.cpp"
	"../Siv3D/src/Siv3D/Subdivision2D/SivSubdivision2D.cpp"
	"../Siv3D/src/Siv3D/System/SystemFactory.cpp"
	"../Siv3D/src/Siv3D/System/SivSystem.cpp"
	"../Siv3D/src/Siv3D/TCPClient/SivTCPClient.cpp"
	"../Siv3D/src/Siv3D/TCPClient/TCPClientDetail.cpp"
	"../Siv3D/src/Siv3D/TCPServer/SivTCPServer.cpp"
	"../Siv3D/src/Siv3D/TCPServer/TCPServerDetail.cpp"
	"../Siv3D/src/Siv3D/TOMLReader/SivTOMLReader.cpp"
	"../Siv3D/src/Siv3D/TextBox/SivTextBox.cpp"
	"../Siv3D/src/Siv3D/TextBox/TextBoxDetail.cpp"
	"../Siv3D/src/Siv3D/TextEncoding/SivTextEncoding.cpp"
	"../Siv3D/src/Siv3D/TextInput/SivTextInput.cpp"
	"../Siv3D/src/Siv3D/TextInput/TextInputFactory.cpp"
	"../Siv3D/src/Siv3D/TextReader/SivTextReader.cpp"
	"../Siv3D/src/Siv3D/TextReader/TextReaderDetail.cpp"
	"../Siv3D/src/Siv3D/TextToSpeech/SivTextToSpeech.cpp"
	"../Siv3D/src/Siv3D/TextToSpeech/TextToSpeechFactory.cpp"
	"../Siv3D/src/Siv3D/TextWriter/SivTextWriter.cpp"
	"../Siv3D/src/Siv3D/TextWriter/TextWriterDetail.cpp"
	"../Siv3D/src/Siv3D/Texture/SivTexture.cpp"
	"../Siv3D/src/Siv3D/TextureAsset/SivTextureAsset.cpp"
	"../Siv3D/src/Siv3D/TextureDesc/SivTextureDesc.cpp"
	"../Siv3D/src/Siv3D/TextureFormat/SivTextureFormat.cpp"
	"../Siv3D/src/Siv3D/TextureRegion/SivTextureRegion.cpp"
	"../Siv3D/src/Siv3D/TexturedCircle/SivTexturedCircle.cpp"
	"../Siv3D/src/Siv3D/TexturedQuad/SivTexturedQuad.cpp"
	"../Siv3D/src/Siv3D/TexturedRoundRect/SivTexturedRoundRect.cpp"
	"../Siv3D/src/Siv3D/Threading/SivThreading.cpp"
	"../Siv3D/src/Siv3D/TimeProfiler/SivTimeProfiler.cpp"
	"../Siv3D/src/Siv3D/TimeProfiler/TimeProfilerDetail.cpp"
	"../Siv3D/src/Siv3D/Timer/SivTimer.cpp"
	"../Siv3D/src/Siv3D/ToastNotification/SivToastNotification.cpp"
	"../Siv3D/src/Siv3D/Transformer2D/SivTransformer2D.cpp"
	"../Siv3D/src/Siv3D/Transition/SivTransition.cpp"
	"../Siv3D/src/Siv3D/Triangle/SivTriangle.cpp"
	"../Siv3D/src/Siv3D/Triangle3D/SivTriangle3D.cpp"
	"../Siv3D/src/Siv3D/Twitter/SivTwitter.cpp"
	"../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp"
	"../Siv3D/src/Siv3D/Vector2D/SivVector2D.cpp"
	"../Siv3D/src/Siv3D/Vector3D/SivVector3D.cpp"
	"../Siv3D/src/Siv3D/Vector4D/SivVector4D.cpp"
	"../Siv3D/src/Siv3D/VertexShader/SivVertexShader.cpp"
	"../Siv3D/src/Siv3D/VideoWriter/SivVideoWriter.cpp"
	"../Siv3D/src/Siv3D/Wave/SivWave.cpp"
	"../Siv3D/src/Siv3D/Webcam/SivWebcam.cpp"
	"../Siv3D/src/Siv3D/Webcam/WebcamDetail.cpp"
	"../Siv3D/src/Siv3D/Window/WindowFactory.cpp"
	"../Siv3D/src/Siv3D/Window/SivWindow.cpp"
	"../Siv3D/src/Siv3D/WritableMemoryMapping/SivWritableMemoryMapping.cpp"
	"../Siv3D/src/Siv3D/XInput/SivXInput.cpp"
	"../Siv3D/src/Siv3D/XInput/XInputFactory.cpp"
	"../Siv3D/src/Siv3D/XMLReader/SivXMLReader.cpp"
	"../Siv3D/src/Siv3D/XXHash/SivXXHash.cpp"
	"../Siv3D/src/Siv3D/ZIPReader/SivZIPReader.cpp"
	"../Siv3D/src/Siv3D/ZIPReader/ZIPReaderDetail.cpp"
	"../Siv3D/src/Siv3D/Zlib/SivZlib.cpp"

	"../Siv3D/src/Siv3D-Platform/Linux/Siv3DMain.cpp"

	"../Siv3D/src/Siv3D-Platform/Linux/Audio/AL/CAudio_AL.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Audio/AudioFactory.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/AudioFormat/AAC/AudioFormat_AAC.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/AudioFormat/MP3/AudioFormat_MP3.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/BinaryReader/BinaryReaderDetail.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/BinaryWriter/BinaryWriterDetail.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/ByteArray/ByteArrayDetail_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Clipboard/CClipboard.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Codec/CCodec.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Console/CConsole.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/ConstantBuffer/GL/GLConstantBuffer.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/ConstantBuffer/SivConstantBuffer.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Cursor/CCursor.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/DLL/SivDLL.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Date/SivDate_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/DateTime/SivDateTime_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Dialog/SivDialog_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/DirectoryWatcher/DirectoryWatcherDetail.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/DragDrop/CDragDrop.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/EngineLog/SivEngineLog.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/EngineMessageBox/SivEngineMessageBox.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/FileSystem/SivFileSystem_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Gamepad/CGamepad.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Gamepad/SivGamepad_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Graphics/GL/BlendState/GLBlendState.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Graphics/GL/CGraphics_GL.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Graphics/GL/RasterizerState/GLRasterizerState.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Graphics/GL/SamplerState/GLSamplerState.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Graphics/GL/SceneTexture.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Graphics/GraphicsFactory.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Graphics/SivGraphics_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Keyboard/CKeyboard.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Logger/CLogger.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/MemoryMapping/MemoryMappingDetail.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/MessageBox/SivMessageBox.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Microphone/MicrophoneDetail.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Monitor/SivMonitor.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Mouse/CMouse.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/NLP/SivNLP_Japanese.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Network/CNetwork.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/PowerStatus/SivPowerStatus.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Process/ChildProcessDetail.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Renderer2D/GL/CRenderer2D_GL.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Renderer2D/GL/GLRenderer2DCommand.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Renderer2D/GL/GLSpriteBatch.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Renderer2D/Renderer2DFactory.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Resource/SivResource.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/ScreenCapture/CScreenCapture_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Shader/GL/CShader_GL.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Shader/GL/PixelShader_GL.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Shader/GL/VertexShader_GL.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Shader/ShaderFactory.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Siv3DMain.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/System/CSystem.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/System/SivSystem_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/TextInput/CTextInput.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/TextReader/TextReaderDetail_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/TextToSpeech/CTextToSpeech.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Texture/GL/CTexture_GL.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Texture/GL/Texture_GL.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Texture/TextureFactory.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Time/SivTime.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/ToastNotification/CToastNotification.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/ToastNotification/ToastNotificationFactory.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Unicode/SivUnicode_Platform.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/VideoWriter/VideoWriterDetail.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/Window/CWindow.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/WritableMemoryMapping/WritableMemoryMappingDetail.cpp"
	"../Siv3D/src/Siv3D-Platform/Linux/XInput/CXInput.cpp"

	"../Siv3D/src/ThirdParty/angelscript/as_atomic.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_builder.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_bytecode.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_callfunc.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_callfunc_x64_gcc.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_compiler.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_configgroup.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_context.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_datatype.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_gc.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_generic.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_globalproperty.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_memory.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_module.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_objecttype.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_outputbuffer.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_parser.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_restore.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_scriptcode.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_scriptengine.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_scriptfunction.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_scriptnode.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_scriptobject.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_string.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_string_util.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_thread.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_tokenizer.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_typeinfo.cpp"
	"../Siv3D/src/ThirdParty/angelscript/as_variablescope.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/Shapes/b2ChainShape.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/Shapes/b2CircleShape.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/Shapes/b2EdgeShape.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/Shapes/b2PolygonShape.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/b2BroadPhase.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/b2CollideCircle.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/b2CollideEdge.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/b2CollidePolygon.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/b2Collision.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/b2Distance.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/b2DynamicTree.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Collision/b2TimeOfImpact.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Common/b2BlockAllocator.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Common/b2Draw.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Common/b2Math.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Common/b2Settings.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Common/b2StackAllocator.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Common/b2Timer.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Contacts/b2CircleContact.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Contacts/b2Contact.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Contacts/b2ContactSolver.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Contacts/b2PolygonContact.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2DistanceJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2FrictionJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2GearJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2Joint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2MotorJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2MouseJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2PulleyJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2RopeJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2WeldJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/Joints/b2WheelJoint.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/b2Body.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/b2ContactManager.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/b2Fixture.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/b2Island.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/b2World.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Dynamics/b2WorldCallbacks.cpp"
	"../Siv3D/src/ThirdParty/Box2D/Rope/b2Rope.cpp"
	"../Siv3D/src/ThirdParty/FID/FID.cpp"
	"../Siv3D/src/ThirdParty/FastNoiseSIMD/FastNoiseSIMD.cpp"
	"../Siv3D/src/ThirdParty/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp"
	"../Siv3D/src/ThirdParty/FastNoiseSIMD/FastNoiseSIMD_avx512.cpp"
	"../Siv3D/src/ThirdParty/FastNoiseSIMD/FastNoiseSIMD_internal.cpp"
	"../Siv3D/src/ThirdParty/FastNoiseSIMD/FastNoiseSIMD_neon.cpp"
	"../Siv3D/src/ThirdParty/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp"
	"../Siv3D/src/ThirdParty/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp"
	"../Siv3D/src/ThirdParty/FeatureDetector/cpu_x86.cpp"
	"../Siv3D/src/ThirdParty/QRCode/qrcode.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/DetourAlloc.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/DetourAssert.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/DetourCommon.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/DetourNavMesh.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/DetourNavMeshBuilder.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/DetourNavMeshQuery.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/DetourNode.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/Recast.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastAlloc.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastArea.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastAssert.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastContour.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastFilter.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastLayers.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastMesh.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastMeshDetail.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastRasterization.cpp"
	"../Siv3D/src/ThirdParty/RecastDetour/RecastRegion.cpp"
	"../Siv3D/src/ThirdParty/double-conversion/bignum-dtoa.cc"
	"../Siv3D/src/ThirdParty/double-conversion/bignum.cc"
	"../Siv3D/src/ThirdParty/double-conversion/cached-powers.cc"
	"../Siv3D/src/ThirdParty/double-conversion/diy-fp.cc"
	"../Siv3D/src/ThirdParty/double-conversion/double-conversion.cc"
	"../Siv3D/src/ThirdParty/double-conversion/fast-dtoa.cc"
	"../Siv3D/src/ThirdParty/double-conversion/fixed-dtoa.cc"
	"../Siv3D/src/ThirdParty/double-conversion/strtod.cc"
	"../Siv3D/src/ThirdParty/easyexif/exif.cpp"
	"../Siv3D/src/ThirdParty/fmt/format.cc"
	#"../Siv3D/src/ThirdParty/giflib/dgif_lib.c"
	#"../Siv3D/src/ThirdParty/giflib/egif_lib.c"
	#"../Siv3D/src/ThirdParty/giflib/gif_err.c"
	#"../Siv3D/src/ThirdParty/giflib/gif_font.c"
	#"../Siv3D/src/ThirdParty/giflib/gif_hash.c"
	#"../Siv3D/src/ThirdParty/giflib/gif_quantize.c"
	#"../Siv3D/src/ThirdParty/giflib/gifalloc.c"
	#"../Siv3D/src/ThirdParty/giflib/openbsd-reallocarray.c"
	"../Siv3D/src/ThirdParty/libsvm/svm.cpp"
	"../Siv3D/src/ThirdParty/minizip/aescrypt.c"
	"../Siv3D/src/ThirdParty/minizip/aeskey.c"
	"../Siv3D/src/ThirdParty/minizip/aestab.c"
	"../Siv3D/src/ThirdParty/minizip/hmac.c"
	"../Siv3D/src/ThirdParty/minizip/sha1.c"
	"../Siv3D/src/ThirdParty/minizip/sha2.c"
	"../Siv3D/src/ThirdParty/minizip/mz_compat.c"
	"../Siv3D/src/ThirdParty/minizip/mz_crypt.c"
	"../Siv3D/src/ThirdParty/minizip/mz_crypt_brg.c"
	"../Siv3D/src/ThirdParty/minizip/mz_os.c"
	"../Siv3D/src/ThirdParty/minizip/mz_os_posix.c"
	"../Siv3D/src/ThirdParty/minizip/mz_strm.c"
	"../Siv3D/src/ThirdParty/minizip/mz_strm_buf.c"
	"../Siv3D/src/ThirdParty/minizip/mz_strm_mem.c"
	"../Siv3D/src/ThirdParty/minizip/mz_strm_os_posix.c"
	"../Siv3D/src/ThirdParty/minizip/mz_strm_pkcrypt.c"
	"../Siv3D/src/ThirdParty/minizip/mz_strm_split.c"
	"../Siv3D/src/ThirdParty/minizip/mz_strm_wzaes.c"
	"../Siv3D/src/ThirdParty/minizip/mz_strm_zlib.c"
	"../Siv3D/src/ThirdParty/minizip/mz_zip.c"
	"../Siv3D/src/ThirdParty/minizip/mz_zip_rw.c"
	"../Siv3D/src/ThirdParty/msdf/core/Bitmap.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/Contour.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/EdgeHolder.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/Shape.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/SignedDistance.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/Vector2.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/edge-coloring.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/edge-segments.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/equation-solver.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/msdfgen.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/render-sdf.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/save-bmp.cpp"
	"../Siv3D/src/ThirdParty/msdf/core/shape-description.cpp"
	"../Siv3D/src/ThirdParty/msdf/ext/import-font.cpp"
	"../Siv3D/src/ThirdParty/muparser/muParser.cpp"
	"../Siv3D/src/ThirdParty/muparser/muParserBase.cpp"
	"../Siv3D/src/ThirdParty/muparser/muParserBytecode.cpp"
	"../Siv3D/src/ThirdParty/muparser/muParserCallback.cpp"
	"../Siv3D/src/ThirdParty/muparser/muParserDLL.cpp"
	"../Siv3D/src/ThirdParty/muparser/muParserError.cpp"
	"../Siv3D/src/ThirdParty/muparser/muParserInt.cpp"
	"../Siv3D/src/ThirdParty/muparser/muParserTokenReader.cpp"
	"../Siv3D/src/ThirdParty/pffft/pffft.c"
	"../Siv3D/src/ThirdParty/quirc/decode.c"
	"../Siv3D/src/ThirdParty/quirc/identify.c"
	"../Siv3D/src/ThirdParty/quirc/quirc.c"
	"../Siv3D/src/ThirdParty/quirc/version_db.c"
	"../Siv3D/src/ThirdParty/serial/list_ports_linux.cc"
	"../Siv3D/src/ThirdParty/serial/serial.cc"
	"../Siv3D/src/ThirdParty/serial/unix.cc"
	"../Siv3D/src/ThirdParty/tinyxml/tinyxml2.cpp"
	"../Siv3D/src/ThirdParty/tsl/hopscotch_growth_policy.cpp"
	"../Siv3D/src/ThirdParty/zstd/common/debug.c"
	"../Siv3D/src/ThirdParty/zstd/common/entropy_common.c"
	"../Siv3D/src/ThirdParty/zstd/common/error_private.c"
	"../Siv3D/src/ThirdParty/zstd/common/fse_decompress.c"
	"../Siv3D/src/ThirdParty/zstd/common/pool.c"
	"../Siv3D/src/ThirdParty/zstd/common/threading.c"
	"../Siv3D/src/ThirdParty/zstd/common/xxhash.c"
	"../Siv3D/src/ThirdParty/zstd/common/zstd_common.c"
	"../Siv3D/src/ThirdParty/zstd/compress/fse_compress.c"
	"../Siv3D/src/ThirdParty/zstd/compress/hist.c"
	"../Siv3D/src/ThirdParty/zstd/compress/huf_compress.c"
	"../Siv3D/src/ThirdParty/zstd/compress/zstd_compress.c"
	"../Siv3D/src/ThirdParty/zstd/compress/zstd_compress_literals.c"
	"../Siv3D/src/ThirdParty/zstd/compress/zstd_compress_sequences.c"
	"../Siv3D/src/ThirdParty/zstd/compress/zstd_double_fast.c"
	"../Siv3D/src/ThirdParty/zstd/compress/zstd_fast.c"
	"../Siv3D/src/ThirdParty/zstd/compress/zstd_lazy.c"
	"../Siv3D/src/ThirdParty/zstd/compress/zstd_ldm.c"
	"../Siv3D/src/ThirdParty/zstd/compress/zstd_opt.c"
	"../Siv3D/src/ThirdParty/zstd/compress/zstdmt_compress.c"
	"../Siv3D/src/ThirdParty/zstd/decompress/huf_decompress.c"
	"../Siv3D/src/ThirdParty/zstd/decompress/zstd_ddict.c"
	"../Siv3D/src/ThirdParty/zstd/decompress/zstd_decompress.c"
	"../Siv3D/src/ThirdParty/zstd/decompress/zstd_decompress_block.c"
	"../Siv3D/src/ThirdParty/zstd/dictBuilder/cover.c"
	"../Siv3D/src/ThirdParty/zstd/dictBuilder/divsufsort.c"
	"../Siv3D/src/ThirdParty/zstd/dictBuilder/fastcover.c"
	"../Siv3D/src/ThirdParty/zstd/dictBuilder/zdict.c"
	"../Siv3D/src/ThirdParty/GLFW/context.c"
	"../Siv3D/src/ThirdParty/GLFW/egl_context.c"
	"../Siv3D/src/ThirdParty/GLFW/init.c"
	"../Siv3D/src/ThirdParty/GLFW/input.c"
	"../Siv3D/src/ThirdParty/GLFW/monitor.c"
	"../Siv3D/src/ThirdParty/GLFW/posix_thread.c"
	"../Siv3D/src/ThirdParty/GLFW/vulkan.c"
	"../Siv3D/src/ThirdParty/GLFW/window.c"
	"../Siv3D/src/ThirdParty/GLFW/glx_context.c"
	"../Siv3D/src/ThirdParty/GLFW/osmesa_context.c"
	"../Siv3D/src/ThirdParty/GLFW/linux_joystick.c"
	"../Siv3D/src/ThirdParty/GLFW/posix_time.c"
	"../Siv3D/src/ThirdParty/GLFW/x11_init.c"
	"../Siv3D/src/ThirdParty/GLFW/x11_monitor.c"
	"../Siv3D/src/ThirdParty/GLFW/x11_window.c"
	"../Siv3D/src/ThirdParty/GLFW/xkb_unicode.c"
	"../Siv3D/src/ThirdParty/RtAudio/RtAudio.cpp"
)

add_library(Siv3D STATIC ${SOURCE_FILES})

target_link_libraries(Siv3D
)

