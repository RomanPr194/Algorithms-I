#include <iostream>
#include <vector>
#include <string>
#include <time.h> // for random seed!
#include <algorithm> // for 

#define LOG(x) std::cout << x << std::endl;

class QuickUnionUF
{
private:
    std::vector<int> id;
    std::vector<int> sz; //sizes of sub-trees

    int root(int& i)
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

    virtual void connect(int p, int q)
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

    int getValAt(int i) const
    {
        return this->id[i];
    }

    int size() const
    {
        return this->id.size();
    }
};

class Field_QUUF: public QuickUnionUF
{
private:
    int m_row; //rows
    int m_col; //columns
public:
    Field_QUUF(const int& i, const int& j)
        : QuickUnionUF(i*j), m_row(i), m_col(j)
    {}

    void connect(int p, int q) override
    {
        if(isNeighbor(p, q))
        {
            QuickUnionUF::connect(p, q);
        }
        else
            std::cout << "Those nodes are not a neighbors! \n";
    }

    void connectAll()
    {
        for(int j = 0; j < m_row; j++)
            for(int i = 1; i <= m_col; i++)
            {
                int LT = (j * m_col) + i - 1;
                int LB = (j * m_col + m_col) + i - 1;

                this->connect(LT, LT + 1);
                this->connect(LT, LB);
            }
    }

    void connectRand(int n) // generate random connections n times
    {
        int k = 0;
        std::srand (time(0));

        while(k < n)
        {
            int p = rand() % this->size();
            int q = rand() % this->size();
            //std::cout << p << " -> " << q << std::endl;
            if(!isConnected(p, q) && isNeighbor(p, q))
            {
                connect(p, q);
                k++;
            }
        }
    }

    bool isNeighbor(int p, int q)
    {   
        // calc num of line
        int p_row = p / m_row;
        int q_row = q / m_row;
        int p_col = p % m_row;
        int q_col = q % m_row;

        // check if on same line
        bool same_row = p_row == q_row;
        bool same_col = p_col == q_col;
        bool same_line = same_row || same_col;

        // check if on neighbor line
        bool close_row = std::abs(p_row - q_row) == 1;
        bool close_col = std::abs(p_col - q_col) == 1;
        bool neighbor_line = close_row || close_col;

        return same_line && neighbor_line;
    }

    void getPath(int i)
    {
        int k = 0;
        int ref = i;
        while(k < 10)
        {
            ref = this->getValAt(ref);
            std::cout << this->getValAt(ref) << "->";
            k++;
        }
        std::cout << std::endl;
    }

    void drawConnect();    
};

void Field_QUUF::drawConnect()
{
    for(int j = 0; j < m_row; j++)
    {
        std::string line0 = "";
        std::string line1 = "";

        for(int i = 1; i <= m_col; i++)
        {   
            // Filling first line
            int L = this->getValAt((j * m_col) + i - 1); // this->getValAt((j * m_col) + i - 1);
            int R = this->getValAt((j * m_col) + i);     // this->getValAt((j * m_col) + i);
            bool L_to_R = this->isConnected(L, R);
            if(L < 10 && i == 1) // add first space(for small number) + Number
            {
                line0 += " ";
                line0 += std::to_string(L);
                line1 += " "; // add first space
            }
            else
            {
                line0 += std::to_string(L);
                if(i == 1)
                    line1 += " "; // add first space
            }    
            if(L_to_R && i < m_col)
            {
                if(R < 10) line0 += "———";
                else line0 += "——";
            }
            else
            {
                if(R < 10) line0 += "   ";
                else line0 += "  ";
            }

            // Filling second line
            if(j != m_row-1) //check if it's NOT the LAST row
            {   
                int LT = L;
                int LB = this->getValAt((j * m_col + m_col) + i - 1); // this->getValAt((j+1 * m_col) + i);
                int LT_to_LB = this->isConnected(LT, LB);

                if(LT_to_LB)
                {
                    line1 += "|   ";
                }
                else
                {
                    line1 += "    ";
                }
                
            }
        }
        std::cout << line0 << std::endl;
        std::cout << line1 << std::endl;
    }
}

int main()
{
    Field_QUUF field(8, 8);
    //field.connectAll();
    field.connectRand(45);

    //field.connect(0, 1);
    //field.connect(11, 6);
    //field.connect(23, 18);
    field.drawConnect();
    field.getPath(10);
    std::cout << field.isConnected(20, 30) << std::endl;

    std::cin.get();  //Program waiting for the last symbol
} 