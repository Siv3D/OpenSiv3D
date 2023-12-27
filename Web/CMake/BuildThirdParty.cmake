add_library(absl)

target_sources(absl
    PRIVATE
        ../Siv3D/src/ThirdParty/absl/numeric/int128.cc
        ../Siv3D/src/ThirdParty/absl/random/discrete_distribution.cc
        ../Siv3D/src/ThirdParty/absl/random/gaussian_distribution.cc
)



add_library(box2d)

target_sources(box2d
    PRIVATE
        ../Siv3D/src/ThirdParty/box2d/collision/b2_broad_phase.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_chain_shape.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_circle_shape.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_collide_circle.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_collide_edge.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_collide_polygon.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_collision.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_distance.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_dynamic_tree.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_edge_shape.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_polygon_shape.cpp
        ../Siv3D/src/ThirdParty/box2d/collision/b2_time_of_impact.cpp
        ../Siv3D/src/ThirdParty/box2d/common/b2_block_allocator.cpp
        ../Siv3D/src/ThirdParty/box2d/common/b2_draw.cpp
        ../Siv3D/src/ThirdParty/box2d/common/b2_math.cpp
        ../Siv3D/src/ThirdParty/box2d/common/b2_settings.cpp
        ../Siv3D/src/ThirdParty/box2d/common/b2_stack_allocator.cpp
        ../Siv3D/src/ThirdParty/box2d/common/b2_timer.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_body.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_chain_circle_contact.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_chain_polygon_contact.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_circle_contact.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_contact.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_contact_manager.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_contact_solver.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_distance_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_edge_circle_contact.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_edge_polygon_contact.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_fixture.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_friction_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_gear_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_island.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_motor_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_mouse_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_polygon_circle_contact.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_polygon_contact.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_prismatic_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_pulley_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_revolute_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_weld_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_wheel_joint.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_world.cpp
        ../Siv3D/src/ThirdParty/box2d/dynamics/b2_world_callbacks.cpp
        ../Siv3D/src/ThirdParty/box2d/rope/b2_rope.cpp    
)



add_library(cpu_features)

target_sources(cpu_features
    PRIVATE
        # ../Siv3D/src/ThirdParty/cpu_features/cpuinfo_x86.c
        ../Siv3D/src/ThirdParty/cpu_features/filesystem.c
        ../Siv3D/src/ThirdParty/cpu_features/stack_line_reader.c
        ../Siv3D/src/ThirdParty/cpu_features/string_view.c
)



add_library(double_conversion)

target_sources(double_conversion
    PRIVATE
        ../Siv3D/src/ThirdParty/double-conversion/bignum-dtoa.cc
        ../Siv3D/src/ThirdParty/double-conversion/bignum.cc
        ../Siv3D/src/ThirdParty/double-conversion/cached-powers.cc
        ../Siv3D/src/ThirdParty/double-conversion/double-to-string.cc
        ../Siv3D/src/ThirdParty/double-conversion/fast-dtoa.cc
        ../Siv3D/src/ThirdParty/double-conversion/fixed-dtoa.cc
)



add_library(easyexif)

target_sources(easyexif
    PRIVATE
        ../Siv3D/src/ThirdParty/easyexif/exif.cpp
)



add_library(fmt)

target_sources(fmt
    PRIVATE
        ../Siv3D/src/ThirdParty/fmt/format.cc
)



add_library(lua)

target_sources(lua
    PRIVATE
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
)



add_library(lunasvg)

target_sources(lunasvg
    PRIVATE
        ../Siv3D/src/ThirdParty/lunasvg/canvas.cpp
        ../Siv3D/src/ThirdParty/lunasvg/clippathelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/defselement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/element.cpp
        ../Siv3D/src/ThirdParty/lunasvg/gelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/geometryelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/graphicselement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/layoutcontext.cpp
        ../Siv3D/src/ThirdParty/lunasvg/markerelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/maskelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/paintelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/parser.cpp
        ../Siv3D/src/ThirdParty/lunasvg/property.cpp
        ../Siv3D/src/ThirdParty/lunasvg/stopelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/styledelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/svgelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/symbolelement.cpp
        ../Siv3D/src/ThirdParty/lunasvg/useelement.cpp
)



add_library(minizip)

target_sources(minizip
    PRIVATE
        ../Siv3D/src/ThirdParty/minizip/mz_compat.c
        ../Siv3D/src/ThirdParty/minizip/mz_crypt.c
        ../Siv3D/src/ThirdParty/minizip/mz_crypt_brg.c
        ../Siv3D/src/ThirdParty/minizip/mz_os.c
        ../Siv3D/src/ThirdParty/minizip/mz_os_posix.c
        ../Siv3D/src/ThirdParty/minizip/mz_strm.c
        ../Siv3D/src/ThirdParty/minizip/mz_strm_buf.c
        ../Siv3D/src/ThirdParty/minizip/mz_strm_mem.c
        ../Siv3D/src/ThirdParty/minizip/mz_strm_os_posix.c
        ../Siv3D/src/ThirdParty/minizip/mz_strm_pkcrypt.c
        ../Siv3D/src/ThirdParty/minizip/mz_strm_split.c
        ../Siv3D/src/ThirdParty/minizip/mz_strm_wzaes.c
        ../Siv3D/src/ThirdParty/minizip/mz_strm_zlib.c
        ../Siv3D/src/ThirdParty/minizip/mz_zip.c
        ../Siv3D/src/ThirdParty/minizip/mz_zip_rw.c
)



add_library(msdfgen)

target_sources(msdfgen
    PRIVATE
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
)



add_library(muparser)

target_sources(muparser
    PRIVATE
        ../Siv3D/src/ThirdParty/muparser/muParser.cpp
        ../Siv3D/src/ThirdParty/muparser/muParserBase.cpp
        ../Siv3D/src/ThirdParty/muparser/muParserBytecode.cpp
        ../Siv3D/src/ThirdParty/muparser/muParserCallback.cpp
        ../Siv3D/src/ThirdParty/muparser/muParserError.cpp
        ../Siv3D/src/ThirdParty/muparser/muParserInt.cpp
        ../Siv3D/src/ThirdParty/muparser/muParserTokenReader.cpp
)



add_library(Oniguruma)

target_sources(Oniguruma
    PRIVATE
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
)



add_library(pffft)

target_sources(pffft
    PRIVATE
    ../Siv3D/src/ThirdParty/pffft/pffft.c
)



add_library(plutovg)

target_sources(plutovg
    PRIVATE
        ../Siv3D/src/ThirdParty/plutovg/plutovg-blend.c
        ../Siv3D/src/ThirdParty/plutovg/plutovg-dash.c
        ../Siv3D/src/ThirdParty/plutovg/plutovg-geometry.c
        ../Siv3D/src/ThirdParty/plutovg/plutovg-paint.c
        ../Siv3D/src/ThirdParty/plutovg/plutovg-rle.c
        ../Siv3D/src/ThirdParty/plutovg/plutovg.c
        ../Siv3D/src/ThirdParty/plutovg/sw_ft_math.c
        ../Siv3D/src/ThirdParty/plutovg/sw_ft_raster.c
        ../Siv3D/src/ThirdParty/plutovg/sw_ft_stroker.c
)

add_library(qr)

target_sources(qr
    PRIVATE
        ../Siv3D/src/ThirdParty/qr-code-generator-library/qrcodegen.cpp
)



add_library(quirc)

target_sources(quirc
    PRIVATE
        ../Siv3D/src/ThirdParty/quirc/decode.c
        ../Siv3D/src/ThirdParty/quirc/identify.c
        ../Siv3D/src/ThirdParty/quirc/quirc.c
        ../Siv3D/src/ThirdParty/quirc/version_db.c
)



add_library(RecastDetour)

target_sources(RecastDetour
    PRIVATE
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
)



add_library(rtaudio)

target_sources(rtaudio
    PRIVATE
    ../Siv3D/src/ThirdParty/rtaudio/RtAudio.cpp
)



add_library(serial)

target_sources(serial
    PRIVATE
        ../Siv3D/src/ThirdParty/serial/impl/list_ports/list_ports_linux.cc
        ../Siv3D/src/ThirdParty/serial/impl/unix.cc
        ../Siv3D/src/ThirdParty/serial/serial.cc
)



add_library(soloud)

target_sources(soloud
    PRIVATE
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/monotone/soloud_monotone.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/noise/soloud_noise.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/sfxr/soloud_sfxr.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/darray.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/klatt.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/resonator.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/soloud_speech.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/tts.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/tedsid/sid.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/tedsid/soloud_tedsid.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/tedsid/ted.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/vic/soloud_vic.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/vizsn/soloud_vizsn.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/wav/dr_impl.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/wav/soloud_wav.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/wav/soloud_wavstream.cpp
        ../Siv3D/src/ThirdParty/soloud/src/audiosource/wav/stb_vorbis.c
        ../Siv3D/src/ThirdParty/soloud/src/backend/alsa/soloud_alsa.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/coreaudio/soloud_coreaudio.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/jack/soloud_jack.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/miniaudio/soloud_miniaudio.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/nosound/soloud_nosound.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/null/soloud_null.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/openal/soloud_openal.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/openal/soloud_openal_dll.c
        ../Siv3D/src/ThirdParty/soloud/src/backend/opensles/soloud_opensles.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/oss/soloud_oss.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/portaudio/soloud_portaudio.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/portaudio/soloud_portaudio_dll.c
        ../Siv3D/src/ThirdParty/soloud/src/backend/sdl2_static/soloud_sdl2_static.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/sdl/soloud_sdl1.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/sdl/soloud_sdl1_dll.c
        ../Siv3D/src/ThirdParty/soloud/src/backend/sdl/soloud_sdl2.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/sdl/soloud_sdl2_dll.c
        ../Siv3D/src/ThirdParty/soloud/src/backend/sdl_static/soloud_sdl_static.cpp
        # ../Siv3D/src/ThirdParty/soloud/src/backend/vita_homebrew/soloud_vita_homebrew.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/wasapi/soloud_wasapi.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/winmm/soloud_winmm.cpp
        ../Siv3D/src/ThirdParty/soloud/src/backend/xaudio2/soloud_xaudio2.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_audiosource.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_bus.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_3d.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_basicops.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_faderops.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_filterops.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_getters.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_setters.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_voicegroup.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_voiceops.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_fader.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_fft.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_fft_lut.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_file.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_filter.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_misc.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_queue.cpp
        ../Siv3D/src/ThirdParty/soloud/src/core/soloud_thread.cpp
        ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_biquadresonantfilter.cpp
        ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_dcremovalfilter.cpp
        ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_echofilter.cpp
        ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_eqfilter.cpp
        ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_fftfilter.cpp
        ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_flangerfilter.cpp
        ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_freeverbfilter.cpp
        ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_lofifilter.cpp
)



add_library(SplineLib)

target_sources(SplineLib
    PRIVATE
    ../Siv3D/src/ThirdParty/SplineLib/Splines.cpp
)



add_library(tinyxml)

target_sources(tinyxml
    PRIVATE
        ../Siv3D/src/ThirdParty/tinyxml/tinyxml2.cpp
)



add_library(zstd)

target_sources(zstd
    PRIVATE
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
