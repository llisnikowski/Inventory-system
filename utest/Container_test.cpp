#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "llgame/Slot.hpp"
#include "llgame/Container.hpp"
#include "ItemMock.hpp"

using testing::Return;

namespace
{


template<typename T>
class SlotMock : public llgame::Slot<T>
{
public:
protected:
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
