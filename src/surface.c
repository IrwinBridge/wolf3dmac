/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 19:38:53 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/22 21:13:09 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	clear_screen(t_engine *engine, Uint32 color)
{
	SDL_FillRect(engine->surface, NULL, color);
}

void	put_pixel(t_engine *engine, int x, int y, Uint32 color)
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return ;
	*(Uint32 *)(engine->surface->pixels + (x + y * WINDOW_WIDTH) * 4) = color;
}

void	update_screen(t_engine *engine)
{
	SDL_UpdateWindowSurface(engine->window);
}
