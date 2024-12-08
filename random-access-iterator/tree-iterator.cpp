#include "tree.hpp"

// Реализация функции `at` для нахождения узла по индексу
auto tree::iterator::at(tree_node *node, ptrdiff_t index) const -> tree_node* {
    while (node) {
        int left_size = node->left ? node->left->subtree_size : 0;
        if (index < left_size) {
            node = node->left;  // Идем в левое поддерево
        } else if (index > left_size) {
            index -= (left_size + 1);
            node = node->right;  // Идем в правое поддерево
        } else {
            return node;  // Найден узел по индексу
        }
    }
    return nullptr;
}

// Оператор `+` для итератора: смещение на diff элементов вперед
tree::iterator operator+(tree::iterator const &self, ptrdiff_t diff) {
    tree::iterator temp = self;
    temp.current_node = temp.at(temp.current_node, temp.current_index + diff);
    temp.current_index += diff;
    return temp;
}

// Оператор `-` для итератора: смещение на diff элементов назад
tree::iterator operator-(tree::iterator const &self, ptrdiff_t diff) {
    tree::iterator temp = self;
    temp.current_node = temp.at(temp.current_node, temp.current_index - diff);
    temp.current_index -= diff;
    return temp;
}

// Разница между двумя итераторами: возвращает разницу в индексах
ptrdiff_t operator-(tree::iterator const &self, tree::iterator other) {
    return self.current_index - other.current_index;
}

// Начальный итератор (на минимальный элемент в дереве)
auto tree::begin() const -> iterator {
    tree_node *node = root.get();
    ptrdiff_t index = 0;

    // Идем до самого левого элемента
    while (node && node->left) {
        node = node->left;
    }

    return iterator{node, index};
}

// Конечный итератор (указатель на конец дерева)
auto tree::end() const -> iterator {
    return iterator{nullptr, root ? root->subtree_size : 0};  // Указывает на позицию за последним элементом
}
