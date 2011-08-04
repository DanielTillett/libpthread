/*
 * Copyright (c) 2011, Dongsheng Song <songdongsheng@live.cn>
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <pthread.h>
#include <pthread_clock.h>
#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

#include "../src/misc.h"

static volatile int was_changed = 0;

static void *wroker(void *arg)
{
    was_changed = 1;
    return NULL;
}

int main(int argc, char *argv[])
{
    int rc, i = 0;
    void * result;
    pthread_t t;

    while (i++ < 120) {
        was_changed = 0;
        rc = pthread_create(&t, NULL, wroker, NULL);
        assert(rc == 0);

        /* printf("[%03d] rc: %d, t: %p\n", i, rc, t); */

        rc = pthread_join(t, &result);
        assert(rc == 0);
        assert(result == NULL);
        assert(was_changed == 1);
    }

    printf("pthread_join passed\n");

    return 0;
}
