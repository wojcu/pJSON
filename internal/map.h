#ifndef MAP_H
#define MAP_H

#include <memory>

namespace persistent {
template <typename K, typename V>
class map {
  class map_node {
    using s_node = std::shared_ptr<const map_node>;

   public:
    static s_node create(K key, V value, s_node left, s_node right) {
      return s_node(new map_node(std::move(key), std::move(value),
                                 std::move(left), std::move(right)));
    }

    static s_node insert(const s_node &t, K key, V value) {
      if (!t) {
        return map_node::create(std::move(key), std::move(value), nullptr,
                                nullptr);
      }
      if (key < t->key()) {
        return balance(create(
            t->key(), t->value(),
            insert(t->left(), std::move(key), std::move(value)), t->right()));
      }
      if (t->key() < key) {
        return balance(
            create(t->key(), t->value(), t->left(),
                   insert(t->right(), std::move(key), std::move(value))));
      }
      return balance(
          create(std::move(key), std::move(value), t->left(), t->right()));
    }

    static s_node nth(const s_node &t, size_t n) {
      if (!t) {
        return nullptr;
      }
      if (n >= t->size()) {
        return nullptr;
      }
      size_t lsize = t->left() ? t->left()->size() : 0;
      if (n < lsize) {
        return nth(t->left(), n);
      } else if (lsize < n) {
        return nth(t->right(), n - lsize - 1);
      }
      return create(t->key(), t->value(), nullptr, nullptr);
    }

    static s_node erase(const s_node &t, const K &key) {
      if (!t) {
        return nullptr;
      }
      if (key < t->key()) {
        return balance(
            create(t->key(), t->value(), erase(t->left(), key), t->right()));
      }
      if (t->key() < key) {
        return balance(
            create(t->key(), t->value(), t->left(), erase(t->right(), key)));
      }
      if (!t->left()) {
        return t->right();
      }
      if (!t->right()) {
        return t->left();
      }
      const auto low = min_node(t->right());
      return balance(create(low->key(), low->value(), t->left(),
                            pop_min_node(t->right())));
    }

    static s_node find(const s_node &t, const K &key) {
      if (!t) {
        return nullptr;
      }
      if (key < t->key()) {
        return find(t->left(), key);
      }
      if (t->key() < key) {
        return find(t->right(), key);
      }
      return create(t->key(), t->value(), nullptr, nullptr);
    }

    const K &key() const { return m_data.first; }
    const V &value() const { return m_data.second; }
    const std::pair<const K, const V> &data() const { return m_data; }
    const s_node &left() const { return m_left; }
    const s_node &right() const { return m_right; }
    size_t size() const { return m_size; }
    size_t depth() const { return m_depth; }

    template <typename F>
    void fold(F func) const {
      if (left()) {
        left()->fold(func);
      }
      func(key(), value());
      if (right()) {
        right()->fold(func);
      }
    }

   private:
    enum e_rotation { rotation_left, rotation_right };

    static s_node rotate(const s_node &t, e_rotation direction) {
      if (!t) {
        return nullptr;
      }
      if (direction == rotation_left) {
        return create(
            t->right()->key(), t->right()->value(),
            create(t->key(), t->value(), t->left(), t->right()->left()),
            t->right()->right());
      }
      return create(
          t->left()->key(), t->left()->value(), t->left()->left(),
          create(t->key(), t->value(), t->left()->right(), t->right()));
    }

    static int stability(const s_node &t) {
      if (!t) {
        return 0;
      }
      const int ldepth = t->left() ? t->left()->depth() : 0;
      const int rdepth = t->right() ? t->right()->depth() : 0;
      return ldepth - rdepth;
    }

    static s_node balance(const s_node &t) {
      if (!t) {
        return nullptr;
      }
      const int stab = stability(t);
      if (stab < -1) {
        if (stability(t->right()) > 1) {
          return rotate(create(t->key(), t->value(), t->left(),
                               rotate(t->right(), rotation_right)),
                        rotation_left);
        }
        return rotate(t, rotation_left);
      } else if (stab > 1) {
        if (stability(t->left()) < -1) {
          return rotate(create(t->key(), t->value(),
                               rotate(t->left(), rotation_left), t->right()),
                        rotation_right);
        }
        return rotate(t, rotation_right);
      }
      return t;
    }

    static s_node min_node(const s_node &t) {
      if (!t) {
        return nullptr;
      }
      if (t->left()) {
        return min_node(t->left());
      }
      return t;
    }

    static s_node pop_min_node(const s_node &t) {
      if (!t) {
        return nullptr;
      }
      if (t->left()) {
        return balance(
            create(t->key(), t->value(), pop_min_node(t->left()), t->right()));
      }
      return t->right();
    }

    map_node(K key, V value, s_node left, s_node right)
        : m_data(std::move(key), std::move(value)),
          m_left(std::move(left)),
          m_right(std::move(right)),
          m_size((m_left ? m_left->size() : 0) +
                 (m_right ? m_right->size() : 0) + 1),
          m_depth(std::max(m_left ? m_left->depth() : 0,
                           m_right ? m_right->depth() : 0) +
                  1) {}

    const std::pair<const K, const V> m_data;
    const s_node m_left;
    const s_node m_right;
    const size_t m_size;
    const size_t m_depth;
  };

  using s_node = std::shared_ptr<const map_node>;

 public:
  map() {}

  void insert(K key, V value) {
    m_node = map_node::insert(m_node, std::move(key), std::move(value));
  }

  bool contains(const K &key) const {
    return m_node ? (bool)map_node::find(m_node, key) : false;
  }

  const std::pair<const K, const V> &at(const K &key) const {
    return map_node::find(m_node, key)->data();
  }

  const std::pair<const K, const V> &nth(size_t n) const {
    return map_node::nth(m_node, n)->data();
  }

  void erase(const K &key) { m_node = map_node::erase(m_node, key); }

  size_t size() const { return m_node ? m_node->size() : 0; }

  template <typename F>
  void fold(F func) const {
    if (m_node) {
      m_node->fold(func);
    }
  }

 private:
  s_node m_node;
};
}  // persistent

#endif  // MAP_H
