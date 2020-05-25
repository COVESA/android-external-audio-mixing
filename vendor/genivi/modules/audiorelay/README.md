# Copyright
Copyright (C) 2020, TietoEVRY

# License
This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Overview
genivi.audiorelay is small service which intention is to create named socket for listening and forward data coming from it to IP socket. Idea behind is to send data from Audio HAL to this service and then forward it to end point. Reason for this service is that Audio HAL SELinux policy forbids it to use network socket.
This solution was developed and tested for emulator and is basing on implementation of Audio HAL derived from goldfish. 

genivi.audiorelay will try to send data to `10.0.2.2:5000`. In order to change change const values in `audiorelay.cc`.

## Build instructions
###
Add genivi device to lunch menu (deploy device folder on top of aosp tree).

Deploy the repository inside AOSP tree i.e. `/vendor/genivi/modules/audiorelay` and build:
```
source build/envsetup.sh
lunch genivi_car_x86_64-userdebug
```
You can launch emulator now:
```
emulator
``` 
## Virtualized environment
If you are running your build on virtual machine emulator most probably will not work on you guest. You need to move build artifacts to your host and run emulator there. In order to do this images needs to be copied to folder available on host:

`<path where all images are stored>\system-images\$BUILD_ID`
```
$ANDROID_PRODUCT_OUT/system/build.prop
$ANDROID_PRODUCT_OUT/userdata-qemu.img
$ANDROID_PRODUCT_OUT/system-qemu.img
$ANDROID_PRODUCT_OUT/vendor-qemu.img 
$ANDROID_PRODUCT_OUT/advancedFeatures.ini
$ANDROID_PRODUCT_OUT/encryptionkey.img
$ANDROID_PRODUCT_OUT/kernel-ranchu
$ANDROID_PRODUCT_OUT/ramdisk.img
$ANDROID_PRODUCT_OUT/VerifiedBootParams.textproto
```
Next config file needs to be created:
```
AvdId=$BUILD_ID
PlayStore.enabled=false
abi.type=x86_64
avd.ini.displayname=AOSP API 29
avd.ini.encoding=UTF-8
disk.dataPartition.size=800M
fastboot.chosenSnapshotFile=
fastboot.forceChosenSnapshotBoot=no
fastboot.forceColdBoot=no
fastboot.forceFastBoot=yes
hw.accelerometer=no
hw.arc=false
hw.audioInput=yes
hw.battery=no
hw.camera.back=None
hw.camera.front=None
hw.cpu.arch=x86_64
hw.cpu.ncore=4
hw.dPad=no
hw.device.hash2=MD5:a4efca3a5bf3723f0109829d049371a6
hw.device.manufacturer=Google
hw.device.name=automotive_1024p_landscape
hw.gps=yes
hw.gpu.enabled=yes
hw.gpu.mode=auto
hw.initialOrientation=landscape
hw.keyboard=yes
hw.lcd.density=160
hw.lcd.height=768
hw.lcd.width=1024
hw.mainKeys=no
hw.ramSize=1536
hw.sdCard=no
hw.sensors.orientation=no
hw.sensors.proximity=no
hw.trackBall=no
image.sysdir.1=$SYSTEM_IMAGE_DIR_WIN
runtime.network.latency=none
runtime.network.speed=full
showDeviceFrame=yes
skin.dynamic=yes
tag.display=AOSP
tag.id=android-automotive
vm.heapSize=80
```
Above configuration should be stored in

`<path where all images are stored>\avd\$BUILD_ID.avd`.

Emulator needs also file containing description of launch configuration:
```
avd.ini.encoding=UTF-8
path=<path where all images are stored>\avd\$BUILD_ID.avd
target=android-29
```
Above file needs to be put under following path:

`<path where all images are stored>\avd\$BUILD_ID.ini`

To run emulator following command should be used:
```
set ANDROID_SDK_DIR=C:\Users\<windows user>\AppData\Local\Android\Sdk
set ANDROID_AVD_HOME=<path where all images are stored>\avd
%ANDROID_SDK_DIR%\emulator\emulator.exe -avd $BUILD_DIR -skindir %ANDROID_SDK_DIR%\skins -skin automotive_1024 
```
