#ifndef TORALIZE_H
#define TORALIZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dlfcn.h>

#define PROXY      "127.0.0.1"
#define PROXYPORT  9050
#define USERNAME   "user"

typedef unsigned char  int8;
typedef unsigned short int16;
typedef unsigned int   int32;

// Sock4 request pcket
struct proxy_request {
    int8  vn;       
    int8  cd;       // connect cmnd
    int16 dstport;  
    int32 dstip;    
    unsigned char userid[8];
};

//response pacet
struct proxy_response {
    int8  vn;   
    int8  cd;   
    int16 _;
    int32 __;
};

typedef struct proxy_request  Req;
typedef struct proxy_response Res;

#define reqsize sizeof(Req)
#define ressize sizeof(Res)

Req* request(struct sockaddr_in*);
int  connect(int, const struct sockaddr*, socklen_t);

#endif