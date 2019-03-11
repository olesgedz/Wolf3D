/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:14:24 by lsandor-          #+#    #+#             */
/*   Updated: 2019/03/11 18:02:29 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void ft_init_sound(t_wolf *w)
{
	w->sdl->wav_spec = ft_safe_malloc(sizeof(SDL_AudioSpec) * 2);
	w->sdl->wav_buffer = ft_safe_malloc(sizeof(Uint8 *) * 2);
	w->sdl->wav_length = ft_safe_malloc(sizeof(Uint32) * 2);
	w->sdl->audio_device = ft_safe_malloc(sizeof(SDL_AudioDeviceID) * 2);
	SDL_LoadWAV("Sounds/pistol.wav", &w->sdl->wav_spec[0], &w->sdl->wav_buffer[0], &w->sdl->wav_length[0]);
	SDL_LoadWAV("Sounds/qliqc-7567m.wav", &w->sdl->wav_spec[1], &w->sdl->wav_buffer[1],& w->sdl->wav_length[1]);
	w->sdl->audio_device[0] = SDL_OpenAudioDevice(NULL, 0, &w->sdl->wav_spec[0], NULL, 0);
	w->sdl->audio_device[1] = SDL_OpenAudioDevice(NULL, 0, &w->sdl->wav_spec[1], NULL, 0);
	// ADD THIS BEFORE RETURN IN MAIN FUNC WE NEED TO FREE ALL THAT SHIT && TEXTURES TOO
	//SDL_CloseAudioDevice(deviceId);
	//SDL_FreeWAV(wavBuffer);
}

void    ft_load_sound(t_wolf *w)
{
	w->t.sound_old_time = w->t.sound_time;
	w->t.sound_time = SDL_GetTicks();
	w->t.change_of_time = (w->t.sound_time - w->t.sound_old_time);
	w->t.sound_sum_time[0] += w->t.change_of_time;
	w->t.sound_sum_time[1] += w->t.change_of_time;
	//w->t.frame_time = (w->t.time - w->t.old_time) / 1000.0;
	//SDL_FreeWAV(w->sdl->wav_buffer);
	// w->sdl->wav_spec = malloc(sizeof(SDL_AudioSpec *) * 2);
	// w->sdl->wav_buffer = malloc(sizeof(Uint8 *) * 2);
	// w->sdl->wav_length = malloc(sizeof(Uint32 *) * 2);
	// SDL_LoadWAV("Sounds/pistol.wav", w->sdl->wav_spec[0], w->sdl->wav_buffer[0], &w->sdl->wav_length[0]);
	// SDL_LoadWAV("Sounds/qliqc-7567m.wav", &w->sdl->wav_spec[1], &w->sdl->wav_buffer[1], &w->sdl->wav_length[1]);
	//w->sdl->audio_device = SDL_OpenAudioDevice(NULL, 0, &w->sdl->wav_spec[w->sdl->i], NULL, 0);
	// if (w->t.sound_sum_time >= w->t.play_time)
	// {
	// 	w->sdl->audio_device = SDL_OpenAudioDevice(NULL, 0, &w->sdl->wav_spec[w->sdl->i], NULL, 0);
	// }	//SDL_LockAudioDevice(w->sdl->audio_device);
		//SDL_UnlockAudioDevice(w->sdl->audio_device);
	if (w->t.sound_sum_time[0] >= w->t.play_time[0] && w->sdl->i == 0)
	{
		w->t.sound_sum_time[0] = 0;
		SDL_QueueAudio(w->sdl->audio_device[0], w->sdl->wav_buffer[0], w->sdl->wav_length[0]);
		SDL_PauseAudioDevice(w->sdl->audio_device[0], 0);
		//SDL_Delay(100);
	}
	if (w->t.sound_sum_time[1] >= w->t.play_time[1] && w->sdl->i == 1)
	{
		w->t.sound_sum_time[1] = 0;
		SDL_QueueAudio(w->sdl->audio_device[1], w->sdl->wav_buffer[1], w->sdl->wav_length[1]);
		SDL_PauseAudioDevice(w->sdl->audio_device[1], 0);
	}
	//SDL_CloseAudioDevice(w->sdl->audio_device);
	//SDL_QueueAudio(w->sdl->audio_device, w->sdl->wav_buffer, w->sdl->wav_length);
	//SDL_PauseAudioDevice(w->sdl->audio_device, 0);
	//SDL_CloseAudioDevice(deviceId);
	//SDL_FreeWAV(wavBuffer);
}