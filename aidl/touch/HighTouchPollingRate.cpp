/*
 * SPDX-FileCopyrightText: 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch-service.oplus"

#include "HighTouchPollingRate.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>

#include <HighTouchPollingRateConfig.h>

using ::android::base::ReadFileToString;
using ::android::base::Trim;
using ::android::base::WriteStringToFile;

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

HighTouchPollingRate::HighTouchPollingRate(std::shared_ptr<IOplusTouch> oplusTouch)
    : mOplusTouch(std::move(oplusTouch)) {}

ndk::ScopedAStatus HighTouchPollingRate::getEnabled(bool* _aidl_return) {
    std::string value;

    if (!ReadFileToString(kHighTouchPollingRatePath, &value)) {
        LOG(ERROR) << "Failed to read HighTouchPollingRate state";
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    *_aidl_return = Trim(value)[0] != '0';
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus HighTouchPollingRate::setEnabled(bool enable) {
    if (!WriteStringToFile(enable ? "1" : "0", kHighTouchPollingRatePath, true)) {
        LOG(ERROR) << "Failed to write HighTouchPollingRate state";
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
