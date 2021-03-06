/*
** rediretions.c for 42sh in /home/jussea_m/rendu/my_42
**
** Made by jussea_m@epitech.eu
** Login   <jussea_m@epitech.net>
**
** Started on  Sun May 11 14:12:05 2014 jussea_m@epitech.eu
** Last update Mon Jun  2 21:13:23 2014 Gysc0
*/

#include "my_sh.h"

int	my_rr(char **param, char **param2, char **env)
{
  t_redir	r;

  if (param2)
    {
      if ((r.file = open(param2[0], O_WRONLY | O_TRUNC | O_CREAT, 0660)) == -1)
	{
	  my_putstr("Cant't use file\n", 2);
	  return (1);
	}
      if ((r.pid = fork()) < 0)
	return (1);
      if (r.pid == 0)
	{
	  dup2(r.file, 1);
	  my_parser(param, 1, env);
	  exit(0);
	}
      else
	{
	  waitpid(r.pid, &r.status, 0);
	  close(r.file);
	}
    }
  return (r.status);
}

int		my_drr(char **param, char **param2, char **env)
{
  t_redir	r;

  if (param2)
    {
      if ((r.file = open(param2[0], O_WRONLY | O_APPEND, 0660)) == -1)
	{
	  my_putstr("Cant't use file\n", 2);
	  return (1);
	}
      if ((r.pid = fork()) < 0)
	return (1);
      if (r.pid == 0)
	{
	  dup2(r.file, 1);
	  my_parser(param, 1, env);
	  exit(0);
	}
      else
	{
	  waitpid(r.pid, &r.status, 0);
	  close(r.file);
	}
    }
  return (r.status);
}

int		my_lr(char **param, char **param2, char **env)
{
  t_redir	r;

  if (param2)
    {
      if ((r.file = open(param2[0], O_RDONLY)) == -1)
	{
	  my_putstr("Cant't use file\n", 2);
	  return (1);
	}
      if ((r.pid = fork()) < 0)
	return (1);
      if (r.pid == 0)
	{
	  dup2(r.file, 0);
	  my_parser(param, 1, env);
	  exit(0);
	}
      else
	{
	  waitpid(r.pid, &r.status, 0);
	  close(r.file);
	}
    }
  return (r.status);
}

void	prompt_dlr(t_redir *r, char *buff, char *stop)
{
  int	i;

  while (my_strncmp(buff, stop, my_strlen(stop)))
    {
      i = -1;
      my_putstr("> ", 1);
      while (++i < 4096)
	buff[i] = 0;
      xread(0, buff, 4096);
      if (my_strncmp(buff, stop, my_strlen(stop)))
	write(r->file, buff, my_strlen(buff));
    }
}

int		my_dlr(char **param, char **param2, char **env)
{
  char		tmp[] = "/tmp/42sh";
  char		*file[] = {tmp, NULL};
  char		buff[4096];
  t_redir	r;
  int		i;

  i = -1;
  r.file = 0;
  r.file = open(tmp, O_WRONLY | O_TRUNC | O_CREAT, 0660);
  while (++i < 4096)
    buff[i] = 0;
  if (r.file == -1)
    {
      my_putstr("Cant't use file\n", 2);
      return (1);
    }
  if (param2)
    {
      prompt_dlr(&r, buff, param2[0]);
      close(r.file);
      i = my_lr(param, file, env);
    }
  return (i);
}
