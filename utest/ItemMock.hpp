#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class ItemMock
{
public:
    MOCK_METHOD(bool, transferFrom, (std::shared_ptr<ItemMock>) );
};
