#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include "log.h"

void
log_msg(const char* file, const int line, const char *format, ...) {
    FILE *log_file = fopen("game.log", "a");
    if (log_file == NULL) {
        fprintf(stderr, "Error opening log file: %s\n", strerror(errno));
        exit(1);
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    int timestamp_len = fprintf(
            log_file,
            "[%04d-%02d-%02d %02d:%02d:%02d] [%s:%d] ",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec,
            file, line
    );
    if (timestamp_len < 0) {
        fprintf(stderr, "Error writing timestamp: %s\n", strerror(errno));
        fclose(log_file);
        exit(1);
    }

    va_list args;
    va_start(args, format);
    int message_len = vfprintf(log_file, format, args);
    va_end(args);

    if (message_len < 0) {
        fprintf(stderr, "Error writing message: %s\n", strerror(errno));
        fclose(log_file);
        exit(1);
    }

    fflush(log_file);
    if (ferror(log_file)) {
        fprintf(stderr, "Error flushing log file: %s\n", strerror(errno));
        exit(1);
    }

    if (fclose(log_file) == EOF) {
        fprintf(stderr, "Error closing log file: %s\n", strerror(errno));
        exit(1);
    }
}