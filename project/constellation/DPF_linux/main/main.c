#include <signal.h>
#include <sys/wait.h>
#include "../common/common.h"
#include "../mouse/mouse.h"
#include "../mp3/play.h"
#include "../jpeg/welcome.h"
#include "../jpeg/jpeg.h"

int main()
{
	fb_info fb_inf;
	pid_t pid;
	pid_t mp3_id;

	if (init_frambuffer(&fb_inf) < 0){
		fprintf(stderr, "Error initial framebuffer\n");
		return 1;
	}

	filename_list();		//jpeg file txt

	pid = fork();
	if (pid == 0) start_mp3(fb_inf);
	mp3_id = pid;

	disp_background("../jpeg/welcome/background.jpg", fb_inf);
	disp_constellation("../jpeg/welcome/constellation.jpg", fb_inf);

	welcome_screen(fb_inf);

	if (mouse_operate(fb_inf, &mp3_id))
	{
		kill(mp3_id, SIGKILL);
		wait(NULL);
	}

	exit_screen(fb_inf);

	munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);

	return 0;
}
