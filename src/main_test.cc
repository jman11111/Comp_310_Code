#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>
#include "hashtab.h"
#include "queue.h"
#include <string.h>
#include "main.h"

TEST(main_test, HashtabIns) {
	HashTable_t *hashtab = ht_create(10);
	struct Queue *queue;
	char *test = "test";
	hashtab_insert(hashtab,test,queue);
	ASSERT_FALSE(lookup(hashtab,"test") == NULL);
}

TEST(main_test, Dequeue) {
	HashTable_t *hashtab = ht_create(10);
        struct Queue *queue;
        char *test = "test";
	hashtab_insert(hashtab,test,queue);
	del_from_hashtab(hashtab,queue);
	ASSERT_TRUE(lookup(hashtab,"test") == NULL);
}


int run(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
