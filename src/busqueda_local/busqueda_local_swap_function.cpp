#include <iostream>
#include <set>
#include <vector>

using namespace std;

double node_weight_in_subset(int node, int subset, const vector<set<int> > &partition, const vector<vector<double> > &adym, int except);
double partition_weight(const vector<set<int>> & particion, vector<vector<double> > &adym);

int busqueda_local_swap(vector<vector<double> > &adym, vector<set<int> > partition)
{
  double total_weight = partition_weight(partition, adym);
  vector<int> node_indexed_partition(n, 0);
  bool has_improved = true;
  while (has_improved) {
    has_improved = false;
    for (int first_node = 0; first_node < n; ++first_node) {
      double first_node_current_weight = node_weight_in_subset(first_node, node_indexed_partition[first_node], partition, adym, -1);
      bool swapped = false;
      int second_node = first_node+1;
      while (!swapped && second_node < n) {
        if (node_indexed_partition[second_node] != node_indexed_partition[first_node]) {
          double second_node_current_weight = node_weight_in_subset(second_node, node_indexed_partition[second_node], partition, adym, -1);
          double first_node_new_weight = node_weight_in_subset(first_node, node_indexed_partition[second_node], partition, adym, second_node);
          double second_node_new_weight = node_weight_in_subset(second_node, node_indexed_partition[first_node], partition, adym, first_node);
          // if what I remove is greater than what I'm adding
          bool swap_improves = (first_node_current_weight+second_node_current_weight) > (first_node_new_weight+second_node_new_weight);
          if (swap_improves) {
            partition[node_indexed_partition[first_node]].erase(first_node);
            partition[node_indexed_partition[second_node]].erase(second_node);
            partition[node_indexed_partition[first_node]].insert(second_node);
            partition[node_indexed_partition[second_node]].insert(first_node);
            int temp = node_indexed_partition[second_node];
            node_indexed_partition[second_node] = node_indexed_partition[first_node];
            node_indexed_partition[first_node] = temp;
            total_weight = total_weight - (first_node_current_weight+second_node_current_weight) + (first_node_new_weight+second_node_new_weight);
            has_improved = true;
            swapped = true;
          }
        }
        ++second_node;
      }
    }
  }

  return total_weight;
}

double node_weight_in_subset(int node, int subset, const vector<set<int> > &partition, const vector<vector<double> > &adym, int except)
{
  double node_weight = 0;
  for (set<int>::iterator it = partition[subset].begin(); it != partition[subset].end(); ++it) {
    if (*it != except) {
      node_weight += adym[node][*it];
    }
  }

  return node_weight;
}

double partition_weight(const vector<set<int>> & particion, vector<vector<double> > &adym) {
    double res = 0;
    for (auto & conjunto : particion) {
        for (auto i = conjunto.begin(); i != conjunto.end(); i++) {
            int v = *i;
            auto j = i;
            j++;
            while (j != conjunto.end()) {
                res += adym[v][*j];
                j++;
            }
        }
    }
    return res;
}
