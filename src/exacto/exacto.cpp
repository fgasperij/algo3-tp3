#include <iostream>
#include <vector>
#include <list>

using namespace std;

void kpmp(vector<vector<float> > &adym, vector<list<int> > &partitions, 
    vector<list<int> > &min_partitions, int node, int k, int k_actual, 
    float total_weight, float min_weight);

int main (int argc, char *argv[])
{
  int n, m, k;
  cin >> n >> m >> k;

  // having w((u, v)) = 0 || (u, v) not in E is the same 
  vector<vector<float> > adym(n, vector<float> (n, 0));
  int u, v;
  float w;
  for(int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adym[u][v] = w;
    adym[v][u] = w;
  }

  vector<list<int> > partitions(k, list<int>());
  vector<list<int> > min_partitions(k, list<int>());
  partitions[0].push_back(0);
  kpmp(adym, partitions, min_partitions, 1, k, 0, 0, numeric_limits<float>::max());

  vector<int> node_indexed_partitions(n, -1);
  for (int i = 0; i < k; i++) {
    for(list<int>::iterator it = partitions[i].begin(); it != partitions[i].end(); it++) {
      node_indexed_partitions[*it] = i;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << node_indexed_partitions[i] << ' ';
  }
  cout << endl;

  return 0;
}

void kpmp(vector<vector<float> > &adym, vector<list<int> > &partitions, 
    vector<list<int> > &min_partitions, int node, int k, int k_actual, 
    float total_weight, float min_weight)
{
  if (node == adym.size()) {
    if (total_weight < min_weight) {
      min_partitions = partitions;
      min_weight = total_weight;
    }
    return;
  }

  for (int i = 0; i <= k_actual; i++) {
    float added_weight = 0;
    for(list<int>::iterator it = partitions[i].begin(); it != partitions[i].end(); it++) {
      added_weight += adym[node][*it];
    }
    partitions[i].push_back(node);
    kpmp(adym, partitions, min_partitions, node+1, k, k_actual, 
        total_weight+added_weight, min_weight);
    partitions[i].pop_back();
  }

  if (k_actual < k-1) {
    // try adding new partition
    partitions[k_actual+1].push_back(node);
    kpmp(adym, partitions, min_partitions, node+1, k, k_actual+1, 
        total_weight, min_weight);
    partitions[k_actual+1].pop_back();
  }
}
