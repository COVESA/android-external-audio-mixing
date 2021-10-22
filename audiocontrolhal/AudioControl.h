// Copyright (C) 2021 TietoEVRY
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <android/hardware/automotive/audiocontrol/1.0/IAudioControl.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android::hardware::automotive::audiocontrol::implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct AudioControl : public V1_0::IAudioControl {
    // Methods from ::android::hardware::automotive::audiocontrol::V1_0::IAudioControl follow.
    Return<int32_t> getBusForContext(::android::hardware::automotive::audiocontrol::V1_0::ContextNumber contextNumber) override;
    Return<void> setBalanceTowardRight(float value) override;
    Return<void> setFadeTowardFront(float value) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IAudioControl* HIDL_FETCH_IAudioControl(const char* name);

}  // namespace android::hardware::automotive::audiocontrol::implementation
