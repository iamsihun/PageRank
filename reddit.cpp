#include "reddit.h"

namespace reddit {

Reddit::~Reddit(){
    if (minDist != NULL) {
        delete[] minDist;
    }
    if (next != NULL) {
        delete[] next;
    }
}

void Reddit::parseData(const std::string& data_file) {
    std::ifstream file(data_file);
    std::string line;
    std::stringstream ss;
    while (getline(file, line)) {  
        ss << line;
        std::string source;
        std::string target;
        ss >> source >> target;
        if (!g_.vertexExists(source)) {
            g_.insertVertex(source);
            g_flipped_.insertVertex(source);
        }
        if (!g_.vertexExists(target)) {
            g_.insertVertex(target);
            g_flipped_.insertVertex(target);
        }
        
        if (!g_.edgeExists(source, target)) {
            g_.insertEdge(source, target);
            g_.setEdgeWeight(source, target, 1); 
            g_flipped_.insertEdge(target, source);
        } 
        
        ss.str(std::string()); // clears the stringstream
    }
    file.close();
}

void Reddit::findConnectedComponents() {
    std::map<Vertex, bool> visited;
    for (auto& vertex : g_.getVertices()) {
        visited[vertex] = false;
    }
    for (auto& vertex : g_.getVertices()) {
        if (!visited[vertex]) {
            std::vector<Vertex> connected;
            DFS(vertex, visited, connected);
            connected_components_.push_back(connected);
        }
    }
}

void Reddit::DFS(const Vertex& visited_vertex, std::map<Vertex, bool>& visited, std::vector<Vertex>& connected) {
    visited[visited_vertex] = true;
    connected.push_back(visited_vertex);
    for (auto& adj : g_.getAdjacent(visited_vertex)) {
        if (!visited[adj]) {
            DFS(adj, visited, connected);
        }
    }
    for (auto& adj : g_flipped_.getAdjacent(visited_vertex)) {
        if (!visited[adj]) {
            DFS(adj, visited, connected);
        }
    }
}

void Reddit::handleDanglingNodes() {
    for (auto& comp : connected_components_) {
        for (auto& vertex : comp) {
            if (g_.getAdjacent(vertex).empty()) {
                for (auto& node : comp) {
                    g_.insertEdge(vertex, node);
                    g_flipped_.insertEdge(node, vertex);
                }
            }
        }
    }
}

void Reddit::pagerank() {
    findConnectedComponents();
    handleDanglingNodes();
    double d = 0.85; // initialize the damping factor
    // initialize the distributions to 1 / # vertices in component
    std::vector<std::map<Vertex, double>> init_distr;
    for (auto& comp : connected_components_) {
        std::map<Vertex, double> init_map;
        std::map<Vertex, double> pagerank_map;
        for (auto& vertex : comp) {
            init_map[vertex] = 1.0 / comp.size();
            pagerank_map[vertex] = 0.0;
        }
        init_distr.push_back(init_map);
        pagerank_distr_.push_back(pagerank_map);
    }

    // perform the pagerank algorithm for each component
    for (unsigned int i = 0; i < connected_components_.size(); i++) {
        for (auto& vertex : connected_components_[i]) {
            for (auto& source : g_flipped_.getAdjacent(vertex)) { // gets all vertices pointing TO vertex
                int num_adj = g_.getAdjacent(source).size();
                pagerank_distr_[i][vertex] += init_distr[i][source] / num_adj;
                // adds the initial probabiliity of each source pointing to vertex divided by
                // the number of vertices that source points to
            }
            // add in the damping factor to deal with dangling nodes
            pagerank_distr_[i][vertex] = ((1 - d) / connected_components_[i].size()) + d * pagerank_distr_[i][vertex];
        }
    }

    // print out the distributions for each component
    for (unsigned int i = 0; i < pagerank_distr_.size(); i++) {
        std::cout << "component: " << i << std::endl;
        for (auto& vertex : pagerank_distr_[i]) {
            std::cout << vertex.first << ": " << vertex.second << std::endl;
        }
    }
}

void Reddit::printData() {
    for (unsigned int i = 0; i < connected_components_.size(); i++) {
        std::cout << i << std::endl;
        for (auto& comp : connected_components_[i]) {
            std::cout << comp << " ";
        }
        std::cout << "\n";
    }
}

void Reddit::printFW() {
    buildShortestPaths();
    int numVertices = (int) g_.getVertices().size();
    for (Vertex i : g_.getVertices()) {
            for (Vertex j : g_.getVertices()) {
                    cout << i << "->" << j << endl;
                    if (minDist[vertextoInt[i]*numVertices+vertextoInt[j]] == MAX_INPUT) {
                        cout << "           no path" << endl;
                    }
                    else cout << "       " << minDist[vertextoInt[i]*numVertices+vertextoInt[j]] << endl;
            }
    }
}

void Reddit::buildShortestPaths() {
    int numVertices = (int)g_.getVertices().size();  //get num of vertices
    minDist = new int[numVertices*numVertices];  //init array to hold shortest distance values for each subreddit pair
    next = new int[numVertices*numVertices];

    //  INITIALIZING minDist & next
    for (int i=0; i < numVertices*numVertices; i++) { 
        minDist[i] = MAX_INPUT;                         //init each dist to infinity according to FW algorithm
        next[i] = -1;                                   //init each value to null (-1 in this case) according to FW algorithm
    }


    //INITIALIZING vertextoInt
    vector<Vertex> vertices = g_.getVertices();  //hold the vertices of graph in 'vertices'
    for(int i=0; i<(int)vertices.size(); i++) {   //map each vertex to an int starting from 0
            vertextoInt[vertices[i]] = i;
    }
    
    //FW ALG 
    for(auto& edge : g_.getEdges()) {    //populate dist with existing weights
            Vertex source = edge.source;
            Vertex dest = edge.dest;
            int u = vertextoInt[source];
            int v = vertextoInt[dest];
            minDist[u*numVertices + v] = edge.getWeight();
            next[u*numVertices + v] = v;
    }

    for(auto& vertex : vertices) {   //set distances to self to 0
            int v = vertextoInt[vertex];
            minDist[v*numVertices+v] = 0;
            next[v*numVertices+v] = v;
    }

    for(int k=0; k<numVertices; k++) {
        for(int i=0; i<numVertices; i++) {
            for(int j=0; j<numVertices; j++) {
                if(minDist[i*numVertices+j]   >   minDist[i*numVertices+k]   +  minDist[k*numVertices+j]) {
                    minDist[i*numVertices+j]   =   minDist[i*numVertices+k]   +   minDist[k*numVertices+j];
                    next[i*numVertices+j]  =  next[i*numVertices+k];
                }
            }
        }
    }

    //for(int i=0; i<numVertices*numVertices; i++) cout << minDist[i] << endl;

/*                 if dist[i][j] > dist[i][k] + dist[k][j] then
                    dist[i][j] ← dist[i][k] + dist[k][j]
                    next[i][j] ← next[i][k] */
}

int Reddit::getshortestDist(const Vertex& source, const Vertex& dest) {
    int numVertices = (int)g_.getVertices().size(); 
    int input_source = vertextoInt[source];
    int input_dest = vertextoInt[dest];
    return minDist[numVertices*input_source + input_dest];
}

void Reddit::findPath(const Vertex& source, const Vertex& dest) {
    int numVertices = (int) g_.getVertices().size(); //number of vertices in graph g_
    int i = 0; 
    int j = 0;
    while (source != g_.getVertices()[i]) {
        if (i == numVertices - 1) break;
        i++;
    }

    while (dest != g_.getVertices()[j]) {
        if (j == numVertices - 1) break;
        j++;
    }

    int u = vertextoInt[g_.getVertices()[i]];
    int v = vertextoInt[g_.getVertices()[j]];
    if (next[u*numVertices+v] == -1) {
        path_.clear();
    }
    while (u != v) {
        u = next[u*numVertices+v];
        path_.push_back(g_.getVertices()[u]);
    }
}

void Reddit::printInputPath(const Vertex& start, const Vertex& dest) {
    path_.clear();
    buildShortestPaths();
    cout << '\n' << '\n' << endl;
    int numVertices = (int) g_.getVertices().size();
    if (minDist[vertextoInt[start]*numVertices+vertextoInt[dest]] == MAX_INPUT) {
        cout << "no path found" << endl;
        cout << '\n' << '\n' << endl;
        return;
    }
    cout << "START:   " << start << " ->" << endl;
    findPath(start, dest);
    int pathLength = path_.size();    
    if (!path_.empty()) {
        for(int i = 0; i < pathLength; i++) {
            if (i == pathLength - 1) {
                cout << "END:     " << path_[i] << endl;
                break;
            } 
            cout << "              " << path_[i] << " ->" << endl;
        }
    } else {
        if (start == dest) {
            cout << "path to itself" << endl;
            return;
        }
        cout << "no path found" << endl;
        return;
    }

    cout<<'\n'<< '\n' <<endl;
    cout << "LENGTH: " << getshortestDist(start, dest) << " subreddits" << endl;

    cout<<'\n'<< '\n' <<endl;
}

const Graph& Reddit::getGraph() {
    return g_;
}

const std::vector<std::vector<Vertex>>& Reddit::getConnectedComponents() {
    return connected_components_;
}

const std::vector<std::map<Vertex, double>>& Reddit::getPagerankDistr() {
    return pagerank_distr_;
}

const vector<Vertex>& Reddit::getPath() {
    return path_;
}
}//EOF