#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

string EXP;
vector<string> subExp;

bool isFNC(){
	int prt = 0;

	for(int i = 0; i < EXP.size(); i++){
		if(EXP[i] == '(') prt++;
		else if(EXP[i] == ')') prt--;
		else if(EXP[i] == '.'){
			if(EXP[i + 1] != '(' || EXP[i - 1] != ')') return false;
		}

		else if(prt == 0){
			if(EXP[i] != '.') return false;
		}

		if(prt > 1) return false;
	}

	return true;
}

bool isHorn(){
	int prt = 0, varT = 0, varN = 0;

	for(int i = 0; i < EXP.size(); i++){
		if(EXP[i] == '(') prt++;
		else if(EXP[i] == ')') prt--;

		else if(prt == 1){
			if(EXP[i] == 'a' || EXP[i] == 'b' || EXP[i] == 'c' || EXP[i] == 'd') varT++;
			else if(EXP[i] == '-') varN++;
		}

		if(prt == 0){
			if(varT - varN > 1){
				return false;
			}
			varN = 0; varT = 0;
		}
	}

	return true;
}

void SUBEXP(){
	int inicio; 

	for(int i = 0; i < EXP.size(); i++){
		if(EXP[i] == '(') inicio = i;
		else if(EXP[i] == ')'){
			string str = EXP.substr(inicio, i - inicio + 1);
			subExp.push_back(str);
		}
	}

	//for(int i = 0; i < subExp.size(); i++)
	//	cout << subExp[i] << " ";

	//cout << endl;

	int flag = 0;
	
	while(flag == 0){
		flag = 1;
		for(int i = 0; i < subExp.size(); i++){
		if(subExp[i].size() == 3){
			if(subExp[i][1] == 'a'){
				for(int j = 0; j < subExp.size(); j++){
					if(j == i) continue;

					for(int k = 0; k < subExp[j].size(); k++){
						if(subExp[j][k] == 'a'){
							if(subExp[j][k - 1] == '-'){
								int ini, fim;
								if(subExp[j][k - 2] != '('){
									ini = k - 2;
									fim = k;
								}
								else if(subExp[j][k - 2] == '('){
									ini = k - 1;
									if(subExp[j][k + 1] == ')') fim = k;
									else fim = k + 1;
								}
								
								subExp[j].erase(ini, fim - ini + 1);
								if(subExp[j].size() == 3 || subExp[j].size() == 4) flag = 0;
							}
							else{
								subExp.erase(subExp.begin()+j);
								j--;
								break;
							}
						}
					}
				}
			}
			else if(subExp[i][1] == 'b'){
				for(int j = 0; j < subExp.size(); j++){
					if(j == i) continue;	
			
					for(int k = 0; k < subExp[j].size(); k++){
						if(subExp[j][k] == 'b'){
							if(subExp[j][k - 1] == '-'){
								int ini, fim;
								if(subExp[j][k - 2] != '('){
									ini = k - 2;
									fim = k;
								}
								else if(subExp[j][k - 2] == '('){
									ini = k - 1;
									if(subExp[j][k + 1] == ')') fim = k;
									else fim = k + 1;
								}
								
								subExp[j].erase(ini, fim - ini + 1);
								if(subExp[j].size() == 3 || subExp[j].size() == 4) flag = 0;
							}
							else{
								subExp.erase(subExp.begin()+j);
								j--;
								break;
							}
						}
					}
				}
			}
			else if(subExp[i][1] == 'c'){
				for(int j = 0; j < subExp.size(); j++){
					if(j == i) continue;	
			
					for(int k = 0; k < subExp[j].size(); k++){
						if(subExp[j][k] == 'c'){
							if(subExp[j][k - 1] == '-'){
								int ini, fim;
								if(subExp[j][k - 2] != '('){
									ini = k - 2;
									fim = k;
								}
								else if(subExp[j][k - 2] == '('){
									ini = k - 1;
									if(subExp[j][k + 1] == ')') fim = k;
									else fim = k + 1;
								}
								
								subExp[j].erase(ini, fim - ini + 1);
								if(subExp[j].size() == 3 || subExp[j].size() == 4) flag = 0;
							}
							else{
								subExp.erase(subExp.begin()+j);
								j--;
								break;
							}
						}
					}
				}
			}
			else if(subExp[i][1] == 'd'){
				for(int j = 0; j < subExp.size(); j++){
					if(j == i) continue;	
			
					for(int k = 0; k < subExp[j].size(); k++){
						if(subExp[j][k] == 'd'){
							if(subExp[j][k - 1] == '-'){
								int ini, fim;
								if(subExp[j][k - 2] != '('){
									ini = k - 2;
									fim = k;
								}
								else if(subExp[j][k - 2] == '('){
									ini = k - 1;
									if(subExp[j][k + 1] == ')') fim = k;
									else fim = k + 1;
								}
								
								subExp[j].erase(ini, fim - ini + 1);
								if(subExp[j].size() == 3 || subExp[j].size() == 4) flag = 0;
							}
							else{
								subExp.erase(subExp.begin()+j);
								j--;
								break;
							}
						}
					}
				}
			}
		}
		else if(subExp[i].size() == 4){
			if(subExp[i][2] == 'a'){
				for(int j = 0; j < subExp.size(); j++){
					if(j == i) continue;

					for(int k = 0; k < subExp[j].size(); k++){
						if(subExp[j][k] == 'a'){
							if(subExp[j][k - 1] == '-'){
								subExp.erase(subExp.begin()+j);
								j--;
								break;
							}
							else{
								int ini, fim;
								if(subExp[j][k - 1] != '('){
									ini = k - 1;
									fim = k;
								}
								else if(subExp[j][k - 1] == '('){
									ini = k;
									if(subExp[j][k + 1] == ')') fim = k;
									else fim = k + 1;
								}

								subExp[j].erase(ini, fim - ini + 1);
								if(subExp[j].size() == 3 || subExp[j].size() == 4) flag = 0;
							}
						}
					}
				}
			}
			else if(subExp[i][2] == 'b'){
				for(int j = 0; j < subExp.size(); j++){
					if(j == i) continue;	
				
					for(int k = 0; k < subExp[j].size(); k++){
						if(subExp[j][k] == 'b'){
							if(subExp[j][k - 1] == '-'){
								subExp.erase(subExp.begin()+j);
								j--;
								break;
							}
							else{
								int ini, fim;
								if(subExp[j][k - 1] != '('){
									ini = k - 1;
									fim = k;
								}
								else if(subExp[j][k - 1] == '('){
									ini = k;
									if(subExp[j][k + 1] == ')') fim = k;
									else fim = k + 1;
								}
								
								subExp[j].erase(ini, fim - ini + 1);
								if(subExp[j].size() == 3 || subExp[j].size() == 4) flag = 0;
							}
						}
					}
				}
			}
			else if(subExp[i][2] == 'c'){
				for(int j = 0; j < subExp.size(); j++){
					if(j == i) continue;	
				
					for(int k = 0; k < subExp[j].size(); k++){
						if(subExp[j][k] == 'c'){
							if(subExp[j][k - 1] == '-'){
								subExp.erase(subExp.begin()+j);
								j--;
								break;
							}
							else{
								int ini, fim;
								if(subExp[j][k - 1] != '('){
									ini = k - 1;
									fim = k;
								}
								else if(subExp[j][k - 1] == '('){
									ini = k;
									if(subExp[j][k + 1] == ')') fim = k;
									else fim = k + 1;
								}
								
								subExp[j].erase(ini, fim - ini + 1);
								if(subExp[j].size() == 3 || subExp[j].size() == 4) flag = 0;
							}
						}
					}
				}
			}
			else if(subExp[i][2] == 'd'){
				for(int j = 0; j < subExp.size(); j++){
					if(j == i) continue;	
				
					for(int k = 0; k < subExp[j].size(); k++){
						if(subExp[j][k] == 'd'){
							if(subExp[j][k - 1] == '-'){
								subExp.erase(subExp.begin()+j);
								j--;
								break;
							}
							else{
								int ini, fim;
								if(subExp[j][k - 1] != '('){
									ini = k - 1;
									fim = k;
								}
								else if(subExp[j][k - 1] == '('){
									ini = k;
									if(subExp[j][k + 1] == ')') fim = k;
									else fim = k + 1;
								}
								
								subExp[j].erase(ini, fim - ini + 1);
								if(subExp[j].size() == 3 || subExp[j].size() == 4) flag = 0;
							}
						}
					}
				}
			}
		}
		}
	}


	//for(int i = 0; i < subExp.size(); i++)
	//	cout << subExp[i] << " ";

	//cout << endl;
}

bool HornSAT(){
	for(int i = 0; i < subExp.size(); i++){
		if(subExp[i].size() == 2) return false;
	}

	return true;
}

int main(){
	freopen("Expressoes.in", "r", stdin);
	freopen("Expressoes.out", "w", stdout);

	int t, caso = 0;

	cin >> t;
	while(t--){
		subExp.clear();
		cin >> EXP;

		caso++;
		cout << "caso #" << caso << ": ";

		if(!isFNC()){
			cout << "nao esta na FNC" << endl;
			continue;
		}

		if(!isHorn()){
			cout << "nem todas as clausulas sao de horn" << endl;
			continue;
		}

		SUBEXP();
		int SAT = HornSAT();

		if(SAT)
			cout << "satisfativel" << endl;
		else
			cout << "insatisfativel" << endl;
	}

	return 0;
}
