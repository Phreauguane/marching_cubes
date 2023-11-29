#include "glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "mainLoop.hpp"

/****************************************************************************
 * SIMPLE COMMAND LINE PARSER                                               *
 ****************************************************************************/

void parseCommandlineArgs(AppConfig& cfg, int argc, char**argv)
{
	for (int i = 1; i < argc; i++) {
		if (!std::strcmp(argv[i], "--fullscreen")) {
			cfg.fullscreen = true;
			cfg.decorated = false;
		} else if (!std::strcmp(argv[i], "--undecorated")) {
			cfg.decorated = false;
		} else if (!std::strcmp(argv[i], "--gl-debug-sync")) {
			cfg.debugOutputSynchronous = true;
		}
		else if (i + 1 < argc) {
			if (!std::strcmp(argv[i], "--width")) {
				cfg.width = (int)strtol(argv[++i], NULL, 10);
			} else if (!std::strcmp(argv[i], "--height")) {
				cfg.height = (int)strtol(argv[++i], NULL, 10);
			} else if (!std::strcmp(argv[i], "--x")) {
				cfg.posx = (int)strtol(argv[++i], NULL, 10);
			} else if (!std::strcmp(argv[i], "--y")) {
				cfg.posy = (int)strtol(argv[++i], NULL, 10);
			} else if (!std::strcmp(argv[i], "--frameCount")) {
				cfg.frameCount = (unsigned)strtoul(argv[++i], NULL, 10);
			} else if (!std::strcmp(argv[i], "--gl-debug-level")) {
				cfg.debugOutputLevel = (DebugOutputLevel)strtoul(argv[++i], NULL, 10);
			}
		}
	}
}

/****************************************************************************
 * PROGRAM ENTRY POINT                                                      *
 ****************************************************************************/

int main (int argc, char **argv)
{
	AppConfig cfg;	/* the generic configuration */
	App app;	/* the cube application stata stucture */

	parseCommandlineArgs(cfg, argc, argv);

	if (initApplication(&app, cfg)) {
		/* initialization succeeded, enter the main loop */
		mainLoop(&app, cfg);
	}
	/* clean everything up */
	destroyApp(&app);

	return 0;
}