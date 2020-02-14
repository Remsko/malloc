/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:48:13 by rpinoit           #+#    #+#             */
/*   Updated: 2020/02/14 15:48:30 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

char			*config_type_to_string(t_config_type type)
{
	if (type == TINY)
		return ("TINY");
	if (type == SMALL)
		return ("SMALL");
	return ("LARGE");
}
