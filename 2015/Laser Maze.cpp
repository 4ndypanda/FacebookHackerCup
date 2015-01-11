#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

#define MAX_SIZE 100

bool seen[MAX_SIZE][MAX_SIZE][4];

// Directions are encoded as:
//   0 = north '^'
//   1 = east  '>'
//   2 = south 'v'
//   3 = west  '<'
// Note that opposite directions are always 2 apart from each other. This is
// useful for the function valid_step(...).
int di[4] = {-1, 0, 1, 0};
int dj[4] = { 0, 1, 0,-1};
string laser_direction = "^>v<";

struct state
{
  int i, j, steps;
  state(int i, int j, int steps)
  {
    this->i = i;
    this->j = j;
    this->steps = steps;
  }
};

bool out_of_bounds(const vector<string> &maze, int i, int j)
{
  return i < 0 || i >= maze.size() || j < 0 || j >= maze[0].length();
}

/**
 * Determine if the given state is a valid step in the maze.
 */
bool valid_step(const vector<string> &maze, state state)
{
  // Out of bounds check.
  if (out_of_bounds(maze, state.i, state.j))
    return false;

  // Wall or laser turret check.
  if (maze[state.i][state.j] == '#' || laser_direction.find(maze[state.i][state.j]) != string::npos)
    return false;

  // We only have to check the row and column for lasers. Remember that lasers
  // do not go through walls or laser turrets. If a laser is facing in the
  // opposite direction of where we are looking, then we are in the laser's
  // path. k will be the direction we are facing when looking for lasers.
  for (int k = 0; k < 4; k++)
  {
    int i = state.i, j = state.j;
    while (!out_of_bounds(maze, i, j) && maze[i][j] != '#')
    {
      int initial_laser_direction = laser_direction.find(maze[i][j]);
      // Found a laser turret.
      if (initial_laser_direction != string::npos)
      {
        int laser_direction = (initial_laser_direction + state.steps) % 4;
        // Remember that directions are opposite based on the encoding above.
        if (k == (laser_direction + 2) % 4)
          return false;
        break;
      }
      i += di[k], j += dj[k];
    }
  }
  return true;
}

/**
 * BFS through the maze to determine the minimum number of steps to reach the
 * goal. The lasers in the maze can only be in 4 different configurations.
 */
string solve(const vector<string> &maze, int start_i, int start_j, int end_i, int end_j)
{
  fill(**seen, **seen + MAX_SIZE * MAX_SIZE * 4, false);
  queue<state> states;
  states.push(state(start_i, start_j, 0));
  seen[start_i][start_j][0] = true;
  while (!states.empty())
  {
    state current = states.front();
    states.pop();
    for (int k = 0; k < 4; k++)
    {
      int i = current.i + di[k], j = current.j + dj[k];
      state new_state = state(i, j, current.steps + 1);
      int lasers_configuration = new_state.steps % 4;
      if (!valid_step(maze, new_state) || seen[i][j][lasers_configuration])
        continue;
      if (i == end_i && j == end_j)
        return to_string(new_state.steps);
      seen[i][j][lasers_configuration] = true;
      states.push(new_state);
    }
  }
  return "impossible";
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    int M, N;
    cin >> M >> N;
    vector<string> maze;
    int start_i, start_j, end_i, end_j;
    for (int i = 0; i < M; i++)
    {
      string row;
      cin >> row;
      maze.push_back(row);
      int j = row.find('S');
      if (j != string::npos)
        start_i = i, start_j = j;
      j = row.find('G');
      if (j != string::npos)
        end_i = i, end_j = j;
    }
    printf("Case #%d: %s\n", t, solve(maze, start_i, start_j, end_i, end_j).c_str());
  }
  return 0;
}
