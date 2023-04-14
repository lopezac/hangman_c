#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXWORD 150

char *dictionary_path = "./english_words.txt";

int count_lines(FILE *fp);
int get_random_number(int max_number);
char *get_line_n(FILE *fp, int line_number);
char *get_random_word(void);

int main()
{
    char *word;

    get_random_word();
    // printf("Random word is %s", "word");
    return 0;
}

char *get_random_word(void)
{
    char *word;
    int number_lines = 1, random_line;
    FILE *fp;

    if ((fp = fopen(dictionary_path, "r")) == NULL)
    {
        printf("Error reading dictionary %s\n", dictionary_path);
        return 0;
    }
    number_lines = count_lines(fp);
    fseek(fp, 0, SEEK_SET);
    random_line = get_random_number(number_lines);
    word = get_line_n(fp, random_line);
    printf("nmber_lines %d\nrandom_line %d\nword is %s", number_lines, random_line, word);
    fclose(fp);
    // return word;
}

char *get_line_n(FILE *fp, int line_number)
{
    int c;
    char *line;

    while ((c = getc(fp)) != EOF)
    {
        if (c != '\n')
            continue;
        if (line_number == 0)
            return fgets(line, MAXWORD, fp);
        line_number--;
    }
    return line;
}

int get_random_number(int max_number)
{
    // srand is used to seed rand so it's a random number each time
    srand(time(NULL));
    return rand() % max_number;
}

int count_lines(FILE *fp)
{
    int n = 1, c;

    while ((c = getc(fp)) != EOF)
        if (c == '\n')
            n++;
    return n;
}