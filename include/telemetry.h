#ifndef SYSTEM_TELEMETRY_H
#define SYSTEM_TELEMETRY_H

#include <stddef.h> // size_t veri tipi ve platform bağımsız boyutlar için

/*
 * ============================================================================
 * Platform Tespiti ve Kütüphane Yönlendirmesi
 * ----------------------------------------------------------------------------
 * Windows ortamında GlobalMemoryStatusEx gibi sistem WinAPI fonksiyonlarına
 * erişebilmek için <windows.h> dâhil edilir.
 * ============================================================================
 */
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

/*
 * ============================================================================
 * Yapı (Struct): MemoryTelemetry
 * ----------------------------------------------------------------------------
 * Windows ve Linux sistemlerinden okunan bellek metriklerini tutan yapı.
 * 
 * Veri Tipleri & Birimler:
 * - unsigned long long: 64-bit platformlarda devasa RAM miktarlarını (Bayt cinsinden)
 *   taşma (overflow) olmadan tutmak için seçilmiştir (min 8 bayt).
 * - double: %0.00 - %100.00 arası hassas kullanım oranını temsil eder.
 * ============================================================================
 */
typedef struct {
    unsigned long long total_memory_bytes;     // Toplam Fiziksel RAM (Bayt)
    unsigned long long free_memory_bytes;      // Boş RAM (Bayt)
    unsigned long long available_memory_bytes; // Kullanılabilir RAM (Bayt)
    double memory_usage_percentage;            // Hesaplanan Bellek Kullanım Yüzdesi (%)
} MemoryTelemetry;

/*
 * ============================================================================
 * Fonksiyon Prototipi: get_memory_telemetry
 * ----------------------------------------------------------------------------
 * Çalıştığı platformu otomatik tespit eder:
 * - Windows ise: Win32 API (GlobalMemoryStatusEx) ile RAM verilerini çeker.
 * - Linux ise: /proc/meminfo sanal dosya sistemini okur.
 * 
 * Parametre:
 *   - MemoryTelemetry *telemetry: Bellek verilerinin yazılacağı struct adresi.
 * 
 * Dönüş Değeri (int):
 *   -  0 : Veri toplama başarılı.
 *   - -1 : Sistem çağrısı veya dosya okuma hatası.
 * ============================================================================
 */
int get_memory_telemetry(MemoryTelemetry *telemetry);

#endif // SYSTEM_TELEMETRY_H