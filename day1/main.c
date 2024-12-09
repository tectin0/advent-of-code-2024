#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "day1.h"

#define CAPACITY 1000

int main()
{
    char *input = read_file("input");
    char *line = input;

    bool is_first_column = true;

    int first_column[CAPACITY];
    int second_column[CAPACITY];

    int line_counter = 0;

    // iterate over the input line by line and extract numbers to the first and second column
    while (*line != '\0')
    {
        while (*line != '\n' && *line != '\0')
        {
            if (*line == ' ')
            {
                is_first_column = false;
            }

            int digits[10];
            int counter = 0;

            while (is_digit(*line) && *line != '\n' && *line != '\0')
            {
                int digit = to_digit(*line);

                // printf("%c - %d\n", *line, digit);

                digits[counter] = digit;

                counter++;
                line++;
            }

            // convert the array of digits to a number
            int number = 0;

            for (int i = 0; i < counter; i++)
            {
                number = number * 10 + digits[i];
            }

            // printf("%d\n", number);

            if (number > 0)
            {

                if (is_first_column)
                {
                    first_column[line_counter] = number;
                }
                else
                {
                    second_column[line_counter] = number;
                }
            }

            // printf("%c", *line);
            line++;
        }

        if (*line == '\n')
        {
            // printf("\n");
            is_first_column = true;
            line_counter++;
            line++;
        }
    }

    free(input);

    sort(first_column, CAPACITY);
    sort(second_column, CAPACITY);

    int total_distance = 0;
    int total_similarity = 0;

    for (int i = 0; i < CAPACITY; i++)
    {
        int first_number = first_column[i];
        int second_number = second_column[i];

        // printf("%d %d\n", first_number, second_number);
        total_distance += abs(first_number - second_number);

        int first_count_in_second = count(second_column, CAPACITY, first_number);

        int similarity = first_count_in_second * first_number;

        total_similarity += similarity;
    }

    printf("Total distance: %d\n", total_distance);
    printf("Total similarity: %d\n", total_similarity);

    return 0;
}

char *read_file(const char *filename)
{
    // Open in read binary mode -> CLRF will not be converted to LF
    // otherwise the length of the file will be wrong
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        return NULL;
    }

    // fseek: set the file position of the stream to the given offset
    // SEEK_END: offset is relative to the end of the file
    fseek(file, 0, SEEK_END);

    // ftell: returns the current value of the position indicator of the stream
    long length = ftell(file);

    // SEEK_SET: offset is relative to the start of the file
    fseek(file, 0, SEEK_SET);

    // malloc: allocates size bytes and returns a pointer to the allocated memory
    char *buffer = malloc(length + 1);
    if (!buffer)
    {
        fprintf(stderr, "Error: could not allocate memory for file %s\n", filename);
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);

    return buffer;
}

bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

int to_digit(char c)
{
    return c - '0';
}

// Exchange sort
void sort(int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (array[i] > array[j])
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int count(int *array, int length, int number)
{
    int counter = 0;

    for (int i = 0; i < length; i++)
    {
        if (array[i] == number)
        {
            counter++;
        }
    }

    return counter;
}