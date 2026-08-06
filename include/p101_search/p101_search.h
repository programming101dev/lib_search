#ifndef LIBP101_SEARCH_P101_SEARCH_H
#define LIBP101_SEARCH_P101_SEARCH_H

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

#ifndef LIBP101_SEARCH_SHARED_DECLARATIONS
    #define LIBP101_SEARCH_SHARED_DECLARATIONS
    #include <p101_env/env.h>
    #include <p101_error/attributes.h>
    #include <search.h>
#endif    // LIBP101_SEARCH_SHARED_DECLARATIONS

#ifdef __cplusplus
extern "C"
{
#endif

    int    p101_hcreate(const struct p101_env *env, struct p101_error *err, size_t nel);
    void   p101_hdestroy(const struct p101_env *env);
    ENTRY *p101_hsearch(const struct p101_env *env, struct p101_error *err, ENTRY item, ACTION action);
    void   p101_insque(const struct p101_env *env, void *element, void *pred);
    void  *p101_lfind(const struct p101_env *env, const void *key, const void *base, size_t *nelp, size_t width, int (*compar)(const void *, const void *));
    void  *p101_lsearch(const struct p101_env *env, struct p101_error *err, const void *key, void *base, size_t *nelp, size_t width, int (*compar)(const void *, const void *));
    void   p101_remque(const struct p101_env *env, void *element);
    void  *p101_tdelete(const struct p101_env *env, const void *restrict key, void **restrict rootp, int (*compar)(const void *, const void *));
    void  *p101_tfind(const struct p101_env *env, const void *key, void *const *rootp, int (*compar)(const void *, const void *));
    void  *p101_tsearch(const struct p101_env *env, struct p101_error *err, const void *key, void **rootp, int (*compar)(const void *, const void *));
    void   p101_twalk(const struct p101_env *env, const void *root, void (*action)(const void *, VISIT, int));

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_SEARCH_P101_SEARCH_H
