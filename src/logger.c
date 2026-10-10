#include <stdio.h>
#include <time.h>
#include "../include/event_logger.h"

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RED    "\033[31m"
#define COLOR_MAGENTA "\033[35m"

void zaps_log(log_level level,const char *message)
{
    time_t raw_time;
    struct tm *time_info;
    char time_buffer[20];
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", time_info);
    
    //1. Log seviyelerinin metin karşılıkları

    const char *level_strings[]=
    {
        "[INFO]",
        "[WARNING]",
        "[ERROR]",
        "[CRITICAL]"
    };

    // 2. Log seviyelerine göre renkleri belirleme
    const char *level_colors[]=
    {
        COLOR_GREEN, //INFO -> yeşil
        COLOR_YELLOW, //WARNING -> sarı
        COLOR_RED, //ERROR -> kırmızı
        COLOR_MAGENTA //CRITICAL -> mor
    };

    // 3. Log mesajını yazdırma
    printf("[%s] %s%s" COLOR_RESET " %s\n",time_buffer,level_colors[level],level_strings[level], message);

}


// main fonksiyonu, zaps_log fonksiyonunu test etmek için kullanılır. Farklı log seviyelerinde mesajlar yazdırır.
