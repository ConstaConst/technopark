#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#define DEFAULT_SIZE 8
#define MULT 2

/*Returns NULL on failure.*/
char* readLine(bool* isEnd);
/*Returns NULL on failure*/
char** read(size_t* numLines);
void deleteArray(char*** stringArray, size_t size);
/*Returns NULL on failure*/
char** filter(char** input, size_t size);
void printResult(char** resultArray);

int main(int argc, char *argv[]) {
    size_t numInputLines = 0;
    char** input = read(&numInputLines);
    if (input == NULL) {
        printResult(NULL);
    } else {
        char** result = filter(input, numInputLines);
        if (result == NULL) {
            printResult(NULL);
        } else {
            printResult(result);
            deleteArray(&result, (size_t)(-1));
        }
        deleteArray(&input, numInputLines);
    }

    return 0;
}


char* readLine(bool* isEnd) {
    size_t capacity = DEFAULT_SIZE;
    char* line = (char*)malloc(capacity * sizeof(char));
    if (line == NULL)
        return NULL;

    size_t curLength = 0;
    int checkInput = 0;
    char c = '\0';
    while ((checkInput = scanf("%c", &c)) == 1 && c != '\n') {
        if (curLength >= capacity - 1) {
            capacity *= MULT;
            char* increasedBuffer = (char*)realloc(line, capacity * sizeof(char));
            if (increasedBuffer == NULL) {
                free(line);
                return NULL;
            }
            line = increasedBuffer;
        }
        line[curLength++] = c;
    }

    if (checkInput != 0) {
        line[curLength] = '\0';
        if (checkInput == EOF) {
            *isEnd = true;
        }
        return line;
    }
    //Input error
    free(line);
    return  NULL;
}

char** read(size_t* numLines) {
    *numLines = 0;
    bool isEnd = false;

    size_t capacity = DEFAULT_SIZE;
    char** input = (char**)malloc(capacity * sizeof(char*));
    if (input == NULL) {
        return NULL;
    }

    char* line = NULL;
    while ((line = readLine(&isEnd)) != NULL && isEnd != true) {
        if (*numLines >= capacity - 1) {
            capacity *= MULT;
            char** increasedBuffer = (char**)realloc(input, capacity * sizeof(char*));
            if (increasedBuffer == NULL) {
                deleteArray(&input, *numLines);
                free(line);
                *numLines = 0;
                return NULL;
            }
            input = increasedBuffer;
        }
        input[(*numLines)++] = line;
    }

    if (line == NULL) {
        deleteArray(&input, *numLines);
        *numLines = 0;
        return NULL;
    }
    input[(*numLines)++] = line;
    return input;
}

void deleteArray(char*** stringArray, size_t size) {
    if(*stringArray == NULL) {
        return;
    }

    for (size_t i = 0; i < size && (*stringArray)[i] != NULL; ++i) {
        free((*stringArray)[i]);
    }

    free(*stringArray);
    *stringArray = NULL;
}

char** filter(char** input, size_t size) {
    if (input == NULL || size == 0) {
        return NULL;
    }

    size_t capacity = DEFAULT_SIZE;
    char** result = (char**)malloc(capacity * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    const char* filterKeys[] = {"Date:", "From:", "To:", "Subject:"};
    const size_t keysSizes[] = {5, 5, 3, 8};
    const size_t numFilterKeys = 4;

    size_t numResultLines = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < numFilterKeys; ++j) {
            if (strncmp(input[i], filterKeys[j], keysSizes[j]) == 0) {
                if (numResultLines >= capacity - 2) {
                    capacity *= MULT;
                    char** increasedBuffer = (char**)realloc(result, capacity * sizeof(char*));
                    if (increasedBuffer == NULL) {
                        deleteArray(&result, numResultLines);
                        return NULL;
                    }
                    result = increasedBuffer;
                }
                char* lineBuffer = (char*)malloc(strlen(input[i]) + 1);
                if (lineBuffer == NULL) {
                    deleteArray(&result, numResultLines);
                    return NULL;
                }
                strcpy(lineBuffer, input[i]);
                result[numResultLines++] = lineBuffer;
                break;
            }
        }
    }

    result[numResultLines] = NULL;
    return result;
}


void printResult(char** resultArray) {
    if (resultArray != NULL) {
        for (size_t i = 0; resultArray[i] != NULL; i++) {
            printf("%s\n", resultArray[i]);
        }
    } else {
        printf("[error]");
    }
}