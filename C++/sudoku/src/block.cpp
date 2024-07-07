#include "block.h"

#include <cassert>
#include <iostream>

#include "color.h"
#include "common.h"
#include "display_symbol.h"


CBlock::CBlock()
    : _count(0) {}

bool CBlock::isValid() const
{
    assert(MAX_COUNT == _count);

    for (int i = 0; i < _count - 1; ++i)
    {
        for (int j = i + 1; j < _count; ++j)
        {
            if (UNSELECTED == _numbers[i]->value || UNSELECTED == _numbers[j]->value)
                continue;

            if (_numbers[i]->value == _numbers[j]->value)
                return false;
        }
    }

    return true;
}

bool CBlock::isFull() const
{
    for (int i = 0; i < _count; ++i)
    {
        point_value_t *p_point_value = _numbers[i];
        if (nullptr == p_point_value || UNSELECTED == p_point_value->value)
            return false;
    }
    return true;
}

void CBlock::print() const {
  std::cout << Color::Modifier(Color::FG_LIGHT_BLUE) << PIPE << Color::Modifier(Color::RESET) << " ";
  for (int i = 0; i < _count; ++i) {
    if ((i+1)%3 == 0){
      auto number = *(_numbers[i]);
      if (0 == number.value)
        std::cout << ' ' << " " << Color::Modifier(Color::FG_LIGHT_BLUE) << PIPE << Color::Modifier(Color::RESET) << " ";
      else {
        if (number.state == State::ERASED)
          std::cout << Color::Modifier(Color::FG_GREEN) << number.value
                    << Color::Modifier(Color::RESET) << " " << Color::Modifier(Color::FG_LIGHT_BLUE) << PIPE << Color::Modifier(Color::RESET) << " ";
        else
          std::cout << number.value << " " << Color::Modifier(Color::FG_LIGHT_BLUE) << PIPE << Color::Modifier(Color::RESET) << " ";
      }
    }
    else {
      auto number = *(_numbers[i]);
      if (0 == number.value)
        std::cout << ' ' << " " << PIPE << " ";
      else {
        if (number.state == State::ERASED)
          std::cout << Color::Modifier(Color::FG_GREEN) << number.value
                    << Color::Modifier(Color::RESET) << " " << PIPE << " ";
        else
          std::cout << number.value << " " << PIPE << " ";
      }
    }
  }
  std::cout << std::endl;
}

void CBlock::push_back(point_value_t *point)
{
    assert(nullptr != point);
    _numbers[_count++] = point;
}
