#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <assert.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <ctype.h>

// new
#include <time.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <semaphore.h>

#include "hftp.h"
#include "http_core.h"
#include "http_method.h"
#include "threads.h"

#define INPUT_BUFFER_SIZE 2048
char g_input_buffer[INPUT_BUFFER_SIZE];
extern int g_debug_log;

int main(int argc, char** argv)
{
    if (hftp_log_init())
        return 1;
    if (threads_init())
        return 1;

    if (argc >= 2)
    {
        g_debug_log = strtol(argv[1], NULL, 10);

        if (g_debug_log)
            hftp_log_out("%d,%s\n",g_debug_log, argv[1]);
    }


    input_cond_blocking();

    hftp_log_out("it will terminated.. wait..\n");

    threads_join();
    threads_destroy();
    hftp_log_destroy();

    return 0;
}

