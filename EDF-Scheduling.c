#include <stdio.h>
#include <limits.h> // INT_MAX için

// Görev yapısı
typedef struct {
    int execution_time; // Görevin çalışma süresi
    int period;         // Görevin periyodu
    int remaining_time; // Görevin kalan çalışma süresi
    int deadline;       // Görevin bitiş zamanı
    int id;             // Görevin kimliği
} Task;

// En erken deadline'ı bul
int find_earliest_deadline(Task tasks[], int n, int current_time) {
    int min_deadline = INT_MAX;
    int task_index = -1;

    for (int i = 0; i < n; i++) {
        // Görev çalışabilir mi?
        if (tasks[i].remaining_time > 0 && tasks[i].deadline < min_deadline) {
            min_deadline = tasks[i].deadline;
            task_index = i;
        }
    }
    return task_index;
}

int main() {
    int n, simulation_time;

    // kullanıcıdan görev sayısını al
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];

    // kullanıcıdan görev bilgilerini al
    for (int i = 0; i < n; i++) {
        printf("Enter execution time and period for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].execution_time, &tasks[i].period);
        tasks[i].remaining_time = 0; // başlangıçta kalan süre 0
        tasks[i].deadline = tasks[i].period; // ilk deadline periyoda eşittir
        tasks[i].id = i + 1; // Görevi tanımlamak için bir kimlik
    }

    // kullanıcıdan simülasyon süresini al
    printf("Enter simulation time: ");
    scanf("%d", &simulation_time);

    printf("\nEDF Schedule:\n");

    // Simülasyonu başlat
    for (int current_time = 0; current_time < simulation_time; current_time++) {
        // Görevleri güncelle
        for (int i = 0; i < n; i++) {
            if (current_time % tasks[i].period == 0) { // Görev yeni periyoda başlıyor
                tasks[i].remaining_time = tasks[i].execution_time; // çalışma süresini sıfırla
                tasks[i].deadline = current_time + tasks[i].period; // Yeni deadline'ı ayarla
            }
        }

        // çalıştırılacak görevi bul (en erken deadline)
        int task_index = find_earliest_deadline(tasks, n, current_time);

        if (task_index != -1) {
            // Görevi çalıştır
            tasks[task_index].remaining_time--;

            // çıktıyı yazdır
            printf("%d-%d: t_%d\n", current_time, current_time + 1, tasks[task_index].id);
        } else {
            // Idle durumu
            printf("%d-%d: Idle\n", current_time, current_time + 1);
        }
    }

    return 0;
}
