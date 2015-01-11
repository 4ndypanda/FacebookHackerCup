#include <iostream>
#include <vector>

using namespace std;

struct food
{
  int protein, carbohydrates, fat;
  food(int protein, int carbohydrates, int fat)
  {
    this->protein = protein;
    this->carbohydrates = carbohydrates;
    this->fat = fat;
  }
};

/**
 * Brute force all possible combinations of foods to determine if it is possible
 * to achieve the amount of protein, carbohydrates, and fat provided.
 */
bool is_possible(vector<food> foods, int protein, int carbohydrates, int fat)
{
  for (int i = 0; i < (1 << foods.size()); i++)
  {
    int current_protein = 0, current_carbohydrates = 0, current_fat = 0;
    for (int j = 0; j < foods.size(); j++)
      if (i >> j & 1)
      {
        current_protein += foods[j].protein;
        current_carbohydrates += foods[j].carbohydrates;
        current_fat += foods[j].fat;
      }
    if (current_protein == protein && current_carbohydrates == carbohydrates && current_fat == fat)
      return true;
  }
  return false;
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    int protein_goal, carbohydrates_goal, fat_goal;
    cin >> protein_goal >> carbohydrates_goal >> fat_goal;
    int N;
    cin >> N;
    vector<food> foods;
    for (int i = 0; i < N; i++)
    {
      int protein, carbohydrates, fat;
      cin >> protein >> carbohydrates >> fat;
      foods.push_back(food(protein, carbohydrates, fat));
    }
    bool possible = is_possible(foods, protein_goal, carbohydrates_goal, fat_goal);
    printf("Case #%d: %s\n", t, possible ? "yes" : "no");
  }
  return 0;
}
