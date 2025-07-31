// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test_ex.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/29 10:05:21 by aoussama          #+#    #+#             */
// /*   Updated: 2025/07/30 14:18:53 by aoussama         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// int	has_pattern(const char *input)
// {
// 	const char	*start_pattern = "~<<<";
// 	const char	*end_pattern = ">>>~";
// 	size_t		start_len;
// 	size_t		end_len;
// 	size_t		i;
// 	size_t		j;

// 	start_len = ft_strlen(start_pattern);
// 	end_len = ft_strlen(end_pattern);
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (ft_strncmp(input + i, start_pattern, start_len) == 0)
// 		{
// 			j = i + start_len;
// 			while (input[j])
// 			{
// 				if (ft_strncmp(input + j, end_pattern, end_len) == 0)
// 					return (1);
// 				j++;
// 			}
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// // Extract inner content from pattern
// char	*wrap_with_pattern(const char *input)
// {
// 	const char	*start_pattern = "~<<<";
// 	const char	*end_pattern = ">>>~";
// 	size_t		input_len;
// 	size_t		start_len;
// 	size_t		end_len;
// 	size_t		total_len;
// 	char		*result;

// 	input_len = strlen(input);
// 	start_len = strlen(start_pattern);
// 	end_len = strlen(end_pattern);
// 	// طول النص الجديد = طول بداية النمط + طول النص + طول نهاية النمط
// 	+1 للنهاية '\0' total_len = start_len + input_len + end_len + 1;
// 	result = malloc(total_len);
// 	if (!result)
// 		return (NULL); // فشل في الحجز
// 	// نسخ البداية
// 	strcpy(result, start_pattern);
// 	// نسخ النص الأصلي بعد البداية
// 	strcpy(result + start_len, input);
// 	// نسخ نهاية النمط بعد النص
// 	strcpy(result + start_len + input_len, end_pattern);
// 	return (result);
// }
// char	*extract_string(const char *input)
// {
// 	const char	*start_pattern = "~<<<";
// 	const char	*end_pattern = ">>>~";
// 	size_t		start_len;
// 	size_t		end_len;
// 	size_t		i;
// 	const char	*start = NULL;
// 	const char	*end = NULL;
// 	size_t		len;
// 	char		*out;
// 	size_t		j;

// 	start_len = ft_strlen(start_pattern);
// 	end_len = ft_strlen(end_pattern);
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (ft_strncmp(input + i, start_pattern, start_len) == 0)
// 		{
// 			start = input + i + start_len;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (!start)
// 		return (NULL);
// 	i = 0;
// 	while (start[i])
// 	{
// 		if (ft_strncmp(start + i, end_pattern, end_len) == 0)
// 		{
// 			end = start + i;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (!end)
// 		return (NULL);
// 	// Trim leading spaces
// 	while (*start == ' ' || *start == '\t')
// 		start++;
// 	// Trim trailing spaces
// 	while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t'))
// 		end--;
// 	len = (size_t)(end - start);
// 	// Allocate memory for the extracted string + null terminator
// 	out = malloc(len + 1);
// 	if (!out)
// 		return (NULL); // malloc failed
// 	// Copy characters manually (because no ft_strncpy that returns char*)
// 	j = 0;
// 	while (j < len)
// 	{
// 		out[j] = start[j];
// 		j++;
// 	}
// 	out[j] = '\0';
// 	return (out);
// }
// void	remove_pattern(char *input)
// {
// 	const char	*start_pattern = "~<<<";
// 	const char	*end_pattern = ">>>~";
// 	size_t		start_len;
// 	size_t		end_len;
// 	char		*write_pos;
// 	char		*read_pos;
// 	char		*start;
// 	char		*end;
// 	char		*inner_start;
// 	char		*inner_end;

// 	start_len = strlen(start_pattern);
// 	end_len = strlen(end_pattern);
// 	write_pos = input;
// 	read_pos = input;
// 	while (*read_pos)
// 	{
// 		// ابحث عن بداية النمط
// 		start = strstr(read_pos, start_pattern);
// 		if (!start)
// 		{
// 			// لا نمط موجود، انسخ باقي النص
// 			while (*read_pos)
// 			{
// 				*write_pos++ = *read_pos++;
// 			}
// 			break ;
// 		}
// 		// انسخ كل شيء قبل النمط
// 		while (read_pos < start)
// 		{
// 			*write_pos++ = *read_pos++;
// 		}
// 		// ابحث عن نهاية النمط
// 		end = strstr(start + start_len, end_pattern);
// 		if (!end)
// 		{
// 			// ما في نهاية، انسخ باقي النص ثم اكسر
// 			while (*read_pos)
// 			{
// 				*write_pos++ = *read_pos++;
// 			}
// 			break ;
// 		}
// 		// محتوى بين الأنماط بدون إزالة الفراغات
// 		inner_start = start + start_len;
// 		inner_end = end;
// 		// انسخ المحتوى الداخلي كامل بدون حذف الفراغات
// 		while (inner_start < inner_end)
// 		{
// 			*write_pos++ = *inner_start++;
// 		}
// 		// تقدم إلى بعد نهاية النمط
// 		read_pos = end + end_len;
// 	}
// 	*write_pos = '\0';
// }

// // Remove pattern and keep inner content
// // void remove_pattern(char *input)
// // {
// //     const char *start_pattern = "~<<<";
// //     const char *end_pattern = ">>>~";
// //     size_t start_len = ft_strlen(start_pattern);
// //     size_t end_len = ft_strlen(end_pattern);

// //     char *write_pos = input;
// //     char *read_pos = input;

// //     while (*read_pos) {
// //         // Look for start pattern
// //         char *start = NULL;
// //         char *end = NULL;
// //         size_t i = 0;

// //         // Find start pattern
// //         while (read_pos[i]) {
// //             if (ft_strncmp(read_pos + i, start_pattern, start_len) == 0) {
// //                 start = read_pos + i;
// //                 break ;
// //             }
// //             i++;
// //         }

// //         if (!start) {
// //             // No more patterns found, copy rest of string
// //             while (*read_pos) {
// //                 *write_pos++ = *read_pos++;
// //             }
// //             break ;
// //         }

// //         // Copy characters before pattern
// //         while (read_pos < start) {
// //             *write_pos++ = *read_pos++;
// //         }

// //         // Find end pattern
// //         i = 0;
// //         while (start[i]) {
// //             if (ft_strncmp(start + i, end_pattern, end_len) == 0) {
// //                 end = start + i + end_len;
// //                 break ;
// //             }
// //             i++;
// //         }

// //         if (!end) {
// //             // No end pattern found, copy rest of string
// //             while (*read_pos) {
// //                 *write_pos++ = *read_pos++;
// //             }
// //             break ;
// //         }

// //         // Process inner content (trim spaces)
// //         char *inner_start = start + start_len;
// //         while (*inner_start == ' ' || *inner_start == '\t') {
// //             inner_start++;
// //         }

// //         char *inner_end = end - end_len - 1;
// //         while (inner_end > inner_start && (*inner_end == ' '
// 		|| *inner_end == '\t'))
// 		{
// 			//             inner_end--;
// 			//         }

// 			//         // Copy trimmed inner content
// 			//         while (inner_start <= inner_end) {
// 			//             *write_pos++ = *inner_start++;
// 			//         }

// 			//         // Move read position to after the end pattern
// 			//         read_pos = end;
// 			//     }

// 			//     // Null terminate the result
// 			//     *write_pos = '\0';
// 			// }
