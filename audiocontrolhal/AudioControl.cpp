// Copyright (C) 2021 TietoEVRY
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <utils/Log.h>

#include "AudioControl.h"
#include "AudioControlClient.h"

namespace android::hardware::automotive::audiocontrol::implementation {

// Methods from ::android::hardware::automotive::audiocontrol::V1_0::IAudioControl follow.
Return<int32_t> AudioControl::getBusForContext(::android::hardware::automotive::audiocontrol::V1_0::ContextNumber /*contextNumber*/) {
    // TODO implement
    return int32_t {};
}

Return<void> AudioControl::setBalanceTowardRight(float value) {
    ALOGI("Changing balance");
    AudioControlClient::setBalanceTowardRight(value);
    return Void();
}

Return<void> AudioControl::setFadeTowardFront(float /*value*/) {
    ALOGI("Changing fade");
    // TODO implement
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//IAudioControl* HIDL_FETCH_IAudioControl(const char* /* name */) {
    //return new AudioControl();
//}
//
}  // namespace android::hardware::automotive::audiocontrol::implementation
