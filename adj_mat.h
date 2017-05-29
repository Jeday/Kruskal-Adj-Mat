#ifndef ADJ_MAT_H
#define ADJ_MAT_H


#include <vector>
#include <set>
#include <queue>
#include <map>
#include <utility>
#include <algorithm>
class adj_mat
    {



public:
    std::vector<std::vector<int>> mat;

    adj_mat(int graphs);

    int add_vertex();
    void delete_vertex(int ind);
    void connect_nodes(int ind1, int ind2, int price);
    void disconnect_nodes(int ind1, int ind2);
    void connect_nodes_tw(int ind1, int ind2, int price);
    void disconnect_nodes_tw(int ind1, int ind2);
    int price(int ind1, int ind2);
    void set_price(int ind1, int ind2, int price);
    void set_price_tw(int ind1, int ind2, int price);
    int max_price(int ind, int& max_ind);
    int min_price(int ind, int& min_ind);
    bool is_path(int ind1, int ind2, const std::set<int>& S);
    bool is_path(int ind1, int ind2);
    int size();
    };

#endif // ADJ_MAT_H
