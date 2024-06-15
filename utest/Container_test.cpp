#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "llgame/Slot.hpp"
#include "llgame/Container.hpp"
#include "ItemMock.hpp"


namespace
{
using testing::Return;
using testing::_;

template<typename T>
class SlotMock : public llgame::Slot<T>
{
public:
    MOCK_METHOD(bool, canBePlaced, (std::shared_ptr<T>), (override));
};

}

TEST(Container_test, setItem)
{
    llgame::Container<SlotMock<ItemMock>> container(4);
    auto item1 = std::make_shared<ItemMock>();
    auto item2 = std::make_shared<ItemMock>();
    EXPECT_EQ(container.setItem(4, item1), item1);

    EXPECT_EQ(container.setItem(2, item1), nullptr);
    EXPECT_EQ(container.getSlot(2).getItem(), item1);

    EXPECT_EQ(container.setItem(2, item2), item1);
    EXPECT_EQ(container.getSlot(2).getItem(), item2);

    EXPECT_EQ(container.setItem(2, nullptr), item2);
    EXPECT_EQ(container.getSlot(2).getItem(), nullptr);
}

TEST(Container_test, getSlots)
{
    llgame::Container<SlotMock<ItemMock>> container(4);

    EXPECT_EQ(container.size(), 4);

    auto item1 = std::make_shared<ItemMock>();
    EXPECT_EQ(container.setItem(2, item1), nullptr);
    EXPECT_EQ(container.getSlots()[2].getItem(), item1);

    const auto &ref = container;

    EXPECT_EQ(&container.getSlots(), &ref.getSlots());
}

TEST(Container_test, iterators)
{
    llgame::Container<SlotMock<ItemMock>> container(4);
    const auto &constContainer = container;

    auto &slots            = container.getSlots();
    const auto &constSlots = constContainer.getSlots();

    EXPECT_EQ(container.begin(), slots.begin());
    EXPECT_EQ(constContainer.begin(), constSlots.begin());
    EXPECT_EQ(container.cbegin(), slots.cbegin());
    EXPECT_EQ(container.end(), slots.end());
    EXPECT_EQ(constContainer.end(), constSlots.end());
    EXPECT_EQ(container.cend(), slots.cend());


    EXPECT_EQ(container.rbegin(), slots.rbegin());
    EXPECT_EQ(constContainer.rbegin(), constSlots.rbegin());
    EXPECT_EQ(container.crbegin(), slots.crbegin());
    EXPECT_EQ(container.rend(), slots.rend());
    EXPECT_EQ(constContainer.rend(), constSlots.rend());
    EXPECT_EQ(container.crend(), slots.crend());
}

TEST(Container_test, addItem)
{
    llgame::Container<SlotMock<ItemMock>> container(3);
    auto item1 = std::make_shared<ItemMock>();
    auto item2 = std::make_shared<ItemMock>();
    auto item3 = std::make_shared<ItemMock>();
    auto item4 = std::make_shared<ItemMock>();
    auto item5 = std::make_shared<ItemMock>();

    EXPECT_CALL(container.getSlot(0), canBePlaced(item1))
    .WillOnce(Return(true));
    EXPECT_EQ(container.addItem(item1), nullptr);
    EXPECT_EQ(container.getSlot(0).getItem(), item1);

    EXPECT_CALL(*item1, transferFrom(item2)).WillOnce(Return(item2));
    EXPECT_CALL(container.getSlot(1), canBePlaced(item2))
    .WillOnce(Return(true));
    EXPECT_EQ(container.addItem(item2), nullptr);
    EXPECT_EQ(container.getSlot(1).getItem(), item2);

    EXPECT_CALL(*item1, transferFrom(item3)).WillOnce(Return(item3));
    EXPECT_CALL(*item2, transferFrom(item3)).WillOnce(Return(item3));
    EXPECT_CALL(container.getSlot(2), canBePlaced(item3))
    .WillOnce(Return(true));
    EXPECT_EQ(container.addItem(item3), nullptr);
    EXPECT_EQ(container.getSlot(2).getItem(), item3);

    EXPECT_CALL(*item1, transferFrom(item4)).WillOnce(Return(item4));
    EXPECT_CALL(*item2, transferFrom(item4)).WillOnce(Return(nullptr));
    EXPECT_CALL(*item3, transferFrom(_)).Times(0);
    EXPECT_EQ(container.addItem(item4), nullptr);
    EXPECT_EQ(container.getSlot(1).getItem(), item2);

    EXPECT_CALL(*item1, transferFrom(item5)).WillOnce(Return(item5));
    EXPECT_CALL(*item2, transferFrom(item5)).WillOnce(Return(item5));
    EXPECT_CALL(*item3, transferFrom(item5)).WillOnce(Return(item5));
    EXPECT_EQ(container.addItem(item5), item5);
}
