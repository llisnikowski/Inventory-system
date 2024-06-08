#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "llgame/Slot.hpp"

using testing::Return;

class ItemMock
{
public:
    MOCK_METHOD(bool, transferFrom, (std::shared_ptr<ItemMock>) );
};


TEST(Slot_test, addItem)
{
    llgame::Slot<ItemMock> slot;
    EXPECT_FALSE(slot.getItem());

    auto item1 = std::make_shared<ItemMock>();
    EXPECT_TRUE(slot.addItem(item1));
    EXPECT_EQ(slot.getItem(), item1);

    auto item2 = std::make_shared<ItemMock>();
    EXPECT_CALL(*item1, transferFrom(item2)).Times(1).WillOnce(Return(false));
    EXPECT_FALSE(slot.addItem(item2));
    EXPECT_EQ(slot.getItem(), item1);
}

TEST(Slot_test, stackable)
{
    llgame::Slot<ItemMock> slot;
    EXPECT_FALSE(slot.getItem());

    auto item1 = std::make_shared<ItemMock>();
    EXPECT_TRUE(slot.addItem(item1));

    auto item2 = std::make_shared<ItemMock>();
    EXPECT_CALL(*item1, transferFrom(item2)).Times(1).WillOnce(Return(true));
    EXPECT_TRUE(slot.addItem(item2));
    EXPECT_EQ(slot.getItem(), item1);
}

template<typename T>
class SlotMock : public llgame::Slot<T>
{
public:
    MOCK_METHOD(bool, canBePlaced, (std::shared_ptr<T>), (override));
};


TEST(Slot_test, cannotBePlaced)
{
    SlotMock<ItemMock> slot;
    EXPECT_FALSE(slot.getItem());

    auto item1 = std::make_shared<ItemMock>();
    EXPECT_CALL(slot, canBePlaced(item1)).Times(1).WillOnce(Return(false));
    EXPECT_FALSE(slot.addItem(item1));
    EXPECT_EQ(slot.getItem(), nullptr);
}
