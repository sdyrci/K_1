#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/telemetry.h"

int get_memory_telemetry(MemoryTelemetry *telemetry) {
    if (telemetry == NULL) {
        return -1;
    }

#if defined(_WIN32) || defined(_WIN64)
    // ========================================================================
    // WINDOWS ORTAMI (Win32 API - GlobalMemoryStatusEx)
    // ========================================================================
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status); // WinAPI için yapı boyutunu bildirmek şarttır

    // Windows kernel'inden bellek durumunu sorguluyoruz
    if (GlobalMemoryStatusEx(&status)) {
        telemetry->total_memory_bytes     = status.ullTotalPhys;
        telemetry->available_memory_bytes = status.ullAvailPhys;
        telemetry->free_memory_bytes      = status.ullAvailPhys; // Windows'ta kullanılabilir RAM esas alınır
        telemetry->memory_usage_percentage = (double)status.dwMemoryLoad;

        return 0; // Windows verisi başarıyla çekildi
    } else {
        return -1; // API çağrısı başarısız oldu
    }

#else
    // ========================================================================
    // LINUX / WSL ORTAMI (/proc/meminfo Sanal Dosyası)
    // ========================================================================
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        return -1;
    }

    char line[256];
    unsigned long total_kb = 0, free_kb = 0, avail_kb = 0;
    int found_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "MemTotal: %lu kB", &total_kb) == 1) {
            found_count++;
        } else if (sscanf(line, "MemFree: %lu kB", &free_kb) == 1) {
            found_count++;
        } else if (sscanf(line, "MemAvailable: %lu kB", &avail_kb) == 1) {
            found_count++;
        }

        if (found_count == 3) {
            break;
        }
    }

    fclose(file);

    if (found_count < 3) {
        return -1;
    }

    // KB birimini Bayt (Byte) birimine çeviriyoruz (1 KB = 1024 Byte)
    telemetry->total_memory_bytes     = (unsigned long long)total_kb * 1024;
    telemetry->free_memory_bytes      = (unsigned long long)free_kb * 1024;
    telemetry->available_memory_bytes = (unsigned long long)avail_kb * 1024;

    if (telemetry->total_memory_bytes > 0) {
        unsigned long long used_bytes = telemetry->total_memory_bytes - telemetry->available_memory_bytes;
        telemetry->memory_usage_percentage = ((double)used_bytes / telemetry->total_memory_bytes) * 100.0;
    } else {
        telemetry->memory_usage_percentage = 0.0;
    }

    return 0;
#endif
}

