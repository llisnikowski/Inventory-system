#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "llgame/Slot.hpp"
#include "ItemMock.hpp"

using testing::Return;


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

TEST(Slot_test, setItem)
{
    llgame::Slot<ItemMock> slot;

    auto item1 = std::make_shared<ItemMock>();
    auto item2 = std::make_shared<ItemMock>();

    EXPECT_EQ(slot.setItem(item1), nullptr);
    EXPECT_EQ(slot.getItem(), item1);

    EXPECT_EQ(slot.setItem(item2), item1);
    EXPECT_EQ(slot.getItem(), item2);

    EXPECT_EQ(slot.operator=(item1), item2);
    EXPECT_EQ(slot.getItem(), item1);

    EXPECT_EQ(slot.setItem(nullptr), item1);
    EXPECT_EQ(slot.getItem(), nullptr);
}
