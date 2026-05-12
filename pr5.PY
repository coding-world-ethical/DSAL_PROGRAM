from collections import deque
import copy


class BSTNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def insert(self, key):
        def _insert(node, key):
            if node is None:
                return BSTNode(key)

            if key < node.key:
                node.left = _insert(node.left, key)

            elif key > node.key:
                node.right = _insert(node.right, key)

            else:
                print(f"Duplicate entry '{key}' not inserted.")

            return node

        self.root = _insert(self.root, key)

    def search(self, key):
        node = self.root

        while node:
            if key < node.key:
                node = node.left

            elif key > node.key:
                node = node.right

            else:
                return True

        return False

    def _find_min_node(self, node):
        while node and node.left:
            node = node.left

        return node

    def delete(self, key):
        def _delete(node, key):
            if not node:
                return node

            if key < node.key:
                node.left = _delete(node.left, key)

            elif key > node.key:
                node.right = _delete(node.right, key)

            else:
                if not node.left:
                    return node.right

                elif not node.right:
                    return node.left

                temp = self._find_min_node(node.right)
                node.key = temp.key
                node.right = _delete(node.right, temp.key)

            return node

        self.root = _delete(self.root, key)

    def inorder(self):
        res = []

        def _in(node):
            if not node:
                return

            _in(node.left)
            res.append(node.key)
            _in(node.right)

        _in(self.root)
        return res

    def preorder(self):
        res = []

        def _pre(node):
            if not node:
                return

            res.append(node.key)
            _pre(node.left)
            _pre(node.right)

        _pre(self.root)
        return res

    def postorder(self):
        res = []

        def _post(node):
            if not node:
                return

            _post(node.left)
            _post(node.right)
            res.append(node.key)

        _post(self.root)
        return res

    def depth(self):
        def _depth(node):
            if not node:
                return 0

            return 1 + max(
                _depth(node.left),
                _depth(node.right)
            )

        return _depth(self.root)

    def mirror(self):
        def _mirror_node(node):
            if node is None:
                return None

            new_node = BSTNode(node.key)

            new_node.left = _mirror_node(node.right)
            new_node.right = _mirror_node(node.left)

            return new_node

        mirrored = BinarySearchTree()
        mirrored.root = _mirror_node(self.root)

        return mirrored

    def copy(self):
        return copy.deepcopy(self)

    def parents_with_children(self):
        pairs = []

        def _visit(node):
            if not node:
                return

            children = []

            if node.left:
                children.append(node.left.key)

            if node.right:
                children.append(node.right.key)

            if children:
                pairs.append((node.key, children))

            _visit(node.left)
            _visit(node.right)

        _visit(self.root)

        return pairs

    def leaf_nodes(self):
        leaves = []

        def _leaf(node):
            if not node:
                return

            if not node.left and not node.right:
                leaves.append(node.key)

            _leaf(node.left)
            _leaf(node.right)

        _leaf(self.root)

        return leaves

    def level_wise(self):
        levels = []

        if not self.root:
            return levels

        q = deque([self.root])

        while q:
            level_size = len(q)
            level = []

            for _ in range(level_size):
                node = q.popleft()
                level.append(node.key)

                if node.left:
                    q.append(node.left)

                if node.right:
                    q.append(node.right)

            levels.append(level)

        return levels


if __name__ == "__main__":
    bst = BinarySearchTree()

    while True:
        print("\n--- Binary Search Tree Menu ---")
        print("1. Insert")
        print("2. Delete")
        print("3. Search")
        print("4. Display Inorder")
        print("5. Display Preorder")
        print("6. Display Postorder")
        print("7. Display Depth")
        print("8. Display Mirror Image (Inorder)")
        print("9. Create Copy (Inorder)")
        print("10. Display Parent-Child Pairs")
        print("11. Display Leaf Nodes")
        print("12. Display Level-wise")
        print("0. Exit")

        choice = input("Enter choice: ")

        if choice == "1":
            val = int(input("Enter value to insert: "))
            bst.insert(val)

        elif choice == "2":
            val = int(input("Enter value to delete: "))
            bst.delete(val)

        elif choice == "3":
            val = int(input("Enter value to search: "))
            print("Found" if bst.search(val) else "Not found")

        elif choice == "4":
            print("Inorder:", bst.inorder())

        elif choice == "5":
            print("Preorder:", bst.preorder())

        elif choice == "6":
            print("Postorder:", bst.postorder())

        elif choice == "7":
            print("Depth of tree:", bst.depth())

        elif choice == "8":
            mirror_tree = bst.mirror()
            print(
                "Mirror image inorder:",
                mirror_tree.inorder()
            )

        elif choice == "9":
            copied_tree = bst.copy()
            print(
                "Copied tree inorder:",
                copied_tree.inorder()
            )

        elif choice == "10":
            print(
                "Parent-Child pairs:",
                bst.parents_with_children()
            )

        elif choice == "11":
            print(
                "Leaf nodes:",
                bst.leaf_nodes()
            )

        elif choice == "12":
            print(
                "Level-wise:",
                bst.level_wise()
            )

        elif choice == "0":
            print("Exiting...")
            break

        else:
            print("Invalid choice! Try again.")