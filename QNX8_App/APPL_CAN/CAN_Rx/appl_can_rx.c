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

int main(int argc, char **argv) {
    int fd;
    struct can_msg canmsg;

    printf("[App] Opening CAN receive mailbox: %s\n", RX_MAILBOX_PATH);

    // Open the specific child mailbox node to correctly bind the resource manager OCB
    fd = open(RX_MAILBOX_PATH, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "[App] Failed to open %s: %s\n", RX_MAILBOX_PATH, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("[App] Successfully opened mailbox. Polling for CAN frames...\n");

    while (1) {
        memset(&canmsg, 0, sizeof(canmsg));

        // Invoke devctl using the correct command code and passing the full struct size
        int ret = devctl(fd, CAN_DEVCTL_READ_CANMSG_EXT, &canmsg, sizeof(canmsg), NULL);
        
        if (ret == EOK) {
            printf("[App] Received Frame -> MID: 0x%X | Length: %d | Data: ", 
                   canmsg.mid, canmsg.len);
            
            for (int i = 0; i < canmsg.len; i++) {
                printf("0x%02X ", canmsg.dat[i]);
            }
            printf("\n");
        } else {
            fprintf(stderr, "[App] CAN receive devctl failed: %s\n", strerror(ret));
        }

        usleep(10000); // 10 ms poll delay
    }

    close(fd);
    return EXIT_SUCCESS;
}