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

    // 1. Open RX path created by your driver
    fd = open(RX_MAILBOX_PATH, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "[DEBUG] CRITICAL: Failed to open %s | errno: %d (%s)\n", 
                RX_MAILBOX_PATH, errno, strerror(errno));
        return EXIT_FAILURE;
    }
    printf("[DEBUG] Successfully opened %s with file descriptor: %d\n", RX_MAILBOX_PATH, fd);
    printf("[DEBUG] Listening for Arduino frames (IDs 0x200 - 0x205)...\n");
    fflush(stdout);

    unsigned long rx_packet_count = 0;

    while (1) {
        memset(&rx_msg, 0, sizeof(rx_msg));

        // Use devctl to read the structured CAN message via the driver's extension handler[cite: 4]
        int result = devctl(fd, CAN_DEVCTL_READ_CANMSG_EXT, &rx_msg, sizeof(rx_msg), NULL);

        if (result == EOK) {
            // Filter to exclusively capture Arduino's range (0x200 to 0x205)[cite: 4]
            if (rx_msg.mid >= 0x200 && rx_msg.mid <= 0x205) {
                rx_packet_count++;
                
                // Explicitly printing rx_msg.len and all 8 bytes to verify byte-index 7[cite: 4]
                printf("[DEBUG] [QNX RX PKT #%lu] ID: 0x%X | DLC Reported: %d | Data: %02X %02X %02X %02X %02X %02X %02X %02X\n",
                       rx_packet_count, 
                       rx_msg.mid, 
                       rx_msg.len, // Check if this reports 8
                       rx_msg.dat[0], rx_msg.dat[1], rx_msg.dat[2], rx_msg.dat[3],
                       rx_msg.dat[4], rx_msg.dat[5], rx_msg.dat[6], rx_msg.dat[7]); //[cite: 4]
                fflush(stdout);
            }
        } else {
            // Sleep briefly if no message is ready to prevent CPU spiking[cite: 4]
            usleep(1000); 
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}