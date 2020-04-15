#include <iostream>
#include <fstream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class UF
{
private:
    int n;
    std::vector<std::vector<int>> sets;

public:
    UF(int n)
    {
        std::cout << "Created UnionFind object with " << n << " elements!" << std::endl;
        this->n = n;
        this->sets.reserve(n);
        for(int i = 0; i < n; i++)
        {
            this->sets.push_back({i});
        }
    }

    void showSets() const
    {
        for(auto set : sets)
        {
            std::cout << "{ ";
            for(auto e : set)
                std::cout << e << " ";
            std::cout << "} ";
        }
        std::cout << std::endl;
    }

    int inSetN(int n)
    {
        int index = -1;
        for(uint j = 0; j < this->sets.size(); j++)
            for(uint i = 0; i < this->sets[j].size(); i++)
                if(this->sets[j][i] == n)
                    index = j;
        return index;
    }

    void connect(int p, int q)
    {
        int find_p_inSetN = this->inSetN(p);
        int find_q_inSetN = this->inSetN(q);

        if(find_p_inSetN == -1 || find_q_inSetN == -1)
            std::cout <<"At least one point is not exist! " << p << " or " << q << std::endl;
        else
            if(!isConnected(p, q))
            {
                for(auto e : this->sets[find_q_inSetN])
                    this->sets[find_p_inSetN].push_back(e);
                this->sets.erase(this->sets.begin() + find_q_inSetN);
            }
    }

    bool isConnected(int p, int q)
    {
        int find_p_inSetN = this->inSetN(p);
        int find_q_inSetN = this->inSetN(q);

        if(find_p_inSetN == find_q_inSetN)
        {
            std::cout <<"Already connected nodes " << p << " and " << q << std::endl;
            return true;
        }
        else return false;
    }
};

int main()
{
    int N;
    std::cout << "Enter number of points: \n";
    std::cin >> N;

    UF uf1(N);
    uf1.showSets();

    for(int i = 0; i < N; i++)
    {
        int p;
        int q;
        std::cout << i <<": Enter two connected nodes \n";
        std::cin >> p >> q;
        if(!uf1.isConnected(p, q))
        {
            uf1.connect(p, q);
            uf1.showSets();
        }
    }

    std::cin.get();  //Program waiting for the last symbol
} 