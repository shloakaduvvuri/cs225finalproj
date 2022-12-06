#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <climits>

using namespace std;

int main() {
    int index = 0;
    //int sum = 0;
    int key;
    int x;
    ifstream inFile;
    inFile.open("roadNet-TX.txt");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    map<int, vector<int>> graph_;
    while (inFile >> x) {
        //std::cout << x << std::endl;
        if (index % 2 == 0) {
            key = x;
            if (graph_.find(key) == graph_.end()) {
                vector<int> vals;
                graph_.insert(make_pair(key, vals));
            }
        } else if (index % 2 == 1) {
          graph_[key].push_back(x);   
        }
        index++;
    }
    inFile.close();
    // std::cout << graph_.size() << std::endl;
    // std::cout << graph_.at(1).size() << std::endl;

    // for (auto node_relation : graph_) {
    //     sort(node_relation.second.begin(), node_relation.second.end());
    // }
    // for (auto node_relation : graph_) {
    // std::cout << "City " << node_relation.first << " Connects To: " << std::endl;
    // std::cout << "{ ";
    //     for (int neighbor : node_relation.second) {
    //         std::cout << neighbor << " ";
    //     }
    //      std::cout << "}" << std::endl;
    // }
    // std::cout << "}" << std::endl;

    //BFS TRAVERSAL
}

// Structure to represent a min heap node
struct MinHeapNode
{
    int  v;
    int dist;
};
 
// Structure to represent a min heap
struct MinHeap
{
     
    // Number of heap nodes present currently
    int size;    
   
    // Capacity of min heap
    int capacity; 
   
    // This is needed for decreaseKey()
    int *pos;   
    struct MinHeapNode **array;
};
 
// A utility function to create a
// new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v,
                                 int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*)
      malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*)
      malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(
            capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**)
                 malloc(capacity *
       sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap,
                                  int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist <
         minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist <
         minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode =
             minHeap->array[smallest];
        MinHeapNode *idxNode =
                 minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest],
                         &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if
// the given minHeap is empty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract
// minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap*
                                   minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root =
                   minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode =
         minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasekey dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(struct MinHeap* minHeap,
                         int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete
    // tree is not heapified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist <
           minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =
                                      (i-1)/2;
        minHeap->pos[minHeap->array[
                             (i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], 
                 &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// The main function that calculates
// distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(map<int, vector<int>> graph, int src)
{
     
    // Get the number of vertices in graph
    int V = graph.size();
   
    // dist values used to pick
    // minimum weight edge in cut
    vector<int> dist(V);
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v,
                                      dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] =
          newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the following loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode* minHeapNode =
                     extractMin(minHeap);
       
        // Store the extracted vertex number
        int u = minHeapNode->v;
 
        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        struct AdjListNode* pCrawl =
                     graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
 
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            if (isInMinHeap(minHeap, v) &&
                      dist[u] != INT_MAX &&
              pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
 
                // update distance
                // value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    // print the calculated shortest distances
    printArr(dist, V);
}