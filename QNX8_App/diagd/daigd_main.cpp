#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>
#include <dlt/dlt.h>

// Add these missing networking headers:
#include <sys/socket.h>   // For socket(), bind(), listen(), accept(), recv(), send(), shutdown()
#include <netinet/in.h>   // For sockaddr_in, AF_INET, SOCK_STREAM
#include <unistd.h>  // Declares close()




DLT_DECLARE_CONTEXT(diag_daemon_ctx);

void log_hex(const std::string& prefix, const uint8_t* data, size_t len) {
    std::ostringstream oss;
    for (size_t i = 0; i < len; ++i) {
        oss << std::hex << std::uppercase << std::setw(2)
            << std::setfill('0') << static_cast<int>(data[i]) << " ";
    }
    DLT_LOG(diag_daemon_ctx, DLT_LOG_INFO, DLT_STRING((prefix + oss.str()).c_str()));
}

void full_duplex(int src_fd, int dst_fd) {
    std::thread([=]() {
        uint8_t buffer[1024];
        while (true) {
            DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Receiving data from source FD"), DLT_INT(src_fd));
            ssize_t len = recv(src_fd, buffer, sizeof(buffer), 0);
            if (len <= 0) {
                if (len == 0) {
                    DLT_LOG(diag_daemon_ctx, DLT_LOG_INFO, DLT_STRING("Source FD"), DLT_INT(src_fd), DLT_STRING("closed connection"));
                } else {
                    DLT_LOG(diag_daemon_ctx, DLT_LOG_ERROR, DLT_STRING("Receive failed on FD"), DLT_INT(src_fd), 
                            DLT_STRING("error"), DLT_STRING(strerror(errno)));
                }
                DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Shutting down write on destination FD"), DLT_INT(dst_fd));
                shutdown(dst_fd, SHUT_WR);
                break;
            }
            log_hex("Forwarding from FD " + std::to_string(src_fd) + " to FD " + std::to_string(dst_fd) + ": ", buffer, len);
            DLT_LOG(diag_daemon_ctx, DLT_LOG_INFO, DLT_STRING("Sending"), DLT_INT(len), DLT_STRING("bytes to destination FD"), DLT_INT(dst_fd));
            ssize_t sent = send(dst_fd, buffer, len, 0);
            if (sent < 0) {
                DLT_LOG(diag_daemon_ctx, DLT_LOG_ERROR, DLT_STRING("Send failed on FD"), DLT_INT(dst_fd), 
                        DLT_STRING("error"), DLT_STRING(strerror(errno)));
                break;
            }
            DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Sent"), DLT_INT(sent), DLT_STRING("bytes to FD"), DLT_INT(dst_fd));
        }
    }).detach();
}

int main() {
    setenv("DLT_PIPE_DIR", "/tmp", 1);
    setenv("DLT_FORCE_QUIT", "1", 1);
    DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Waiting for DLT FIFO /tmp/dlt"));
    struct stat fifo_stat;
    int waited = 0;
    while (::stat("/tmp/dlt", &fifo_stat) != 0 || !S_ISFIFO(fifo_stat.st_mode)) {
        if (waited >= 10) {
            DLT_LOG(diag_daemon_ctx, DLT_LOG_ERROR, DLT_STRING("Timeout waiting for FIFO /tmp/dlt"));
            std::cerr << "Timeout waiting for FIFO: /tmp/dlt" << std::endl;
            exit(EXIT_FAILURE);
        }
        DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("FIFO not ready, waiting"), DLT_INT(waited + 1));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        waited++;
    }
    DLT_LOG(diag_daemon_ctx, DLT_LOG_INFO, DLT_STRING("DLT FIFO ready"));

    DLT_REGISTER_APP("DIAD", "Diagnostics Daemon");
    DLT_REGISTER_CONTEXT(diag_daemon_ctx, "DIAD", "Diagnostics Daemon Context");
    DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Enabling local print for testing"));
    DLT_ENABLE_LOCAL_PRINT();

    DLT_LOG(diag_daemon_ctx, DLT_LOG_INFO, DLT_STRING("Starting Diagnostics Daemon"));
    DLT_LOG(diag_daemon_ctx, DLT_LOG_INFO, DLT_STRING("[TIMING] Application Starting..."));

    DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Creating server socket"));
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        DLT_LOG(diag_daemon_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to create socket"), DLT_STRING(strerror(errno)));
        std::cerr << "[DIAGD] Failed to create socket: " << strerror(errno) << "\n";
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(13400);
    addr.sin_addr.s_addr = INADDR_ANY;

    DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Binding socket to port 13400"));
    if (bind(server_fd, (sockaddr *)&addr, sizeof(addr)) < 0) {
        DLT_LOG(diag_daemon_ctx, DLT_LOG_ERROR, DLT_STRING("Bind failed"), DLT_STRING(strerror(errno)));
        std::cerr << "[DIAGD] Bind failed: " << strerror(errno) << "\n";
        close(server_fd);
        return 1;
    }

    DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Listening on socket"));
    if (listen(server_fd, 5) < 0) {
        DLT_LOG(diag_daemon_ctx, DLT_LOG_ERROR, DLT_STRING("Listen failed"), DLT_STRING(strerror(errno)));
        std::cerr << "[DIAGD] Listen failed: " << strerror(errno) << "\n";
        close(server_fd);
        return 1;
    }

    DLT_LOG(diag_daemon_ctx, DLT_LOG_INFO, DLT_STRING("Proxy listening on port 13400"));
    std::cout << "[DIAGD] Proxy listening on port 13400...\n";

    while (true) {
        DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Waiting for client connection"));
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            DLT_LOG(diag_daemon_ctx, DLT_LOG_ERROR, DLT_STRING("Accept failed"), DLT_STRING(strerror(errno)));
            std::cerr << "[DIAGD] Accept failed: " << strerror(errno) << "\n";
            continue;
        }

        DLT_LOG(diag_daemon_ctx, DLT_LOG_INFO, DLT_STRING("Client connection accepted, FD"), DLT_INT(client_fd));
        std::thread([client_fd]() {
            DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Creating socket for diag_app connection"));
            int diag_sock = socket(AF_INET, SOCK_STREAM, 0);
            if (diag_sock < 0) {
                DLT_LOG(diag_daemon_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to create diag_app socket"), 
                        DLT_STRING(strerror(errno)));
                std::cerr << "[DIAGD] Failed to create diag_app socket: " << strerror(errno) << "\n";
                close(client_fd);
                return;
            }

            sockaddr_in diag_addr{};
            diag_addr.sin_family = AF_INET;
            diag_addr.sin_port = htons(13401);
            inet_pton(AF_INET, "127.0.0.1", &diag_addr.sin_addr);

            DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Connecting to diag_app at 127.0.0.1:13401"));
            if (connect(diag_sock, (sockaddr *)&diag_addr, sizeof(diag_addr)) < 0) {
                DLT_LOG(diag_daemon_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to connect to diag_app"), 
                        DLT_STRING(strerror(errno)));
                std::cerr << "[DIAGD] Failed to connect to diag_app: " << strerror(errno) << "\n";
                close(client_fd);
                close(diag_sock);
                return;
            }

            DLT_LOG(diag_daemon_ctx, DLT_LOG_INFO, DLT_STRING("Connected to diag_app, FD"), DLT_INT(diag_sock));
            DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Starting full-duplex forwarding: client FD"), 
                    DLT_INT(client_fd), DLT_STRING("to diag_app FD"), DLT_INT(diag_sock));
            full_duplex(client_fd, diag_sock);
            DLT_LOG(diag_daemon_ctx, DLT_LOG_DEBUG, DLT_STRING("Starting full-duplex forwarding: diag_app FD"), 
                    DLT_INT(diag_sock), DLT_STRING("to client FD"), DLT_INT(client_fd));
            full_duplex(diag_sock, client_fd);
        }).detach();
    }
}
