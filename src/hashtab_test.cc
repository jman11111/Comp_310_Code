#include <gtest/gtest.h>
#include "hashtab.h"

class HashTabTest : public ::testing::Test {
protected:
	HashTable_t *instest;

	void SetUp() override{
		instest = ht_create(10);
		ht_insert(instest,"test",1);
	}

	void TearDown() override {
		ht_free(instest);
	}

};

TEST_F(HashTabTest, Insertstring){
    ASSERT_TRUE(instest != NULL);
    ASSERT_TRUE(lookup(instest,"test") != NULL);
}

TEST_F(HashTabTest, Hash) {
    ASSERT_TRUE(instest != NULL);
    ASSERT_FALSE(hash(instest,"test") == -1);
}

TEST_F(HashTabTest, InsertCount) {
    ASSERT_TRUE(instest != NULL);
    ASSERT_TRUE(ht_index(instest,"test") == 1);
}

TEST_F(HashTabTest, Comparator) {
    TableEntry_t *test_comp = createtab("test",1);
    TableEntry_t *test_comper = createtab("tester",2);
    ASSERT_TRUE(compare(test_comp,test_comper) == 1);
}

TEST_F(HashTabTest, Capacity) {
    ASSERT_TRUE(instest != NULL);
    ASSERT_TRUE(instest->size == 10);
}

TEST_F(HashTabTest, TableEntryFree) {
    ASSERT_TRUE(instest != NULL);
    TableEntry_t *test_free = lookup(instest,"test");
}

TEST_F(HashTabTest, TableEntryCreate) {
    TableEntry_t *test_free = createtab("test",1);
    ASSERT_TRUE(strcmp(test_free->key,"test") == 0);
    ASSERT_TRUE(test_free->val == 1);
}

TEST_F(HashTabTest, Lookup) {
    TableEntry_t *testEntry = lookup(instest,"test");
    ASSERT_TRUE(instest != NULL);
    ASSERT_STREQ(testEntry->key,"test");
    ASSERT_TRUE(testEntry->val == 1);
}

TEST_F(HashTabTest, Resize) {
    ASSERT_TRUE(instest != NULL);
    ASSERT_TRUE(instest->size == 10);
}

TEST_F(HashTabTest, Delete) {
    ASSERT_TRUE(instest != NULL);
    ht_delete(instest,"test");
    ASSERT_TRUE(lookup(instest,"test") == NULL);
}

TEST_F(HashTabTest, Printht) {
    ASSERT_TRUE(instest != NULL);
    ht_insert(instest,"testtwo",2);
    ht_insert(instest,"testthree",4);
    ht_insert(instest,"testfour",4);
    ht_insert(instest,"testfive",5);
    ASSERT_TRUE(print_ht(4,instest) == 1);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


