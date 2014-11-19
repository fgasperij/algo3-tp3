#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <map>
#include <string>
#include <limits>
#include <chrono>
#include <climits>

using namespace std;

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

#define MAX_N 20 
#define MIN_N 3 // this dependes on the test.in
#define INSTANCES_BY_N 100
int main (int argc, char *argv[])
{
  vector<map<string, bool> > prune_options(5, map<string, bool> ());
  prune_options[0] = {{"min_weight", false}, {"k_subsets", false}, {"can_improve", false}};
  prune_options[1] = {{"min_weight", false}, {"k_subsets", true}, {"can_improve", false}};
  prune_options[2] = {{"min_weight", true}, {"k_subsets", false}, {"can_improve", false}};
  prune_options[3] = {{"min_weight", false}, {"k_subsets", false}, {"can_improve", true}};
  prune_options[4] = {{"min_weight", true}, {"k_subsets", true}, {"can_improve", true}};

  ofstream ofs("test.out", std::ofstream::out);
  for (int instance_size = MIN_N; instance_size < MAX_N; ++instance_size) {
    ofs << instance_size << ' ';
    cout << "INSTANCE SET OF SIZE: " << instance_size << endl;
    // sumaTiemposPorN
    // [0] -> sin_podas
    // [1] -> k_subset
    // [2] -> min_weight
    // [3] -> can_improve
    // [4] -> all
    vector<int> sumaTiemposPorN(5, 0);
    for (int instance_of_size = 0; instance_of_size < 100; ++instance_of_size) {
      cout << "Instance: " << instance_of_size << endl;
      int n, m, k;
      cin >> n >> m >> k;

      // having w((u, v)) = 0 || (u, v) not in E is the same 
      vector<vector<double> > adym(n, vector<double> (n, 0));
      int u, v;
      double w;
      for(int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        adym[u-1][v-1] = w;
        adym[v-1][u-1] = w;
      }

      // one for each prune
      for (int prune = 1; prune < 5; prune++) {
        std::chrono::microseconds minTiempo(INT_MAX);
        for (int i = 0; i < 10; ++i) {
          auto start_time = std::chrono::high_resolution_clock::now();
          if (!prune_options[prune]["min_weight"] && !prune_options[prune]["k_subsets"] &&
              !prune_options[prune]["can_improve"]) {
            Partition partition(n, k);
            partition.push_back_to_subset(0, 0);
            Partition min_partition(n, k);
            min_partition.weight = numeric_limits<double>::max();
            kpmp(adym, partition, min_partition, 1, prune_options[prune]);
          } else {
            Partition partition(k, k);
            partition.push_back_to_subset(0, 0);
            Partition min_partition(k, k);
            min_partition.weight = numeric_limits<double>::max();
            kpmp(adym, partition, min_partition, 1, prune_options[prune]);
          }
          auto end_time = std::chrono::high_resolution_clock::now();
          std::chrono::microseconds tiempoRep = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
          if (tiempoRep < minTiempo) {
              minTiempo = tiempoRep;
          }
          sumaTiemposPorN[prune] += minTiempo.count();
        }
      }
    }
    // sin_podas k_subset min_weight can_improve all
    ofs /*<< sumaTiemposPorN[0]/INSTANCES_BY_N << ' '*/ << sumaTiemposPorN[1]/INSTANCES_BY_N << ' ' << 
      sumaTiemposPorN[2]/INSTANCES_BY_N << ' ' << sumaTiemposPorN[3]/INSTANCES_BY_N << ' ' << 
      sumaTiemposPorN[4]/INSTANCES_BY_N << endl;
  }

  ofs.close();

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
