#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class QuickUnionUF
{
private:
    std::vector<int> id;

    int root(int i)
    {
        while(i != this->id[i])
            i = this->id[i];
        return i;
    }

public:
    QuickUnionUF(const int n)
    {
        for(int i = 0; i < n; i++)
            this->id.push_back(i);
        std::cout << "Created QuickUnionUF object with " << n << " elements!\n";
    }

    bool isConnected(int p, int q)
    {
        return root(p) == root(q);
    }

    void connect(int p, int q)
    {
        int i = root(p);
        int j = root(q);

        if(!isConnected(p, q))
            this->id[i] = j;
        else
            std::cout << "Already connected! \n";
    }

    void show() const
    {
        for(unsigned int i = 0; i < this->id.size(); i++)
            std::cout << this->id[i] << " ";
        std::cout << std::endl;
    }
};

int main()
{
    int N;
    std::cout << "Enter number of points: \n";
    std::cin >> N;

    QuickUnionUF qu1(N);
    qu1.show();

    for(int i = 0; i < N; i++)
    {
        int p;
        int q;
        std::cout << i <<": Enter child and parrent nodes \n";
        std::cin >> p >> q;
        qu1.connect(p, q);
        qu1.show();
    }

    std::cin.get();  //Program waiting for the last symbol
} 