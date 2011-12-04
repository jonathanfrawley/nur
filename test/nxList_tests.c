#include <glib.h>

#include <nxCore/nxList.h>
#include <nxCore/nxMM.h>
#include <nxCore/nxConstants.h>

static int a = 999;

void setup_nxList(nxList* list, gconstpointer user_data)
{
//    nxList* testList = nxList_alloc();
//    testList->data = (void*)&a;
    list->data = NX_NULL;
    list->next = NX_NULL;
}

/*
void test_nxList_length(nxList* list, gconstpointer user_data)
{
//    const nxList* list = (const nxList*)user_data;
    nxList* listPtr = (nxList*)list;
    g_assert(nxList_getLength(listPtr) == 1);
}
*/

static void test_nxList_length(void)
{
//    const nxList* list = (const nxList*)user_data;
    nxList* list = NX_NULL;
    g_assert(nxList_getLength(list) == 0);
    nxList_free(list);
}

//void test_nxList_append(gconstpointer user_data)
//void test_nxList_append(nxList* list, gconstpointer user_data)
static void test_nxList_append(void)
{
//    nxList* list = nxList_alloc();
    nxList* list = NX_NULL;

    int* data = nxMalloc(sizeof(int));
    (*data) = 213;

    g_assert(nxList_getLength(list) == 0);
    list = nxList_append(list, data);
    g_assert(nxList_getLength(list) == 1);

    nxList_free(list);
}

//void test_nxList_remove(gconstpointer user_data)
//void test_nxList_remove(nxList* list, gconstpointer user_data)
static void test_nxList_remove()
{
//    nxList* list = nxList_alloc();
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

//void test_nxList_empty(gconstpointer user_data)
static void test_nxList_empty()
{
//    nxList* list = nxList_alloc();
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

    /*
    nxList* testList = nxList_alloc();
    int a = 999;
    testList->data = (void*)&a;
    */

    //nxList* testList = NX_NULL;
    //g_test_add_func("/nxCore/nxList_append", test_nxList_append);

    g_test_add_func("/nxCore/nxList_length", test_nxList_length);
    g_test_add_func("/nxCore/nxList_append", test_nxList_append);
    g_test_add_func("/nxCore/nxList_remove", test_nxList_remove);
    g_test_add_func("/nxCore/nxList_empty", test_nxList_empty);

    /*
    g_test_add("/nxCore/nxList_length", 
            nxList,
            testList,
            setup_nxList,
            test_nxList_length,
            0);

     */
    /*
    g_test_add("/nxCore/nxList_append", 
            nxList,
            testList,
            setup_nxList,
            test_nxList_append,
            0);
            */

    /*
    g_test_add("/nxCore/nxList_remove", 
            nxList,
            testList,
            0,
            test_nxList_remove,
            0);
    
    g_test_add("/nxCore/nxList_empty", 
            nxList,
            testList,
            0,
            test_nxList_empty,
            0);
            */

//    nxList_free(testList);

    return g_test_run_suite(g_test_get_root());
}
