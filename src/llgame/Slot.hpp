#pragma once
#include <vector>
#include <memory>

namespace llgame
{

template<typename T>
class Slot
{
public:
    using Item = std::shared_ptr<T>;

    virtual ~Slot() = default;

    const Item getItem() const;
    bool addItem(Item item);

protected:
    Item item;
};

//-------------------------------------

template<typename T>
auto Slot<T>::getItem() const -> const Item
{
    return item;
}

template<typename T>
bool Slot<T>::addItem(Item item)
{
    if(this->item) return false;
    this->item = item;
    return true;
}

} // namespace llgame
