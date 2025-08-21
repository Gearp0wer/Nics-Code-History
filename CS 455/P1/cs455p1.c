#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <Winsock2.h>

void dnsGenerator(const char *hostname, const char *queryType);
void dnsOutbound(const unsigned char * query, int queryLength);
uint16_t randomID();
void dnsReceiver(const unsigned char * response, int responseLength);

struct headerStruct {
    uint16_t id;
    uint16_t flags;
    uint16_t questionCount;
    uint16_t answerCount;
    uint16_t authCount;
    uint16_t recordsCount;
};
int main() {
    WSADATA wsa;
    char hostname[100];
    char queryType[4];

    if (WSAStartup(MAKEWORD(2, 2), & wsa) != 0) {
        printf("Failed to initialize Winsock. Error: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Please enter the hostname (or type 'QUIT' to exit): ");
    if (fgets(hostname, sizeof(hostname), stdin) == NULL) {
        printf("Error reading hostname.\n");
    }
    hostname[strcspn(hostname, "\n")] = 0; // Remove newline character

    if (strcmp(hostname, "QUIT") == 0) {
        return 0;
    }

    printf("Please enter the query type (A or AAAA): ");
    if (fgets(queryType, sizeof(queryType), stdin) == NULL) {
        printf("Error reading query type.\n");
        return 0;
    }
    queryType[strcspn(queryType, "\n")] = 0; // Remove newline character

    // Validate query type
    if (strcmp(queryType, "AAA") == 0) {
        strcat(queryType, "A");
    }
    if (strcmp(queryType, "A") != 0 && strcmp(queryType, "AAAA") != 0) {
        printf("Invalid query type: %s. Please enter 'A' or 'AAAA'.\n", queryType);
        return 0;
    }

    printf("Hostname received: %s, Query Type: %s\n", hostname, queryType);
    dnsGenerator(hostname, queryType);

    WSACleanup();
    return 0;
}

uint16_t randomID() {
    srand(time(NULL));
    return (uint16_t) rand();
}

void dnsGenerator(const char * hostname,
    const char * queryType) {
    struct headerStruct header;
    char * hostname_copy = NULL;
    unsigned char query[512];
    int queryLength = 0;

    header.id = randomID();
    header.flags = htons(0x0100);
    //printf("Flags set: 0x%04X\n", ntohs(header.flags));
    header.questionCount = htons(1);
    header.answerCount = 0;
    header.authCount = 0;
    header.recordsCount = 0;

    memcpy(query, & header, sizeof(header));
    queryLength += sizeof(header);
    hostname_copy = (char * ) malloc(strlen(hostname) + 1);
    strcpy(hostname_copy, hostname);
    const char * delim = ".";
    char * label = strtok(hostname_copy, delim);

    while (label) {
        int labelLength = strlen(label);
        query[queryLength++] = (unsigned char) labelLength;
        memcpy( & query[queryLength], label, labelLength);
        queryLength += labelLength;
        label = strtok(NULL, delim);
    }
    free(hostname_copy);
    query[queryLength++] = 0;
    query[queryLength++] = 0x00;
    if (strcmp(queryType, "A") == 0) {
        query[queryLength++] = 0x01;
    } // IPv4
    else {
        query[queryLength++] = 0x1C;
    } //IPV6
    query[queryLength++] = 0x00;
    query[queryLength++] = 0x01;
    printf("DNS Query crafted. Now Sending.\n");
    dnsOutbound(query, queryLength);
}

void dnsOutbound(const unsigned char * query, int queryLength) {
    struct sockaddr_in dest;
    SOCKET sockfd;
    fd_set fds;
    struct timeval timeout;
    int n = 0;
    int attempt = 0;
    char buffer[512];
    int responseLength;
    const char * dnsIP = "8.8.8.8";
    const int dnsPort = 53;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        return;
    }
    memset( & dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(dnsPort);
    dest.sin_addr.s_addr = inet_addr(dnsIP);
    while (attempt < 3) {
        printf("Sending DNS query (attempt %d)...\n", attempt + 1);
        if (sendto(sockfd, (const char * ) query, queryLength, 0, (struct sockaddr * ) & dest, sizeof(dest)) == SOCKET_ERROR) {
            printf("sending failed with error: %d\n", WSAGetLastError());
            closesocket(sockfd);
            return;
        }

        FD_ZERO( & fds);
        FD_SET(sockfd, & fds);
        timeout.tv_sec = 5;
        n = select(0, & fds, NULL, NULL, & timeout);
        if (n == 0) {
            printf("Timeout waiting for DNS response.\n");
            attempt++;
        } else if (n < 0) {
            printf("Selection error.\n");
            closesocket(sockfd);
            return;
        } else {
            // Receive the response
            responseLength = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
            if (responseLength == SOCKET_ERROR) {
                printf("Receiver failed! error nnumber: %d\n", WSAGetLastError());
            } else {
                printf("DNS Response received. Attempt number: %d\n", attempt + 1);
                dnsReceiver((unsigned char * ) buffer, responseLength);
                closesocket(sockfd);
                return;
            }
        }
    }
    printf("Dns unresponsive. Attempt limit reached.\n");
    closesocket(sockfd);
}

void dnsReceiver(const unsigned char * response, int responseLength) {
    printf("Dns response now processing.\n");
    struct headerStruct * header = (struct headerStruct * ) response;

    printf("\nDNS Header \n"); //looks awful. format later?
    printf("ID: 0x%04X\n", ntohs(header -> id));
    printf("QR: %d\n", (ntohs(header -> flags) & 0x8000) >> 15);
    printf("OPCODE: %d\n", (ntohs(header -> flags) & 0x7800) >> 11);
    printf("AA: %d\n", (ntohs(header -> flags) & 0x0400) >> 10);
    printf("TC: %d\n", (ntohs(header -> flags) & 0x0200) >> 9);
    printf("RD: %d\n", (ntohs(header -> flags) & 0x0100) >> 8);
    printf("RA: %d\n", (ntohs(header -> flags) & 0x0080) >> 7);
    printf("Z: %d\n", (ntohs(header -> flags) & 0x0040) >> 6);
    printf("RCode: %d\n", ntohs(header -> flags) & 0x000F);
    printf("questionCount: %d\n", ntohs(header -> questionCount));
    printf("answerCount: %d\n", ntohs(header -> answerCount));
    printf("authCount: %d\n", ntohs(header -> authCount));
    printf("recordsCount: %d\n", ntohs(header -> recordsCount));

    int offset = sizeof(struct headerStruct);

    printf("\nQuestion Section\n");
    printf("QNAME: ");
    while (response[offset] != 0) {
        int len = response[offset];
        offset++;
        for (int i = 0; i < len; i++) {
            printf("%c", response[offset]);
            offset++;
        }
        printf(".");
    }
    offset++;

    uint16_t qtype = (response[offset] << 8) | response[offset + 1];
    printf("\nQTYPE: %d\n", ntohs(qtype));
    offset += 2;

    uint16_t qclass = (response[offset] << 8) | response[offset + 1];
    printf("QCLASS: %d\n", ntohs(qclass));
    offset += 2;

    if (ntohs(header -> answerCount) > 0) {
        printf("\nAnswer Section\n");

        if ((response[offset] & 0xC0) == 0xC0) {
            offset += 2;
        } else {
            while (response[offset] != 0) {
                offset++;
            }
            offset++;
        }
        uint16_t type = (response[offset] << 8) | response[offset + 1];
        printf("TYPE: %d\n", ntohs(type));
        offset += 2;
        uint16_t class = (response[offset] << 8) | response[offset + 1];
        printf("CLASS: %d\n", ntohs(class));
        offset += 2;
        uint32_t ttl = (response[offset] << 24) | (response[offset + 1] << 16) | (response[offset + 2] << 8) | response[offset + 3];
        printf("TTL: %d\n", ntohl(ttl));
        offset += 4;
        uint16_t rdlength = (response[offset] << 8) | response[offset + 1];
        printf("RDLENGTH: %d\n", ntohs(rdlength));
        offset += 2;
        if (type == 1) { // A record (IPv4)
            printf("RDATA (IPv4 Address): %d.%d.%d.%d\n",
                response[offset], response[offset + 1],
                response[offset + 2], response[offset + 3]);
        } else if (type == 28) { // AAAA record (IPv6)
            printf("RDATA (IPv6 Address): ");
            for (int i = 0; i < 16; i += 2) {
                printf("%02x%02x", response[offset + i], response[offset + i + 1]);
                if (i < 14) printf(":");
            }
            printf("\n");
        }
    }
}