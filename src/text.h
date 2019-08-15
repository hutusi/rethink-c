/**
 * @file text.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Text string. (similar to string in C++.)
 *
 * @date 2019-08-15
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_TEXT_H
#define RETHINK_C_TEXT_H

/**
 * @brief Definition of a @ref Text.
 *
 */
typedef struct _Text Text;

#define CHAR_NIL 0

/**
 * @brief Allocate a new empty Text.
 * 
 * @return Text*        The new Text if success, otherwise NULL.
 */
Text *text_new();

/**
 * @brief New a new Text from a string.
 * 
 * @param string    The original string.
 * @param length    The length of the string.
 * @return Text*    The new Text if success, otherwise NULL.
 */
Text *text_new_from(char *string, int length);

/**
 * @brief Delete a Text and free back memory.
 *
 * @param text      The Text to delete.
 */
void text_free(Text *text);

/**
 * @brief Clone a new text from text.
 * 
 * @param text      The text.
 * @return Text*    The clone new text.
 */
Text *text_clone(Text *text);

/**
 * @brief Get the length of a text.
 * 
 * @param text              The text.
 * @return unsigned int     The length.
 */
unsigned int text_length(Text *text);

/**
 * @brief Get the indicated index charactor of a text.
 * 
 * @param text      The text.
 * @param index     The indicated index.
 * @return char     The charactor.
 */
char text_char_at(Text *text, unsigned int index);

#endif /* #ifndef RETHINK_C_TEXT_H */
