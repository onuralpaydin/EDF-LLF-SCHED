#include <stdio.h>
#include <stdlib.h>

// Görev yapısını tanımlama
typedef struct
{
    int task_id;          // Görev numarasý
    int execution_time;   // Çalýþma süresi
    int period;           // Periyod
    int deadline;         // Mevcut deadline
    int remaining_time;   // Kalan çalýþma süresi
    int next_arrival;     // Bir sonraki gelme zamaný
} Task;

// LLF Zamanlama Algoritmasý
void llf_scheduler(Task tasks[], int n, int simulation_time)
{
    printf("\nLLF Schedule:\n");
    int time = 0;

    while (time < simulation_time)
    {
        int min_laxity = 1e9; // Esneklik için başlangıç değeri
        int selected_task = -1;

        // Hazır görevleri bul ve esneklik (laxity) hesapla
        for (int i = 0; i < n; i++)
        {
            if (tasks[i].next_arrival <= time && tasks[i].remaining_time > 0)
            {
                int laxity = (tasks[i].deadline - time) - tasks[i].remaining_time;
                if (laxity < min_laxity)
                {
                    min_laxity = laxity;
                    selected_task = i;
                }
            }
        }

        // Eðer hiçbir görev çalışmaya hazır değilse
        if (selected_task == -1)
        {
            printf("%d-%d: Idle\n", time, time + 1);
            time++;
            continue;
        }

        // Seçilen görevi çalıştır
        printf("%d-%d: t_%d\n", time, time + 1, tasks[selected_task].task_id);
        tasks[selected_task].remaining_time--;

        // Görev tamamlanırsa deadline ve arrival güncelle
        if (tasks[selected_task].remaining_time == 0)
        {
            tasks[selected_task].deadline += tasks[selected_task].period;
            tasks[selected_task].next_arrival += tasks[selected_task].period;
            tasks[selected_task].remaining_time = tasks[selected_task].execution_time;
        }
        time++;
    }
}

// Ana Fonksiyon
int main()
{
    int n, simulation_time;

    // Kullanıcıdan girdi al
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    Task tasks[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter execution time and period for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].execution_time, &tasks[i].period);
        tasks[i].task_id = i + 1;
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].deadline = tasks[i].period;
        tasks[i].next_arrival = 0;
    }

    printf("Enter simulation time: ");
    scanf("%d", &simulation_time);

    // LLF Zamanlaması
    llf_scheduler(tasks, n, simulation_time);

    return 0;
}
