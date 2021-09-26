// ismain.cpp
// wpf 20210925 14h30min
//
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <array>
#include <random>
#include <iomanip>

const size_t n = 2;
const size_t N = n + 2;

const void show(const std::array<std::array<int, N>, N>& s)
{   for (size_t l = 0; l < N; ++l)
    {   for (size_t c = 0; c < N; ++c)
        {   std::cout << std::setw(3) << s[l][c];
        }
        std::cout << "\n";
    }
    return;
}

int u(const std::array<std::array<int, N>, N>& s, int l, int c)
{   return -s[l][c]*(s[l][c+1]+s[l-1][c]+s[l][c-1]+s[l+1][c]);
}

float bf(int ui, int uf)
{   return std::exp(-(uf-ui));
}

int main(int argc, char * argv[])
{
    // random number generators initialization
    std::random_device dev0;
    std::mt19937 rng0(dev0());
    std::uniform_real_distribution<> rnd0(0.0, 1.0);

    std::random_device dev1;
    std::mt19937 rng1(dev1());
    std::uniform_int_distribution<std::mt19937::result_type> rnd1(0, 1);

    std::random_device devi;
    std::mt19937 rngi(devi());
    std::uniform_int_distribution<std::mt19937::result_type> rndi(1, n);
    
    std::cout << "Magnetism model\n";

    std::array<std::array<int, N>, N> s {};

    // randomically populate
    for (size_t l = 0 + 1; l < N - 1; ++l)
    {   for (size_t c = 0 + 1; c < N - 1; ++c)
        {   s[l][c] = rnd1(rng1) * 2 - 1;
        }
    }

    show(s);
    
    // shake
    std::cout << "shake\n";
    for (size_t i = 0; i < n * n; ++i)
    {   size_t l = rndi(rngi);
        size_t c = rndi(rngi);
        std::cout << "(" << l << ", " << c << ")\n";
        int ui = u(s,l,c);
        s[l][c] *= -1;
        int uf = u(s,l,c);
        if (uf >= ui)
        {   if (rnd0(rng0) > bf(ui,uf))
            {   s[l][c] *= -1;
            }
        }
    }
    std::cout <<"\n";

    show(s);

    //results
    std::string fn("ising.dat");
    std::fstream ofs;
    ofs.open(fn,std::ios::out);
    if (!ofs.is_open())
    {   std::cout<<"Unable to write to file \""<<fn<<"\"\n";
        return 4;
    }
    ofs<<"Ok."<<std::endl;
    ofs.close();
    std::cout<<"Results written to "<<fn<<"\n";
    std::cout<<"Program run successfully.\n";
}   
