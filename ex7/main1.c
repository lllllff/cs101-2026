#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 69
#define PICK_COUNT 7
#define MAX_SETS 5

int main(void) {
int n;
printf("歡迎光臨長庚樂透彩購買機台\n");
printf("請問您要買幾組樂透彩:");
if (scanf("%d", &n) != 1) {
return 1;
}

if (n < 1) n = 1;
if (n > MAX_SETS) n = MAX_SETS;

FILE *fp = fopen("lotto.txt", "w");
if (fp == NULL) {
perror("無法開啟 lotto.txt");
return 1;
}

time_t now = time(NULL);
char *time_str = ctime(&now);
if (time_str != NULL) {
for (int i = 0; time_str[i] != '\0'; i++) {
if (time_str[i] == '\n') {
time_str[i] = '\0';
break;
}
}
}

srand((unsigned int)time(NULL));

fprintf(fp, "lotto649\n");
fprintf(fp, "= %s =\n", (time_str != NULL) ? time_str : "");

for (int s = 1; s <= MAX_SETS; s++) {
fprintf(fp, "[%d]: ", s);
if (s <= n) {
int used[MAX_NUM + 1] = {0};
int picked = 0;
while (picked < PICK_COUNT) {
int num = rand() % MAX_NUM + 1;
if (!used[num]) {
used[num] = 1;
fprintf(fp, "%02d", num);
picked++;
if (picked < PICK_COUNT) {
fprintf(fp, " ");
}
}
}
fprintf(fp, "\n");
} else {
fprintf(fp, "--\n");
}
}

fprintf(fp, "csie@CGU\n");
fclose(fp);

printf("已為您購買的%d組樂透組合輸出至 lotto.txt\n", n);
return 0;
}
