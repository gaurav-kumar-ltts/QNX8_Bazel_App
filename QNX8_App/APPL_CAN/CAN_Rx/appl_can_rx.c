#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <devctl.h>
#include <sys/can_dcmd.h>

#define RX_MAILBOX_PATH "/dev/can0/rx0"

int main(void) {
    int fd;
    struct can_msg rx_msg;

    fd = open(RX_MAILBOX_PATH, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Failed to open %s\n", RX_MAILBOX_PATH);
        return EXIT_FAILURE;
    }

    unsigned long rx_packet_count = 0;
    printf("[DEBUG] Listening for Arduino frames (IDs 0x200 - 0x205)...\n");

    while (1) {
        memset(&rx_msg, 0, sizeof(rx_msg));

        int result = devctl(fd, CAN_DEVCTL_READ_CANMSG_EXT, &rx_msg, sizeof(rx_msg), NULL);

        if (result == EOK) {
            // Optional filter to exclusively print Arduino's range if desired
            if (rx_msg.mid >= 0x200 && rx_msg.mid <= 0x205) {
                rx_packet_count++;
                printf("[DEBUG] [RX PKT #%lu] ID: 0x%X | DLC: %d | Data: %02X %02X %02X %02X %02X %02X %02X %02X\n",
                       rx_packet_count, 
                       rx_msg.mid, 
                       rx_msg.len, 
                       rx_msg.dat[0], rx_msg.dat[1], rx_msg.dat[2], rx_msg.dat[3],
                       rx_msg.dat[4], rx_msg.dat[5], rx_msg.dat[6], rx_msg.dat[7]);
                fflush(stdout);
            }
        } else {
            usleep(1000); 
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}