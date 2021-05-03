/**
* @file list.hpp
* @author yahya mohammed ( goldroger.1993@outlook.com )
* @brief a singly linked list with modern c++
* @version 0.2
* @date 2021-04-28
* @license MIT License 2021
*/

#ifndef LIST_HPP
#define LIST_HPP

#include <exception>
#include <initializer_list>
#include <iostream>
#include <memory>


template <typename T> class List_ {
  class Node {
  public:
    T m_data{};
    std::shared_ptr<Node> m_next{nullptr};
  }; // end of class Node

private:
  std::shared_ptr<Node> m_head{nullptr};
  std::shared_ptr<Node> m_tail{nullptr};
  std::size_t m_size{};

public:
  /* constructors */
  List_() = default;

  List_(const std::initializer_list<T> &arg) {
    for (const auto &i : arg) { push_back(i); }
  }

  /*@ methods: */
  /**
   * @brief check if list is empty
   * @complexity O(1)
   * @return true
   * @return false
   */
  [[nodiscard]] constexpr inline auto is_empty() -> bool {
    return m_head == nullptr ? true : false;
  }

  /**
   * @brief returns size of the list
   * @complexity O(1)
   * @return std::size_t
   */
  [[nodiscard]] constexpr inline auto size() -> std::size_t { return m_size; }

  /**
   * @brief returns first element
   * @complexity O(1)
   * @return T&
   */
  [[nodiscard]] constexpr inline auto front() -> T & {
    if (is_empty()) { throw std::runtime_error("list is empty...\n"); }
    return m_head->m_data;
  }

  /**
   * @brief return last element&
   * @complexity O(1)
   * @return T&
   */
  [[nodiscard]] constexpr inline auto back() -> T &
  {
    if (is_empty()) { throw std::runtime_error("list is empty...\n"); }
    return m_tail->m_data;
  }

  auto print() -> void
  {
    if (!is_empty()) {
      std::shared_ptr<Node> it{};
      for (it = m_head; it != nullptr; it = it->m_next) {
        std::cout << it->m_data << ' ';
      }
      return;
    }
    throw std::runtime_error("list is empty...\n");
  }

  /**
   * @brief return element at given position&
   * @complexity O(n)
   * @param times
   * @return auto&
   */
  [[nodiscard]] constexpr auto at(const std::size_t times) -> auto &
  {
    if (is_empty()) {
      throw std::runtime_error("list is empty...\n");
    }
    if (times < 0 || times >= size()) {
      throw std::runtime_error("--out of range...");
    }
    std::shared_ptr<Node> it{m_head};
    for (std::size_t i = 0; i < times; ++i) {
      it = it->m_next;
    }
    return it->m_data;
  }

  /**
   * @brief add element at end of list
   * @complexity O(1)
   * @param arg
   */
  auto push_back(const T &arg) -> void
  {
    std::shared_ptr<Node> new_node = std::make_shared<Node>();
    new_node->m_data = arg;
    new_node->m_next = nullptr;
    //
    if (is_empty()) {
      m_head = new_node; // |0, null|
      m_tail = new_node; // |0, null|
    }
    m_tail->m_next = new_node; // changes head-> next too, then it changes
    // the previous temps next
    // head ->|0, 0x1| -> |1, 0x2| -> |2, null|
    m_tail = new_node; // now tail points to temp
    //
    ++m_size;
  }

  auto push_back(T &&arg) -> void
  {
    std::shared_ptr<Node> new_node = std::make_shared<Node>();
    new_node->m_data = arg;
    new_node->m_next = nullptr;
    //
    if (is_empty()) {
      m_head = new_node; // |0, null|
      m_tail = new_node; // |0, null|
    }
    m_tail->m_next = new_node; // changes head-> next too, then it changes
    // the previous temps next
    // head ->|0, 0x1| -> |1, 0x2| -> |2, null|
    m_tail = new_node; // now tail points to temp
    //
    ++m_size;
  }

  /**
   * @brief add element at the beginning of list
   * @complexity O(1)
   * @param arg
   */
  auto push_front(const T &arg) -> void
  {
    std::shared_ptr<Node> new_node = std::make_shared<Node>();
    new_node->m_data = arg;
    new_node->m_next = m_head;
    // now temp-> next points to what old head was pointing at
    m_head = new_node; // new head points to new node (old head)
    //
    ++m_size;
  }

  /**
 * @brief add element at given position
 * @complexity O(n)
 * @param pos
 * @param arg
 */
  auto push_at(const std::size_t pos, const T &arg) -> void
  {
    if (is_empty()) {
      throw std::runtime_error("list is empty...\n");
    }
    if (pos == 0) { push_front(arg); }
    if (pos == size()-1) { push_back(arg); }
    /* adding nodes between previous and next */
    std::shared_ptr<Node> prev_node =
        std::make_shared<Node>(); // hold previous node
    std::shared_ptr<Node> new_node = std::make_shared<Node>(); // hold new node
    std::shared_ptr<Node> next_node = m_head; // points to next node
    //
    for (std::size_t i = 0; i < pos; ++i) {
      prev_node = next_node;
      next_node = next_node->m_next;
    }
    new_node->m_data = arg;
    prev_node->m_next = new_node;
    new_node->m_next = next_node;
    //
    ++m_size;
  }

  /**
   * @brief remove last element
   * @complexity O(n)
   */
  auto pop_back() -> void
  {
    if (is_empty()) {
      throw std::runtime_error("list is empty...\n");
    }
    //
    std::shared_ptr<Node> last{m_head};
    while (last->m_next->m_next != nullptr) {
      last = last->m_next;
    }
    m_tail = last; // tail points to 1 step before old tail
    m_tail->m_next = nullptr;
    //
    --m_size;
    last.reset();
  }

  /**
   * @brief remove first element
   * @complexity O(1)
   */
  auto pop_front() -> void
  {
    if (is_empty()) {
      throw std::runtime_error("list is empty...\n");
    }
    //
    std::shared_ptr<Node> first{m_head}; // first points to old head
    m_head = m_head->m_next; // head points to one step ahead of old head
    //
    --m_size;
    first.reset();
  }

  /**
  * @brief remove element at given position
  * @complexity O(n)
  */
  auto pop_at(const std::size_t pos) -> void
  {
    const std::size_t s = size();
    if (pos < 0 || pos >= s) {
      throw std::runtime_error("--out of range...");
    }
    if (is_empty()) {
      throw std::runtime_error("list is empty...\n");
    }
    if (pos == 0) { pop_front(); return; }
    else if ( pos == s-1) { pop_back(); return; }
    //
    std::shared_ptr<Node> prev = std::make_shared<Node>();
    std::shared_ptr<Node> next = m_head;
    // ex: 0, 1, 2, 3, 4, 5 : pop_at(1) now:
    std::shared_ptr<Node> it = m_head;
    for (std::size_t i = 0; i < pos && next != nullptr; ++i) {
      prev = it;                 // 0
      next = it->m_next->m_next; // 2
      it = it->m_next;           // 1
    }
    prev->m_next = next; // 0 -> 2 -> 3 -> 4 -> 5 and whatever was node 1, is now gone
    --m_size;
    //
    it = nullptr; // 1 -> nullptr
  }

  /**
  * @brief splitiing the current list into two lists
  * @complexity O(n)
  * @param l1
  * @param l2
  */
  auto split(List_<T> &l1, List_<T> &l2) -> void
  {
    if (is_empty()) { throw std::runtime_error("--list is empty..."); }
    const auto& s = size();
    for (std::size_t i = 0; i < (s/2); ++i) {
      l1.push_back( at(i) );
    }
    for ( std::size_t i = (s/2); i < s; ++i ) {
      l2.push_back( at(i) );
    }
  }

  /**
  * @brief merges two lists into one
  * @complexity O(n)
  * @param l1
  * @param l2
  */
  auto merge( List_<T>& l1,  List_<T>& l2) ->void
  {
    if (l1.is_empty()) { throw std::runtime_error("--list is empty..."); }
    if (l2.is_empty()) { throw std::runtime_error("--list is empty..."); }
    for (std::size_t i = 0; i < l1.size(); ++i) {
      push_back( l1.at(i) );
    }
    for (std::size_t i = 0; i < l2.size(); ++i) {
      push_back( l2.at(i) );
    }
  }

  /**
  * @brief erases the list
  * @complexity O(n)
  */
  auto clear() ->void
  {
    if (is_empty()) { throw std::runtime_error("--list is empty..."); }
    std::shared_ptr<Node> it{ m_head };
    std::shared_ptr<Node> temp{};
    while ( it != nullptr ) {
      temp = it->m_next;
      it.reset();
      it = temp;
    }
    m_head.reset();
    m_tail.reset();
  }

}; // end of class List_<T>

#endif // LIST_HPP
