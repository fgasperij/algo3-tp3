#include <iostream>
#include <set>
#include <vector>

using namespace std;

double node_weight_in_subset(int node, int subset, const vector<set<int> > &partition, const vector<vector<double> > &adym);

int main(int argc, char *argv[])
{
  int n, m, k;
  cin >> n >> m >> k;

  // having w((u, v)) = 0 || (u, v) not in E is the same 
  vector<vector<double> > adym(n, vector<double> (n, 0));
  int u, v;
  double w;
  double total_weight = 0;
  for(int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adym[u][v] = w;
    adym[v][u] = w;
    total_weight += w;
  }

  vector<set<int> > partition(k, set<int>());
  for(int i = 0; i < n; ++i) {
    partition[0].insert(i);
  }

  cout << "Starting with a total weight of " << total_weight << endl;
  vector<int> node_indexed_partition(n, 0);
  bool has_improved = true;
  while (has_improved) {
    has_improved = false;
    for (int i = 0; i < n; ++i) {
      double node_weight_in_current_subset = 
        node_weight_in_subset(i, node_indexed_partition[i], partition, adym);
      bool swapped = false;
      int subset = 0;
      while (!swapped && subset < k) {
        if (subset != node_indexed_partition[i]) {
          cout << "Considering swapping node " << i << " from subset " << node_indexed_partition[i] << " to subset " << subset << endl;
          double node_weight_in_subset_j = node_weight_in_subset(i, subset, partition, adym);
          if (node_weight_in_current_subset > node_weight_in_subset_j) {
            cout << "FOUND IMPROVEMENT!" << endl;
            cout << " Swapping node " << i << " from subset " << node_indexed_partition[i] << " to subset " << subset << endl;
            partition[node_indexed_partition[i]].erase(i);
            partition[subset].insert(i);
            node_indexed_partition[i] = subset;
            total_weight = total_weight - node_weight_in_current_subset + node_weight_in_subset_j;
            cout << "New total weight is: " << total_weight << endl;
            has_improved = true;
            swapped = true;
          }
        }
        ++subset;
      }
    }
  }

  cout << "Minimum weight reached: " << total_weight << endl;
  cout << "PARTITION" << endl;
  for (int i = 0; i < k; ++i) {
    cout << "Partition " << i << ": ";
    for(set<int>::iterator it = partition[i].begin(); it != partition[i].end(); ++it) {
      cout << *it << ' ';
    }
    cout << endl;
  }

  return 0;
}

double node_weight_in_subset(int node, int subset, const vector<set<int> > &partition, const vector<vector<double> > &adym)
{
  double node_weight = 0;
  for (set<int>::iterator it = partition[subset].begin(); it != partition[subset].end(); ++it) {
    node_weight += adym[node][*it];
  }

  return node_weight;
}
