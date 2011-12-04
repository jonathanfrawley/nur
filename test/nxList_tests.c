#include <glib.h>

#include <nxCore/nxList.h>
#include <nxCore/nxMM.h>
#include <nxCore/nxConstants.h>

static int a = 999;

static void test_nxList_length(void)
{
    nxList* list = NX_NULL;
    g_assert(nxList_getLength(list) == 0);
    nxList_free(list);
}

static void test_nxList_append(void)
{
    nxList* list = NX_NULL;

    int* data = nxMalloc(sizeof(int));
    (*data) = 213;

    g_assert(nxList_getLength(list) == 0);
    list = nxList_append(list, data);
    g_assert(nxList_getLength(list) == 1);

    nxList_free(list);
}

static void test_nxList_remove()
{
    nxList* list = NX_NULL;

    int* data = nxMalloc(sizeof(int));
    (*data) = 213;

    g_assert(nxList_getLength(list) == 0);
    list = nxList_append(list, data);
    g_assert(nxList_getLength(list) == 1);
    list = nxList_remove(list, data);
    g_assert(nxList_getLength(list) == 0);

    nxList_free(list);
}

static void test_nxList_empty()
{
    nxList* list = NX_NULL;

    int* data = nxMalloc(sizeof(int));
    (*data) = 213;

    g_assert(nxList_getLength(list) == 0);
    list = nxList_append(list, data);
    g_assert(nxList_getLength(list) == 1);
    list = nxList_append(list, data);
    g_assert(nxList_getLength(list) == 2);
    list = nxList_empty(list);
    g_assert(nxList_getLength(list) == 0);

    nxList_free(list);
}

int main(int argc, char *argv[])
{
    g_test_init(&argc, &argv, NULL);

    g_test_add_func("/nxCore/nxList_length", test_nxList_length);
    g_test_add_func("/nxCore/nxList_append", test_nxList_append);
    g_test_add_func("/nxCore/nxList_remove", test_nxList_remove);
    g_test_add_func("/nxCore/nxList_empty", test_nxList_empty);

    return g_test_run_suite(g_test_get_root());
}
