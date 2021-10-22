// Copyright (C) 2021 TietoEVRY
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <unistd.h>

#include <android-base/logging.h>
#include <android/binder_process.h>
#include <hidl/HidlTransportSupport.h>
#include <utils/Errors.h>
#include <utils/Looper.h>
#include <utils/StrongPointer.h>

#include "AudioControl.h"

// libhidl:
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

// Generated HIDL files
using android::hardware::automotive::audiocontrol::V1_0::IAudioControl;

using android::Looper;
using android::OK;
using android::hardware::automotive::audiocontrol::implementation::AudioControl;
//using android::hardware::automotive::audiocontrol::implementation::WatchdogClient;


// Main service entry point
int main() {
    // Create an instance of our service class
    android::sp<AudioControl> service = new AudioControl();
    configureRpcThreadpool(4, false /*callerWillJoin*/);

    if (service->registerAsService() != OK) {
        LOG(ERROR) << "registerAsService failed";
        return 1;
    }
    joinRpcThreadpool();

    // Setup a binder thread pool to be a car watchdog client.
//    ABinderProcess_setThreadPoolMaxThreadCount(1);
//    ABinderProcess_startThreadPool();
//    android::sp<Looper> looper(Looper::prepare(0 /* opts */));
//    std::shared_ptr<WatchdogClient> watchdogClient =
//            ndk::SharedRefBase::make<WatchdogClient>(looper, service.get());
//    if (!watchdogClient->initialize()) {
//        ALOGE("Failed to initialize car watchdog client");
//        return 1;
//    }
    ALOGI("Ready");
//    while (true) {
//        looper->pollAll(-1 /* timeoutMillis */);
//    }

    // We don't ever actually expect to return, so return an error if we do get here
    return 1;
}
