/**
 * @file text.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Text string. (similar to string in C++.)
 * 
 * The most difference between Text and char string is:
 * 
 *      Text can contain '\0', NIL, or any charactor.
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
 * @return Text*    Return new Text if success, otherwise NULL.
 */
Text *text_from(const char *string);

/**
 * @brief New a new Text from a string with length.
 *
 * @param string    The original string.
 * @param length    The length of the string.
 * @return Text*    The new Text if success, otherwise NULL.
 */
Text *text_n_from(const char *string, int length);

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
Text *text_clone(const Text *text);

/**
 * @brief Convert a text as a const char string.
 *
 * @param text          The text.
 * @return const char*  The char string.
 */
const char *text_char_string(const Text *text);

/**
 * @brief Get the length of a text.
 *
 * @param text              The text.
 * @return unsigned int     The length.
 */
unsigned int text_length(const Text *text);

/**
 * @brief Get the indicated index charactor of a text.
 *
 * @param text      The text.
 * @param index     The indicated index.
 * @return char     The charactor.
 */
char text_char_at(const Text *text, unsigned int index);

/**
 * @brief Compare two text.
 *
 * @param text1     One text.
 * @param text2     Another text.
 * @return int      1 if the first text greater than the second; -1 if the
 *                  second text greater than the first; 0 if two text have same
 *                  content.
 */
int text_compare(const Text *text1, const Text *text2);

/**
 * @brief Judge the equality of two text's content.
 * 
 * @param text1     One text.
 * @param text2     Another text.
 * @return int      Return 1 if equal, otherwise return 0.
 */
int text_equal(const Text *text1, const Text *text2);

#endif /* #ifndef RETHINK_C_TEXT_H */
