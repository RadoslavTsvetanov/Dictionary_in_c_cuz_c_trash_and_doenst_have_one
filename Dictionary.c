#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define type int

typedef struct DictionaryPair
{
    char *key;
    type value;
} DictionaryPair;

typedef struct Dictionary
{
    DictionaryPair *dictionary;
    int len;
} Dictionary;

Dictionary *init(int size)
{
    Dictionary *dictionary = (Dictionary *)malloc(sizeof(Dictionary));

    if (dictionary != NULL)
    {
        dictionary->dictionary = (DictionaryPair *)malloc(size * sizeof(DictionaryPair));

        if (dictionary->dictionary != NULL)
        {
            dictionary->len = 0;
        }
        else
        {
            free(dictionary);
            return NULL;
        }
    }

    return dictionary;
}

void AddKeyValuePair(Dictionary *self, char key[], type value)
{
    self->dictionary = (DictionaryPair *)realloc(self->dictionary, (self->len + 1) * sizeof(DictionaryPair));

    if (self->dictionary != NULL)
    {
        self->dictionary[self->len].key = strdup(key);

        if (self->dictionary[self->len].key != NULL)
        {
            self->dictionary[self->len].value = value;
            self->len++;
        }
        else
        {
            free(self->dictionary);
        }
    }
}

int main(void)
{
    Dictionary *myDict = init(10);

    if (myDict != NULL)
    {
        AddKeyValuePair(myDict, "key1", 42);
        AddKeyValuePair(myDict, "key2", 100);

        for (int i = 0; i < myDict->len; i++)
        {
            printf("Key: %s, Value: %d\n", myDict->dictionary[i].key, myDict->dictionary[i].value);
        }

        for (int i = 0; i < myDict->len; i++)
        {
            free(myDict->dictionary[i].key);
        }
        free(myDict->dictionary);
        free(myDict);
    }
    else
    {
        printf("Failed to initialize the dictionary.\n");
    }

    return 0;
}
