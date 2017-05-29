#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>


using namespace std;
void printBoard(vector<int> board);
int checkAttacks(vector<int> board);
vector<int> mutate(vector<int> individual);
vector<int> crossover(vector<int> individual1,vector<int> individual2);
vector< vector<int> > generateMutants (vector< vector<int> > population);
vector< vector<int> > generateOffspring (vector< vector<int> > population);
void printPopulation(vector< vector<int> > population);
vector< vector<int> > naturalSelection( vector< vector<int> > population);
int qualityPopulation( vector< vector<int> > population);
void printVector(vector<int> a);


int main()
{
      vector< vector<int> > population; //stores entire population
      vector<int> qualities; //stores the amount of attacks of each generation, to keep track of the improvement
  
      //next few lines generate the first population, values in the arrays should be changed to choose the initial population
      int arr[] = {0,1,2,3,4,5,6,7};
      vector<int> inicial1(arr, arr + sizeof(arr)/sizeof(int));
      population.push_back(inicial1);

      int arr1[] = {0,0,0,0,2,3,4,5};
      vector<int> inicial2(arr1, arr1 + sizeof(arr1)/sizeof(int));
      population.push_back(inicial2);

      int arr2[] = {0,1,2,3,2,6,6,7};
      vector<int> inicial3(arr2, arr2 + sizeof(arr2)/sizeof(int));
      population.push_back(inicial3);

      int arr3[] = {1,1,2,2,4,5,6,7};
      vector<int> inicial4(arr3, arr3 + sizeof(arr3)/sizeof(int));
      population.push_back(inicial4);
  
  
  
      population = generateOffspring(population);
      population = generateMutants(population);
      
      qualities.push_back(qualityPopulation(population));

      for(int i = 0; i < 2 ; i++)
      {
            cout<<"GENERATION::"<<i<<endl;
            population = naturalSelection(population);
            population = generateOffspring(population);
            population = generateMutants(population);
            qualities.push_back(qualityPopulation(population));
      }

      cout<<"Amount of attacks between two queens in each generation:"<<endl;
      for(int i = 0; i < qualities.size() ; i++)
            cout<<"Generation "<< i<<" : "<<qualities[i]<<endl;

  return 0;

}





void printBoard(vector<int> board)
{
      cout<<"           "<<endl;
      for(int i = 0; i < 8;i++)
      {
            for(int j = 0; j < 8;j++)
            {
                if(board[i] != j)
                    cout<<"[_]";
                else
                    cout<<"[X]";
            }
            cout<<endl;
          }
}

int checkAttacks(vector<int> board)
{
      int attacksVertical = 0;
      for (int i = 0; i < 8; i++ )
      {
            for(int j = 0; j < 8 ; j++)
            {
                  if(board[i] == board[j])
                  {
                      attacksVertical+=1;
                  }
            }
      }
      attacksVertical -=8;
      attacksVertical /= 2;
      cout<<attacksVertical<<endl;

      int attacksDiagonal = 0;
      int x1,y1,x2,y2,deltax,deltay;
      for (int i = 0; i < 8; i++ )
      {
            x1 = i;
            y1 = board[i];
            for(int j = 0; j < 8 ; j++)
            {
                  x2 = j;
                  y2 = board[j];

                  deltax = x1 - x2;
                  deltay = y1 - y2;

                  if(abs(deltax) == abs(deltay))
                  {
                      attacksDiagonal+=1;
                  }
            }
      }
      attacksDiagonal -= 8;
      attacksDiagonal /= 2;
      cout<<attacksDiagonal<<endl;
      return attacksDiagonal + attacksVertical;


}


vector<int> crossover(vector<int> individuo1,vector<int> individuo2)
{
    vector<int> result;
  
    for(int i = 0; i < 4;i++ )
    {
          result.push_back(individuo1[i]);
    }
    for(int i = 4; i < 8;i++ )
    {
          result.push_back(individuo2[i]);
    }
  
    return result;
}

vector<int> mutate(vector<int> individuo)
{
      vector<int> result;
  
      result = individuo;
      result[rand() % 8] = rand() % 8;
      result[rand() % 8] = rand() % 8;
    
      return result;
}

vector< vector<int> > generateMutants (vector< vector<int> > population)
{
      vector< vector<int> > result = population;
      result.push_back(mutate(population[4]));
      result.push_back(mutate(population[5]));
      result.push_back(mutate(population[6]));
      result.push_back(mutate(population[7]));
  
      return result;

}


vector< vector<int> > generateOffspring (vector< vector<int> > population)
{
      vector< vector<int> > result = population;


      result.push_back(crossover(population[0],population[1]));
      result.push_back(crossover(population[1],population[0]));
      result.push_back(crossover(population[2],population[3]));
      result.push_back(crossover(population[3],population[2]));

      return result;

}

void printPopulation(vector< vector<int> > population)
{
  
      cout<<"*****PARENTS******"<<endl;

      printBoard(population[0]);
      printBoard(population[1]);
      printBoard(population[2]);
      printBoard(population[3]);

      cout<<"*****OFFSPRING******"<<endl;

      printBoard(population[4]);
      printBoard(population[5]);
      printBoard(population[6]);
      printBoard(population[7]);

      cout<<"*****MUTANTS******"<<endl;

      printBoard(population[8]);
      printBoard(population[9]);
      printBoard(population[10]);
      printBoard(population[11]);

}



int qualityPopulation(vector< vector<int> > population)
{
      int quality = 0;
      for(int i = 0; i < population.size() ; i++)
      {
            quality += checkAttacks(population[i]);
      }

      return quality;

}



vector< vector<int> > naturalSelection( vector< vector<int> > population)
{
      vector<int> qualitiesUnsorted;
      vector<int> qualitiesSorted;
      vector<int> chosenIndexes;
      vector< vector<int> > newPopulation;

      for(int i = 0; i < population.size() ; i++)
      {
             qualitiesUnsorted.push_back(checkAttacks(population[i]));
      }

      qualitiesSorted = qualitiesUnsorted;
      sort(qualitiesSorted.begin(), qualitiesSorted.end());
      cout<<"Amount of attacks in the best individual of this generation:"<<qualitiesSorted[0]<<endl;


      for(int j = 0; j < 4 ; j++)
      {
            for(int i = 0; i <  12;i++)
            {
                if(qualitiesSorted[j] == qualitiesUnsorted[i] )
                {
                      chosenIndexes.push_back(i);
                      qualitiesUnsorted[i] = 1000;
                      i = 12;
                }
            }
      }


      for(int i = 0; i < chosenIndexes.size(); i++)
      {
            newPopulation.push_back(population[chosenIndexes[i]]);
      }


      return newPopulation;



}


void printVector(vector<int> a)
{
      for(int i = 0; i < a.size() ; i++)
            cout<<a[i]<<", ";
      cout<<endl;

}
