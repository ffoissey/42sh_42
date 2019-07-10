/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:45:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/07/09 13:01:25 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCTL_H
# define JOBCTL_H
# include "struct.h"

int8_t	am_i_forked(t_registry *shell, char *name);

void	jobctl(t_registry *shell, t_job *job, uint8_t flag);
void	job_already_done(t_registry *shell, t_job *job);
t_list	*get_job_ptr(t_list **list, t_list *job_ptr);

void	update_jobinfos(t_registry *shell);
void	push_current_job(t_registry *shell, t_list *job);
void	pop_current_job(t_registry *shell, t_job *job);
t_list	*remove_job_from_list(t_list **joblst, t_job *job);
void	remove_done_jobs(t_registry *shell);

int		setup_background_job(t_job *job);

void	print_jobs(t_job *job, uint8_t flag);
void	state_to_str(t_job *job, char **str);
void	get_job_av(t_job *job, char **str);
void	get_process_av(t_process *proc, char **str);
int8_t	parse_jobid(t_job **job, char *param);

void	notify_job_info(t_list *joblist, char *info);
uint8_t	mark_proc_status(void);
void	mark_proc(pid_t pid, int status);
void	mark_job_as_stopped(t_job *job);
void	mark_job_as_completed(t_job *job);
void	mark_job_as_running(t_job *job);
uint8_t	jobctl_is_active(t_registry *shell);

#endif
