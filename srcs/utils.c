/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 04:31:12 by veronikalub       #+#    #+#             */
/*   Updated: 2025/04/16 19:58:30 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", 3) == 0 ||
		ft_strncmp(cmd, "echo", 5) == 0 ||
		ft_strncmp(cmd, "env", 4) == 0 ||
		ft_strncmp(cmd, "pwd", 4) == 0 ||
		ft_strncmp(cmd, "export", 7) == 0 ||
		ft_strncmp(cmd, "unset", 6) == 0 ||
		ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

// In command_parse.c, when filling in t_command
// if (command->argv && command->argv[0])
//     command->is_builtin = is_builtin(command->argv[0]); // Setting the flag of the built-in command


/**
* Counts the number of words in a string separated by a separator character.
 * s The source string for splitting.
 * c Separator character.
 * ret The number of words per line.
 */
// static size_t count_words(char const *s, char c)
// {
//     size_t count = 0;
//     size_t in_word = 0;

//     if (!s)
//         return (0);
//     while (*s)
//     {
//         if (*s != c && !in_word) // The beginning of a new word
//         {
//             in_word = 1;
//             count++;
//         }
//         else if (*s == c) // End of a word when encountering a separator
//             in_word = 0;
//         s++;
//     }
//     return (count);
// }

/**
* Copies one word from the string, starting from the specified position.
 * s Original string.
 * start is the index of the beginning of the word.
 * len is the length of the word.
 * ret Pointer to the selected line with a word or NULL in case of an error.
 */
// static char *copy_word(char const *s, size_t start, size_t len)
// {
//     char *word;

//     if (!s)
//         return (NULL);
//     word = malloc(len + 1);
//     if (!word)
//         return (NULL);
//     ft_strlcpy(word, s + start, len + 1); // Copying the word
//     return (word);
// }

/**
* Splits a string into an array of strings using a specified separator.
 * s is a string for splitting.
 * c Separator character.
 * ret An array of strings ending in NULL, or NULL in case of a memory allocation error.
 */
// char **ft_split(char const *s, char c)
// {
//     size_t i = 0;
//     size_t j = 0;
//     size_t start = 0;
//     size_t word_count;
//     char **result;

//     if (!s)
//         return (NULL);
//     word_count = count_words(s, c);
//     result = malloc(sizeof(char *) * (word_count + 1));
//     if (!result)
//         return (NULL);
//     while (s[i])
//     {
//         if (s[i] != c && (i == 0 || s[i - 1] == c)) // The beginning of a word
//             start = i;
//         if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')) // End of the word
//         {
//             result[j] = copy_word(s, start, i - start + 1);
//             if (!result[j]) // Memory allocation error
//             {
//                 while (j-- > 0) // Freeing up the already allocated memory
//                     free(result[j]);
//                 free(result);
//                 return (NULL);
//             }
//             j++;
//         }
//         i++;
//     }
//     result[j] = NULL;
//     return (result);
// }

// Testing
// Input: "echo hello world", delimiter ' '.
// Expected result: array ["echo", "hello", "world", NULL].

/**
* Frees up the memory allocated for the array of strings.
 * tokens Array of strings ending in NULL.
 */
// void free_tokens(char **tokens)
// {
//     size_t i = 0;

//     if (!tokens)
//         return;
//     while (tokens[i])
//     {
//         free(tokens[i]);
//         i++;
//     }
//     free(tokens);
// }
