/**
 * @file text.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to text.h
 * @date 2019-08-15
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "text.h"
#include "def.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief All ways append '\0' to text, for dapat c string.
 * 
 */

/**
 * @brief Definition of a @ref Text.
 *
 */
struct _Text {
    char *data;
    unsigned int length;
    unsigned int _allocated;
};

static inline Text *text_new_with_size(unsigned int size)
{
    Text *text= (Text *)malloc(sizeof(Text));
    text->_allocated = size;
    text->length = 0;
    text->data = (char *)malloc(text->_allocated * sizeof(char));
    return text;
}

Text *text_new()
{
    return text_new_with_size(16); /** initial default. */
}

Text *text_from(const char *string)
{
    size_t len = strlen(string);
    Text *text = text_new_with_size(len + 1);
    strcpy(text->data, string);
    text->length = len;
    return text;
}

Text *text_n_from(const char *string, int length)
{
    Text *text = text_new_with_size(length + 1);
    strncpy(text->data, string, length);
    text->data[length] = '\0';
    text->length = length;
    return text;
}

void text_free(Text *text)
{
    free(text->data);
    free(text);
}

Text *text_clone(const Text *text)
{
    Text *clone = text_new_with_size(text->_allocated);
    strncpy(clone->data, text->data, text->length + 1);
    clone->length = text->length;
    return clone;
}

const char *text_char_string(const Text *text)
{
    return text->data;
}

unsigned int text_length(const Text *text)
{
    return text->length;
}

char text_char_at(const Text *text, unsigned int index)
{
    if (index >= text->length) {
        return CHAR_NIL;
    } else {
        return text->data[index];
    }
}

int text_compare(const Text *text1, const Text *text2)
{
    for (unsigned int i = 0; i < text1->length; ++i) {
        if (text1->data[i] > text2->data[i]) {
            return 1;
        } else if (text1->data[i] < text2->data[i]) {
            return -1;
        } else {
            continue;
        }
    }

    if (text1->length > text2->length) {
        return 1;
    } else if (text1->length < text2->length) {
        return -1;
    } else {
        return 0;
    }
}

int text_equal(const Text *text1, const Text *text2)
{
    return text_compare(text1, text2) == 0;
}
