#include "service.h"

void chatter(int d) {
    char pseudo_name[MAX_NAME_LENGTH];
    char pseudo_name_client[MAX_NAME_LENGTH];
    char msg_recu[MAX_NAME_LENGTH];
    char msg_env[MAX_NAME_LENGTH];

    printf("Pseudo name: ");
    fgets(pseudo_name, MAX_NAME_LENGTH, stdin);
    pseudo_name[strcspn(pseudo_name, "\n")] = '\0'; 
    send(d, pseudo_name, strlen(pseudo_name) + 1, 0);
    recv(d, pseudo_name_client, sizeof(pseudo_name_client), 0);
    printf("Listening...\n");
    printf("Pseudo name of remote user: %s\n", pseudo_name_client);

    while (1) {
        strcpy(msg_recu, "");
        strcpy(msg_env, "");
        printf("Listening...\n");
        recv(d, msg_recu, sizeof(msg_recu), 0);
        printf("%s says: %s\n", pseudo_name_client, msg_recu);
        if (strcmp(msg_recu, "quitter") == 0)
            break;
        printf("Enter message: ");
        fgets(msg_env, MAX_NAME_LENGTH, stdin);
        msg_env[strcspn(msg_env, "\n")] = '\0'; 
        send(d, msg_env, strlen(msg_env) + 1, 0);
        if (strcmp(msg_env, "quitter") == 0)
            break;
    }
}

int main(int argc, char *argv[]) {
    int dsm, dsc, port, err;
    struct sockaddr_in addr_socket_local, addr_socket_client;
    socklen_t addr_len = sizeof(addr_socket_client);

    dsm = socket(AF_INET, SOCK_STREAM, 0);
    if (dsm < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    port = atoi(argv[1]);

    memset(&addr_socket_local, 0, sizeof(addr_socket_local));
    addr_socket_local.sin_family = AF_INET;
    addr_socket_local.sin_addr.s_addr = INADDR_ANY; 
    addr_socket_local.sin_port = htons(port);

    printf("Binding...\n");
    err = bind(dsm, (struct sockaddr *)&addr_socket_local, sizeof(addr_socket_local));
    if (err < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    printf("Listening...\n");
    err = listen(dsm, NBR_MAX_CLIENT);
    if (err < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        dsc = accept(dsm, (struct sockaddr *)&addr_socket_client, &addr_len);
        if (dsc < 0) {
            perror("accept");
            continue;
        }
        printf("Client connected @ %s\n", inet_ntoa(addr_socket_client.sin_addr));
        chatter(dsc);
        close(dsc);
    }

    close(dsm);
    return 0;
}

