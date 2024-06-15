#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class ItemMock
{
public:
    MOCK_METHOD(
    std::shared_ptr<ItemMock>, transferFrom, (std::shared_ptr<ItemMock>) );
};
