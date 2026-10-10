#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

// Bellek kullanım uyarısı için eşik yüzdeleri (%)
#define RAM_THRESHOLD_WARNING   70.0
#define RAM_THRESHOLD_CRITICAL  85.0

/*
 * ============================================================================
 * Fonksiyon: start_memory_monitoring
 * ----------------------------------------------------------------------------
 * Telemetri modülünden periyodik olarak bellek verilerini çeker,
 * eşik değerleriyle (thresholds) karşılaştırır ve duruma göre
 * event_logger modülü üzerinden zaman damgalı log basar.
 * 
 * Parametreler:
 *   - interval_seconds: Kaç saniyede bir kontrol yapılacağı
 *   - max_iterations: Kaç defa kontrol edilip çıkılacağı (0 verilirse sonsuz döngü)
 * ============================================================================
 */
void start_memory_monitoring(int interval_seconds, int max_iterations);

#endif // SYSTEM_MONITOR_H