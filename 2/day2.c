#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ENTRIES 1000

struct entry
{
    int min;
    int max;
    char req;

    char pass[21];
};

struct entry * read_passwords()
{
    struct entry * passes = (struct entry *) malloc(NUM_ENTRIES * sizeof(struct entry));

    FILE *fp = fopen("input.txt", "r");

    int i = 0;

    while (!feof(fp) && i < NUM_ENTRIES)
    {
        struct entry *cur = passes + i;

        fscanf(fp, "%d-%d %c: %s\n", &(cur->min), &(cur->max), &(cur->req), cur->pass);
        i++;
    }

    fclose(fp);

    return passes;
}

int is_valid_pass(struct entry e)
{
    int count = 0;
    for (int i = 0; i < strlen(e.pass); i++)
    {
        if (e.pass[i] == e.req) count++;
    }

    if (count >= e.min && count <= e.max) return 1;
    else return 0;
}

int num_valid(struct entry* entries, int num_entries)
{
    int count = 0;
    for (int i = 0; i < num_entries; i++)
    {
        if (is_valid_pass(entries[i])) count++;
    }

    return count;
}

int is_valid_pass_pt2(struct entry e)
{
    if (e.pass[e.min-1] == e.req ^ e.pass[e.max-1] == e.req) return 1;
    else return 0;
}

int num_valid_pt2(struct entry* entries, int num_entries)
{
    int count = 0;
    for (int i = 0; i < num_entries; i++)
    {
        if (is_valid_pass_pt2(entries[i])) count++;
    }

    return count;
}

int main()
{
    struct entry * entries = read_passwords();

    int valid = num_valid(entries, NUM_ENTRIES);
    int valid_pt2 = num_valid_pt2(entries, NUM_ENTRIES);

    printf("Part 1: Number of valid passwords: %d\n", valid);
    printf("Part 2: Number of valid passwords: %d\n", valid_pt2);

    free(entries);

    return 0;
}
