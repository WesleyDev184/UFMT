#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int s, b, a;
    int s1, b1, a1;
} GameStats;

typedef struct {
    double sum_s, sum_b, sum_a;
    double sum_s1, sum_b1, sum_a1;
} GameTotalStats;

GameStats read_game_stats() {
    GameStats stats;
    char name[10000];
    scanf("%s", name);
    scanf("%d%d%d", &stats.s, &stats.b, &stats.a);
    scanf("%d%d%d", &stats.s1, &stats.b1, &stats.a1);
    return stats;
}

void accumulate_game_stats(GameStats stats, GameTotalStats *total_stats) {
    total_stats->sum_s += stats.s;
    total_stats->sum_b += stats.b;
    total_stats->sum_a += stats.a;
    total_stats->sum_s1 += stats.s1;
    total_stats->sum_b1 += stats.b1;
    total_stats->sum_a1 += stats.a1;
}

double calculate_percentage(double numerator, double denominator) {
    if (denominator == 0) {
        return 0.0;
    }
    return (numerator / denominator) * 100.0;
}

void print_percentage(char *label, double percentage) {
    printf("%s: %.2lf %%.\n", label, percentage);
}

int main() {
    int n, i;
    GameTotalStats total_stats = {0};
    scanf("%d", &n);
    for(i=1; i<=n; i++) {
        GameStats stats = read_game_stats();
        accumulate_game_stats(stats, &total_stats);
    }
    double ans_s = calculate_percentage(total_stats.sum_s1, total_stats.sum_s);
    double ans_b = calculate_percentage(total_stats.sum_b1, total_stats.sum_b);
    double ans_a = calculate_percentage(total_stats.sum_a1, total_stats.sum_a);
    print_percentage("Pontos de Saque", ans_s);
    print_percentage("Pontos de Bloqueio", ans_b);
    print_percentage("Pontos de Ataque", ans_a);
    return 0;
}
