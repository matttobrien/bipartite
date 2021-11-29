#include <iostream>
#include <time.h>
#include <vector>
#include <map>

using namespace std;

bool colorVertex(int color, vector<int> neighbours, vector<int> coloredVertices) {
  for (size_t i = 0; i < neighbours.size(); ++i) {
    // check if neighbour has already been colored the same color
    if (coloredVertices[neighbours[i]-1] == color) {
      return false;
    }
  }
  return true;
}

bool bipartite(vector<int> vertices, map<int, vector<int> > neighbours) {
  vector<int> coloredVertices(vertices.size(), -1);
  int colors[2] = {1, 2};
  // loop through verticies
  for (size_t i = 0; i < vertices.size(); ++i) {
    if (i == 0) {
      coloredVertices[0] = 1;
    } else {
      int color = 1, vertex = vertices[i];
      // check if neighbours have been colored
      vector<int> vNeighbours = neighbours.find(vertex)->second;
      for (size_t j = 0; j < 2; j++) {
        // if color is valid
        if (colorVertex(color, vNeighbours, coloredVertices)) {
          break;
        } else {
          // else increment color
          color++;
        }
      }
      // valid colors are 1 & 2.. if 3 then graph is not bipartite
      if (color > 2) return false;
      coloredVertices[i] = color;
    } 
  }
  return true;
}

int main(int argc, char **argv) {
  string filename(argv[1]);

  // file pointers
  FILE* matrix = fopen(filename.c_str(), "r");
  if (matrix == NULL) {
    exit(EXIT_FAILURE);
  }

  // init vertices vector
  vector<int> vertices;
  // init neighbours map
  map<int, vector<int> > neighbours;

  vector<int> neighbour;
  int c, i = 0, j = 0, row = 1, column = 1;
  while ((c = fgetc(matrix)) != EOF)  {
    if (c == '\n') {
      // insert neighbours into map
      neighbours.insert(pair<int, vector<int> >(row, neighbour));
      // push vertex into vertices
      vertices.push_back(row);
      neighbour.clear();
      row++;
      column = 1;
    } else if (c == '0') {
      column++;
    } else {
      // edge exists
      neighbour.push_back(column);
      column++;
    }
  }
  // start timer
  clock_t t;
  t = clock();
  if (bipartite(vertices, neighbours)) {
    cout << "Is biapartite" << endl;
  } else {
    cout << "Is not biapartite" << endl;
  }
  t = clock() - t;
  cout << "It took me " << ((float)t/CLOCKS_PER_SEC*1000.00) << " ms." << endl;
}