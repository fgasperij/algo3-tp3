#include <iostream>
#include <vector>
#include <list>
#include <limits>

using namespace std;

void kpmp(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight);

void show_list_vector(vector<list<int> > vlint)
{
  for (int i = 0; i < vlint.size(); i++) {
    for(list<int>::iterator it = vlint[i].begin(); it != vlint[i].end(); it++) {
      cout << *it << ' ';
    }
    cout << endl;
  }
}

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
    adym[u - 1][v - 1] = w;
    adym[v - 1][u - 1] = w;
  }

  vector<list<int> > partition(k, list<int>());
  vector<list<int> > min_partition(k, list<int>());
  partition[0].push_back(0);
  float min_weight = numeric_limits<float>::max();
  kpmp(adym, partition, min_partition, 1, k, 0, 0, min_weight);

  vector<int> node_indexed_partition(n, -1);
  for (int i = 0; i < k; i++) {
    for(list<int>::iterator it = min_partition[i].begin(); it != min_partition[i].end(); it++) {
      node_indexed_partition[*it] = i;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << node_indexed_partition[i] << ' ';
  }
  cout << endl;

  return 0;
}



void kpmp(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight)
{
  if (node == adym.size()) {
    if (total_weight < min_weight) {
      min_partition = partition;
      min_weight = total_weight;
    }
    return;
  }

  for (int i = 0; i <= max_k_used; i++) {
    float added_weight = 0;
    for(list<int>::iterator it = partition[i].begin(); it != partition[i].end(); it++) {
      added_weight += adym[node][*it];
    }
    partition[i].push_back(node);
    kpmp(adym, partition, min_partition, node+1, k, max_k_used, 
        total_weight+added_weight, min_weight);
    partition[i].pop_back();
  }

  if (max_k_used < k-1) {
    // try adding new partition
    partition[max_k_used+1].push_back(node);
    kpmp(adym, partition, min_partition, node+1, k, max_k_used+1, 
        total_weight, min_weight);
    partition[max_k_used+1].pop_back();
  }
}
