#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <limits>

using namespace std;

void show_list_vector(vector<list<int> > vlint)
{
  for (int i = 0; i < vlint.size(); i++) {
    for(list<int>::iterator it = vlint[i].begin(); it != vlint[i].end(); it++) {
      cout << *it << ' ';
    }
    cout << endl;
  }
}

struct Partition {
  Partition() : partition(vector<list<int> > (1, list<int> ())), weight(0), subsets_used(0), allowed_subsets(1) {};
  Partition(int subsets, int allowed_subsets) : partition(vector<list<int> > (subsets, list<int> ())), weight(0), subsets_used(0), allowed_subsets(allowed_subsets) {};

  void push_back_to_subset(int subset, int node)
  {
    if (partition[subset].empty()) {
      ++subsets_used;
    }
    partition[subset].push_back(node);
  };

  void pop_back_from_subset(int subset)
  {
    partition[subset].pop_back();
    if (partition[subset].empty()) {
      --subsets_used;
    }
  };

  double weight_in_subset(const vector<vector<double> > &adym, int node, int subset) const
  {
    double weight = 0; 
    for(list<int>::const_iterator it = partition[subset].begin(); it != partition[subset].end(); it++) {
      weight += adym[node][*it];
    }

    return weight;
  };

  int total_subsets() const
  {
    return partition.size();
  };

  vector<list<int> > partition;
  double weight;
  int subsets_used;
  int allowed_subsets;
};

/*
 * options:
 * -min_weight
 * -k_subsets
 * -can_improve
 **/   
void kpmp(vector<vector<double> > &adym, Partition &partition, Partition &min_partition, int node, map<string, bool> &options);

int main (int argc, char *argv[])
{
  map<string, bool> options = {{"min_weight", true}, {"k_subsets", true}, {"can_improve", true}};
  
  int n, m, k;
  cin >> n >> m >> k;

  // having w((u, v)) = 0 || (u, v) not in E is the same 
  vector<vector<double> > adym(n, vector<double> (n, 0));
  int u, v;
  double w;
  for(int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adym[u][v] = w;
    adym[v][u] = w;
  }

  Partition partition(k, k);
  partition.push_back_to_subset(0, 0);
  Partition min_partition(k, k);
  min_partition.weight = numeric_limits<double>::max();
  kpmp(adym, partition, min_partition, 1, options);

  vector<int> node_indexed_partition(n, -1);
  for (int i = 0; i < k; i++) {
    for(list<int>::iterator it = min_partition.partition[i].begin(); it != min_partition.partition[i].end(); it++) {
      node_indexed_partition[*it] = i;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << node_indexed_partition[i] << ' ';
  }
  cout << endl;

  return 0;
}

int nodes_left(int n, int current_node)
{
  // since first node is 0
  return n - current_node;
}

void kpmp(vector<vector<double> > &adym, Partition &partition, Partition &min_partition, int node, map<string, bool> &options)
{
  // check if has added all nodes
  if (node == adym.size()) {
    if (partition.weight < min_partition.weight &&
       partition.subsets_used <= partition.allowed_subsets) {
      min_partition = partition;
    }
    return;
  }

  // poda k_subsets
  if (options["k_subsets"]) {
    int subsets_left = partition.allowed_subsets - partition.subsets_used;
    if (nodes_left(adym.size(), node) == subsets_left) {
      partition.push_back_to_subset(partition.subsets_used, node);
      kpmp(adym, partition, min_partition, node+1, options);
      partition.pop_back_from_subset(partition.subsets_used-1);
    }
  }

  // poda pesada
  if (options["can_improve"]) {
    if (partition.subsets_used == partition.allowed_subsets) {
      double min_weight_of_adding_rest = 0;
      for (int current_node = node; current_node < adym.size(); current_node++) {
        double min_weight_in_subset = numeric_limits<double>::max();
        for (int subset = 0; subset < partition.subsets_used; ++subset) {
          double current_weight = partition.weight_in_subset(adym, current_node, subset);
          if (current_weight < min_weight_in_subset) {
            min_weight_in_subset = current_weight;
          }
        }
        min_weight_of_adding_rest += min_weight_in_subset;
      }

      if (min_weight_of_adding_rest + partition.weight >= min_partition.weight) {
        return;
      }
    }
  }

  // try adding it to every non-empty subset
  for (int subset = 0; subset < partition.subsets_used; ++subset) {
    double added_weight = partition.weight_in_subset(adym, node, subset);
    // poda min_weight
    if (options["min_weight"]) {
      if (partition.weight+added_weight < min_partition.weight) {
        partition.push_back_to_subset(subset, node);
        partition.weight += added_weight;
        kpmp(adym, partition, min_partition, node+1, options);
        partition.pop_back_from_subset(subset);
        partition.weight -= added_weight;
      }
    } else {
      partition.push_back_to_subset(subset, node);
      partition.weight += added_weight;
      kpmp(adym, partition, min_partition, node+1, options);
      partition.pop_back_from_subset(subset);
      partition.weight -= added_weight;
    }
  }

  if (options["k_subsets"]) {
    if (partition.subsets_used < partition.allowed_subsets) {
      // try adding new partition
      partition.push_back_to_subset(partition.subsets_used, node);
      kpmp(adym, partition, min_partition, node+1, options);
      partition.pop_back_from_subset(partition.subsets_used-1);
    }
  } else {
    if (partition.subsets_used < partition.total_subsets()) {
      partition.push_back_to_subset(partition.subsets_used, node);
      kpmp(adym, partition, min_partition, node+1, options);
      partition.pop_back_from_subset(partition.subsets_used-1);
    }
  }
}
