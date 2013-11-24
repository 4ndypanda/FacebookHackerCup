#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct player
{
    string name;
    int shot_percentage, height;

    player(string name, int shot_percentage, int height)
    {
        this->name = name;
        this->shot_percentage = shot_percentage;
        this->height = height;
    }

    bool operator < (const player & b) const
    {
        if (shot_percentage == b.shot_percentage)
            return height > b.height;
        return shot_percentage > b.shot_percentage;
    }
};

vector <string> get_players(vector <player> team, int P, int M)
{
    vector <string> lineup;
    for (int i = P - 1; i >= 0; i--)
        lineup.push_back(team[i].name);
    for (int i = P; i < team.size(); i++)
        lineup.push_back(team[i].name);
    int left_shift = M % team.size();
    vector <string> current_players;
    for (int p = 0; p < P; p++)
    {
        current_players.push_back(lineup[left_shift]);
        left_shift = (left_shift + 1) % team.size();
    }
    return current_players;
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        int N, M, P;
        cin >> N >> M >> P;
        vector <player> players;
        for (int i = 0; i < N; i++) 
        {
            string name;
            int shot_percentage, height;
            cin >> name >> shot_percentage >> height;
            players.push_back(player(name, shot_percentage, height));
        }
        sort(players.begin(), players.end());
        vector <player> first_team, second_team;
        for (int i = 0; i < players.size(); i++) 
            (i % 2 ? second_team : first_team).push_back(players[i]);
        vector <string> first_players = get_players(first_team, P, M);
        vector <string> second_players = get_players(second_team, P, M);
        set <string> current_players(first_players.begin(), first_players.end());
        current_players.insert(second_players.begin(), second_players.end());
        printf("Case #%d:", t);
        for (set <string>::iterator it = current_players.begin(); it != current_players.end(); it++)
            printf(" %s", it->c_str());
        printf("\n");
    }
    return 0;
}
