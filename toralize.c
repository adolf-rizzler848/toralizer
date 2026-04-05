#include "toralize.h"

Req* request(struct sockaddr_in *sock2) {
    Req *req = malloc(reqsize);
    req->vn      = 4;
    req->cd      = 1;
    req->dstport = sock2->sin_port;         
    req->dstip   = sock2->sin_addr.s_addr;  
    strncpy((char*)req->userid, USERNAME, 8);
    return req;
}
int connect(int s2, const struct sockaddr *sock2, socklen_t addrlen) {
    int s;
    struct sockaddr_in sock;
    Req *req;
    Res *res;
    char buf[ressize];

    int (*real_connect)(int, const struct sockaddr*, socklen_t);
    real_connect = dlsym(RTLD_NEXT, "connect");

    s = socket(AF_INET, SOCK_STREAM, 0);

    sock.sin_family      = AF_INET;
    sock.sin_port        = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);

 
    real_connect(s, (struct sockaddr*)&sock, sizeof(sock));
    printf("Connected to Proxy\n");

    //building and sending
    req = request((struct sockaddr_in*)sock2);
    write(s, req, reqsize);

    //reading the respone of tor
    memset(buf, 0, ressize);
    read(s, buf, ressize);
    res = (Res*)buf;

    
    if (res->cd != 90) {
        fprintf(stderr, "Proxy rejected: code %d\n", res->cd);
        free(req); close(s);
        return -1;
    }

    printf("Connected through the proxy.\n");

    
    dup2(s, s2);

    free(req);
    close(s);
    return 0;
}