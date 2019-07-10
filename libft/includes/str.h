/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedricmpassi <cempassi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 20:36:32 by cedricmpa         #+#    #+#             */
/*   Updated: 2019/07/04 04:13:57 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H
# include <string.h>
# define VECTOR_BUFFER_SIZE 16

typedef struct		s_magic
{
	unsigned long int	lw;
	unsigned long int	hi;
	unsigned long int	lo;

}					t_magic;

typedef struct		s_file
{
	int				fd;
	int				status;
	char			*str;
}					t_file;

int					ft_strendswith(char *string, char *suffix);
int					ft_strbeginswith(const char *string, char *prefix);
void				ft_strclr(char *c);
char				*ft_strcat(char *s1, const char *s2);
void				ft_strdel(char **as);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnew(size_t size);
char				**ft_strsplit(char const *s, char *c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
char				*ft_strinsert(char **str, char c, size_t index);
size_t				ft_strcspn(const char *s, const char *charset);
size_t				ft_strspn(const char *s, const char *charset);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s1);
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
size_t				ft_strlen(const char *s);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strrev(char *str);
void				ft_strupper(char *str);
void				ft_strlower(char *str);
int					ft_isnumeric(char *str);
int					ft_strcheck(char *str, int (*f)(int));
int					ft_getdelim(const int fd, char **line, char delim);
char				*ft_strnstr(const char *haystack, const char *needle,\
					size_t len);
#endif
