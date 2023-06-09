#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAXWORD 150
#define EMPTY_LETTER '_'

char *dictionary_path = "./english_words.txt";
char word[MAXWORD];
char cur_char = ' ';
int player_lives = 5;
int letters_left = 0;

// main loop
int is_game_over(int letters_left);
int get_user_letter(void);
void replace_letter(char *s1, char *s2, int letter);
void get_empty_word(char *empty, char *word);
// get random word from dictionary
int count_lines(FILE *fp);
int get_random_number(int max_number);
int get_line_nth(char *s, int line_num, FILE *fp);
void get_random_word(char *s);
void start_game(char *s);

int main()
{
    int user_letter;
    char word_guessed[MAXWORD];

    start_game(word_guessed);
    while (!is_game_over(letters_left))
    {
        user_letter = get_user_letter();
        if (strchr(word, user_letter) && !strchr(word_guessed, user_letter))
            replace_letter(word, word_guessed, user_letter);
        else
        {
            player_lives--;
            printf("Lives left %d\n", player_lives);
        }
        printf("%s\n", word_guessed);
        if (is_game_over(letters_left))
        {
            printf("\nEnter (y) to restart the game\n");
            user_letter = get_user_letter();
            if (user_letter == 'y')
                start_game(word_guessed);
        }
    }
    return 0;
}

void start_game(char *word_guessed)
{
    get_random_word(word);
    get_empty_word(word_guessed, word);
    letters_left = strlen(word) - 2;
    player_lives = 5;
    printf("\nWelcome to Hangman Game!\n");
    printf("Word to guess: %s", word);
    printf("You have %d lives!\n", player_lives);
    printf("Enter your guess:\n");
}

void get_empty_word(char *empty, char *word)
{
    int len;

    len = strlen(word) - 2;
    while (len--)
    {
        *empty = EMPTY_LETTER;
        *empty++;
        *word++;
    }
    *empty = '\0';
}

// replace letter that match letters in s1 in s2
void replace_letter(char *s1, char *s2, int letter)
{
    while (*s1 != EOF && *s1 != '\0')
    {
        if (*s1 == letter)
        {
            *s2 = letter;
            letters_left--;
        }
        *s1++;
        *s2++;
    }
}

int get_user_letter(void)
{
    int c;

    while (!isalpha(c = getchar()))
        ;
    cur_char = tolower(c);
    return tolower(c);
}

int is_game_over(int letters_left)
{
    return (player_lives && letters_left) ? 0 : 1;
}

void get_random_word(char *str)
{
    int number_lines = 1, random_line;
    FILE *fp;

    if ((fp = fopen(dictionary_path, "r")) == NULL)
    {
        printf("Error reading dictionary %s\n", dictionary_path);
        return;
    }
    number_lines = count_lines(fp);
    fseek(fp, 0, SEEK_SET);
    random_line = get_random_number(number_lines);
    if (get_line_nth(str, random_line, fp) <= 0)
        printf("Can't read word from dictionary %s\n", dictionary_path);
    fclose(fp);
}

int get_line_nth(char *str, int line_num, FILE *fp)
{
    int c;

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n' && line_num-- && line_num == 0)
        {
            return fgets(str, MAXWORD, fp) ? strlen(str) : 0;
        }
    }
    return 0;
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
