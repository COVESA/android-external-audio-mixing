// Copyright (C) 2020 TietoEVRY
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <linux/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <map>
#include <vector>
#include <string>

#include <android/log.h>

#define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

const char* kServerSocketPrefix = "#genivi_audio_relay_in_";
const char* kTargetAudioIp = "10.0.2.2";
const int kTargetAudioPort = 5000;

const uint64_t kRecvBufferLength = 1024 * 5;
bool local_shutdown = false;

#undef LOG_TAG
#define LOG_TAG "GeniviAudioRelay"

std::map<std::string, int> bus_sockets = {
    {"bus0_media_out", 5000  },
    {"bus3_call_ring_out", 5001 },
    {"bus6_notification_out", 5002 },
    {"bus7_system_sound_out", 5003 },
    {"bus1_navigation_out", 5004 },
    {"bus2_voice_command_out", 5005 },
    {"bus4_call_out", 5006 },
    {"bus5_alarm_out", 5007 }
};

int create_server(int *fd, std::string socket_name) {
    if ((*fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
        LOGE("Cannot create socket %s", socket_name.c_str());
        return -1;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", socket_name.c_str());
    // Create abstract domain unix socket
    addr.sun_path[0] = 0;

    if (bind(*fd, (struct sockaddr *)&addr,
             (socklen_t)(sizeof(sa_family_t) + strlen(socket_name.c_str()))) < 0) {
      LOGE("Bind error, errno: %d, %s", errno, strerror(errno));
      return -1;
    }

    LOGI("Server created successfully");
    return 0;
}

int create_client_socket(int* sockfd, const char* address, int port) {
    if((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      LOGE("PK>> Cant create audio socket %d, error: %s", errno, strerror(errno));
    }
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(address);
    serv_addr.sin_port = htons(port);
    if (connect(*sockfd, (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0)
    {
      LOGE("PK>> Cant connect audio socket %d %s", errno, strerror(errno));
    }
    LOGI("Client socket created successfully");
    return 0;
}

static void *forward(void* args) {
    std::string bus_address(static_cast<char*>(args));
    int server_fd;
    int send_to_fd;
    char buffer[kRecvBufferLength];
    LOGD("PK>> creating server: %s", (kServerSocketPrefix + bus_address).c_str());
    create_server(&server_fd, kServerSocketPrefix + bus_address);
    LOGD("PK>> creating client socket to port %d", bus_sockets[bus_address]);
    create_client_socket(&send_to_fd, kTargetAudioIp, bus_sockets[bus_address]);
    int received = -1;
    int sent = -1;

    while (!local_shutdown) {
      received = recv(server_fd, buffer, kRecvBufferLength, 0);
      if (received <= 0) {
        LOGE("PK>> Error in receiving %d %s", received, strerror(errno));
      }
      sent = send(send_to_fd, buffer, received, 0);
      if (sent != received) {
        LOGI("PK>> Sending partial buffer recv: %d, sent: %d, errno: %d", received, sent, errno);
      }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
  std::vector<pthread_t> relays;
  pthread_t relay;
  for (auto entry : bus_sockets) {
    LOGD("PK>> Creating thread for bus address: %s", entry.first.c_str());
    //TODO clean it up later
    char* bus_address = new char[entry.first.length() + 1];
    strcpy(bus_address, entry.first.c_str());
    pthread_create(&relay, NULL, forward, (void *) bus_address);
    relays.push_back(relay);
  }

  for (auto i = relays.begin(); i != relays.end(); ++i) {
    pthread_join(*i, NULL);
  }
  LOGI("Shutting down.");
  return 0;
}