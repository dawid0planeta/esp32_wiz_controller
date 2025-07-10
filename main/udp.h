#ifndef UDP_H
#define UDP_H
#include "esp_err.h"

esp_err_t udp_socket_init(void);
esp_err_t udp_socket_send(char *msg);


#endif