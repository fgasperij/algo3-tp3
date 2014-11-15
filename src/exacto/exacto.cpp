#include <iostream>
#include <vector>
#include <list>

using namespace std;

void kpmp_sin_podas(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight);
void kpmp_solo_k_subconjuntos(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight);
void kpmp_peso_minimo(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight);
void kpmp_poda_pesada(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight);
void kpmp_poda_total(vector<vector<float> > &adym, vector<list<int> > &partition, 
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
    adym[u][v] = w;
    adym[v][u] = w;
  }

  vector<list<int> > partition(k, list<int>());
  vector<list<int> > min_partition(k, list<int>());
  partition[0].push_back(0);
  float min_weight = numeric_limits<float>::max();
  //kpmp_sin_podas(adym, partition, min_partition, 1, k, 0, 0, min_weight);
  //kpmp_solo_k_subconjuntos(adym, partition, min_partition, 1, k, 0, 0, min_weight);
  //kpmp_peso_minimo(adym, partition, min_partition, 1, k, 0, 0, min_weight);
  //kpmp_poda_pesada(adym, partition, min_partition, 1, k, 0, 0, min_weight);
  kpmp_poda_total(adym, partition, min_partition, 1, k, 0, 0, min_weight);

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

int weight_in_subset(int node, const list<int> &subset, const vector<vector<float> > &adym)
{
  int weight = 0; 
  for(list<int>::const_iterator it = subset.begin(); it != subset.end(); it++) {
    weight += adym[node][*it];
  }

  return weight;
}


void kpmp_sin_podas(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight)
{
  // check if has added all nodes
  if (node == adym.size()) {
    if (total_weight < min_weight && max_k_used < k) {
      min_partition = partition;
      min_weight = total_weight;
    }
    return;
  }

  // try adding it to every non-empty subset
  for (int i = 0; i <= max_k_used; i++) {
    float added_weight = weight_in_subset(node, partition[i], adym);
    partition[i].push_back(node);
    kpmp_sin_podas(adym, partition, min_partition, node+1, k, max_k_used, 
        total_weight+added_weight, min_weight);
    partition[i].pop_back();
  }
  // try adding new partition
  partition[max_k_used+1].push_back(node);
  kpmp_sin_podas(adym, partition, min_partition, node+1, k, max_k_used+1, 
      total_weight, min_weight);
  partition[max_k_used+1].pop_back();
}

void kpmp_peso_minimo(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight)
{
  // check if has added all nodes
  if (node == adym.size()) {
    if (total_weight < min_weight && max_k_used < k) {
      min_partition = partition;
      min_weight = total_weight;
    }
    return;
  }

  // try adding it to every non-empty subset
  for (int i = 0; i <= max_k_used; i++) {
    float added_weight = weight_in_subset(node, partition[i], adym);
    if (total_weight+added_weight < min_weight) {
      partition[i].push_back(node);
      kpmp_peso_minimo(adym, partition, min_partition, node+1, k, max_k_used, 
          total_weight+added_weight, min_weight);
      partition[i].pop_back();
    }
  }
  // try adding new partition
  partition[max_k_used+1].push_back(node);
  kpmp_peso_minimo(adym, partition, min_partition, node+1, k, max_k_used+1, 
      total_weight, min_weight);
  partition[max_k_used+1].pop_back();
}

void kpmp_solo_k_subconjuntos(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight)
{
  // check if has added all nodes
  if (node == adym.size()) {
    if (total_weight < min_weight) {
      min_partition = partition;
      min_weight = total_weight;
    }
    return;
  }
  // because max_k_used starts at 0
  if (adym.size()-node == (k-1)-max_k_used) {
    for (int i = 0; i < (k-1)-max_k_used; ++i) {
      partition[max_k_used+i+1].push_back(node+i);
    }
    kpmp_solo_k_subconjuntos(adym, partition, min_partition, adym.size(), k, k-1, 
        total_weight, min_weight);
    return;
  }

  // try adding it to every non-empty subset
  for (int i = 0; i <= max_k_used; i++) {
    float added_weight = weight_in_subset(node, partition[i], adym);
    partition[i].push_back(node);
    kpmp_solo_k_subconjuntos(adym, partition, min_partition, node+1, k, max_k_used, 
        total_weight+added_weight, min_weight);
    partition[i].pop_back();
  }

  if (max_k_used < k-1) {
    // try adding new partition
    partition[max_k_used+1].push_back(node);
    kpmp_solo_k_subconjuntos(adym, partition, min_partition, node+1, k, max_k_used+1, 
        total_weight, min_weight);
    partition[max_k_used+1].pop_back();
  }
}

void kpmp_poda_pesada(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight)
{
  // check if has added all nodes
  if (node == adym.size()) {
    if (total_weight < min_weight) {
      min_partition = partition;
      min_weight = total_weight;
    }
    return;
  }
  // because max_k_used starts at 0
  if (adym.size()-node == (k-1)-max_k_used) {
    for (int i = 0; i < (k-1)-max_k_used; ++i) {
      partition[max_k_used+i+1].push_back(node+i);
    }
    kpmp_poda_pesada(adym, partition, min_partition, adym.size(), k, k-1, 
        total_weight, min_weight);
    return;
  }

  // poda pesada
  if (max_k_used == k-1) {
    int min_weight_of_adding_rest = 0;
    for (int i = node; i < adym.size(); i++) {
      float min_weight_in_subset = numeric_limits<float>::max();
      for (int j = 0; j < k; j++) {
        float current_weight = weight_in_subset(i, partition[j], adym);
        if (current_weight < min_weight_in_subset) {
          min_weight_in_subset = current_weight;
        }
      }
      min_weight_of_adding_rest += min_weight_in_subset;
    }

    if (min_weight_of_adding_rest+total_weight >= min_weight) {
      return;
    }
  }

  // try adding it to every non-empty subset
  for (int i = 0; i <= max_k_used; i++) {
    float added_weight = weight_in_subset(node, partition[i], adym);
    partition[i].push_back(node);
    kpmp_poda_pesada(adym, partition, min_partition, node+1, k, max_k_used, 
        total_weight+added_weight, min_weight);
    partition[i].pop_back();
  }

  if (max_k_used < k-1) {
    // try adding new partition
    partition[max_k_used+1].push_back(node);
    kpmp_poda_pesada(adym, partition, min_partition, node+1, k, max_k_used+1, 
        total_weight, min_weight);
    partition[max_k_used+1].pop_back();
  }
}

void kpmp_poda_total(vector<vector<float> > &adym, vector<list<int> > &partition, 
    vector<list<int> > &min_partition, int node, int k, int max_k_used, 
    float total_weight, float &min_weight)
{
  // check if has added all nodes
  if (node == adym.size()) {
    if (total_weight < min_weight) {
      min_partition = partition;
      min_weight = total_weight;
    }
    return;
  }
  // because max_k_used starts at 0
  if (adym.size()-node == (k-1)-max_k_used) {
    for (int i = 0; i < (k-1)-max_k_used; ++i) {
      partition[max_k_used+i+1].push_back(node+i);
    }
    kpmp_poda_pesada(adym, partition, min_partition, adym.size(), k, k-1, 
        total_weight, min_weight);
    return;
  }

  // poda pesada
  if (max_k_used == k-1) {
    int min_weight_of_adding_rest = 0;
    for (int i = node; i < adym.size(); i++) {
      float min_weight_in_subset = numeric_limits<float>::max();
      for (int j = 0; j < k; j++) {
        float current_weight = weight_in_subset(i, partition[j], adym);
        if (current_weight < min_weight_in_subset) {
          min_weight_in_subset = current_weight;
        }
      }
      min_weight_of_adding_rest += min_weight_in_subset;
    }

    if (min_weight_of_adding_rest+total_weight >= min_weight) {
      return;
    }
  }

  // try adding it to every non-empty subset
  for (int i = 0; i <= max_k_used; i++) {
    float added_weight = weight_in_subset(node, partition[i], adym);
    if (total_weight+added_weight < min_weight) {
      partition[i].push_back(node);
      kpmp_peso_minimo(adym, partition, min_partition, node+1, k, max_k_used, 
          total_weight+added_weight, min_weight);
      partition[i].pop_back();
    }
  }

  if (max_k_used < k-1) {
    // try adding new partition
    partition[max_k_used+1].push_back(node);
    kpmp_poda_pesada(adym, partition, min_partition, node+1, k, max_k_used+1, 
        total_weight, min_weight);
    partition[max_k_used+1].pop_back();
  }
}
