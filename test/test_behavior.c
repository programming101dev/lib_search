#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_search/search.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>

static int failures;
static int walk_visits;

#define EXPECT(condition)                                                                                                                                                                                                                                          \
    do                                                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                              \
        if(!(condition))                                                                                                                                                                                                                                           \
        {                                                                                                                                                                                                                                                          \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition);                                                                                                                                                                                   \
            failures++;                                                                                                                                                                                                                                            \
        }                                                                                                                                                                                                                                                          \
    } while(0)

struct queue_node
{
    struct queue_node *forward;
    struct queue_node *backward;
    int                value;
};

static int compare_ints(const void *first, const void *second)
{
    const int *a = first;
    const int *b = second;

    return (*a > *b) - (*a < *b);
}

static void visit_tree(const void *node, VISIT visit, int level)
{
    (void)node;
    (void)visit;
    (void)level;
    walk_visits++;
}

static void test_hash_table(const struct p101_env *env)
{
    EXPECT(hcreate(4) != 0);
    /* P101_TEST_CASE(p101_hdestroy) */
    p101_hdestroy(env);
}

static void test_intrusive_queue(const struct p101_env *env)
{
    struct queue_node first  = {0};
    struct queue_node second = {0};

    first.value  = 1;
    second.value = 2;
    /* P101_TEST_CASE(p101_insque) */
    p101_insque(env, &second, &first);
    EXPECT(first.forward == &second);
    EXPECT(second.backward == &first);
    /* P101_TEST_CASE(p101_remque) */
    p101_remque(env, &second);
    EXPECT(first.forward == NULL);
}

static void test_linear_search(const struct p101_env *env)
{
    int    values[] = {1, 3, 5};
    int    key      = 3;
    size_t count    = sizeof(values) / sizeof(values[0]);
    int   *found;

    /* P101_TEST_CASE(p101_lfind) */
    found = p101_lfind(env, &key, values, &count, sizeof(values[0]), compare_ints);
    EXPECT(found != NULL && *found == key);
}

static void test_tree_search(const struct p101_env *env)
{
    void *root = NULL;
    int   key  = 7;
    void *result;

    EXPECT(tsearch(&key, &root, compare_ints) != NULL);
    /* P101_TEST_CASE(p101_tfind) */
    result = p101_tfind(env, &key, &root, compare_ints);
    EXPECT(result != NULL);
    walk_visits = 0;
    /* P101_TEST_CASE(p101_twalk) */
    p101_twalk(env, root, visit_tree);
    EXPECT(walk_visits > 0);
    /* P101_TEST_CASE(p101_tdelete) */
    result = p101_tdelete(env, &key, &root, compare_ints);
    (void)result;
    EXPECT(root == NULL);
}

int main(void)
{
    struct p101_error *err;
    struct p101_env   *env;

    err = p101_error_create(false);
    if(err == NULL)
    {
        return EXIT_FAILURE;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return EXIT_FAILURE;
    }
    test_hash_table(env);
    test_intrusive_queue(env);
    test_linear_search(env);
    test_tree_search(env);
    p101_env_destroy(env);
    p101_error_destroy(err);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
