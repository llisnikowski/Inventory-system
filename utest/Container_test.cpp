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
