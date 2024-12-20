/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2020. All rights reserved.
 * Description: Pthread struct file
 * Author: Huawei LiteOS Team
 * Create: 2013-01-01
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------- */

#ifndef _HWLITEOS_POSIX_PPRIVATE_H
#define _HWLITEOS_POSIX_PPRIVATE_H

#include "pthread.h"
#include "limits.h"
#include "sys/types.h"
#include "los_sem_pri.h"
#include "los_task_pri.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define ERROR     (-1)
#define PTHREAD_DATA_NAME_MAX 20
/*
 * Thread control data structure
 * Per-thread information needed by POSIX
 */
typedef struct _pthread_data_tag {
    pthread_attr_t      attr; /* Current thread attributes */
    pthread_t           id; /* My thread ID */
    LosTaskCB           *task; /* pointer to Huawei LiteOS thread object */
    CHAR                name[PTHREAD_DATA_NAME_MAX]; /* Thread name */
    UINT8               state; /* Thread state */
    UINT8               cancelstate; /* Cancel state of thread */
    volatile UINT8      canceltype; /* Cancel type of thread */
    volatile UINT8      canceled; /* pending cancel flag */
    UINT8 tsd_used : 1; /* pthread tsd */
    struct pthread_cleanup_buffer *cancelbuf; /* cleanup buffer */
    UINT32              freestack; /* stack malloced, must be freed */
    UINT32              stackmem; /* base of stack memory area only valid if freestack == true */
    VOID                **thread_data; /* Per-thread data table pointer */
    VOID *tsd[PTHREAD_KEYS_MAX];
} _pthread_data;

#define PTHREAD_DATA_UNUSED          0   /* The thread data is unused */
#define PTHREAD_DATA_USED            1   /* The thread data is used */

#define PTHREAD_CANCEL_STATE_INIT    0  /* The thread cancel state is init */
#define PTHREAD_CANCEL_STATE_PEND    1  /* The thread cancel state is pend */
#define PTHREAD_CANCEL_STATE_EXEC    2  /* The thread cancel state is executed */

extern _pthread_data *pthread_get_self_data(void);
#define __pthread_self() pthread_get_self_data()

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
