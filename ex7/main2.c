#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_LEN 128
#define BOOK_COUNT 6

typedef struct Books {
int id;
int price;
char title[TITLE_LEN];
} book_t;

void total_price(const book_t books[], int count) {
long long sum = 0;
for (int i = 0; i < count; i++) {
sum += books[i].price;
}
printf("所有書籍總價: %lld 元\n", sum);
}

void list_books(const book_t books[], int count) {
printf("%-4s | %-6s | %s\n", "Id", "Price", "Title");
printf("-----+--------+--------------------------------------------------\n");
for (int i = 0; i < count; i++) {
printf("%-4d | %-6d | %s\n", books[i].id, books[i].price, books[i].title);
}
}

int main(void) {
book_t books[BOOK_COUNT] = {
{1, 1000, "All the Light We Cannot See"},
{2, 300, "The 38 Letters from J.D. Rockefeller to his son"},
{3, 1000, "The Ballad of Songbirds and Snakes"},
{4, 550, "Killers of the Flower Moon"},
{5, 870, "Elon Musk"},
{6, 1344, "Milk and Honey 12-Month 2024"}
};

FILE *fp = fopen("Book.bin", "wb");
if (fp == NULL) {
perror("無法建立 Book.bin");
return 1;
}
fwrite(books, sizeof(book_t), BOOK_COUNT, fp);
fclose(fp);
book_t loaded[BOOK_COUNT];
FILE *rfp = fopen("Book.bin", "rb");
if (rfp == NULL) {
perror("無法讀取 Book.bin");
return 1;
}
size_t read_count = fread(loaded, sizeof(book_t), BOOK_COUNT, rfp);
fclose(rfp);

list_books(loaded, (int)read_count);
total_price(loaded, (int)read_count);

return 0;
}
