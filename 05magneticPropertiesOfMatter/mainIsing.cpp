#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
 
class Ising
{   
    static const size_t n = 40;
    static const size_t N = n + 2;
    
    using Array=std::array<int, N>;

    public:
        Ising()
            : 
              rng_(rd_()), uid01_(std::uniform_int_distribution<int>(0, 1)),
                           uid1n_(std::uniform_int_distribution<int>(1, n)),
                           urd01_(std::uniform_real_distribution<float>(0.0f, 1.0f))
        {   // random init
            for (size_t l = 0 + 1; l < N - 1; ++l)
            {   for (size_t c = 0 + 1; c < N - 1; ++c)
                {   s_[l][c] = uid01_(rng_) * 2 - 1;
                }
            }

        }

        ~Ising()=default;

        const void show() // -------------------------------------------------
        {   for (size_t l = 0; l < N; ++l)
            {   for (size_t c = 0; c < N; ++c)
                {   std::cout << std::setw(3) << s_[l][c];
                }
                std::cout << "\n";
            }
            std::cout << "\n";
            return;
        }

        const int u(const std::array<std::array<int, N>, N>& s, int l, int c)
        {   return -s[l][c]*(s[l][c+1]+s[l-1][c]+s[l][c-1]+s[l+1][c]);
        }

        float bf(int ui, int uf)
        {   return std::exp(-(uf-ui));
        }

        const void shake()
        {   //std::cout << "shake\n";
            for (size_t i = 0; i < n * n; ++i)
            {   size_t l = uid1n_(rng_);
                size_t c = uid1n_(rng_);
                //std::cout << "(" << l << ", " << c << ")\n";
                int ui = u(s_,l,c);
                s_[l][c] *= -1;
                int uf = u(s_,l,c);
                if (uf >= ui)
                {   if (uid01_(rng_) > bf(ui,uf))
                    {   s_[l][c] *= -1;
                    }
                }
            }
        }
    private:
        std::array<std::array<int, N>, N> s_ {};

        std::random_device rd_;
        std::default_random_engine rng_;
        std::uniform_int_distribution<int> uid01_;
        std::uniform_int_distribution<int> uid1n_;
        std::uniform_real_distribution<float> urd01_;

};

int main(int argc, char * argv[])
{
    int t = std::stoi(argv[1]);
    //std::cout << t << '\n';
    //int num = uniform_dist(e1);
    Ising is;
    is.show();
    for (int i = 0; i < t; ++i)
    {   is.shake();
        is.show();
    }
    return 0;
}
