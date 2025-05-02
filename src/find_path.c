#include "pipex.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    i = 0;
    while (i + 1 < n && s1[i] && s1[i] == s2[i])
        i++;
    return (!!n * ((unsigned char)s1[i] - (unsigned char)s2[i]));
}
char *get_env_value(char **envp, const char *key)
{
    size_t len = ft_strlen(key);
    for (int i = 0; envp[i]; i++)
    {
        if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
        {
            return envp[i] + len + 1; // Skip "PATH="
        }
    }
    return NULL;
}

int ft_access(const char *path)
{
    pid_t pid;
    int status;
    // char *const args[2]; = {(char *)path, NULL};

    pid = fork();
    if (pid == 0)
    {
        execve(path, (char *const[]){(char *)path, NULL}, NULL);
        exit(126 + EXIT_FAILURE);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

char *find_command_path(char *cmd, char **envp)
{
    char *paths;
    char *token;
    char *path_env;

    if (!cmd || ft_strchr(cmd, '/') != NULL)
    {
        if (ft_access(cmd) == EXIT_SUCCESS)
            return ft_strdup(cmd);
        // if (access(cmd, X_OK) == EXIT_SUCCESS)
        //     return ft_strdup(cmd);
        return NULL;
    }
    path_env = get_env_value(envp, "PATH");
    if (!path_env)
        return NULL;
    paths = ft_strdup(path_env);
    if (!paths)
        return NULL;
    token = ft_strtok(paths, ":");
    while (token)
    {
        char *full_path = malloc(ft_strlen((const char *)token) + ft_strlen(cmd) + 2);
        if (!full_path)
            return (free(paths), NULL);
        sprintf(full_path, "%s/%s", token, cmd);
        // if (access(full_path, X_OK) == EXIT_SUCCESS)
        if (ft_access(full_path) == EXIT_SUCCESS)
            return (free(paths), full_path);
        free(full_path);
        token = ft_strtok(NULL, ":");
    }

    return (free(paths), NULL);
}
