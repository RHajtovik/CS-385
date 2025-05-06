/*******************************************************************************
 * Name          : shortestpaths.cpp
 * Author        : Ryan Hajtovik
 * Version       : 1.0
 * Date          : May 6, 2025
 * Description   : Implements Floyd's algorithm to compute the shortest paths.
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <climits>
#include <cctype>
#include <algorithm>
using namespace std;

const long INF = LONG_MAX / 2; // Avoid overflow when adding
int num_vertices;

// Displays the matrix on the screen formatted as a table.
void display_table(const vector<vector<long>> &matrix, const string &label, bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (matrix[i][j] < INF && matrix[i][j] > max_val) {
                max_val = matrix[i][j];
            }
        }
    }

    int cell_width = use_letters ? 1 : to_string(max((long)num_vertices, max_val)).length();
    cout << " ";
    for (int j = 0; j < num_vertices; j++) {
        cout << " " << setw(cell_width) << static_cast<char>('A' + j);
    }
    cout << endl;

    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>('A' + i);
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(cell_width);
            if (matrix[i][j] == INF) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>('A' + matrix[i][j]);
            } else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void display_intermediate_table(const vector<vector<int>> &matrix, const string &label) {
    cout << label << "\n ";
    for (int j = 0; j < num_vertices; j++) {
        cout << " " << static_cast<char>('A' + j);
    }
    cout << endl;

    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>('A' + i);
        for (int j = 0; j < num_vertices; j++) {
            cout << " ";
            if (matrix[i][j] == -1) {
                cout << "-";
            } else {
                cout << static_cast<char>('A' + matrix[i][j]);
            }
        }
        cout << endl;
    }
    cout << endl;
}

void build_path(int i, int j, const vector<vector<int>> &intermediate, vector<int> &path) {
    if (intermediate[i][j] == -1) return;

    build_path(i, intermediate[i][j], intermediate, path);
    path.push_back(intermediate[i][j]);
    build_path(intermediate[i][j], j, intermediate, path);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./shortestpaths <filename>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    string line;
    int line_num = 0;
    if (!getline(infile, line)) {
        cerr << "Error: Invalid number of vertices '' on line 1." << endl;
        return 1;
    }
    ++line_num;

    istringstream ss(line);
    if (!(ss >> num_vertices) || num_vertices < 1 || num_vertices > 26) {
        cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
        return 1;
    }

    vector<vector<long>> dist(num_vertices, vector<long>(num_vertices, INF));
    vector<vector<long>> path_len(num_vertices, vector<long>(num_vertices, INF));
    vector<vector<int>> intermediate(num_vertices, vector<int>(num_vertices, -1));

    for (int i = 0; i < num_vertices; ++i) {
        dist[i][i] = 0;
    }

    while (getline(infile, line)) {
        ++line_num;
        istringstream edge_ss(line);
        string start_vertex_str, end_vertex_str, weight_str;
        long weight;
        char extra;

        if (!(edge_ss >> start_vertex_str >> end_vertex_str >> weight_str)) {
            cerr << "Error: Invalid edge data '" << line << "' on line " << line_num << "." << endl;
            return 1;
        }
        
        if (!(istringstream(weight_str) >> weight) || (istringstream(weight_str) >> weight >> extra) || weight <= 0) {
            cerr << "Error: Invalid edge weight '" << weight_str << "' on line " << line_num << "." << endl;
            return 1;
        }
        
        if (start_vertex_str.size() != 1 || !isupper(start_vertex_str[0]) || start_vertex_str[0] - 'A' >= num_vertices) {
            cerr << "Error: Starting vertex '" << start_vertex_str << "' on line " << line_num << " is not among valid values A-" << (char)('A' + num_vertices - 1) << "." << endl;
            return 1;
        }

        if (end_vertex_str.size() != 1 || !isupper(end_vertex_str[0]) || end_vertex_str[0] - 'A' >= num_vertices) {
            cerr << "Error: Ending vertex '" << end_vertex_str << "' on line " << line_num << " is not among valid values A-" << (char)('A' + num_vertices - 1) << "." << endl;
            return 1;
        }

        int u = start_vertex_str[0] - 'A', v = end_vertex_str[0] - 'A';
        dist[u][v] = weight;
    }

    path_len = dist;
    for (int k = 0; k < num_vertices; ++k) {
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = 0; j < num_vertices; ++j) {
                if (path_len[i][k] < INF && path_len[k][j] < INF && path_len[i][k] + path_len[k][j] < path_len[i][j]) {
                    path_len[i][j] = path_len[i][k] + path_len[k][j];
                    intermediate[i][j] = k;
                }
            }
        }
    }

    display_table(dist, "Distance matrix:");
    display_table(path_len, "Path lengths:");
    display_intermediate_table(intermediate, "Intermediate vertices:");

    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            cout << (char)('A' + i) << " -> " << (char)('A' + j) << ", distance: ";
            if (path_len[i][j] >= INF) {
                cout << "infinity, path: none" << endl;
            } else {
                vector<int> path;
                build_path(i, j, intermediate, path);

                cout << path_len[i][j] << ", path: " << (char)('A' + i);
                for (int v : path) {
                    cout << " -> " << (char)('A' + v);
                }
                if (i != j) {
                    cout << " -> " << (char)('A' + j);
                }
                cout << endl;
            }
        }
    }

    return 0;
}