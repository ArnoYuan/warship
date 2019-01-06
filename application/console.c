#include <common/pie.h>
#include <console/console.h>
#include "console.h"

IMPORT_STDIO();

char console_buffer[128];

MODULE_CONSOLE(0) = {.stdio = STDIO()};

void console_server_init(void)
{
    console_server_start(CONSOLE(0), console_buffer, sizeof(console_buffer), 256);
}
