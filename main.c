/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/22 14:25:31 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Main function
int main() {
    t_shell shell;
    char *input;

    // Initialize shell structure
    shell.tokens = NULL;
    shell.cmd = NULL;
    shell.pid = NULL;

    while (1) {
        // Display prompt and read input
        input = readline("minishell$ ");
        if (!input) {
            printf("\n");
            break; // Exit the loop when input is NULL (Ctrl+D)
        }

        // Add input to history
        add_history(input);

        // Parse the command
        paring_cmd(input);

        // Execute the command
        execute_cmd(&shell);

        // Free input after use
        free(input);
    }

}
