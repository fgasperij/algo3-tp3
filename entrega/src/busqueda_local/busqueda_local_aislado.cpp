#include <iostream>
#include <set>
#include <vector>

using namespace std;

double node_weight_in_subset_pasa(int node, int subset, const vector<set<int> > &partition, const vector<vector<double> > &adym);
double node_weight_in_subset(int node, int subset, const vector<set<int> > &partition, const vector<vector<double> > &adym, int except);
double partition_weight(const vector<set<int>> & particion, vector<vector<double> > &adym);
vector<int> index_node_by_partition(vector<set<int> > &partition, int n);

double busqueda_local_nodo_pasa(vector<vector<double> > &adym, vector<set<int> > partition, int max_it)
{
  double total_weight = partition_weight(partition, adym);
  int n = adym.size();
  int k = partition.size();
  vector<int> node_indexed_partition = index_node_by_partition(partition, n);
  bool has_improved = true;
  //while (has_improved) {
  int it = 0;
  while(it < max_it) {
    ++it;
    has_improved = false;
    for (int i = 0; i < n; ++i) {
      double node_weight_in_current_subset = 
        node_weight_in_subset_pasa(i, node_indexed_partition[i], partition, adym);
      bool swapped = false;
      int subset = 0;
      while (!swapped && subset < k) {
        if (subset != node_indexed_partition[i]) {
          double node_weight_in_subset_j = node_weight_in_subset_pasa(i, subset, partition, adym);
          if (node_weight_in_current_subset > node_weight_in_subset_j) {
            partition[node_indexed_partition[i]].erase(i);
            partition[subset].insert(i);
            node_indexed_partition[i] = subset;
            total_weight = total_weight - node_weight_in_current_subset + node_weight_in_subset_j;
            has_improved = true;
            swapped = true;
          }
        }
        ++subset;
      }
    }
  }

  return total_weight;
}

int busqueda_local_swap(vector<vector<double> > &adym, vector<set<int> > partition, int max_it)
{
  double total_weight = partition_weight(partition, adym);
  int n = adym.size();
  vector<int> node_indexed_partition = index_node_by_partition(partition, n);
  bool has_improved = true;
  int it = 0;
  //while (has_improved) {
  while (it < max_it) {
    ++it;
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

vector<int> index_node_by_partition(vector<set<int> > &partition, int n)
{
  vector<int> result(n, 0);
  for (int p = 0; p < partition.size(); ++p) {
    for (set<int>::iterator it = partition[p].begin(); it != partition[p].end(); ++it) {
      result[*it] = p;
    }
  }

  return result;
}

double node_weight_in_subset_pasa(int node, int subset, const vector<set<int> > &partition, const vector<vector<double> > &adym)
{
  double node_weight = 0;
  for (set<int>::iterator it = partition[subset].begin(); it != partition[subset].end(); ++it) {
    node_weight += adym[node][*it];
  }

  return node_weight;
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
