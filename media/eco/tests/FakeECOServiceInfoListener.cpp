/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "FakeFakeECOServiceInfoListener"

#include "FakeECOServiceInfoListener.h"

#include <android-base/unique_fd.h>
#include <android/binder_parcel.h>
#include <cutils/ashmem.h>
#include <gtest/gtest.h>
#include <math.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <utils/Log.h>

namespace android {
namespace media {
namespace eco {

FakeECOServiceInfoListener::FakeECOServiceInfoListener(int32_t width, int32_t height,
                                                       bool isCameraRecording,
                                                       std::shared_ptr<IECOSession> session)
      : mWidth(width),
        mHeight(height),
        mIsCameraRecording(isCameraRecording),
        mECOSession(session) {
    ALOGD("FakeECOServiceInfoListener construct with w: %d, h: %d, isCameraRecording: %d", mWidth,
          mHeight, mIsCameraRecording);
}

FakeECOServiceInfoListener::FakeECOServiceInfoListener(int32_t width, int32_t height,
                                                       bool isCameraRecording)
      : mWidth(width), mHeight(height), mIsCameraRecording(isCameraRecording) {
    ALOGD("FakeECOServiceInfoListener construct with w: %d, h: %d, isCameraRecording: %d", mWidth,
          mHeight, mIsCameraRecording);
}

FakeECOServiceInfoListener::~FakeECOServiceInfoListener() {
    ALOGD("FakeECOServiceInfoListener destructor");
}

ndk::ScopedAStatus FakeECOServiceInfoListener::getType(int32_t* /*_aidl_return*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus FakeECOServiceInfoListener::getName(std::string* _aidl_return) {
    *_aidl_return = std::string("FakeECOServiceInfoListener");
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus FakeECOServiceInfoListener::getECOSession(::ndk::SpAIBinder* _aidl_return) {
    *_aidl_return = mECOSession->asBinder();
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus FakeECOServiceInfoListener::onNewInfo(
        const ::android::media::eco::ECOData& newInfo) {
    ALOGD("FakeECOServiceInfoListener get new info");
    mInfoAvaiableCallback(newInfo);
    return ndk::ScopedAStatus::ok();
}

// IBinder::DeathRecipient implementation
void FakeECOServiceInfoListener::binderDied(const std::weak_ptr<AIBinder>& /*who*/) {}

}  // namespace eco
}  // namespace media
}  // namespace android
