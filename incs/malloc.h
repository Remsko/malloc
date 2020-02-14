/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:29:16 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 14:32:58 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <stdbool.h>
# include <pthread.h>

void *malloc(size_t size);
void *calloc(size_t count, size_t size);
void *valloc(size_t size);
void *realloc(void *ptr, size_t size);
void *reallocf(void *ptr, size_t size);
void free(void *ptr);

void show_alloc_mem(void);
void show_alloc_mem_ex(void);

void *malloc_unlocked(size_t size);
void *realloc_unlocked(void *ptr, size_t size);
void free_unlocked(void *ptr);

extern pthread_mutex_t g_thread_mutex;

#endif
