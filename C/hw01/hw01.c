#include "hw01.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****  UTILITIES  ************************************************************/

/*
 * Returns true if and only if 'c' is one of the characters of 'str'.
 *
 * DO NOT EDIT THIS FUNCTION, it is not part of your homework.
 * You can, however, use it to make your life easier, like this:
 *
 *      if (isOneOf(c, str)) {
 *          // this will execute if c is contained in str
 *      } else {
 *          // this will execute otherwise
 *      }
 *
 * For instance,
 *      isOneOf(' ', "Hello, World!")   -> true
 *      isOneOf(' ', "Pocahontas")      -> false
 *      isOneOf('.', "Hello, World!")   -> false
 *      isOneOf('!', "Hello, World!")   -> true
 */
bool isOneOf(char c, char str[])
{
    return strchr(str, c) != NULL;
}


/****  HERE BEGINS YOUR HOMEWORK  ********************************************/

/*
 * There shall be no two consecutive spaces in the string.
 * You are to FIND and FIX an error in this code.
 *
 * Examples:
 *  Wrong: "Hello  world."
 *  Wrong: "Hello.  World."
 *  Right: "Hello world."
 *  Right: "Hello. Wonderful. World."
 */
enum parentheses
{
    NONE,
    PARENT,
    BRACES,
    BRACKETS
};

bool isNextNonspaceCapital(size_t index, char str[], size_t len)
{
    for (size_t i = index; i < len; i++) {
        if (str[i] != ' ') {
            return isupper(str[i]);
        }
    }
    return true;
}

size_t findNextSeparator(size_t index, char str[], size_t len)
{
    char *sep = ",.!?";
    do {
        index++;
        if (index >= len) {
            return len;
        }
    } while (!isOneOf(str[index], sep));
    return index;
}

size_t findNextLeftParent(size_t index, char str[], size_t len)
{
    char *leftParents = "([{";
    do {
        index++;
        if (index >= len) {
            return len;
        }
    } while (!isOneOf(str[index], leftParents));
    return index;
}
size_t findNextRightParent(size_t index, char str[], size_t len)
{
    char *rightParents = ")]}";
    do {
        index++;
        if (index >= len) {
            return len;
        }
    } while (!isOneOf(str[index], rightParents));
    return index;
}

bool noTwoConsecutiveSpaces(char str[], size_t len)
{
    for (size_t i = 1; i < len; i++) {
        if (isspace(str[i]) && isspace(str[i - 1]))
            return false;
    }
    return true;
}

/**
 * The string represents a list of sentences. A sentence ends with with a
 * '.', '?', or a '!' sign, and starts with the first nonspace character
 * in the string or after the end of the previous sentence.
 *
 * Hint: see 'isupper' function
 */
bool sentenceStartsWithUppercase(char str[], size_t len)
{
    char *ends = ".!?";

    if (!isNextNonspaceCapital(0, str, len)) {
        return false;
    }
    for (size_t i = 0; i < len; i++) {
        if (isOneOf(str[i], ends)) {
            if (!isNextNonspaceCapital(i + 1, str, len)) {
                return false;
            }
        }
    }
    return true;
}

/*
 * Every sentence in the string ends with '.', '?' or a '!'.
 */
bool allSentencesAreClosed(char str[], size_t len)
{
    while (str[len - 1] == ' ') {
        len--;
    }
    return isOneOf(str[len - 1], ".!?");
}

/**
 * There is no separator with a space before it.
 *
 *  Wrong: "Hello, World !"
 *  Wrong: "Hello , World!"
 *  Right: "Hello, World!"
 */
bool noSpaceBeforeSeparators(char str[], size_t len)
{
    size_t index = 0;
    while ((index = findNextSeparator(index, str, len)) < len) {
        if (str[index - 1] == ' ') {
            return false;
        }
    }
    return true;
}

/**
 * Every seprator (i.e. '.', ',', '!' or '?') is followed by a space,
 * with the exception of the separator is the last character in the string.
 *
 *  Wrong: "Hello,world."
 *  Right: "Hello, world."
 */
bool spaceAfterSeparators(char str[], size_t len)
{
    size_t index = 0;
    while ((index = findNextSeparator(index, str, len)) < len) {
        if (str[index + 1] != ' ' && index != (len - 1)) {
            return false;
        }
    }
    return true;
}

/**
 * Determines which type of parentheses c is
 */
enum parentheses determineParent(char c)
{
    switch (c) {
    case '(':
        return PARENT;
        break;
    case '{':
        return BRACES;
        break;
    case '[':
        return BRACKETS;
        break;
    default:
        return NONE;
        break;
    }
}

/**
 * @return false if c is undesired type of parentheses
 */
bool checkParents(char c, enum parentheses parents)
{
    switch (parents) {
    case PARENT:
        if (c != ')') {
            return false;
        }
        break;
    case BRACES:
        if (c != '}') {
            return false;
        }
        break;
    case BRACKETS:
        if (c != ']') {
            return false;
        }
        break;
    default:
        break;
    }
    return true;
}


/**
 * Every opening bracket '(' is properly closed with ')' and there are no
 * nested parentheses.
 *
 *  Wrong: ":("
 *  Right: "Hello world (again)!"
 *  Wrong: "Hello, (tiny (puny)) world!"
 */
bool properParenthesesPairing(char str[], size_t len)
{
    char *leftParents = "([{";
    char *rightParents = ")]}";

    enum parentheses parentheses = NONE;
    for (size_t i = 0; i < len; i++) {
        if (parentheses == NONE) {
            if (isOneOf(str[i], rightParents)) {
                return false;
            }
            if (isOneOf(str[i], leftParents)) {
                parentheses = determineParent(str[i]);
            }

        } else {
            if (isOneOf(str[i], leftParents)) {
                return false;
            }
            if (isOneOf(str[i], rightParents)) {
                if (!checkParents(str[i], parentheses)) {
                    return false;
                }
                parentheses = NONE;
            }

        }
    }
    return parentheses == NONE;
}

/****  BONUS  ****************************************************************/

/*
 * You are not required to implement the following functions, but you
 * can get up to 3 bonus points if you do it correctly.
 */

/**
 * Parentheses should not cross sencentes. That is, if a bracket is opened
 * outside of a sentence, it must be closed outside as well.
 * On the other hand, a bracket opened inside a sentence has to be
 * closed before the sentence ends.
 *
 *  Right: "(First sentence. Second sentence.) Third sentence."
 *  Right: "First (inside) sentence."
 *  Wrong: "First (sentence. Second) sentence."
 *  Wrong: "(First sentence. Second) sentence."
 */
bool noParenthesesSentenceCrossing(char str[], size_t len)
{
    char *ends = ".!?";
    char *rightParents = ")]}";

    if (!properParenthesesPairing(str, len)) {
        return false;
    }
    size_t firstNonspace = 0;
    while (str[firstNonspace] == ' ') {
        firstNonspace++;
    }

    bool insideSentence;
    size_t index = findNextLeftParent(-1, str, len);

    while (index < len) {
        if (isOneOf(str[index - 1], ends) || index == firstNonspace) {
            insideSentence = false;
        } else {
            insideSentence = true;
        }
        while (!isOneOf(str[index], rightParents)) {
            if (insideSentence && isOneOf(str[index], ends)) {
                return false;
            }
            index++;
        }
        if (!insideSentence && !isOneOf(str[index - 1], ends)) {
            return false;
        }
        index = findNextLeftParent(index, str, len);
    }
    return true;
}

/**
 * There can be double quotes inside the text '"', but always in pair.
 * Opening quote must not be followed by a space and similarly
 * there can be no space before the closing quote.
 */
bool noSpaceBeforeClosingOrAfterOpeningApostrophe(char str[], size_t len)
{
    bool outsideApostrophe = true;

    for (size_t index = 0; index < len; index++) {
        if (outsideApostrophe) {
            if (str[index] == '"') {
                outsideApostrophe = false;
                if (str[index + 1] == ' ') {
                    return false;
                }
            }
        } else {
            if (str[index] == '"') {
                outsideApostrophe = true;
                if (str[index - 1] == ' ') {
                    return false;
                }
            }
        }
    }
    return outsideApostrophe;
}


