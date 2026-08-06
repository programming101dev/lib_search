/*
 * Copyright 2026 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "p101_search/p101_search.h"
#include <p101_env/wrapper.h>

static int search_error_code(int fallback);

static int search_error_code(int fallback)
{
    int err_code;

    err_code = errno;

    if(err_code == 0)
    {
        err_code = fallback;
    }

    return err_code;
}

int p101_hcreate(const struct p101_env *env, struct p101_error *err, size_t nel)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, 0);
    errno   = 0;
    ret_val = hcreate(nel);

    if(ret_val == 0)
    {
        P101_ERROR_RAISE_ERRNO(err, search_error_code(ENOMEM));
    }
    else
    {
        P101_TRACK_RESOURCE_ACQUIRE(env, "process-hash-table", "global", nel, NULL);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

void p101_hdestroy(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    hdestroy();
    P101_TRACK_RESOURCE_RELEASE(env, "process-hash-table", "global", NULL);
    P101_TRACE_EXIT(env);
}

ENTRY *p101_hsearch(const struct p101_env *env, struct p101_error *err, ENTRY item, ACTION action)
{
    ENTRY *ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, NULL);
    errno   = 0;
    ret_val = hsearch(item, action);

    if(ret_val == NULL && action == ENTER)
    {
        P101_ERROR_RAISE_ERRNO(err, search_error_code(ENOMEM));
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

void p101_insque(const struct p101_env *env, void *element, void *pred)
{
    P101_TRACE(env);
    errno = 0;
    insque(element, pred);
    P101_TRACE_EXIT(env);
}

void *p101_lfind(const struct p101_env *env, const void *key, const void *base, size_t *nelp, size_t width, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = lfind(key, base, nelp, width, compar);

    P101_TRACE_EXIT(env);
    return ret_val;
}

void *p101_lsearch(const struct p101_env *env, struct p101_error *err, const void *key, void *base, size_t *nelp, size_t width, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, NULL);
    errno   = 0;
    ret_val = lsearch(key, base, nelp, width, compar);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, search_error_code(ENOMEM));
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

void p101_remque(const struct p101_env *env, void *element)
{
    P101_TRACE(env);
    errno = 0;
    remque(element);
    P101_TRACE_EXIT(env);
}

void *p101_tdelete(const struct p101_env *env, const void *restrict key, void **restrict rootp, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tdelete(key, rootp, compar);

    P101_TRACE_EXIT(env);
    return ret_val;
}

void *p101_tfind(const struct p101_env *env, const void *key, void *const *rootp, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tfind(key, rootp, compar);

    P101_TRACE_EXIT(env);
    return ret_val;
}

void *p101_tsearch(const struct p101_env *env, struct p101_error *err, const void *key, void **rootp, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, NULL);
    errno   = 0;
    ret_val = tsearch(key, rootp, compar);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, search_error_code(ENOMEM));
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

void p101_twalk(const struct p101_env *env, const void *root, void (*action)(const void *, VISIT, int))
{
    P101_TRACE(env);
    errno = 0;
    twalk(root, action);
    P101_TRACE_EXIT(env);
}
