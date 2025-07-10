#include "esp_log.h"
#include "esp_netif.h"
#include "esp_err.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>


#define HOST_IP_ADDR "192.168.50.126"
#define PORT 38899

static const char *TAG = "UDP";

static struct sockaddr_in dest_addr;
static int sock = 0;

esp_err_t udp_socket_init(void)
{
    dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0)
    {
        ESP_LOGE(TAG, "Failed to create a socket");
        return ESP_FAIL;
    }

    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);

    ESP_LOGI(TAG, "Socket for addr: %s, port: %d was created", HOST_IP_ADDR, PORT);

    return ESP_OK;
}


esp_err_t udp_socket_send(char *msg)
{
    int err = sendto(sock, msg, strlen(msg), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err < 0) {
        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        return ESP_FAIL;
    }
    // ESP_LOGI(TAG, "Message %s sent", msg);
    return ESP_OK;
}