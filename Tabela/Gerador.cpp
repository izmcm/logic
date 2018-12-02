#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

// VARIAVEIS
vector<string> subExp[20];
int var[4] = {0}; // = {x, y, z, t}
int openPrt, col, lin, qtdVar;
int qtd0, qtd1;

// FUNCOES 
void init();
void printar();
void debug();
void BubbleSort();
string toBin(int num, int tam);
int findVal(int i, int j, int mid);
void truthTable();
int findTipo();
void printa(int f1);

// PROGRAMA
int main(){
	freopen("Expressoes.in", "r", stdin);
	freopen("Expressoes.out", "w", stdout);
	string exp;

	int n, tabela = 0;
	cin >> n;

	while(n--){
		init();
		int flag = 0;

		cin >> exp;

		string str;
		// a procura de subexpressoes sera feita com base na contagem dos parenteses
		for(int i = 0; i < exp.size(); i++){
			if(exp[i] == '('){
				openPrt++;
				for(int j = i + 1; j < exp.size(); j++){
					if(exp[j] == '(') openPrt++;
					else if(exp[j] == ')') openPrt--;
			
					//printf("dbg1: %d %d %d\n", i, pos, openPrt);

					// fazendo um vector de subexpressões
					if(openPrt == 0){
						str = exp.substr(i, j - i + 1);

						// procura se a subexpressao ja existe no vector
						for(int k = 0; k < subExp[0].size(); k++)
							if(str == subExp[0][k]) flag = 1;
						
						if(flag == 0){
							subExp[0].push_back(str);
							col++;
						}
						break;
					}
				}
			}
			openPrt = 0; flag = 0;
		}

		// faz a contagem das variaveis que existem na expressao, considerando validas
		// apenas {x, y, z, t}, como dito na descricao do projeto
		// adiciona as variaveis existentes a tabela
		for(int i = 0; i < exp.size(); i++){
			if(exp[i] == 't'){
				if(var[3] == 0){
					str = 't';
					subExp[0].push_back(str);
					col++;
				}
				var[3]++;
			}
			else if(exp[i] == 'z'){
				if(var[2] == 0){
					str = 'z';
					subExp[0].push_back(str);
					col++;
				}
				var[2]++;
			}
			else if(exp[i] == 'y'){
				if(var[1] == 0){
					str = 'y';
					subExp[0].push_back(str);
					col++;
				}
				var[1]++;
			}
			else if(exp[i] == 'x'){
				if(var[0] == 0){
					str = 'x';
					subExp[0].push_back(str);
					col++;
				}
				var[0]++;
			}
		}

		// organizando as subexpressoes com base na funcao cmp
		BubbleSort();

		// gera a tabela verdade
		truthTable();
		int f1 = findTipo();
		// 0 - Satisfativel e Tautologia
		// 1 - Insatistafivel e Refutável
		// 2 - Satisfativel e Refutável

		tabela++;
		cout << "Tabela #" << tabela << endl;
		printa(f1);
	}

	return 0;
}

void init(){
	for(int i = 0; i < 20; i++)
		subExp[i].clear();
	
	openPrt = 0;
	col = 0; lin = 0; qtdVar = 0;
	qtd1 = 0; qtd0 = 0;

	for(int i = 0; i < 4; i++)
		var[i] = 0;
}

void BubbleSort(){
	for(int i = subExp[0].size() - 1; i > 0; i--){
		for(int j = 0; j < i; j++){
			if(subExp[0][j].size() > subExp[0][j + 1].size())
				swap(subExp[0][j], subExp[0][j + 1]);
			
			else if(subExp[0][j].size() == subExp[0][j + 1].size()){
				if(subExp[0][j] == "t")
					swap(subExp[0][j], subExp[0][j + 1]);
				
				else if(subExp[0][j + 1] == "t") continue;

				else if(subExp[0][j] > subExp[0][j + 1]) 
					swap(subExp[0][j], subExp[0][j + 1]);
			}
		}
	}
}

string toBin(int num, int tam){
	char bit[10];
	int resto, i = 0;

	while(num >= 1){
		resto = num%2;
		bit[i] = resto + '0';
		i++;

		num /= 2;
	}

	for(int j = i; j < tam; j++)
		bit[j] = '0';

	char aux[10];
	int j = 0;
	for(int i = tam - 1; i >= 0; i--){
		aux[j] = bit[i];
		j++;
	}

	aux[j] = '\0';
	string str = aux;

	return str;
}

// se a flag for 1, procuraremos a subexpressao posterior
// se a flag for 0, procuraremos a subexpressao anterior
int findVal(int i, int j, int mid, int flag){
	openPrt = 0;
	int pos;

	if(flag == 1){
		for(int k = mid + 1; k < subExp[0][j].size(); k++){
			if(subExp[0][j][k] == '(') openPrt++;
			else if(subExp[0][j][k] == ')') openPrt--;

			if(openPrt == 0){
				pos = k;
				break;
			}
		}

		for(int k = 0; k < j; k++){
			if(subExp[0][j].compare(mid + 1, pos - mid, subExp[0][k]) == 0){
				if(subExp[i][k] == "1") return 1;
				return 0;
			}
		}
	}
	else {
		for(int k = mid - 1; k >= 0; k--){
			if(subExp[0][j][k] == ')') openPrt++;
			else if(subExp[0][j][k] == '(') openPrt--;

			if(openPrt == 0){
				pos = k;
				break;
			}
		}

		for(int k = 0; k < j; k++){
			if(subExp[0][j].compare(pos, mid - pos, subExp[0][k]) == 0){
				if(subExp[i][k] == "1") return 1;
				return 0;
			}
		}
	}
}

string gerarValor(int i, int j){
	int mid, v1 = 0, v2 = 0;
	openPrt = 0; // adotando um parenteses fechado ou aberto

	// se for a negativa de alguma subexpressao
	if(subExp[0][j][1] == '-'){
		mid = 1;
		v1 = findVal(i, j, mid, 1);
	}
	else { // caso contrario, procura o meio com base na contagem de parenteses
		for(int q = 0; q < subExp[0][j].size(); q++){
			if(subExp[0][j][q] == '(') openPrt++;
			else if(subExp[0][j][q] == ')') openPrt--;

			if(openPrt == 1){
				if(subExp[0][j][q] == '.' || subExp[0][j][q] == '+' || subExp[0][j][q] == '>'){
					mid = q;
					break;
				}
			}
		}
	
		v1 = findVal(i, j, mid, 0);
		v2 = findVal(i, j, mid, 1);
	}

	// tabela verdade
	if(subExp[0][j][mid] == '.'){
		if(v1 == 1 && v2 == 1) return "1";
		return "0";
	}
	else if(subExp[0][j][mid] == '+'){
		if(v1 == 0 && v2 == 0) return "0";
		return "1";
	}
	else if(subExp[0][j][mid] == '>'){
		if(v1 == 0 || v2 == 1) return "1";
		return "0";
	}
	else if(subExp[0][j][mid] == '-'){
		if(v1 == 0) return "1";
		return "0";
	}
}

void truthTable(){
	// conta variaveis
	for(int i = 0; i < 4; i++)
		if(var[i] > 0) qtdVar++;

	// a qtd de linhas sera dada com base na qtd de variaveis (2^qtdVar)
	lin = pow(2, qtdVar) + 1;

	// percorre as linhas e colunas preenchendo a tabela
	for(int i = 1; i < lin; i++){
		// gera os valores das variaveis em ordem crescente,
		// comecando em 000... ate 111...
		string str = toBin(i - 1, qtdVar);
		for(int j = 0; j < col; j++){
			if(j < qtdVar){
				string aux = str.substr(j, 1);
				subExp[i].push_back(aux);
			}
			else{
				string aux = gerarValor(i, j);

				subExp[i].push_back(aux);
			}
		}
	}
	//debug();
}

int findTipo(){
	for(int i = 1; i < lin; i++){
		if(subExp[i][col - 1] == "1") qtd1++;
		else qtd0++;
	}

	if(qtd1 == 0) return 1;
	else if(qtd0 == 0) return 0;
	else return 2;
} 

void printa(int f1){
	string aux = "-";
	for(int i = 0; i < subExp[0].size(); i++){
		aux += '-';
		for(int j = 0; j < subExp[0][i].size(); j++)
			aux += '-';
	}

	cout << aux << "\n|";
	for(int i = 0; i < col; i++)
		cout << subExp[0][i] << "|";

	for(int i = 1; i < lin; i++){
		cout << "\n" << aux << "\n|";
		for(int j = 0; j < col; j++){
			
			string espacos;
			for(int k = 1; k < subExp[0][j].size(); k++)
				espacos += ' ';

			cout << espacos << subExp[i][j] << "|";
		}
	}
	cout << "\n" << aux << endl;

	if(f1 == 0)
		cout << "satisfativel e tautologia" << endl;
	else if(f1 == 1)
		cout << "insatisfativel e refutavel" << endl;
	else if(f1 == 2)
		cout << "satisfativel e refutavel" << endl;

	cout << endl;
}