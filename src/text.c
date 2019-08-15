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
#include <stdlib.h>
#include <string.h>

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
    text->_allocated = 16; /** initial default. */
    text->length = 0;
    text->data = (char *)malloc(text->_allocated * sizeof(char));
    return text;
}

Text *text_new()
{
    return text_new_with_size(16); /** initial default. */
}

Text *text_new_from(char *string, int length)
{
    Text *text = text_new_with_size(length);
    strncpy(text->data, string, length);
    text->length = length;
    return text;
}

void text_free(Text *text)
{
    free(text->data);
    free(text);
}

Text *text_clone(Text *text)
{
    Text *clone = text_new_with_size(text->_allocated);
    strncpy(clone->data, text->data, text->length);
    clone->length = text->length;
    return clone;
}

unsigned int text_length(Text *text)
{
    return text->length;
}

char text_char_at(Text *text, unsigned int index)
{
    if (index >= text->length) {
        return CHAR_NIL;
    } else {
        return text->data[index];
    }
}
