#include <iostream>
#include <set>
#include <vector>

using namespace std;

double node_weight_in_subset(int node, int subset, const vector<set<int> > &partition, const vector<vector<double> > &adym, int except);

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
    for (int first_node = 0; first_node < n; ++first_node) {
      double first_node_current_weight = node_weight_in_subset(first_node, node_indexed_partition[first_node], partition, adym, -1);
      bool swapped = false;
      int second_node = first_node+1;
      while (!swapped && second_node < n) {
        if (node_indexed_partition[second_node] != node_indexed_partition[first_node]) {
          cout << "Considering swapping node " << first_node << " from subset " << node_indexed_partition[first_node] << 
            " for node" << second_node << " on subset " << node_indexed_partition[second_node] << endl;
          double second_node_current_weight = node_weight_in_subset(second_node, node_indexed_partition[second_node], partition, adym, -1);
          double first_node_new_weight = node_weight_in_subset(first_node, node_indexed_partition[second_node], partition, adym, second_node);
          double second_node_new_weight = node_weight_in_subset(second_node, node_indexed_partition[first_node], partition, adym, first_node);
          // if what I remove is greater than what I'm adding
          bool swap_improves = (first_node_current_weight+second_node_current_weight) > (first_node_new_weight+second_node_new_weight);
          if (swap_improves) {
            cout << "FOUND IMPROVEMENT!" << endl;
            cout << " Swapping node " << first_node << " from subset " << node_indexed_partition[first_node] << "for node " << 
              second_node << " on subset " << node_indexed_partition[second_node] << endl;
            partition[node_indexed_partition[first_node]].erase(first_node);
            partition[node_indexed_partition[second_node]].erase(second_node);
            partition[node_indexed_partition[first_node]].insert(second_node);
            partition[node_indexed_partition[second_node]].insert(first_node);
            int temp = node_indexed_partition[second_node];
            node_indexed_partition[second_node] = node_indexed_partition[first_node];
            node_indexed_partition[first_node] = temp;
            total_weight = total_weight - (first_node_current_weight+second_node_current_weight) + (first_node_new_weight+second_node_new_weight);
            cout << "New total weight is: " << total_weight << endl;
            has_improved = true;
            swapped = true;
          }
        }
        ++second_node;
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
