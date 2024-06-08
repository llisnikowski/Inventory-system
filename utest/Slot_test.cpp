#include "gtest/gtest.h"
#include "llgame/Slot.hpp"

class Item
{
};


TEST(Slot_test, addItem)
{
    llgame::Slot<Item> slot;

    EXPECT_FALSE(slot.getItem());
    auto item = std::make_shared<Item>();
    EXPECT_TRUE(slot.addItem(item));
    EXPECT_EQ(slot.getItem(), item);
    EXPECT_FALSE(slot.addItem(item));
}
