/****************************************************************************
 * apps/testing/testsuites/kernel/sched/cases/api_task_test_006.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>
#include <stdio.h>
#include <syslog.h>
#include <sched.h>
#include <sys/types.h>
#include <nuttx/sched.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "SchedTest.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: schedtask06routine
 ****************************************************************************/

static int schedtask06routine(int argc, char *argv[])
{
  return 0;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: test_nuttx_sched_task06
 ****************************************************************************/

void test_nuttx_sched_task06(FAR void **state)
{
  pid_t pid;
  int status;
  int priority_max;
  int priority_min;

  /* struct sched_param task_entry_param */

  pid = task_create("schedtask06routine", TASK_PRIORITY,
                    DEFAULT_STACKSIZE, schedtask06routine, NULL);
  assert_true(pid > 0);
  priority_max = sched_get_priority_max(SCHED_FIFO);
  priority_min = sched_get_priority_min(SCHED_FIFO);
  assert_int_equal(priority_max, SCHED_PRIORITY_MAX);
  assert_int_equal(priority_min, SCHED_PRIORITY_MIN);
  waitpid(pid, &status, 0);
}
