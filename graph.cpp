#include "graph.h"

map<int, vector<int>> vertex;
int V_source, V_destiny, interactions;
vector<vector<int>> cliquesmax;

int readGraph(string nameFile)
{
    fstream FileReader;

    FileReader.open(nameFile.c_str());

    if (FileReader.is_open())
    {
        FileReader >> V_source >> V_destiny >> interactions;
        for (int i = 0; i < interactions; i++)
        {
            int source, destiny;
            FileReader >> source >> destiny;

            auto iterator = find(vertex[source].begin(), vertex[source].end(), destiny);

            if (source == destiny)
            {
                vertex[source].push_back(destiny);
            }
            else if (iterator == vertex[source].end())
            {
                vertex[source].push_back(destiny);
                vertex[destiny].push_back(source);
            }
        }
    }
    else
    {
        cout << "Erro na Leitura do Arquivo" << endl;
        FileReader.close();
        return -1;
    }

    FileReader.close();
    return V_source;
}

void printDegreeGraph()
{
    cout << "Vertices e seus Graus: " << endl;

    for (int i = 1; i <= vertex.size(); i++)
    {
        cout << "Vertice: " << i;
        cout << "  Grau: " << vertex[i].size() << endl;
    }
    cout << endl;
}

double coeficienteAglomeracao(int vertexIndex)
{
    double coefficient;
    double triangle = 0;
    vector<int> v = vertex[vertexIndex];
    int sizeNeighbors = v.size();

    for (int i = 0; i < sizeNeighbors; i++)
    {
        int first = v[i];

        for (int j = 0; j < sizeNeighbors; j++)
        {
            int second = v[j];

            for (int k = 0; k < vertex[first].size(); k++)
            {
                if (second == vertex[first][k])
                {
                    triangle += 0.5;
                }
            }
        }
    }

    if (sizeNeighbors > 1)
    {
        coefficient = (2 * triangle) / (sizeNeighbors * (sizeNeighbors - 1));
    }
    else
    {
        coefficient = 0.0;
    }

    return coefficient;
}

double averageCoefficient()
{
    double coefficient = 0.0;

    for (int i = 1; i <= V_source; i++)
    {
        coefficient += coeficienteAglomeracao(i);
    }

    return (coefficient / V_source);
}

void printCoefficient()
{
    cout << "Vertices e seus Coeficientes de Aglomeracao: " << endl;
    for (int i = 1; i <= V_source; i++)
    {
        cout << "Vertice -> " << i << " Coeficiente de Aglomeracao -> " << coeficienteAglomeracao(i) << endl;
    }
    cout << endl;
    cout << "Media dos Coeficientes: " << averageCoefficient() << endl;
}

void bronKerbosch(vector<int> r, vector<int> p, vector<int> x)
{
    //clique maximal
    if (p.empty() && x.empty())
    {
        cliquesmax.push_back(r);
    }
    //backtracking
    if (p.empty() && !(x.empty()))
    {
        return;
    }
    // -------------------------------------------------------------------------
    // Map auxiliar da lista do P e do X
    map<int, bool> pmem, xmem;

    for (int i = 0; i <= vertex.size(); i++)
    {
        pmem[i] = false;
        xmem[i] = false;
    }
    for (int i = 0; i < p.size(); i++)
    {
        pmem[p[i]] = true;
    }
    for (int i = 0; i < x.size(); i++)
    {
        xmem[x[i]] = true;
    }
    // -------------------------------------------------------------------------

    for (int i = 0; i < p.size(); i++)
    {
        int pivot = p[i];
        r.push_back(pivot);

        vector<int> pprox, xprox;

        for (int neighborIndex = 0; neighborIndex < vertex[pivot].size(); neighborIndex++)
        {
            if (pmem[vertex[pivot][neighborIndex]])
            {
                pprox.push_back(vertex[pivot][neighborIndex]);
            }
            if (xmem[vertex[pivot][neighborIndex]])
            {
                xprox.push_back(vertex[pivot][neighborIndex]);
            }
        }

        bronKerbosch(r, pprox, xprox);

        r.pop_back();

        pmem[pivot] = false;
        xmem[pivot] = true;
    }
}

void printMaximalCliques()
{
    vector<int> r;
    vector<int> p;
    vector<int> x;

    for (int i = 1; i <= vertex.size(); i++)
    {
        p.push_back(i);
    }

    bronKerbosch(r, p, x);

    cout << "Lista dos cliques maximais: " << endl;

    for (int i = 0; i < cliquesmax.size(); i++)
    {
        cout << i + 1 << " - ";
        for (int j = 0; j < cliquesmax[i].size(); j++)
        {
            cout << cliquesmax[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}