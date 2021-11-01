#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

struct coord {
    int x;
    int y;
    coord() {};
    coord(int x, int y) : x(x), y(y) {};
};

std::ostream& operator<<(std::ostream& os, coord& c) {
    return os << c.x << ", " << c.y;
}

struct node {
    coord pos;
    node* parent;
    float f;
    float h;
    float g;
    node(coord pos, node* parent, float f, float h, float g) {
        this->pos = pos;
        this->parent = parent;
        this->f = f;
        this->h = h;
        this->g = g;
    }
};

float distance(coord cur, coord goal) {
    return sqrt(pow((cur.x - goal.x), 2) + pow((cur.y - goal.y), 2));
}

float distance(const node* n1, const node* n2) {
    return distance(n1->pos, n2->pos);
}

float distance(const node* n1, const coord n2Pos) {
    return distance(n1->pos, n2Pos);
}

node* get_cheapest_node(std::vector<node*>& list) {
    float f_min = 1000000.0f;
    int i_min = -1;
    for (int i = 0; i < int(list.size()); i++) {
        float f = list.at(i)->g + list.at(i)->h;
        if (f <= f_min) {
            f_min = f;
            i_min = i;
        }
    }

    node* result = list.at(i_min);
    list.erase(list.begin() + i_min);
    return result;
}

void move_from_to(node* n, std::vector<node*>& list1, std::vector<node*>& list2) {
    int list1_index;
    for (int i = 0; i < int(list1.size()); i++) {
        if (list1.at(i) == n) {
            list1_index = i;
            break;
        }
    }
    list2.push_back(n);
    list1.erase(list1.begin() + list1_index);
}

node* fromList(coord pos, std::vector<node*> list) {
    for (auto e : list) {
        if (distance(e->pos, pos) == 0) { return e; }
    }
    return nullptr;
}

std::vector<node*> get_successor_nodes(node* node_current, char grid[][41], std::vector<node*> l1, std::vector<node*> l2, node* node_goal) {
    std::vector<node*> successor_list;
    int i_begin = node_current->pos.x - 1;
    int j_begin = node_current->pos.y - 1;
    for (int i = i_begin; i < i_begin + 3; i++) {
        for (int j = j_begin; j < j_begin + 3; j++) {
            // skip if same node
            if (distance(node_current, coord(i, j)) == 0) { continue; }

            // skip if not a free place
            if (grid[i][j] == '#') { continue; };

            // init and safe as successor node IF IT DOES NOT YET EXIST
            node* new_successor_node = fromList(coord(i, j), l1);
            if (new_successor_node == nullptr) {
                new_successor_node = fromList(coord(i, j), l2);
            }

            // check if successor is goal
            if (distance(node_goal, coord(i, j)) == 0) {
                new_successor_node = node_goal;
            }

            if (new_successor_node == nullptr) {
                float distance_end = distance(coord(i, j), coord(40, 40));
                new_successor_node = new node(
                    coord(i, j),
                    nullptr,
                    distance_end,
                    distance_end,
                    0
                );
            }
            successor_list.push_back(new_successor_node);
        }
    }
    return successor_list;
}

int main() {
    char grid[41][41];

    std::string line;
    for (int i = 0; i < 41; i++) {
        std::cin >> line;
        for (int j = 0; j < 41; j++) {
            grid[i][j] = line[j];
        }
    }

    float distance_end = distance(coord(1, 1), coord(39, 39));
    node* node_start = new node(coord(1, 1),
        nullptr,
        distance_end,
        distance_end,
        0
    );
    node* node_goal = new node(coord(39, 39),
        nullptr,
        0,
        0,
        0
    );

    std::vector<node*> open_list;
    std::vector<node*> close_list;

    open_list.push_back(node_start);

    while (open_list.size() != 0) {
        // remove current node from open list
        node* node_current = get_cheapest_node(open_list);

        // break if goal node is found
        if (node_current == node_goal) { break; }

        // get list of successor nodes of current node
        std::vector<node*> successor_list = get_successor_nodes(node_current, grid, open_list, close_list, node_goal);

        for (auto node_successor : successor_list) {
            float node_successor_g = node_current->g + distance(node_current, node_successor);

            if (std::count(open_list.begin(), open_list.end(), node_successor) == 1) {
                if (node_successor->g <= node_successor_g) { continue; }
            }
            else if (std::count(close_list.begin(), close_list.end(), node_successor) == 1) {
                if (node_successor->g <= node_successor_g) { continue; }
                move_from_to(node_successor, close_list, open_list);
            }
            else {
                open_list.push_back(node_successor);
                node_successor->h = distance(node_successor, node_goal);
            }
            node_successor->g = node_successor_g;
            node_successor->parent = node_current;
        }

        close_list.push_back(node_current);
    }

    node* cur = node_goal;
    grid[1][1] = 'o';
    while (distance(cur, node_start) != 0) {
        grid[cur->pos.x][cur->pos.y] = 'o';
        cur = cur->parent;
    }

    // PRINT
    for (int i = 0; i < 41; i++) {
        for (int j = 0; j < 41; j++) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}