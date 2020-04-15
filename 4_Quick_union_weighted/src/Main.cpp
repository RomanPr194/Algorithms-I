#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class QuickUnionUF
{
private:
    std::vector<int> id;
    std::vector<int> sz; //sizes of sub-trees

    int root(int i)
    {
        while(i != this->id[i])
        {
            this->id[i] = this->id[this->id[i]]; //path compression
            i = this->id[i];
        }
        return i;
    }

public:
    QuickUnionUF(const int n)
    {
        for(int i = 0; i < n; i++)
        {
            this->id.push_back(i);
            this->sz.push_back(1);
        }
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
        {
            if(this->sz[i] < this->sz[j])
            {
                this->id[i] = j;
                this->sz[j] += sz[i];
            }
            else
            {
                this->id[j] = i;
                this->sz[i] += sz[j];
            }
        }
        else
            std::cout << "Already connected! \n";
    }

    void show() const
    {   
        std::cout << "id: ";
        for(unsigned int i = 0; i < this->id.size(); i++)
            std::cout << this->id[i] << " ";
        std::cout << std::endl;

        std::cout << "sz: ";
        for(unsigned int i = 0; i < this->sz.size(); i++)
            std::cout << this->sz[i] << " ";
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
    int a;
    int b;
    std::cout << "Type nodes to check connection: \n";
    std::cin >> a >> b;

    if(qu1.isConnected(a, b))
        std::cout << a << " and " << b << " is connected! \n";
    else
        std::cout << a << " and " << b << " NOT connected! \n";
    qu1.show();

    std::cin.get();  //Program waiting for the last symbol
} 