#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class QuickFindUF
{
private:
    std::vector<int> id;

public:
    QuickFindUF(const int n)
    {
        for(int i = 0; i < n; i++)
            this->id.push_back(i);
        std::cout << "Created QuickFindUF object with " << n << " elements!\n";
    }

    bool isConnected(int p, int q)
    {
        return this->id[p] == this->id[q];
    }

    void connect(int p, int q)
    {
        int pid = this->id[p];
        int qid = this->id[q];

        if(!isConnected(p, q))
        {
            for(unsigned int i = 0; i < this->id.size(); i++)
                if(this->id[i] == pid) this->id[i] = qid;
        }
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

    QuickFindUF qf1(N);
    qf1.show();

    for(int i = 0; i < N; i++)
    {
        int p;
        int q;
        std::cout << i <<": Enter two connected nodes \n";
        std::cin >> p >> q;
        qf1.connect(p, q);
        qf1.show();
    }

    std::cin.get();  //Program waiting for the last symbol
} 