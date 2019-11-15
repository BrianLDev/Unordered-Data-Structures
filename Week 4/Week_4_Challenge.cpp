
#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>

// Note: You must not change the definition of DisjointSets here.
class DisjointSets {
public:
  int s[256];
  int distance[256];

  DisjointSets() {
    for (int i = 0; i < 256; i++) s[i] = distance[i] = -1;
  }

  int find(int i) { return s[i] < 0 ? i : find(s[i]); }
  
  void dsunion(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
      s[root_i] = root_j;
      // std::cout << "-- s[" << root_i << "] = " << root_j << std::endl;
    }
  }
  
  void bfs(int i, int n, int m, int edges[][2]);
};


/* Below are two conditions that need to be programmed
 * to allow this procedure to perform a breadth first
 * traversal and mark the edge distance of the graph's
 * vertices from vertex i.
 */

void DisjointSets::bfs(int i, int n, int m, int edges[][2]) {
  
  // BL NOTE: this code is pissing me off, just make an array of explored points
  std::unordered_set<int> explored;
  std::queue<int> frontier;
 
  distance[i] = 0;
  explored.insert(i);
  std::cout << "<^^> explored: " << i << std::endl;

  // no need to iterate more than m times
  // but loop terminates when no new
  // vertices added to the frontier.
  
  for (int d = 1; d < m; d++) {
    std::cout << "##### DISTANCE LOOP " << d << std::endl;
    
    // f is the index of the first
    // vertex added to the frontier
    int f = -1;

    // rooti is the name of the set
    // holding all of the vertices
    // that have already been assigned
    // distances
    // BL NOTE: rooti is not a set but an int and will always be 3. Ignore it.
    
    // int rooti = find(i);  

    // loop through all of the edges
    // (this could be much more efficient
    // if an adjacency list was used
    // instead of a simple edge list)
    
    for (int j = 0; j < m; j++) {

      // root0 and root1 are the names of
      // the sets that the edge's two
      // vertices belong to
      
      int p0 = edges[j][0];
      int p1 = edges[j][1];

      int root0 = find(p0);
      int root1 = find(p1);
      
      std::cout << "*** Looking at pair " << j << ": {" << p0 << "," << p1 << "}" << std::endl;
      

      if ( explored.count(p0)>0 && explored.count(p1)==0 ) {
        
        frontier.push(p1);
        std::cout << "<<v>> frontier: " << p1 << std::endl;

        // add the [1] vertex of the edge
        // to the frontier, either by
        // setting f to that vertex if it
        // is the first frontier vertex
        // found so far, or by unioning
        // it with the f vertex that was
        // already found.
        
        if (f == -1)
          f = p1;
        else {
          dsunion(f,p1);
        }

        // set the distance of this frontier
        // vertex to d
        distance[p1] = d;
        std::cout << "~~~~ Adding dist for: " << p1 << " = " << d << std::endl;
        
      } else if ( explored.count(p0)==0 && explored.count(p1)>0 ) {
        
        frontier.push(p0);
        std::cout << "<<v>> frontier: " << p0 << std::endl;
        
        if (f == -1)
          f = p0;
        else
          dsunion(f,p0);
          
        distance[p0] = d;
        std::cout << "~~~~ Adding dist for: " << p0 << " = " << d << std::endl;
      }
    }
    
    while (frontier.size()>0) {
      int x = frontier.front();
      explored.insert(x);
      std::cout << "<^^> explored: " << x << std::endl;
      frontier.pop();
    }
    
    // if no vertices added to the frontier
    // then we have run out of vertices and
    // are done, otherwise union the frontier
    // set with the set of vertices that have
    // already been processed.
    
    if (f == -1)
      break;
    else
      dsunion(f,i);
  }
}

int main() {

  int edges[8][2] = {{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,3}};  

  DisjointSets d;

  d.bfs(3,8,8,edges);

  for (int i = 0; i < 8; i++)
    std::cout << "Distance to vertex " << i
              << " is " << d.distance[i] << std::endl;

// Should print
// Distance to vertex 0 is 3
// Distance to vertex 1 is 2
// Distance to vertex 2 is 1
// Distance to vertex 3 is 0
// Distance to vertex 4 is 1
// Distance to vertex 5 is 2
// Distance to vertex 6 is 2
// Distance to vertex 7 is 1


  return 0;
}
