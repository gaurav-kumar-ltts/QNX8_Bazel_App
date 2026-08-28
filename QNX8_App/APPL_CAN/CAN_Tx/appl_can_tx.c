#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/neutrino.h>
#include <sys/can_dcmd.h>

#define TX_MAILBOX_PATH "/dev/can0/tx1"

int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv) {
    int fd;
    struct can_msg canmsg;

    uint32_t can_ids[] = {0x100, 0x102, 0x103, 0x104, 0x105};
    int num_ids = sizeof(can_ids) / sizeof(can_ids[0]);
    int id_index = 0;

    printf("[DEBUG] Application starting up...\n");
    fflush(stdout);

    srand((unsigned int)time(NULL));

    // 1. Open CAN TX path
    printf("[DEBUG] Attempting to open TX path: %s\n", TX_MAILBOX_PATH);
    fd = open(TX_MAILBOX_PATH, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "[DEBUG] CRITICAL: Failed to open %s | errno: %d (%s)\n", 
                TX_MAILBOX_PATH, errno, strerror(errno));
        return EXIT_FAILURE;
    }
    printf("[DEBUG] Successfully opened %s with file descriptor: %d\n", TX_MAILBOX_PATH, fd);
    printf("[DEBUG] Entering direct 10ms transmission loop...\n");
    fflush(stdout);

    unsigned long packet_count = 0;

    while (1) {
        packet_count++;
        memset(&canmsg, 0, sizeof(canmsg));
        
        canmsg.mid = can_ids[id_index];
        canmsg.len = 4;

        canmsg.dat[0] = (uint8_t)(rand() % 256);
        canmsg.dat[1] = (uint8_t)(rand() % 256);
        canmsg.dat[2] = (uint8_t)(rand() % 256);
        canmsg.dat[3] = (uint8_t)(rand() % 256);

        // Directly write to the CAN mailbox node
        int bytes_written = write(fd, &canmsg, sizeof(canmsg));
        
        if (bytes_written > 0) {
            printf("[DEBUG] [Packet #%lu] WRITE SUCCESS -> ID: 0x%X | Data: %02X %02X %02X %02X\n", 
                   packet_count, canmsg.mid, canmsg.dat[0], canmsg.dat[1], canmsg.dat[2], canmsg.dat[3]);
            fflush(stdout);
        } else {
            fprintf(stderr, "[DEBUG] [Packet #%lu] WRITE FAILED -> ID: 0x%X | errno: %d (%s)\n", 
                    packet_count, canmsg.mid, errno, strerror(errno));
            fflush(stderr);
        }

        id_index = (id_index + 1) % num_ids;

        // Sleep for 10ms (10000 microseconds)
        usleep(10000);
    }

    close(fd);
    return EXIT_SUCCESS;
}