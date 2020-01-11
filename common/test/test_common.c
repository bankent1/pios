/*
 * test_main.c
 *
 * Travis Banken
 * 1/9/2020
 *
 * Unit tests for common libs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <test.h>

static void test_stdio();
static void test_stdlib();
static void test_string();

void test_common()
{
    kprintf("****************************\n");
    kprintf("         COMMON TESTS       \n");
    kprintf("****************************\n");
    // stdio test
    kprintf("----------------------------\n");
    kprintf("TEST: STDIO\n");
    kprintf("----------------------------\n");
    test_stdio();
    kprintf("----------------------------\n");

    // stdlib test
    kprintf("----------------------------\n");
    kprintf("TEST: STDLIB\n");
    kprintf("----------------------------\n");
    test_stdlib();
    kprintf("----------------------------\n");

    // string test
    kprintf("----------------------------\n");
    kprintf("TEST: STRING\n");
    kprintf("----------------------------\n");
    test_string();
    kprintf("----------------------------\n");
}

static void test_stdio()
{
    char c = 'a';
    kprintf("putc = ");
    putc(c);
    kprintf("\n");
    kprintf("%s %d 0x%x %c %u\n", "String", 42, 42, 'a', -42);
    char alot[] = {'a', 'b', 'c'};
    kprintf("putc \'abc\': ");
    for (int i = 0; i < 3; i++)
        putc(alot[i]);
    kprintf("\n");
}

static void test_stdlib()
{
    // test itoa
    kprintf("*** Testing itoa ***\n");
    char str[32];
    memset(str, 0, 32);
    kprintf("ITOA: conversion for 42\n");
    kprintf("Base 10 -- %s\n", itoa(42, str, 10));
    kprintf("Base 16 -- %s\n", itoa(42, str, 16));
    kprintf("Base 8  -- %s\n", itoa(42, str, 8));
    kprintf("Base 2  -- %s\n", itoa(42, str, 2));
    kprintf("ITOA: conversion for -42\n");
    kprintf("Base 10 -- %s\n", itoa(-42, str, 10));
    kprintf("Base 16 -- %s\n", itoa(-42, str, 16));
    kprintf("Base 8  -- %s\n", itoa(-42, str, 8));
    kprintf("Base 2  -- %s\n", itoa(-42, str, 2));

}

static void test_string()
{
    // test memcpy
    kprintf("*** Testing memcpy ***\n");
    int arr1[] = {0, 1, 2, 3, 4};
    int arr2[5];
    memcpy((void*)arr2, (void*)arr1, sizeof(int)*5);
    for (int i = 0; i < 5; i++) {
        TEST_EQ(arr1[i], arr2[i]);
        TEST_EQ(arr1[i], i);
    }

    // test memset
    kprintf("*** Testing memset ***\n");
    char memarr[5];
    memset(memarr, 'c', 5);
    for (int i = 0; i < 5; i++) {
        TEST_EQ(memarr[i], 'c');
    }

    // test strcpy
    kprintf("*** Testing strcpy ***\n");
    char strsrc[] = "Hello, strcpy!";
    char strdest[14];
    strcpy(strdest, strsrc);
    kprintf("Copy of \"Hello, strcpy!\" -- %s\n", strdest);

    // test strncpy
    kprintf("*** Testing strncpy ***\n");
    char strndest[6];
    strncpy(strndest, strsrc, 5);
    kprintf("First 5 of \"Hello, strcpy!\" -- %s\n", strndest);

    // test strlen
    kprintf("*** Testing strlen ***\n");
    char strlen6[] = "123456";
    char strlen1[] = "1";
    char strlen0[] = "";
    TEST_EQ(strlen(strlen6), 6);
    TEST_EQ(strlen(strlen1), 1);
    TEST_EQ(strlen(strlen0), 0);

    // test strcmp
    kprintf("*** Testing strcmp ***\n");
    char strcmp1[] = "I am string";
    char strcmp2[] = "I am string";
    char strcmp3[] = "I Am string";
    char strcmp0[] = "";
    TEST_EQ(strcmp(strcmp1, strcmp2), 0);
    TEST_EQ(strcmp(strcmp0, strcmp0), 0);
    TEST_NEQ(strcmp(strcmp1, strcmp3), 0);
    TEST_NEQ(strcmp(strcmp2, strcmp0), 0);
}