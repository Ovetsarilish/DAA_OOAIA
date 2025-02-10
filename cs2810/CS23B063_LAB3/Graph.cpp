#include <bits/stdc++.h>

using namespace std;

class Graph{
    public :
        vector<vector<int>> adj;

        Graph(){

        }

        Graph(int n){
            for(int i = 0; i < n; i++){
                vector<int> v(n, 0);
                this->adj.push_back(v);
            }
        }

        void addEdge(int u, int v){
            if(this->adj[u][v] == 0 && this->adj[v][u] == 0){
                this->adj[u][v] = 1; 
                this->adj[v][u] = 1;
            }
        }

        void removeEdge(int u, int v){
            if(this->adj[u][v] == 1 && this->adj[v][u] == 1){
                this->adj[u][v] = 0; 
                this->adj[v][u] = 0;
            }
        }

        Graph operator +(Graph& g2){
            Graph retG(max((int)adj.size(), (int)g2.adj.size()));

            for(int i = 0; i < (int)adj.size(); i++){
                for(int j = 0; j < (int)adj[i].size(); j++){
                    if(this->adj[i][j] == 1){
                        retG.addEdge(i, j);
                    }
                }
            }

            for(int i = 0; i < (int)g2.adj.size(); i++){
                for(int j = 0; j < (int)g2.adj[i].size(); j++){
                    if(g2.adj[i][j] == 1 && g2.adj[j][i] == 1){
                        retG.addEdge(i, j);
                    }
                }
            }
            return retG;
        }

        Graph operator -(Graph& g2){
            Graph retG(max((int)this->adj.size(), (int)g2.adj.size()));

            for(int i = 0; i < min((int)this->adj.size(), (int)g2.adj.size()); i++){
                for(int j = 0; j < min((int)this->adj.size(), (int)g2.adj.size()); j++){
                    if(this->adj[i][j] == 1){
                        retG.addEdge(i, j);
                    }
                }
            }

            for(int i = 0; i < min((int)this->adj.size(), (int)g2.adj.size()); i++){
                for(int j = 0; j < min((int)this->adj.size(), (int)g2.adj.size()); j++){
                    if(!(retG.adj[i][j] == 1 && g2.adj[i][j] == 1)){
                        retG.removeEdge(i, j);
                    }
                }
            }

            return retG;
        }

        Graph operator !(){
            Graph retG((int)this->adj.size());

            for(int i = 0; i < (int)this->adj.size(); i++){
                for(int j = 0; j < (int)this->adj[i].size(); j++){
                    if(this->adj[i][j] == 0 && i != j){
                        retG.addEdge(i, j);
                    }
                }
            }

            return retG;
        }

        bool isReachable(int u, int v){
            if(u == v){
                return true;
            }
            vector<bool> vis(this->adj.size(), false);
            queue<int> q;
            vis[u] = true;
            q.push(u);

            while(!q.empty()){
                int t = q.front();
                q.pop();

                
                for(int i = 0; i < (int)this->adj.size(); i++){
                    if(this->adj[t][i] == 1 && i == v){
                        return true;
                    }

                    if(this->adj[t][i] == 1 && !vis[i]){
                        vis[i] = true;
                        q.push(i);
                    }
                }
            }

            return false;
        }

        friend std::ostream& operator<<(
            std::ostream& stream, Graph& g
        );

        friend std::istream& operator >>(
            std::istream& stream, Graph& g
        );
};

std::ostream& operator <<(std::ostream& stream, Graph& g){
    for(int i = 0; i < (int)g.adj.size(); i++){
        stream << "Vertex " << i << ": ";
        for(int j = 0; j < (int)g.adj[i].size(); j++){
            if(g.adj[i][j] == 1 && g.adj[j][i] == 1){
                stream << j << " ";
            }
        }
        stream << "\n";
    }

    return stream;
}

std::istream& operator >>(std::istream& stream, Graph& g){
    string s;
    stream >> s;
    int n, m;
    stream >> n >> m;
    g = Graph(n);
    for(int i = 0; i < m; i++){
        int u, v;
        stream >> u >> v;
        g.addEdge(u, v);
    }
    return stream;
}

int main(){
    Graph g;
    cin >> g;
    while(true){
        string s;
        cin >> s;
        if(s == "printGraph"){
            cout << g;
        }else if(s == "isReachable"){
            int u, v;
            cin >> u >> v;
            bool ok = g.isReachable(u, v);
            cout << (ok ? "Yes\n" : "No\n");
        }else if(s == "complement"){
            g = !g;
        }else if(s == "remove_edge"){
            int u, v;
            cin >> u >> v;
            g.removeEdge(u, v);
        }else if(s == "add_edge"){
            int u, v;
            cin >> u >> v;
            g.addEdge(u, v);
        }else if(s == "union"){
            Graph g2;
            cin >> g2;
            g = g + g2;
        }else if(s == "intersection"){
            Graph g2;
            cin >> g2;
            g = g - g2;
        }else if(s == "end"){
            break;
        }
    }
}