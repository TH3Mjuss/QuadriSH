/*
** my_exec.c for 42sh in /home/gysc0/rendu/PSU_2013_minishell2
**
** Made by Zackary Beaugelin
** Login   <beauge_z@epitech.net>
**
** Started on  Mon Apr  7 20:11:24 2014 Zackary Beaugelin
** Last update Tue May  6 16:51:00 2014 Gysc0
*/


#include "my_sh.h"

int	g_check;

void		my_exec(char **bin, char **param, char **env, int k)
{
  t_exec	e;

  if (bin[k + 1] == NULL)
    e.path = my_strcat("\0", "./");
  else
    e.path = my_strcat(bin[k], "/");
  e.path = my_strcat(e.path, param[0]);
  if (access(e.path, X_OK) == -1 && !(bin[k + 1]) && g_check)
    {
      my_putstr(param[0], 2);
      my_putstr(": command not found\n", 2);
      return ;
    }
  else if (!access(e.path, X_OK) && g_check)
    {
      e.pid = fork();
      if (e.pid < 0)
	return ;
      if (e.pid == 0)
	execve(e.path, param, env);
      else
	waitpid(e.pid, &e.status, 0);
      g_check = 0;
    }
}

int	my_execve(char **param, char **env)
{
  char	**bin;
  int	k;

  k = 0;
  bin = my_str_to_wordtab(my_find(env, 0, "PATH"), ':', 0);
  g_check = 1;
  while (bin[k])
    {
      my_exec(bin, param, env, k);
      k++;
    }
  return (1);
}
