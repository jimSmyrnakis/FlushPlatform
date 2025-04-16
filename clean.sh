#!/bin/bash



ARCH=$(uname -m)

if [[ "$ARCH" == "x86_64" ]]; then


make clean MODE_PLATFORM=debug-x64 CURRENT_PLATFORM=x64
make clean MODE_PLATFORM=release-x64 CURRENT_PLATFORM=x64
make clean MODE_PLATFORM=dist-x64 CURRENT_PLATFORM=x64

make clean MODE_PLATFORM=debug-x86 CURRENT_PLATFORM=x64
make clean MODE_PLATFORM=release-x86 CURRENT_PLATFORM=x64
make clean MODE_PLATFORM=dist-x86 CURRENT_PLATFORM=x64

make clean MODE_PLATFORM=debug-arm32 CURRENT_PLATFORM=x64
make clean MODE_PLATFORM=release-arm32 CURRENT_PLATFORM=x64
make clean MODE_PLATFORM=dist-arm32 CURRENT_PLATFORM=x64

make clean MODE_PLATFORM=debug-arm64 CURRENT_PLATFORM=x64
make clean MODE_PLATFORM=release-arm64 CURRENT_PLATFORM=x64
make clean MODE_PLATFORM=dist-arm64 CURRENT_PLATFORM=x64
    
elif [[ "$ARCH" == "i686" || "$ARCH" == "i386" ]]; then


make clean MODE_PLATFORM=debug-x64 CURRENT_PLATFORM=x86
make clean MODE_PLATFORM=release-x64 CURRENT_PLATFORM=x86
make clean MODE_PLATFORM=dist-x64 CURRENT_PLATFORM=x86

make clean MODE_PLATFORM=debug-x86 CURRENT_PLATFORM=x86
make clean MODE_PLATFORM=release-x86 CURRENT_PLATFORM=x86
make clean MODE_PLATFORM=dist-x86 CURRENT_PLATFORM=x86

make clean MODE_PLATFORM=debug-arm32 CURRENT_PLATFORM=x86
make clean MODE_PLATFORM=release-arm32 CURRENT_PLATFORM=x86
make clean MODE_PLATFORM=dist-arm32 CURRENT_PLATFORM=x86

make clean MODE_PLATFORM=debug-arm64 CURRENT_PLATFORM=x86
make clean MODE_PLATFORM=release-arm64 CURRENT_PLATFORM=x86
make clean MODE_PLATFORM=dist-arm64 CURRENT_PLATFORM=x86
    
elif [[ "$ARCH" == "armv7l" ]]; then


make clean MODE_PLATFORM=debug-x64 CURRENT_PLATFORM=arm32
make clean MODE_PLATFORM=release-x64 CURRENT_PLATFORM=arm32
make clean MODE_PLATFORM=dist-x64 CURRENT_PLATFORM=arm32

make clean MODE_PLATFORM=debug-x86 CURRENT_PLATFORM=arm32
make clean MODE_PLATFORM=release-x86 CURRENT_PLATFORM=arm32
make clean MODE_PLATFORM=dist-x86 CURRENT_PLATFORM=arm32

make clean MODE_PLATFORM=debug-arm32 CURRENT_PLATFORM=arm32
make clean MODE_PLATFORM=release-arm32 CURRENT_PLATFORM=arm32
make clean MODE_PLATFORM=dist-arm32 CURRENT_PLATFORM=arm32

make clean MODE_PLATFORM=debug-arm64 CURRENT_PLATFORM=arm32
make clean MODE_PLATFORM=release-arm64 CURRENT_PLATFORM=arm32
make clean MODE_PLATFORM=dist-arm64 CURRENT_PLATFORM=arm32

elif [[ "$ARCH" == "aarch64" ]]; then  


make clean MODE_PLATFORM=debug-x64 CURRENT_PLATFORM=arm64
make clean MODE_PLATFORM=release-x64 CURRENT_PLATFORM=arm64
make clean MODE_PLATFORM=dist-x64 CURRENT_PLATFORM=arm64

make clean MODE_PLATFORM=debug-x86 CURRENT_PLATFORM=arm64
make clean MODE_PLATFORM=release-x86 CURRENT_PLATFORM=arm64
make clean MODE_PLATFORM=dist-x86 CURRENT_PLATFORM=arm64

make clean MODE_PLATFORM=debug-arm32 CURRENT_PLATFORM=arm64
make clean MODE_PLATFORM=release-arm32 CURRENT_PLATFORM=arm64
make clean MODE_PLATFORM=dist-arm32 CURRENT_PLATFORM=arm64

make clean MODE_PLATFORM=debug-arm64 CURRENT_PLATFORM=arm64
make clean MODE_PLATFORM=release-arm64 CURRENT_PLATFORM=arm64
make clean MODE_PLATFORM=dist-arm64 CURRENT_PLATFORM=arm64

else
    echo "Not Supported Architecture : $ARCH"
fi
