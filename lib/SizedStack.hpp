
#ifndef CHIP8_LIB_SIZEDSTACK_HPP
#define CHIP8_LIB_SIZEDSTACK_HPP

#include "Macros.hpp"

#include <cstddef>
#include <stack>

template<typename T, std::size_t StackMaxSize>
class SizedStack {

  std::stack<T> stack;

public:

  using const_reference = T const &;
  using reference = T &;

  [[nodiscard]] const_reference top() const {
	  RuntimeAssert(!stack.empty(), "Stack is empty. It is not expected to call top() under this circumstances.");
	  return stack.top();
  }

  [[nodiscard]] reference top() {
	  RuntimeAssert(!stack.empty(), "Stack is empty. It is not expected to call top() under this circumstances.");
	  return stack.top();
  }

  [[nodiscard]] T pop() {
	  RuntimeAssert(!stack.empty(), "Stack is empty. It is not expected to call pop() under this circumstances.");

    T tmp = stack.top();
    stack.pop();
    return tmp;
  }

  void push(T element) {
	  RuntimeAssert(stack.size() <= StackMaxSize, "Stack has already reached max size.");
	  stack.push(std::move(element));
  }

  [[nodiscard]] bool empty() const {
	  return stack.empty();
  }

};

#endif //CHIP8_LIB_SIZEDSTACK_HPP
