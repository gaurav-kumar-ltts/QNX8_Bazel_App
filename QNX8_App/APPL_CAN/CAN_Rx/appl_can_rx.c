#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/neutrino.h>
#include <sys/siginfo.h>
#include <devctl.h>
#include <sys/can_dcmd.h>

#define RX_MAILBOX_PATH "/dev/can0/rx0"
#define TIMER_PULSE_CODE _PULSE_CODE_MINAVAIL

typedef union {
    struct _pulse pulse;
} app_msg_t;

int setup_periodic_timer(timer_t *timer_id, int chid) {
    struct sigevent event;
    struct itimerspec timer_spec;

    SIGEV_PULSE_INIT(&event, chid, SIGEV_PULSE_PRIO_INHERIT, TIMER_PULSE_CODE, 0);

    if (timer_create(CLOCK_REALTIME, &event, timer_id) == -1) {
        return -1;
    }

    timer_spec.it_value.tv_sec = 0;
    timer_spec.it_value.tv_nsec = 10000000; // 10ms initial expiration
    timer_spec.it_interval.tv_sec = 0;
    timer_spec.it_interval.tv_nsec = 10000000; // 10ms periodic interval

    if (timer_settime(*timer_id, 0, &timer_spec, NULL) == -1) {
        return -1;
    }

    return 0;
}

int main(int argc, char **argv) {
    int fd;
    int chid;
    int rcvid;
    timer_t timer_id;
    app_msg_t msg;
    struct can_msg canmsg;

    fd = open(RX_MAILBOX_PATH, O_RDWR);
    if (fd == -1) {
        return EXIT_FAILURE;
    }

    chid = ChannelCreate(0);
    if (chid == -1) {
        close(fd);
        return EXIT_FAILURE;
    }

    if (setup_periodic_timer(&timer_id, chid) == -1) {
        ChannelDestroy(chid);
        close(fd);
        return EXIT_FAILURE;
    }

    while (1) {
        rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);

        if (rcvid == 0) {
            if (msg.pulse.code == TIMER_PULSE_CODE) {
                memset(&canmsg, 0, sizeof(canmsg));
                int ret = devctl(fd, CAN_DEVCTL_READ_CANMSG_EXT, &canmsg, sizeof(canmsg), NULL);
                
                if (ret == EOK) {
                    printf("[App] Received Frame -> MID: 0x%X | Length: %d | Data: ", 
                           canmsg.mid, canmsg.len);
                    for (int i = 0; i < canmsg.len; i++) {
                        printf("0x%02X ", canmsg.dat[i]);
                    }
                    printf("\n");
                }
            }
        } else if (rcvid < 0) {
            if (errno == EINTR) continue;
            break;
        }
    }

    timer_delete(timer_id);
    ChannelDestroy(chid);
    close(fd);
    return EXIT_SUCCESS;
}