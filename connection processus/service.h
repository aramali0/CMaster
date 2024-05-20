#ifndef SERVICE_H
#define SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define NBR_MAX_CLIENT 5
#define MAX_NAME_LENGTH 50

void chatter(int d);

#endif 