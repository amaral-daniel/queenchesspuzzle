#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>


using namespace std;
void printTabuleiro(vector<int> tabuleiro);
int checarRainhas(vector<int> tabuleiro);
vector<int> mutacao(vector<int> individuo);
vector<int> crossover(vector<int> individuo1,vector<int> individuo2);
vector< vector<int> > fazerMutacao (vector< vector<int> > populacao);
vector< vector<int> > fazerCrossover (vector< vector<int> > populacao);
void printPopulacao(vector< vector<int> > populacao);
vector< vector<int> > selecionarMelhores( vector< vector<int> > populacao);
int qualidadePopulacao( vector< vector<int> > populacao);
void printVector(vector<int> a);


int main()
{
  vector< vector<int> > populacao;

  vector<int> qualidades;

  int arr[] = {0,1,2,3,4,5,6,7};
  vector<int> inicial1(arr, arr + sizeof(arr)/sizeof(int));
  populacao.push_back(inicial1);

  int arr1[] = {0,0,0,0,2,3,4,5};
  vector<int> inicial2(arr1, arr1 + sizeof(arr1)/sizeof(int));
  populacao.push_back(inicial2);

  int arr2[] = {0,1,2,3,2,6,6,7};
  vector<int> inicial3(arr2, arr2 + sizeof(arr2)/sizeof(int));
  populacao.push_back(inicial3);

  int arr3[] = {1,1,2,2,4,5,6,7};
  vector<int> inicial4(arr3, arr3 + sizeof(arr3)/sizeof(int));
  populacao.push_back(inicial4);
  populacao = fazerCrossover(populacao);
  populacao = fazerMutacao(populacao);
  //printPopulacao(populacao);
  cout<<"ataques da populacao:"<<qualidadePopulacao(populacao)<<endl;
  qualidades.push_back(qualidadePopulacao(populacao));

  for(int i = 0; i < 2 ; i++)
  {
    cout<<"GERACAO::"<<i<<endl;
    populacao = selecionarMelhores(populacao);
    populacao = fazerCrossover(populacao);
    //cout<<"fez crossover"<<endl;
    populacao = fazerMutacao(populacao);
  //  printPopulacao(populacao);
  //  cout<<"ataques da populacao:"<<qualidadePopulacao(populacao)<<endl;
    qualidades.push_back(qualidadePopulacao(populacao));



  }


      for(int i = 0; i < qualidades.size() ; i++)
        cout<<"Geracao "<< i<<" : "<<qualidades[i]<<endl;


        int arr5[] = {7,2,4,6,0,5,3,1};
          vector<int> inicial5(arr5, arr5 + sizeof(arr5)/sizeof(int));
          printTabuleiro(inicial5);
          cout<<checarRainhas(inicial5)<<endl;

  return 0;

}

void printTabuleiro(vector<int> tabuleiro)
{
  cout<<"           "<<endl;
  for(int i = 0; i < 8;i++)
  {
      for(int j = 0; j < 8;j++)
      {
          if(tabuleiro[i] != j)
            cout<<"[_]";
          else
            cout<<"[X]";

      }
      cout<<endl;
    }
}
int checarRainhas(vector<int> tabuleiro)
{
  int attacksVertical = 0;
  for (int i = 0; i < 8; i++ )
  {
      for(int j = 0; j < 8 ; j++)
      {
          if(tabuleiro[i] == tabuleiro[j])
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
      y1 = tabuleiro[i];
      for(int j = 0; j < 8 ; j++)
      {
          x2 = j;
          y2 = tabuleiro[j];

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
    vector<int> resultado;
  //  cout<<"a"<<endl;
    for(int i = 0; i < 4;i++ )
    {
      resultado.push_back(individuo1[i]);
  //    cout<<i<<endl;
    }
    for(int i = 4; i < 8;i++ )
    {
      resultado.push_back(individuo2[i]);
  //    cout<<i<<endl;
    }
    return resultado;
}

vector<int> mutacao(vector<int> individuo)
{
    vector<int> resultado;
    resultado = individuo;
    resultado[rand() % 8] = rand() % 8;
    resultado[rand() % 8] = rand() % 8;
  return resultado;


}

vector< vector<int> > fazerMutacao (vector< vector<int> > populacao)
{
  vector< vector<int> > resultado = populacao;
  resultado.push_back(mutacao(populacao[4]));
  resultado.push_back(mutacao(populacao[5]));
  resultado.push_back(mutacao(populacao[6]));
  resultado.push_back(mutacao(populacao[7]));
  return resultado;

}


vector< vector<int> > fazerCrossover (vector< vector<int> > populacao)
{
  vector< vector<int> > resultado = populacao;
//  cout<<"entrou"<<endl;
  resultado.push_back(crossover(populacao[0],populacao[1]));
//  cout<<"entrou"<<endl;
  resultado.push_back(crossover(populacao[1],populacao[0]));
//  cout<<"entrou"<<endl;
  resultado.push_back(crossover(populacao[2],populacao[3]));
//  cout<<"entrou"<<endl;
  resultado.push_back(crossover(populacao[3],populacao[2]));
//  cout<<"entrou"<<endl;
  return resultado;

}

void printPopulacao(vector< vector<int> > populacao)
{
    cout<<"*****INICIAIS******"<<endl;

    printTabuleiro(populacao[0]);
    printTabuleiro(populacao[1]);
    printTabuleiro(populacao[2]);
    printTabuleiro(populacao[3]);

    cout<<"*****FILHOS******"<<endl;

    printTabuleiro(populacao[4]);
    printTabuleiro(populacao[5]);
    printTabuleiro(populacao[6]);
    printTabuleiro(populacao[7]);

    cout<<"*****MUTANTES******"<<endl;

    printTabuleiro(populacao[8]);

    printTabuleiro(populacao[9]);
    printTabuleiro(populacao[10]);
    printTabuleiro(populacao[11]);




}



int qualidadePopulacao(vector< vector<int> > populacao)
{
    int qualidade = 0;
    for(int i = 0; i < populacao.size() ; i++)
    {
        qualidade += checarRainhas(populacao[i]);
    }

    return qualidade;



}



vector< vector<int> > selecionarMelhores( vector< vector<int> > populacao)
{
  vector<int> qualidadesDesorganizado;
  vector<int> qualidadesOrganizado;
  vector<int> indicesEscolhidos;
  vector< vector<int> > novaPopulacao;

  for(int i = 0; i < populacao.size() ; i++)
  {
      qualidadesDesorganizado.push_back(checarRainhas(populacao[i]));
  }

  qualidadesOrganizado = qualidadesDesorganizado;
  sort(qualidadesOrganizado.begin(), qualidadesOrganizado.end());
  cout<<"melhor dessa geracao:"<<qualidadesOrganizado[0]<<endl;
//  printVector(qualidadesDesorganizado);
//  printVector(qualidadesOrganizado);
//  cout<<"desorg"<<qualidadesDesorganizado<<endl;

  for(int j = 0; j < 4 ; j++)
  {
  for(int i = 0; i <  12;i++)
  {
      if(qualidadesOrganizado[j] == qualidadesDesorganizado[i] )
      {
              indicesEscolhidos.push_back(i);
            qualidadesDesorganizado[i] = 1000;
            i = 10;
      }

  }
//  printVector(qualidadesDesorganizado);
//  printVector(qualidadesOrganizado);
}


  //cout<<"!!!!!!!!!!!!!!!!!"<<endl;
  for(int i = 0; i < indicesEscolhidos.size(); i++)
  {
      novaPopulacao.push_back(populacao[indicesEscolhidos[i]]);
  //    printTabuleiro(populacao[indicesEscolhidos[i]]);
  }


  return novaPopulacao;



}


void printVector(vector<int> a)
{
  for(int i = 0; i < a.size() ; i++)
    cout<<a[i]<<", ";
  cout<<endl;

}
