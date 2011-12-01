#include <glib.h>

#include <nxCore/nxList.h>
#include <nxCore/nxConstants.h>

static int a = 999;

void setup_nxList(nxList* list, gconstpointer user_data)
{
//    nxList* testList = nxList_alloc();
//    testList->data = (void*)&a;
    list->data = NX_NULL;
    list->next = NX_NULL;
}

void test_nxList_length(nxList* list, gconstpointer user_data)
{
//    const nxList* list = (const nxList*)user_data;
    nxList* listPtr = (nxList*)list;
    g_assert(nxList_getLength(listPtr) == 1);
}

//void test_nxList_append(gconstpointer user_data)
void test_nxList_append(nxList* list, gconstpointer user_data)
{
    /*
 //   const nxList* list = (const nxList*)user_data;

    //nxList* newElem = nxList_alloc();
    int data = 213;
    //newElem->data = (void*)&data;

    nxList* listPtr;

    listPtr = (nxList*)list;
    g_assert(nxList_getLength(listPtr) == 1);
    listPtr = nxList_append(listPtr, (void*)&data);
    g_assert(nxList_getLength(listPtr) == 2);

    //nxList_free(newElem);
    */
}

//void test_nxList_remove(gconstpointer user_data)
void test_nxList_remove(nxList* list, gconstpointer user_data)
{
//    const nxList* list = (const nxList*)user_data;

    //nxList* newElem = nxList_alloc();
    int data = 213;
    //newElem->data = (void*)&data;

    nxList* listPtr;

    listPtr = (nxList*)list;
    g_assert(nxList_getLength(listPtr) == 1);
    listPtr= nxList_append(listPtr, (void*)&data);
    g_assert(nxList_getLength(listPtr) == 2);
    nxList_remove(listPtr, (void*)&data);
    g_assert(nxList_getLength(listPtr) == 1);

    //nxList_free(newElem);
}

//void test_nxList_empty(gconstpointer user_data)
void test_nxList_empty(nxList* list, gconstpointer user_data)
{
    //const nxList* list = (const nxList*)user_data;

    //nxList* newElem = nxList_alloc();
    int data = 213;
    //newElem->data = (void*)&data;

    //nxList* newElem2 = nxList_alloc();
    int data2 = 2134;
    //newElem2->data = (void*)&data2;

    nxList* listPtr;
    listPtr = (nxList*)list;
    
    //Initially empty
    g_assert(nxList_getLength(listPtr) == 1);
    listPtr = nxList_append(listPtr, (void*)&data);
    g_assert(nxList_getLength(listPtr) == 2);
    listPtr = nxList_append(listPtr, (void*)&data);
    g_assert(nxList_getLength(listPtr) == 3);
    nxList_empty(listPtr);
    g_assert(nxList_getLength(listPtr) == 0);

    //nxList_free(newElem);
    //nxList_free(newElem2);
}

int main(int argc, char *argv[])
{
    g_test_init(&argc, &argv, NULL);

    nxList* testList = nxList_alloc();
    int a = 999;
    testList->data = (void*)&a;

    //nxList* testList = NX_NULL;
    //g_test_add_func("/nxCore/nxList_append", test_nxList_append);

    g_test_add("/nxCore/nxList_length", 
            nxList,
            testList,
            setup_nxList,
            test_nxList_length,
            0);

    g_test_add("/nxCore/nxList_append", 
            nxList,
            testList,
            setup_nxList,
            test_nxList_append,
            0);

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

    nxList_free(testList);

    return g_test_run_suite(g_test_get_root());
}
