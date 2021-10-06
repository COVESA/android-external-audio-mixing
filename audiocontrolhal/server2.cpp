// Copyright (C) 2020 TietoEVRY
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>

#include "AudioControlServer.h"

int main() {
    std::string server_address = "192.168.1.19:50050";
    GeniviAudioControlServer server;
    std::cout << "Running gRPC server";
    server.makeServer(server_address);
    return 0;
}

