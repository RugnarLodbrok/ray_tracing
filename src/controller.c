/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:45:11 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/22 16:46:46 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "mlx.h"
#include "mlx_consts.h"
#include "rtx.h"

void	t_controller_update_state(t_controller *c)
{
	c->dx = c->keyboard[KEY_A] - c->keyboard[KEY_D];
	c->dz = c->keyboard[KEY_S] - c->keyboard[KEY_W];
	c->d_tilt = c->keyboard[KEY_Q] - c->keyboard[KEY_E];
	c->d_yaw = c->keyboard[KEY_LEFT] - c->keyboard[KEY_RIGHT];
	c->d_pitch = c->keyboard[KEY_DOWN] - c->keyboard[KEY_UP];
}

int		t_controller_key_press(int keycode, void *p)
{
	t_controller *c;

	c = p;
	if (keycode == KEY_ESC)
		exit(0);
	c->keyboard[keycode] = 1;
	t_controller_update_state(c);
	return (0);
}

int		t_controller_key_release(int keycode, void *p)
{
	t_controller *c;

	c = p;
	c->keyboard[keycode] = 0;
	t_controller_update_state(c);
	return (0);
}

void	bind_keys(void *win, t_controller *c)
{
	mlx_hook(win, MLX_EVENT_KEY_PRESS, 0, t_controller_key_press, c);
	mlx_hook(win, MLX_EVENT_KEY_RELEASE, 0, t_controller_key_release, c);
}
