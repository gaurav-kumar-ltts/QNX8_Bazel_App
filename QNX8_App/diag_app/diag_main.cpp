/*
 * Author: JAINY
 * Afiliation: LTTS (PS NO: 40050058)
 * Department: ADAS
 *
 * Copying it without authors permission is strictly prohibited.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstring>

//#include "/home/prathik/dlt-daemon/include/dlt/dlt.h"

#include <dlt/dlt.h>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <thread>
#include <chrono>
#include <sys/mman.h>

DLT_DECLARE_CONTEXT(diag_ctx);

const uint16_t logical_address = 0x1000; // ECU address
const char* SHM_NAME = "/msm_shared_state";

void log_hex(const std::string& prefix, const std::vector<uint8_t>& data) {
    std::ostringstream oss;
    for (size_t i = 0; i < data.size(); ++i) {
        oss << std::hex << std::uppercase << std::setw(2)
            << std::setfill('0') << static_cast<int>(data[i]) << " ";
    }
    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING((prefix + oss.str()).c_str()));
}

uint8_t read_shared_state() {
    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Reading MSM state from shared memory"));
    int fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (fd < 0) {
        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to open shared memory"), DLT_STRING(strerror(errno)));
        return 0x00;
    }
    void* ptr = mmap(0, sizeof(uint8_t), PROT_READ, MAP_SHARED, fd, 0);
    uint8_t value = (ptr != MAP_FAILED) ? *static_cast<uint8_t*>(ptr) : 0x00;
    if (ptr != MAP_FAILED) {
        DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Read MSM state"), DLT_UINT8(value));
        munmap(ptr, sizeof(uint8_t));
    } else {
        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to map shared memory"), DLT_STRING(strerror(errno)));
    }
    close(fd);
    return value;
}

bool write_shared_state(uint8_t value) {
    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Writing MSM state to shared memory"), DLT_UINT8(value));
    int fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (fd < 0) {
        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to open shared memory for writing"), DLT_STRING(strerror(errno)));
        return false;
    }
    void* ptr = mmap(0, sizeof(uint8_t), PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr != MAP_FAILED) {
        *static_cast<uint8_t*>(ptr) = value;
        DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Wrote MSM state"), DLT_UINT8(value));
        munmap(ptr, sizeof(uint8_t));
    } else {
        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to map shared memory for writing"), DLT_STRING(strerror(errno)));
    }
    close(fd);
    return true;
}

std::string handle_request(const std::vector<uint8_t>& request) {
    log_hex("Raw UDS request: ", request);
    if (request.empty()) {
        DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("Empty UDS request received"));
        return "";
    }

    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Request size"), DLT_UINT(request.size()));
    uint8_t sid = request[0];
    switch (sid) {
        case 0x22:
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Processing UDS Service: RDBI (0x22)"));
            break;
        case 0x2E:
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Processing UDS Service: WDBI (0x2E)"));
            break;
        case 0x31:
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Processing UDS Service: Routine Control (0x31)"));
            break;
        case 0x10:
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Processing UDS Service: Diagnostic Session Control (0x10)"));
            break;
        case 0x11:
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Processing UDS Service: ECU Reset (0x11)"));
            break;
        case 0x3E:
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Processing UDS Service: Tester Present (0x3E)"));
            break;
        default:
            DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("Unknown UDS Service received"), DLT_UINT8(sid));
    }

    if (sid == 0x22 && request.size() >= 3) {
        uint16_t did = (request[1] << 8) | request[2];
        DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Processing RDBI DID"), DLT_UINT16(did));
        if (did == 0x1700) {
            uint8_t value = read_shared_state();
            std::vector<uint8_t> response = { 0x62, 0x17, 0x00, value };
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        } else if (did == 0x1701) {
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Handling RDBI DID 0x1701, returning hardcoded value 0x55"));
            std::vector<uint8_t> response = { 0x62, 0x17, 0x01, 0x55 };
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        } else if (did == 0x1702) {
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Handling RDBI DID 0x1702, returning hardcoded value 0x66"));
            std::vector<uint8_t> response = { 0x62, 0x17, 0x02, 0x66 };
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        }
    }

    if (sid == 0x2E && request.size() >= 4) {
        uint16_t did = (request[1] << 8) | request[2];
        uint8_t value = request[3];
        DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Processing WDBI DID"), DLT_UINT16(did), DLT_STRING("with value"), DLT_UINT8(value));
        if (did == 0x1700) {
            write_shared_state(value);
            std::vector<uint8_t> response = { 0x6E, 0x17, 0x00 };
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        } else if (did == 0x1703 && value == 0x00) {
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Handling WDBI DID 0x1703 with value 0x00, returning positive response"));
            std::vector<uint8_t> response = { 0x6E, 0x17, 0x03 };
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        } else if (did == 0x1704 && value == 0x22) {
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Handling WDBI DID 0x1704 with value 0x22, returning positive response"));
            std::vector<uint8_t> response = { 0x6E, 0x17, 0x04 };
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        }
    }

    if (sid == 0x11 && request.size() >= 2) {  // ECU Reset service
        uint8_t resetType = request[1];
        DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Processing ECU Reset"), DLT_UINT8(resetType));
        
        if (resetType == 0x01) {  // Hard Reset
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("ECU Hard Reset requested (0x1101)"));
            
            // Check if running in Docker by checking environment variable or file
            bool is_docker = false;
            const char* container_env = std::getenv("CONTAINER");
            if (container_env != nullptr && std::string(container_env) == "docker") {
                is_docker = true;
            }
            
            // Also check if /.dockerenv exists
            struct stat docker_stat;
            if (stat("/.dockerenv", &docker_stat) == 0) {
                is_docker = true;
            }
            
            if (is_docker) {
                DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Docker environment detected, will trigger container restart"));
                
                // Send positive response first
                std::vector<uint8_t> response = { 0x51, 0x01 };
                log_hex("UDS response: ", response);
                
                // Schedule docker restart in a separate thread to allow response to be sent
                std::thread([]() {
                    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Initiating Docker container restart in 2 seconds..."));
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    
                    // Execute docker restart command
                    int ret = system("docker restart ita-demo");
                    if (ret == 0) {
                        DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Docker restart command executed successfully"));
                    } else {
                        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING("Docker restart command failed"), DLT_INT(ret));
                    }
                }).detach();
                
                return std::string(response.begin(), response.end());
            } else {
                // Real ECU or QEMU - just return positive response
                // Real ECU hardware will handle the actual reset
                DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Real ECU/QEMU - returning positive response, hardware will handle reset"));
                std::vector<uint8_t> response = { 0x51, 0x01 };
                log_hex("UDS response: ", response);
                return std::string(response.begin(), response.end());
            }
        } else if (resetType == 0x02) {  // Key Off On Reset
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Key Off/On Reset not implemented"));
            std::vector<uint8_t> response = { 0x7F, 0x11, 0x12 };  // Sub-function not supported
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        } else {
            DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("Unsupported ECU Reset type"), DLT_UINT8(resetType));
            std::vector<uint8_t> response = { 0x7F, 0x11, 0x12 };  // Sub-function not supported
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        }
    }

    // Add this case in handle_request() function after the existing switch cases

    if (sid == 0x3E && request.size() >= 2) {  // Tester Present service
        uint8_t subFunction = request[1];
        DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Processing Tester Present"), DLT_UINT8(subFunction));
        
        if (subFunction == 0x00) {  // Tester Present with response
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Tester Present (0x3E00) - sending positive response"));
            std::vector<uint8_t> response = { 0x7E, 0x00 };  // Positive response for Tester Present
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        } else if (subFunction == 0x80) {  // Tester Present without response (suppress positive response)
            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Tester Present (0x3E80) - no response required"));
            return "";  // No response needed for suppress positive response message
        } else {
            DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("Unsupported Tester Present sub-function"), DLT_UINT8(subFunction));
            std::vector<uint8_t> response = { 0x7F, 0x3E, 0x12 };  // Sub-function not supported
            log_hex("UDS response: ", response);
            return std::string(response.begin(), response.end());
        }
    }

    DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("No matching WDBI or RDBI request, returning default response"));
    std::vector<uint8_t> response = { static_cast<uint8_t>(sid | 0x40) };
    log_hex("UDS response: ", response);
    return std::string(response.begin(), response.end());
}

int server_fd = -1;

void cleanup(int) {
    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Shutting down diag_app..."));
    if (server_fd >= 0) {
        DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Closing server socket"));
        close(server_fd);
    }
    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Unregistering DLT context and app"));
    DLT_UNREGISTER_CONTEXT(diag_ctx);
    DLT_UNREGISTER_APP();
    exit(0);
}

int main() {
    // Initialize DLT logging
    setenv("DLT_PIPE_DIR", "/tmp", 1);
    setenv("DLT_FORCE_QUIT", "1", 1);
    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Waiting for DLT FIFO /tmp/dlt"));
    struct stat fifo_stat;
    int waited = 0;
    while (stat("/tmp/dlt", &fifo_stat) != 0 || !S_ISFIFO(fifo_stat.st_mode)) {
        if (waited >= 10) {
            DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING("Timeout waiting for FIFO /tmp/dlt"));
            std::cerr << "Timeout waiting for FIFO: /tmp/dlt" << std::endl;
            exit(EXIT_FAILURE);
        }
        DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("FIFO not ready, waiting"), DLT_INT(waited + 1));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        waited++;
    }
    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("DLT FIFO ready"));

    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Registering signal handlers for SIGINT and SIGTERM"));
    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);

    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Registering DLT application"));
    DLT_REGISTER_APP("DIAG", "Diagnostics App");
    DLT_REGISTER_CONTEXT(diag_ctx, "DIAG", "Diagnostic Context");
    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Enabling local print for testing"));
    DLT_ENABLE_LOCAL_PRINT();
    
    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Starting Diagnostics App"));
    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("[TIMING] Application Starting..."));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(13401);
    addr.sin_addr.s_addr = INADDR_ANY;

    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Creating TCP socket"));
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::stringstream err_log;
        err_log << "Failed to create socket: " << strerror(errno);
        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
        return 1;
    }

    int opt = 1;
    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Setting socket options (SO_REUSEADDR)"));
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::stringstream err_log;
        err_log << "Failed to set socket options: " << strerror(errno);
        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
        close(server_fd);
        return 1;
    }

    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Binding socket to port 13401"));
    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::stringstream err_log;
        err_log << "Bind failed: " << strerror(errno);
        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
        close(server_fd);
        return 1;
    }

    DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Listening on socket"));
    if (listen(server_fd, 5) < 0) {
        std::stringstream err_log;
        err_log << "Listen failed: " << strerror(errno);
        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
        close(server_fd);
        return 1;
    }

    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("diag_app listening on port 13401"));

    while (true) {
        DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Waiting for client connection"));
        int client = accept(server_fd, nullptr, nullptr);
        if (client < 0) {
            std::stringstream err_log;
            err_log << "Accept failed: " << strerror(errno);
            DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
            continue;
        }

        DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Client connection accepted"));

        // Set client socket to non-blocking
        DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Setting client socket to non-blocking"));
        if (fcntl(client, F_SETFL, O_NONBLOCK) < 0) {
            std::stringstream err_log;
            err_log << "Failed to set non-blocking: " << strerror(errno);
            DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
            close(client);
            continue;
        }

        bool routing_activated = false;
        while (true) {
            std::vector<uint8_t> buffer(2048);
            DLT_LOG(diag_ctx, DLT_LOG_DEBUG, DLT_STRING("Waiting for message on client socket"));

            auto start_time = std::chrono::steady_clock::now();
            ssize_t len = -1;
            while (len <= 0) {
                len = recv(client, buffer.data(), buffer.size(), 0);
                if (len > 0) break;
                if (len == 0) {
                    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Connection closed by client"));
                    break;
                }
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    std::stringstream err_log;
                    err_log << "Receive failed: " << strerror(errno);
                    DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
                    break;
                }
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count() > 2000) {
                    DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("Timeout waiting for message"));
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            if (len <= 0) break;

            buffer.resize(len);
            log_hex("Raw TCP buffer: ", buffer);

            if (buffer.size() >= 8 && buffer[0] == 0x02 && buffer[1] == 0xFD) {
                uint16_t payload_type = (static_cast<uint16_t>(buffer[2]) << 8) | buffer[3];
                uint32_t payload_len = (static_cast<uint32_t>(buffer[4]) << 24) |
                                      (static_cast<uint32_t>(buffer[5]) << 16) |
                                      (static_cast<uint32_t>(buffer[6]) << 8) |
                                      static_cast<uint32_t>(buffer[7]);
                std::stringstream pkt_log;
                pkt_log << "DoIP Payload Type: 0x" << std::hex << payload_type
                        << " Payload Length: " << std::dec << payload_len;
                DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING(pkt_log.str().c_str()));

                if (buffer.size() >= 8 + payload_len) {
                    if (payload_type == 0x0005) { // Routing Activation Request
                        DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Processing Routing Activation Request"));
                        if (payload_len == 7) {
                            std::vector<uint8_t> payload(buffer.begin() + 8, buffer.begin() + 8 + payload_len);
                            uint16_t sourceAddress = (static_cast<uint16_t>(payload[0]) << 8) | payload[1];
                            uint8_t activationType = payload[2];
                            std::stringstream rar_log;
                            rar_log << "RAR Source Address: 0x" << std::hex << sourceAddress
                                    << " Activation Type: 0x" << (int)activationType;
                            DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING(rar_log.str().c_str()));
                            std::vector<uint8_t> response = {
                                0x02, 0xFD, 0x00, 0x06, 0x00, 0x00, 0x00, 0x09,
                                static_cast<uint8_t>(sourceAddress >> 8), static_cast<uint8_t>(sourceAddress),
                                static_cast<uint8_t>(logical_address >> 8), static_cast<uint8_t>(logical_address),
                                0x10, 0x00, 0x00, 0x00, 0x00
                            };
                            log_hex("RAR Response: ", response);
                            ssize_t sent = send(client, response.data(), response.size(), 0);
                            if (sent < 0) {
                                std::stringstream err_log;
                                err_log << "Send failed for RAR response: " << strerror(errno);
                                DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
                            } else {
                                std::stringstream sent_log;
                                sent_log << "Sent " << sent << " bytes for RAR response";
                                DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING(sent_log.str().c_str()));
                                routing_activated = true;
                            }
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        } else {
                            DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING("Invalid RAR payload length"), DLT_UINT32(payload_len));
                        }
                    } else if (payload_type == 0x8001) { // Diagnostic Message
                        DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Processing Diagnostic Message"));
                        if (payload_len >= 4 && buffer.size() >= 12 + payload_len - 4) {
                            std::vector<uint8_t> uds(buffer.begin() + 12, buffer.begin() + 8 + payload_len);
                            log_hex("UDS extracted: ", uds);

                            // Send Diagnostic Message Acknowledgment (0x8002)
                            std::vector<uint8_t> ack_response = {
                                0x02, 0xFD, 0x80, 0x02, 0x00, 0x00, 0x00, 0x05,
                                buffer[8], buffer[9], buffer[10], buffer[11], 0x00
                            };
                            log_hex("Diagnostic Message Ack: ", ack_response);
                            ssize_t sent = send(client, ack_response.data(), ack_response.size(), 0);
                            if (sent < 0) {
                                std::stringstream err_log;
                                err_log << "Send failed for Diagnostic Message Ack: " << strerror(errno);
                                DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
                            } else {
                                std::stringstream sent_log;
                                sent_log << "Sent " << sent << " bytes for Diagnostic Message Ack";
                                DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING(sent_log.str().c_str()));
                            }

                            // Process UDS request
                            std::string uds_response = handle_request(uds);
                            if (!uds_response.empty()) {
                                std::vector<uint8_t> doip_response = {
                                    0x02, 0xFD, 0x80, 0x01,
                                    0x00, 0x00, 0x00, static_cast<uint8_t>(4 + uds_response.size()),
                                    buffer[8], buffer[9], buffer[10], buffer[11]
                                };
                                doip_response.insert(doip_response.end(), uds_response.begin(), uds_response.end());
                                log_hex("DoIP UDS Response: ", doip_response);
                                sent = send(client, doip_response.data(), doip_response.size(), 0);
                                if (sent < 0) {
                                    std::stringstream err_log;
                                    err_log << "Send failed for DoIP UDS response: " << strerror(errno);
                                    DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
                                } else {
                                    std::stringstream sent_log;
                                    sent_log << "Sent " << sent << " bytes for DoIP UDS response";
                                    DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING(sent_log.str().c_str()));
                                }
                            } else {
                                DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("No UDS response generated for request"));
                            }
                        } else {
                            DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING("Invalid Diagnostic Message payload length"), 
                                    DLT_UINT32(payload_len), DLT_STRING("received size"), DLT_UINT32(buffer.size()));
                        }
                    } else {
                        DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("Unsupported DoIP payload type"), DLT_UINT16(payload_type));
                    }
                } else {
                    DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("Malformed DoIP packet: insufficient length"), 
                            DLT_UINT32(buffer.size()), DLT_STRING("expected"), DLT_UINT32(8 + payload_len));
                }
            } else {
                DLT_LOG(diag_ctx, DLT_LOG_WARN, DLT_STRING("Non-DoIP or malformed packet received"));
                std::vector<uint8_t> uds = buffer;
                log_hex("Treating as raw UDS: ", uds);
                std::string response = handle_request(uds);
                if (!response.empty()) {
                    log_hex("Raw UDS Response: ", std::vector<uint8_t>(response.begin(), response.end()));
                    ssize_t sent = send(client, response.data(), response.size(), 0);
                    if (sent < 0) {
                        std::stringstream err_log;
                        err_log << "Send failed for raw UDS response: " << strerror(errno);
                        DLT_LOG(diag_ctx, DLT_LOG_ERROR, DLT_STRING(err_log.str().c_str()));
                    } else {
                        std::stringstream sent_log;
                        sent_log << "Sent " << sent << " bytes for raw UDS response";
                        DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING(sent_log.str().c_str()));
                    }
                }
            }
        }

        DLT_LOG(diag_ctx, DLT_LOG_INFO, DLT_STRING("Closing client connection"));
        close(client);
    }

    return 0;
}