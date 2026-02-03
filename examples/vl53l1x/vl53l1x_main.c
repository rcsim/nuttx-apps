/****************************************************************************
 * apps/examples/vl53l1x/vl53l1x_main.c
 *
 *   VL53L1X Time-of-Flight sensor example
 *
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <nuttx/sensors/vl53l1x.h>

/****************************************************************************
 * Configuration
 ****************************************************************************/

#ifndef CONFIG_EXAMPLES_VL53L1X_DEVPATH
#  define CONFIG_EXAMPLES_VL53L1X_DEVPATH "/dev/tof0"
#endif

#ifndef CONFIG_EXAMPLES_VL53L1X_INTERVAL_MS
#  define CONFIG_EXAMPLES_VL53L1X_INTERVAL_MS 1000
#endif

#define INTERVAL_US (CONFIG_EXAMPLES_VL53L1X_INTERVAL_MS * 1000)

/****************************************************************************
 * Private data
 ****************************************************************************/

static volatile bool g_should_exit = false;

/****************************************************************************
 * Signal handler
 ****************************************************************************/

static void vl53l1x_sigint_handler(int signo)
{
  g_should_exit = true;
}

/****************************************************************************
 * Public entry point
 ****************************************************************************/

int vl53l1x_main(int argc, FAR char *argv[])
{
  int fd;
  int ret;
  uint16_t distance_mm;

  /* Open device */

  fd = open(CONFIG_EXAMPLES_VL53L1X_DEVPATH, O_RDONLY);
  if (fd < 0)
    {
      printf("ERROR: Failed to open %s: %d\n",
             CONFIG_EXAMPLES_VL53L1X_DEVPATH, errno);
      return EXIT_FAILURE;
    }

  /* Install SIGINT handler */

  signal(SIGINT, vl53l1x_sigint_handler);

  printf("VL53L1X started (interval=%d ms)\n",
         CONFIG_EXAMPLES_VL53L1X_INTERVAL_MS);

  /* Measurement loop */

  while (!g_should_exit)
    {
      ret = read(fd, &distance_mm, sizeof(distance_mm));
      if (ret < 0)
        {
          printf("ERROR: read failed: %d\n", errno);
          break;
        }
      else if (ret != sizeof(distance_mm))
        {
          printf("WARNING: short read (%d bytes)\n", ret);
        }
      else
        {
          printf("Distance: %u mm\n", distance_mm);
        }

      usleep(INTERVAL_US);
    }

  close(fd);
  printf("VL53L1X stopped\n");
  return EXIT_SUCCESS;
}
