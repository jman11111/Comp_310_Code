/* test cases */

#include <gtest/gtest.h>

#include "queue.h"

TEST(Queue, Enqueue) {
    char *tester;
    tester = "test";
    Queue* queue = createQueue(10);
    enqueue(queue,tester);
    ASSERT_TRUE(queue != NULL);
    ASSERT_FALSE(isEmpty(queue));
    ASSERT_STREQ(queue->array[queue->rear],tester);
    ASSERT_EQ(queue->size, 1);
}

TEST(Queue, Dequeue) {
    char *tester;
    tester = "test";
    Queue* queue = createQueue(10);
    enqueue(queue,tester);
    ASSERT_STREQ(dequeue(queue),tester);
    ASSERT_TRUE(queue != NULL);
    ASSERT_TRUE(isEmpty(queue));
    ASSERT_EQ(queue->size, 0);
}

TEST(Queue, Capacity) {
    char *tester;
    tester = "test";
    Queue* queue = createQueue(10);
    for(int n=0;n<10;n++){
        enqueue(queue,tester);
    }
    ASSERT_TRUE(queue != NULL);
    ASSERT_FALSE(isEmpty(queue));
    ASSERT_TRUE(isFull(queue));
    ASSERT_EQ(queue->size, 10);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

