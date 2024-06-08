#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "llgame/Slot.hpp"

using testing::Return;

class Item
{
public:
    MOCK_METHOD(bool, transferFrom, (std::shared_ptr<Item>) );
};


TEST(Slot_test, addItem)
{
    llgame::Slot<Item> slot;
    EXPECT_FALSE(slot.getItem());

    auto item1 = std::make_shared<Item>();
    EXPECT_TRUE(slot.addItem(item1));
    EXPECT_EQ(slot.getItem(), item1);

    auto item2 = std::make_shared<Item>();
    EXPECT_CALL(*item1, transferFrom(item2)).Times(1).WillOnce(Return(false));
    EXPECT_FALSE(slot.addItem(item2));
    EXPECT_EQ(slot.getItem(), item1);
}

TEST(Slot_test, stackable)
{
    llgame::Slot<Item> slot;
    EXPECT_FALSE(slot.getItem());

    auto item1 = std::make_shared<Item>();
    EXPECT_TRUE(slot.addItem(item1));

    auto item2 = std::make_shared<Item>();
    EXPECT_CALL(*item1, transferFrom(item2)).Times(1).WillOnce(Return(true));
    EXPECT_TRUE(slot.addItem(item2));
    EXPECT_EQ(slot.getItem(), item1);
}
