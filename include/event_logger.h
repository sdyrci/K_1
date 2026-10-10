#ifndef EVENT_LOGGER_H
#define EVENT_LOGGER_H

typedef enum
{
  LOG_INFO=0,
  LOG_WARNING,
  LOG_ERROR,
  LOG_CRITICAL

} log_level;

void zaps_log(log_level level, const char *message);

#endif