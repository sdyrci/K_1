#include <stdio.h>
#include "../include/process_monitor.h"
#include "../include/telemetry.h"
#include "../include/event_logger.h"

// Platforma özel bekleme (sleep) fonksiyonu tanımı
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define sleep_seconds(seconds) Sleep((seconds) * 1000) // Windows Sleep milisaniye alır
#else
    #include <unistd.h>
    #define sleep_seconds(seconds) sleep(seconds)          // POSIX sleep saniye alır
#endif

void start_memory_monitoring(int interval_seconds, int max_iterations) {
    zaps_log(LOG_INFO, "Bellek Izleme Motoru (Monitor) başlatildi.");

    MemoryTelemetry telemetry;
    char log_buffer[256];
    int iteration = 0;

    while (1) {
        // Telemetri modülünden anlık RAM verisini çekiyoruz
        if (get_memory_telemetry(&telemetry) == 0) {
            
            double total_gb = (double)telemetry.total_memory_bytes / (1024 * 1024 * 1024);
            double avail_gb = (double)telemetry.available_memory_bytes / (1024 * 1024 * 1024);

            // Eşik değerlerine göre durum analizi yapıp log basıyoruz
            if (telemetry.memory_usage_percentage >= RAM_THRESHOLD_CRITICAL) {
                snprintf(log_buffer, sizeof(log_buffer), 
                         "KRITIK BELLEK SEVIYESI! Kullanim: %%%.1f (Boş: %.2f GB / Toplam: %.2f GB)", 
                         telemetry.memory_usage_percentage, avail_gb, total_gb);
                zaps_log(LOG_CRITICAL, log_buffer);

            } else if (telemetry.memory_usage_percentage >= RAM_THRESHOLD_WARNING) {
                snprintf(log_buffer, sizeof(log_buffer), 
                         "Yuksek bellek kullanimi tespit edildi! Kullanim: %%%.1f", 
                         telemetry.memory_usage_percentage);
                zaps_log(LOG_WARNING, log_buffer);

            } else {
                snprintf(log_buffer, sizeof(log_buffer), 
                         "Bellek durumu normal. Kullanim: %%%.1f (Kullanilabilir: %.2f GB)", 
                         telemetry.memory_usage_percentage, avail_gb);
                zaps_log(LOG_INFO, log_buffer);
            }

        } else {
            zaps_log(LOG_ERROR, "Telemetri verisi okunamadi!");
        }

        iteration++;

        // Eğer belirli bir sayaç sınırı koyulduysa ve ulaşıldıysa döngüden çık
        if (max_iterations > 0 && iteration >= max_iterations) {
            zaps_log(LOG_INFO, "Izleme periyodu tamamlandi. Monitor kapatiliyor.");
            break;
        }

        // Belirtilen saniye kadar bekle
        sleep_seconds(interval_seconds);
    }
}