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