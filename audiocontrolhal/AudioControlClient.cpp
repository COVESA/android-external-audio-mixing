// Copyright (C) 2021 TietoEVRY
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <grpc++/grpc++.h>

#include "GeniviAudioControl.grpc.pb.h"
#include "AudioControlClient.h"

static const std::string SERVER_ADDRESS = "vsock:2:5599";

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using genivi_audio_control_proto::GeniviAudioControl;

void AudioControlClient::setBalanceTowardRight(float value) {
    ::grpc::ClientContext context;
    auto channel = grpc::CreateChannel(SERVER_ADDRESS, grpc::InsecureChannelCredentials());
    auto stub = GeniviAudioControl::NewStub(channel);
    ::google::protobuf::FloatValue valueSet;
    valueSet.set_value(value);
    ::google::protobuf::Int32Value reply;
    stub->setBalanceTowardRight(&context, valueSet, &reply);
}

void AudioControlClient::setFadeTowardFront(float value) {
    ::grpc::ClientContext context;
    auto channel = grpc::CreateChannel(SERVER_ADDRESS, grpc::InsecureChannelCredentials());
    auto stub = GeniviAudioControl::NewStub(channel);
    ::google::protobuf::FloatValue valueSet;
    valueSet.set_value(value);
    ::google::protobuf::Int32Value reply;
    stub->setFadeTowardFront(&context, valueSet, &reply);
}
