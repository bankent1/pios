#ifndef __TEST_H
#define __TEST_H

#include <stdio.h>


#define TEST_EQ(arg1, arg2) if ((arg1) != (arg2)) { \
    kprintf("%s:%d: TEST FAILED (%d != %d)\n", __FUNCTION__, __LINE__, (arg1), (arg2)); \
} else { \
    kprintf("%s:%d: TEST PASSED\n", __FUNCTION__, __LINE__); \
} 

#define TEST_NEQ(arg1, arg2) if ((arg1) == (arg2)) { \
    kprintf("%s:%d: TEST FAILED (%d != %d)\n", __FUNCTION__, __LINE__, (arg1), (arg2)); \
} else { \
    kprintf("%s:%d: TEST PASSED\n", __FUNCTION__, __LINE__); \
} 

void test_common();


#endif