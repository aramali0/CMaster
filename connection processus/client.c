#include "client.h"

void chatter(int ds) {
    char pseudo_name_server[MAX_NAME_LENGTH];
    char pseudo_name[MAX_NAME_LENGTH];
    char msg_recu[MAX_NAME_LENGTH];
    char msg_env[MAX_NAME_LENGTH];

    printf("Listening...\n");
    recv(ds, pseudo_name_server, sizeof(pseudo_name_server), 0);
    printf("Server Pseudo name: %s\n", pseudo_name_server);
    printf("Pseudo name: ");
    fgets(pseudo_name, MAX_NAME_LENGTH, stdin);
    pseudo_name[strcspn(pseudo_name, "\n")] = '\0'; 
    send(ds, pseudo_name, strlen(pseudo_name) + 1, 0);

    while (1) {
        strcpy(msg_env, "");
        strcpy(msg_recu, "");
        printf("Enter message: ");
        fgets(msg_env, MAX_NAME_LENGTH, stdin);
        msg_env[strcspn(msg_env, "\n")] = '\0'; 
        send(ds, msg_env, strlen(msg_env) + 1, 0);
        printf("Listening...\n");
        recv(ds, msg_recu, sizeof(msg_recu), 0);
        printf("Server says: %s\n", msg_recu);

        if (strcmp(msg_recu, "quitter") == 0 || strcmp(msg_env, "quitter") == 0)
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <IP_address> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int ds;
    struct sockaddr_in addr_socket_server;

    ds = socket(AF_INET, SOCK_STREAM, 0);
    if (ds < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr_socket_server, 0, sizeof(addr_socket_server));
    addr_socket_server.sin_family = AF_INET;
    addr_socket_server.sin_addr.s_addr = inet_addr(argv[1]);
    addr_socket_server.sin_port = htons(atoi(argv[2]));

    if (connect(ds, (struct sockaddr *)&addr_socket_server, sizeof(addr_socket_server)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    printf("Client connected successfully\n");
    chatter(ds);

    close(ds);
    return 0;
}

