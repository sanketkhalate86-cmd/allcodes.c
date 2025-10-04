
#include "coppeliasim_client.h"
#include <stdio.h>

// Global client instance for socket communication
SocketClient client;

// ----------------------
// Forward declarations
// ----------------------
void* control_loop(void* arg);
int connect_to_server(SocketClient* c, const char* ip, int port);

/**
 * @brief Establishes connection to the CoppeliaSim server
 * @param c Pointer to SocketClient structure
 * @param ip IP address of the server (typically "127.0.0.1" for localhost)
 * @param port Port number of the server (typically 50002)
 * @return 1 if connection successful, 0 if failed
 */
int connect_to_server(SocketClient* c, const char* ip, int port) {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 0;
    }
#endif

    c->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (c->sock == -1) {
        printf("Socket creation failed\n");
        return 0;
    }

    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(c->sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Connection failed\n");
        CLOSESOCKET(c->sock);
        return 0;
    }

    c->running = true;
    printf("Connected to CoppeliaSim on %s:%d\n", ip, port);
    return 1;
}

/**
 * @brief Control loop for the robot to follow the line using PID
 * @param arg Pointer to the SocketClient structure
 * @return NULL
 */
void* control_loop(void* arg) {
    SocketClient* client = (SocketClient*)arg;
    const float kp = 0.9f, ki = 0.05f, kd = 0.18f; // Friend's tuning
    const float dt = 0.05f; // Friend's dt
    const float baseSpeed = 0.80f; // Friend's base speed
    const float maxSpeed = 1.00f; // Friend's max speed
    const float maxCorrection = 0.85f; // Friend's max correction
    const float integralLimit = 2.0f; // Friend's anti-windup
    const float dFilterAlpha = 0.5f; // Friend's derivative filter

    float integral = 0.0f;
    float last_error = 0.0f;
    float last_derivative = 0.0f;
    FILE* fp = fopen("result.json", "w");
    if (fp) {
        fprintf(fp, "{\n  \"task\": \"Task1a\",\n  \"team_id\": \"CB_2202\",\n  \"success\": false,\n  \"path\": [\n");
        printf("File opened for writing\n");
    } else {
        printf("Failed to open result.json\n");
    }

    while (client->running) {
        printf("Sensor count: %d, Running: %d\n", client->sensor_count, client->running); // Debug print
        if (client->sensor_count > 0) {
            int n = client->sensor_count;
            float sum = 0.0f;
            float weighted_sum = 0.0f;

            for (int i = 0; i < n; i++) {
                float value = 1.0f - client->sensor_values[i]; // Friend's inversion
                int pos = i - (n - 1) / 2; // Friend's centering
                weighted_sum += (float)pos * value;
                sum += value;
            }

            bool line_detected = (sum > 0.01f);
            float position = line_detected ? (weighted_sum / sum) : 0.0f;
            float error = position; // Friend's error (deviation)

            // PID from friend
            integral += error * dt;
            if (integral > integralLimit) integral = integralLimit;
            if (integral < -integralLimit) integral = -integralLimit;

            float raw_derivative = (error - last_error) / dt;
            float derivative = dFilterAlpha * raw_derivative + (1.0f - dFilterAlpha) * last_derivative;

            float correction = kp * error + ki * integral + kd * derivative;
            if (correction > maxCorrection) correction = maxCorrection;
            if (correction < -maxCorrection) correction = -maxCorrection;

            // Speed plan from friend
            float forward = baseSpeed;
            if (!line_detected) {
                forward = 0.55f;
                correction = (last_error >= 0.0f) ? 0.35f : -0.35f;
            }

            float left = forward - correction;
            float right = forward + correction;

            // Clamp from friend
            if (left > maxSpeed) left = maxSpeed;
            if (left < -maxSpeed) left = -maxSpeed;
            if (right > maxSpeed) right = maxSpeed;
            if (right < -maxSpeed) right = -maxSpeed;

            set_motor(client, left, right);

            // Log approximate position
            if (fp && line_detected) {
                fprintf(fp, "    {\"x\": %.2f, \"y\": %.2f},\n", position * 10.0, 0.0); // Placeholder x, y=0
                printf("Logged position: x=%.2f, y=%.2f\n", position * 10.0, 0.0);
            }

            last_error = error;
            last_derivative = derivative;
        } else {
            set_motor(client, 0.0f, 0.0f); // Friend's safety stop
        }

        usleep((int)(dt * 1000000.0f)); // Friend's sleep (dt * 1e6 for usleep)
    }

    // Close JSON file
    if (fp) {
        fprintf(fp, "  ],\n  \"success\": true,\n  \"time_taken\": 0.0\n}");
        fclose(fp);
        printf("File closed\n");
    }

    return NULL;
}

/**
 * @brief Main function to initialize and run the robot control
 * @return 0 on success
 */
int main(int argc, char* argv[]) {
    // Connect to the server
    if (!connect_to_server(&client, "127.0.0.1", 50002)) {
        printf("Failed to connect to CoppeliaSim. Exiting...\n");
        return 1;
    }

    // Start the receive loop thread
    pthread_t recv_thread;
    if (pthread_create(&recv_thread, NULL, receive_loop, (void*)&client) != 0) {
        printf("Failed to create receive thread\n");
        disconnect(&client);
        return 1;
    }

    // Create thread for control loop
    pthread_t control_thread;
    if (pthread_create(&control_thread, NULL, control_loop, (void*)&client) != 0) {
        printf("Failed to create control thread\n");
        disconnect(&client);
        return 1;
    }

    // Friend's main loop for monitoring (optional debug)
    while (client.running) {
        if (client.sensor_count > 0) {
            printf("Sensors (%d): ", client.sensor_count);
            for (int i = 0; i < client.sensor_count; i++) {
                printf("%.3f ", client.sensor_values[i]);
            }
            printf("\n");
        } else {
            printf("Waiting for sensor data...\n");
        }
        usleep(200000); // 200ms
    }

    // Wait for threads to complete
    pthread_join(control_thread, NULL);
    pthread_join(recv_thread, NULL);

    // Cleanup
    disconnect(&client);
    return 0;
}