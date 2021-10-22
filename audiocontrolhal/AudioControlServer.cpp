// Copyright (C) 2021 TietoEVRY
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <grpc++/grpc++.h>
#include <iostream>
#include <sstream>

#include "GeniviAudioControl.grpc.pb.h"
#include "AudioControlServer.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using genivi_audio_control_proto::GeniviAudioControl;

class GeniviAudioControlServerImpl final : public GeniviAudioControl::Service {
    ::grpc::Status setBalanceTowardRight(::grpc::ServerContext* context,
                                         const ::google::protobuf::FloatValue* request,
                                         ::google::protobuf::Int32Value* response) {
        std::cout << "Balance request: " << request->value() << "\n";
        std::ostringstream command;
        if (request->value() < 0) {
            int new_volume = 100 - (request->value() * -100);
            command << "amixer sset PCM 100%," << new_volume << "%";
        } else {
            int new_volume = 100 - (request->value() * 100);
            command << "amixer sset PCM "<< new_volume << "%,100%";
        }
        int ret = system(command.str().c_str());
        if (ret) {
            std::cerr << command.str().c_str() << "\n";
        }
        return Status::OK;
    }
    ::grpc::Status setFadeTowardFront(::grpc::ServerContext* context,
                                      const ::google::protobuf::FloatValue* request,
                                      ::google::protobuf::Int32Value* response) {
        std::cout << "Fade request: " << request->value() << "\n";
        return Status::OK;
    }
};

void GeniviAudioControlServer::makeServer(const std::string address) {
    ServerBuilder builder;
    GeniviAudioControlServerImpl service;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();
}
