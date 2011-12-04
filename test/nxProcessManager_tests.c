#include <glib.h>

#include <nxLogic/nxProcessManager.h>
#include <nxLogic/nxProcess.h>
#include <nxCore/nxList.h>
#include <nxCore/nxMM.h>
#include <nxCore/nxConstants.h>

static int a = 999;

static void test_nxProcessManager_attach(void)
{
    nxProcessManager* manager = nxProcessManager_alloc();
    nxProcess* process = nxProcess_alloc(NX_PROCESS_WAIT);
    process->waitTime = 10;
    g_assert(nxList_getLength(manager->_processes) == 0);
    nxProcessManager_attach(manager, process);
    g_assert(nxList_getLength(manager->_processes) == 1);
    nxProcessManager_free(manager);
}

static void test_nxProcessManager_update(void)
{
    nxProcessManager* manager = nxProcessManager_alloc();
    nxProcess* process = nxProcess_alloc(NX_PROCESS_WAIT);
    process->waitTime = 10;
    g_assert(nxList_getLength(manager->_processes) == 0);
    nxProcessManager_attach(manager, process);
    g_assert(nxList_getLength(manager->_processes) == 1);
    nxProcessManager_update(manager, 20);
    g_assert(nxList_getLength(manager->_processes) == 0);
    nxProcessManager_free(manager);
}

static void test_nxProcessManager_detach(void)
{
    nxProcessManager* manager = nxProcessManager_alloc();
    nxProcess* process = nxProcess_alloc(NX_PROCESS_WAIT);
    process->waitTime = 10;
    g_assert(nxList_getLength(manager->_processes) == 0);
    nxProcessManager_attach(manager, process);
    g_assert(nxList_getLength(manager->_processes) == 1);
    nxProcessManager_detach(manager, process);
    g_assert(nxList_getLength(manager->_processes) == 0);
    nxProcessManager_free(manager);
}

int main(int argc, char *argv[])
{
    g_test_init(&argc, &argv, NULL);

    g_test_add_func("/nxCore/nxProcessManager_attach", test_nxProcessManager_attach);
    g_test_add_func("/nxCore/nxProcessManager_update", test_nxProcessManager_update);
    g_test_add_func("/nxCore/nxProcessManager_detach", test_nxProcessManager_detach);

    return g_test_run_suite(g_test_get_root());
}
