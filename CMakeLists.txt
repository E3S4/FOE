cmake_minimum_required(VERSION 3.16)
project(FOE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------
# Dependencies
# ----------------------------

# Qt6 (Widgets & GUI stuff)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# FFmpeg
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET
    libavcodec
    libavformat
    libavutil
    libswscale
    libswresample
)

# FFTW (for audio analysis)
find_package(FFTW3 REQUIRED)

# Eigen (math)
find_package(Eigen3 REQUIRED)

# Optional: OpenCV (for CPU effects)
find_package(OpenCV QUIET)

# ----------------------------
# Sources
# ----------------------------
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(foe ${SOURCES})

# ----------------------------
# Includes
# ----------------------------
target_include_directories(foe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${EIGEN3_INCLUDE_DIR}
    ${FFTW3_INCLUDE_DIRS}
)

# ----------------------------
# Linking
# ----------------------------
target_link_libraries(foe PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    PkgConfig::FFMPEG
    FFTW3::fftw3
)

if(OpenCV_FOUND)
    target_include_directories(foe PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(foe PRIVATE ${OpenCV_LIBS})
endif()

