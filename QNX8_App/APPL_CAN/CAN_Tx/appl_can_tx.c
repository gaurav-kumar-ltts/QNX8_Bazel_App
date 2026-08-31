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

int main(void) {
    int fd;
    struct can_msg canmsg;

    uint32_t can_ids[] = {0x100, 0x102, 0x103, 0x104, 0x105};
    int num_ids = sizeof(can_ids) / sizeof(can_ids[0]);
    int id_index = 0;

    fd = open(TX_MAILBOX_PATH, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Failed to open %s | errno: %d\n", TX_MAILBOX_PATH, errno);
        return EXIT_FAILURE;
    }

    unsigned long packet_count = 0;

    while (1) {
        packet_count++;
        memset(&canmsg, 0, sizeof(canmsg));
        
        canmsg.mid = can_ids[id_index];
        canmsg.len = 8; // Set length to 8 bytes

        // Match your specified data fields pattern with 4 padding bytes
        canmsg.dat[0] = rand();
        canmsg.dat[1] = rand();
        canmsg.dat[2] = rand();
        canmsg.dat[3] = rand();
        canmsg.dat[4] = rand();
        canmsg.dat[5] = rand();
        canmsg.dat[6] = rand();
        canmsg.dat[7] = rand();

        int bytes_written = write(fd, &canmsg, sizeof(canmsg));
        
        if (bytes_written > 0) {
            printf("[DEBUG] [Packet #%lu] QNX WRITE SUCCESS -> ID: 0x%X | Data: %02X %02X %02X %02X %02X %02X %02X %02X\n", 
                   packet_count, canmsg.mid, 
                   canmsg.dat[0], canmsg.dat[1], canmsg.dat[2], canmsg.dat[3],
                   canmsg.dat[4], canmsg.dat[5], canmsg.dat[6], canmsg.dat[7]);
            fflush(stdout);
        }

        id_index = (id_index + 1) % num_ids;
        usleep(10000);
    }

    close(fd);
    return EXIT_SUCCESS;
}