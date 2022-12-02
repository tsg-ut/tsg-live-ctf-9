#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define N_NOTES 10
#define BUF_SIZE 40

char flag[100]; // Can you read me?

typedef struct Page {
    struct Page *next;
    char content[];
} Page;
Page *notes[N_NOTES];

void die(const char *msg) {
    puts(msg);
    exit(1);
}

unsigned get_int() {
    unsigned x;
    scanf("%u", &x);
    return x;
}

void readn(char *buf, unsigned size) {
    unsigned cnt = 0;
    for (unsigned i = 0; i < size; i++) {
        unsigned x = read(0, buf + i, 1);
        cnt += x;
        if (x != 1 || buf[cnt - 1] == '\n') break;
    }
    if (cnt == 0) exit(-1);
    if (buf[cnt - 1] == '\n') buf[cnt - 1] = '\x00';
}

void init() {
    alarm(60);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

unsigned get_note_index(const char* msg) {
    printf("%s: ", msg);
    unsigned idx = get_int();
    if (idx >= N_NOTES) die("invalid choice");
    return idx;
}

unsigned page_menu() {
    puts("1. add page");
    puts("2. delete page");
    puts("3. back to main menu");
    printf("> ");
    return get_int();
}

unsigned main_menu() {
    puts("1. modify note");
    puts("2. concat notes");
    puts("3. print note");
    printf("> ");
    return get_int();
}

void add_page(unsigned note_idx) {
    printf("index: ");
    unsigned idx = get_int();

    Page **cur = &notes[note_idx];
    for (int i = 0; i < idx; i++) {
        if (*cur == NULL) die("invalid index");
        cur = &(*cur)->next;
    }
    Page *next = *cur;

    printf("size: ");
    unsigned size = get_int();
    Page *page = (Page *)malloc(size + 8);
    page->next = next;
    printf("data: ");
    readn(page->content, size);
    *cur = page;
}

void delete_page(unsigned note_idx) {
    printf("index: ");
    unsigned idx = get_int();

    Page **cur = &notes[note_idx];
    for (int i = 0; i < idx; i++) {
        if (*cur == NULL) die("invalid index");
        cur = &(*cur)->next;
    }
    if (*cur == NULL) die("invalid index");
    Page *next = (*cur)->next;
    free(*cur);
    *cur = next;
}

void page_main(unsigned note_idx) {
    while (1) {
        switch (page_menu()) {
            case 1:
                add_page(note_idx); break;
            case 2:
                delete_page(note_idx); break;
            default:
                return;
        }
    }
}

void concat_notes(unsigned idx1, unsigned idx2, unsigned idx3) {
    notes[idx3] = notes[idx1];
    Page **cur = &notes[idx3];
    while(*cur != NULL) {
        cur = &(*cur)->next;
    }
    *cur = notes[idx2];
    notes[idx1] = NULL;
    notes[idx2] = NULL;
}

void print_note(unsigned idx) {
    Page **cur = &notes[idx];
    while(*cur != NULL) {
        printf("%s\n", (*cur)->content);
        puts("\n------------\n"); 
        cur = &(*cur)->next;
    }
}
    
int main(void) {
    init();
    unsigned idx1, idx2, idx3;
    int fd = open("flag.txt", O_RDONLY);
    int r = read(fd, flag, 99);
    if (r <= 0) die("ask admin");
    close(fd);
    while (1) {
        switch (main_menu()) {
            case 1:
                page_main(get_note_index("note index")); break;
            case 2: 
                idx1 = get_note_index("note index 1");
                idx2 = get_note_index("note index 2");
                idx3 = get_note_index("note index 3");
                concat_notes(idx1, idx2, idx3); break;
            case 3:
                print_note(get_note_index("note index")); break;
            default:
                return 0;
        }
    }
    return 0;
}
