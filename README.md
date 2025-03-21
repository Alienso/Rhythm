# Rhythm

2D rhythmic arena shooter prototype

![screenshot](/screenshots/1.jpg)

## How to run

* run *vcpkg install* ( or *vcpkg install --triplet x64-mingw-dynamic --host-triplet x64-mingw-dynamic* if you are on minGW)
* set *CMAKE_TOOLCHAIN_FILE* to *{VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake*
* in case portaudio starts spamming to console, build lib with release mode


The audio files for music ARE missing, so you will need to supply some in a form of WAV files with INT_16 as underlying data type
After that, it should work.
