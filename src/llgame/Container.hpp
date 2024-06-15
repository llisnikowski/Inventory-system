#pragma once
#include <vector>

namespace llgame
{

template<typename T>
class Container
{
public:
    using Slots = std::vector<T>;

    explicit Container(std::size_t size);

    template<typename It>
    auto setItem(
    std::size_t x, It it) -> decltype(std::declval<T>().setItem(it));
    T& getSlot(std::size_t x);
    const T& getSlot(std::size_t x) const;

private:
    Slots slots;
};

//-------------------------------------


template<typename T>
Container<T>::Container(std::size_t size)
: slots(size)
{}

template<typename T>
template<typename It>
auto Container<T>::setItem(
std::size_t x, It it) -> decltype(std::declval<T>().setItem(it))
{
    if(x >= slots.size()) return it;
    return slots[x].setItem(it);
}

template<typename T>
auto Container<T>::getSlot(std::size_t x) -> T&
{
    return slots.at(x);
}

template<typename T>
auto Container<T>::getSlot(std::size_t x) const -> const T&
{
    return slots.at(x);
}


} // namespace llgame
