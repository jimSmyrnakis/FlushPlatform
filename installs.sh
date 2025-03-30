#!/bin/bash








ARCH=$(uname -m)

if [[ "$ARCH" == "x86_64" ]]; then
    echo "64-bit (x86_64)."
    
    echo "gcc , g++ for x64 current architecture " 
    sudo apt install gcc g++
    
    echo "gcc , g++ multilib support for x86 architecture cross compilation too"
    sudo apt install g++-multilib gcc-multilib
    
    echo "gcc , g++ for arm 32 bit architecture "
    sudo apt install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
    
    echo "gcc , g++ for arm64 bit architecture "
    sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
elif [[ "$ARCH" == "i686" || "$ARCH" == "i386" ]]; then
    echo "32-bit (x86)."
    
    echo "gcc , g++ for x86 current architecture "
    sudo apt install gcc g++
    
    echo "gcc , g++ for x64 architecture "
    sudo apt install gcc-x86-64-linux-gnu g++-x86-64-linux-gnu
    
    echo "gcc , g++ for arm 32 bit architecture "
    sudo apt install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
    
    echo "gcc , g++ for arm64 bit architecture "
    sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
elif [[ "$ARCH" == "armv7l" ]]; then
    echo "ARM 32-bit (ARMv7)."
    
    echo "gcc , g++ for ARM 32-bit (ARMv7) current architecture "
    sudo apt install gcc g++

    echo "gcc , g++ for arm64 bit architecture "
    sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu

    echo "gcc , g++ for x64 architecture "
    sudo apt install gcc-x86-64-linux-gnu g++-x86-64-linux-gnu

    echo "gcc , g++ for x86 -32bit architecture "
    sudo apt install gcc-i686-linux-gnu g++-i686-linux-gnu

elif [[ "$ARCH" == "aarch64" ]]; then
    echo "ARM 64-bit (AArch64)."

    echo "gcc , g++ for ARM 64-bit (AArch64) current architecture "
    sudo apt install gcc g++

    echo "gcc , g++ for arm 32 bit architecture "
    sudo apt install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf

    echo "gcc , g++ for x64 architecture "
    sudo apt install gcc-x86-64-linux-gnu g++-x86-64-linux-gnu

    echo "gcc , g++ for x86 -32bit architecture "
    sudo apt install gcc-i686-linux-gnu g++-i686-linux-gnu    

else
    echo "Not Supported Architecture : $ARCH"
fi
