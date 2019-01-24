/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 21:24:04 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/24 18:49:51 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

# define MAP_WIDTH 8
# define MAP_HEIGHT 10

int map1[MAP_WIDTH][MAP_HEIGHT] =
{
  {1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,2,2,0,0,0,1},
  {1,0,0,0,2,2,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1}
};

void	turn_player(t_player *player, double angle)
{
	double tmp_dir;
	double tmp_plane;
	double c;
	double s;

	c = cos(angle);
	s = sin(angle);
	tmp_dir = player->dir_x;
	tmp_plane = player->plane_x;
	player->dir_x = tmp_dir * c - player->dir_y * s;
	player->dir_y = tmp_dir * s + player->dir_y * c;
	player->plane_x = tmp_plane * c - player->plane_y * s;
	player->plane_y = tmp_plane * s + player->plane_y * c;
}

void	mouse_move(t_engine *engine, SDL_Event *e)
{
	double deltax;

	engine->mouse->prev_x = engine->mouse->x;
	engine->mouse->x = e->motion.x;
	deltax = (engine->mouse->prev_x - engine->mouse->x) * 0.008f;
	turn_player(engine->player, deltax);
}

void	handle_events(t_engine *engine, SDL_Event *e)
{
	int mapx;
	int mapy;

	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			engine->quit = 1;
		if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_ESCAPE)
			engine->quit = 1;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_LEFT)
			turn_player(engine->player, 0.05235f);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RIGHT)
			turn_player(engine->player, -0.05235f);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_w)
		{
			mapx = (int)(engine->player->x + engine->player->dir_x * 0.1f);
			mapy = (int)(engine->player->y + engine->player->dir_y * 0.1f);
			if (!map1[mapx][(int)engine->player->y])
				engine->player->x += engine->player->dir_x * 0.1f;
			if (!map1[(int)engine->player->x][mapy])
				engine->player->y += engine->player->dir_y * 0.1f;
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_s)
		{
			mapx = (int)(engine->player->x - engine->player->dir_x * 0.1f);
			mapy = (int)(engine->player->y - engine->player->dir_y * 0.1f);
			if (!map1[mapx][(int)engine->player->y])
				engine->player->x -= engine->player->dir_x * 0.1f;
			if (!map1[(int)engine->player->x][mapy])
				engine->player->y -= engine->player->dir_y * 0.1f;
		}
		if (e->type == SDL_MOUSEMOTION)
			mouse_move(engine, e);
	}
}

void	game_loop(t_engine *engine)
{
	SDL_Event e;

	while (!engine->quit)
	{
		handle_events(engine, &e);
		benchmark(engine);
	}
}
