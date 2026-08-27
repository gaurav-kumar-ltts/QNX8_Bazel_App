#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <devctl.h>
#include <sys/can_dcmd.h>

#define CAPTURE_PERIOD_NS (10 * 1000 * 1000L)
#define DEFAULT_RX_NODE "/dev/can0/rx0"

static void print_frame(const CAN_MSG *frame)
{
	uint8_t index;

	printf("timestamp=%u id=0x%X%s%s len=%u data=",
		   frame->ext.timestamp,
		   frame->mid,
		   frame->ext.is_extended_mid ? " extended" : "",
		   frame->ext.is_remote_frame ? " remote" : "",
		   frame->len);

	for (index = 0; index < frame->len; ++index) {
		printf("%02X%s", frame->dat[index], index + 1U == frame->len ? "" : " ");
	}
	putchar('\n');
}

static int add_period(struct timespec *next_capture)
{
	next_capture->tv_nsec += CAPTURE_PERIOD_NS;
	if (next_capture->tv_nsec >= 1000000000L) {
		next_capture->tv_nsec -= 1000000000L;
		++next_capture->tv_sec;
	}
	return 0;
}

static int capture_pending_frames(int rx_fd)
{
	CAN_MSG frame;
	int rc;
	int captured = 0;

	for (;;) {
		memset(&frame, 0, sizeof(frame));
		rc = devctl(rx_fd, CAN_DEVCTL_RX_FRAME_RAW_NOBLOCK,
					&frame, sizeof(frame), NULL);
		if (rc == EOK) {
			print_frame(&frame);
			++captured;
		} else if (rc == EAGAIN || rc == EWOULDBLOCK) {
			break;
		} else if (rc == EINTR) {
			continue;
		} else {
			fprintf(stderr, "CAN receive failed: %s\n", strerror(rc));
			return -1;
		}
	}

	return captured;
}

int main(int argc, char *argv[])
{
	const char *rx_node = argc > 1 ? argv[1] : DEFAULT_RX_NODE;
	struct timespec next_capture;
	int rx_fd;

	rx_fd = open(rx_node, O_RDONLY | O_NONBLOCK);
	if (rx_fd == -1) {
		fprintf(stderr, "Unable to open %s: %s\n", rx_node, strerror(errno));
		return EXIT_FAILURE;
	}

	if (clock_gettime(CLOCK_MONOTONIC, &next_capture) == -1) {
		perror("clock_gettime");
		close(rx_fd);
		return EXIT_FAILURE;
	}

	printf("Capturing CAN data from %s every 10 ms\n", rx_node);
	for (;;) {
		add_period(&next_capture);
		while (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME,
							   &next_capture, NULL) == EINTR) {
		}

		if (capture_pending_frames(rx_fd) == -1) {
			close(rx_fd);
			return EXIT_FAILURE;
		}
	}
}
