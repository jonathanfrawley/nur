#include <glib.h>

void test_nxList_append(void)
{
    //g_test_fail();
}

int main(int argc, char *argv[])
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/nxCore/nxList_append", test_nxList_append);
    return g_test_run_suite(g_test_get_root ());
}
