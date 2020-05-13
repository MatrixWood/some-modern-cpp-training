#include "shared_ptr.hpp"

#include <vector>

#include <gtest/gtest.h>

struct Struct
{
    explicit Struct(int aVal) :
        mVal(aVal)
    {
        ++_mNbInstances;
    }
    ~Struct(void)
    {
        --_mNbInstances;
    }
    void incr(void)
    {
        ++mVal;
    }
    void decr(void)
    {
        --mVal;
    }

    int         mVal;
    static int _mNbInstances;
};

int Struct::_mNbInstances = 0;

TEST(shared_ptr, empty_ptr)
{
    // Create an empty (ie. NULL) shared_ptr
    shared_ptr<Struct> xPtr;

    EXPECT_EQ(false, xPtr);
    EXPECT_EQ(false, xPtr.unique());
    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());

    if (xPtr)
    {
        GTEST_FATAL_FAILURE_("bool cast operator error");
    }

    // Reset to NULL (ie. do nothing)
    xPtr.reset();

    EXPECT_EQ(false, xPtr);
    EXPECT_EQ(false, xPtr.unique());
    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());

    // sub-scope
    {
        // Copy construct the empty (ie. NULL) shared_ptr
        shared_ptr<Struct> yPtr(xPtr);

        EXPECT_EQ(false, xPtr);
        EXPECT_EQ(false, xPtr.unique());
        EXPECT_EQ(0,     xPtr.use_count());
        EXPECT_EQ((void*)NULL,  xPtr.get());
        EXPECT_EQ(false, yPtr.unique());
        EXPECT_EQ(0,     yPtr.use_count());
        EXPECT_EQ((void*)NULL,  yPtr.get());

        // Assign the empty (ie. NULL) shared_ptr
        shared_ptr<Struct> zPtr;
        zPtr = xPtr;

        EXPECT_EQ(false, xPtr);
        EXPECT_EQ(false, xPtr.unique());
        EXPECT_EQ(0,     xPtr.use_count());
        EXPECT_EQ((void*)NULL,  xPtr.get());
        EXPECT_EQ(false, zPtr.unique());
        EXPECT_EQ(0,     zPtr.use_count());
        EXPECT_EQ((void*)NULL,  zPtr.get());
    }
    // end of scope

    EXPECT_EQ(false, xPtr);
    EXPECT_EQ(false, xPtr.unique());
    EXPECT_EQ(0,     xPtr.use_count());
    EXPECT_EQ((void*)NULL,  xPtr.get());
}