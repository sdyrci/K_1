#include <stdio.h>
#include "../include/process_monitor.h"
#include "../include/telemetry.h"
#include "../include/event_logger.h"

int main() {
    zaps_log(LOG_INFO, "=== Sistem Izleme Hizmeti Başlatiliyor ===");

    // 2 saniye aralıklarla 5 defa RAM ölçümü yapıp loglar.
    // (Gerçek ortamda kesintisiz izlemesi için ikinci parametreyi 0 yapabilirsin)
    start_memory_monitoring(2,10);

    zaps_log(LOG_INFO, "=== Sistem Izleme Hizmeti Sonlandirildi ===");
    return 0;
}