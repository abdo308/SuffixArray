#include <iostream>
using namespace std;

class SuffixArray
{
private:
    char arr[1000];
    int ans[1000];
    char suffix[1000][1000];
    int length;

public:
    SuffixArray(const char *v)
    {
        int cnt = 0;
        while (true)
        {
            if (v[cnt] == '$')
            {
                ++cnt;
                break;
            }
            ++cnt;
        }
        length = cnt;
        if (length >= 1000)
        {
            cerr << "Input string is too large!" << endl;
            exit(1);
        }
        for (int i = 0; i < length; i++)
        {
            arr[i] = v[i];
        }
        arr[length] = '\0';
    }

    void ConstructUsingPrefixDoubling()
    {
        char tmp[1000];
        int numSuffixes = 0;
        for (int i = 0, j = length - 1; i <= j; ++i)
        {
            int tmp = 0;
            while ((tmp + i) <= j)
            {
                suffix[i][tmp] = arr[tmp + i];
                ++tmp;
            }
            suffix[i][tmp] = '\0';
            ++numSuffixes;
            // for (int k = numSuffixes - 1; k > 0; --k)
            // {
            //     if (suffix[k][0] < suffix[k - 1][0])
            //     {
            //         swap(suffix[k], suffix[k - 1]);
            //     }
            //     else if (suffix[k][0] == suffix[k - 1][0])
            //     {
            //         for (int c = 1; suffix[k][c] != '\0' && suffix[k - 1][c] != '\0'; ++c)
            //         {

            //             if (suffix[k][c] < suffix[k - 1][c])
            //             {
            //                 swap(suffix[k], suffix[k - 1]);
            //                 break;
            //             }
            //             else if (suffix[k][c] > suffix[k - 1][c])
            //             {
            //                 break;
            //             }
            //         }
            //     }
            // }
        }

        int res[1000];
        int rankInx = 1;
        while (true)
        {
            char stringHolder[1000][1000];
            pair<char *, int> rank[1000];
            int rankSize = 0;
            for (int i = 0; i <= length - 1; ++i)
            {
                for (int j = 0, inx = i; j < rankInx; ++j, ++inx)
                {

                    stringHolder[i][j] = arr[i + j];
                }

                rank[i] = {stringHolder[i], i};
                ++rankSize;

                // sorting
                for (int c = rankSize - 1; c > 0; --c)
                {
                    if (rank[c].first[0] < rank[c - 1].first[0])
                    {
                        swap(rank[c], rank[c - 1]);
                    }
                    else if (rank[c].first[0] == rank[c - 1].first[0])
                    {
                        for (int cnt = 1; cnt < rankSize; ++cnt)
                        {
                            if (rank[c].first[cnt] < rank[c - 1].first[cnt])
                            {
                                swap(rank[c], rank[c - 1]);
                                break;
                            }
                            else if (rank[c].first[cnt] > rank[c - 1].first[cnt])
                            {
                                break;
                            }
                        }
                    }
                }
            }

            int inx = 0;
            res[rank[0].second] = 0;
            for (int i = 1; i < rankSize; ++i)
            {
                for (int j = 0; j < rankInx; ++j)
                {
                    if (rank[i].first[j] == rank[i - 1].first[j] && j + 1 == rankInx)
                    {
                        res[rank[i].second] = inx;
                        break;
                    }
                    else if (rank[i].first[j] != rank[i - 1].first[j])
                    {
                        inx++;
                        res[rank[i].second] = inx;
                        break;
                    }
                }
            }
            bool repeat = false;
            for (int i = 0; i <= length - 1; ++i)
            {
                for (int j = i + 1; j <= length - 1; ++j)
                {
                    if (res[i] == res[j])
                    {
                        repeat = true;
                        break;
                    }
                }
                if (repeat)
                    break;
            }
            if (!repeat)
            {
                break;
            }
            repeat = false;
            rankInx *= 2;
        }
        for (int i = 0; i <= length; ++i)
        {
            this->ans[i] = res[i];
        }
    }

    void display()
    {
        int x = 0;
        while (x != length)
        {
            for (int i = length - 1; i >= 0; --i)
            {
                if (ans[i] == x)
                {
                    cout << i << ' ';
                    ++x;
                    break;
                }
            }
        }
    }
};

int main()
{
    SuffixArray t("BANANA$");
    t.ConstructUsingPrefixDoubling();
    t.display();
    return 0;
}
