#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string encriptar(const string& texto) {
	int clave = 3;
    string resultado = texto;

    for (int i = 0; i < texto.length(); i++) {
        resultado[i] = texto[i] + clave;
    }

    return resultado;
}

string desencriptar(const string& texto) {
	int clave = 3;
    string resultado = texto;

    for (int i = 0; i < texto.length(); i++) {
        resultado[i] = texto[i] - clave;
    }

    return resultado;
}

bool log_in(){
	ifstream archivo_pass("password.txt");
	string password;
	getline(archivo_pass, password);
	archivo_pass.close();

	if (!archivo_pass || password == ""){
		string pass;
		ofstream archivo_nuevo("password.txt");
		cout << "No se ha encontrado ninguna contrasena, ingrese una: " << flush;

		cin >> pass;
		archivo_nuevo << encriptar(pass);
		archivo_nuevo.close();
		ofstream db("db.txt");
		db << "";
		db.close();

	}else{
		string trypass;
		bool correcto = false;
		getline(archivo_pass, password);

		int i = 3;
		while (i != 0){
			cout << "Ingrese la contrasena: " << flush;
			getline(cin, trypass);
			auto hash_trypass = encriptar(trypass);

			if (hash_trypass == password){
				correcto = true;
				break;

			}else{
				cout << "Contrasena incorrecta" << endl;
				i--;
			}
		}
		if (correcto){
			return true;
		}
	}
	return false;
}

array<string, 3> split(const string& data, char separador){
	array<string, 3> array;
	string temp;
	int i = 0;
	for (char c : data){
		if (i == 3) { break; }

		if (c == separador){
			array[i] = temp;
			temp = "";
			i++;
		}
		else { temp += c; }
	}
	return array;
}

int main(){
	bool login_check = log_in();
	if (!login_check) {
		return 1;
	}

	string eleccion;
	while(true){
		cout << "Contrsenas: " << endl;

		ifstream db("db.txt");
		string file_content;
		string format;
		vector<std::array<string, 3 >> data_vector;

		while (getline(db, file_content, '|')){
			data_vector.push_back(split(file_content, ';'));
		}

		for (int i = 0; i < data_vector.size(); i++){
			format += to_string(i) + ". ";

			int count = 0;
			for (auto j : data_vector.at(i)){
				if (count == 0){
					format += desencriptar(j) + ":\n"; 
				}
				else{
					format += "\t";
					format += desencriptar(j) + "\n";
				}
				count ++;
			}
		}
		cout << format << flush;

		cout << "> " << flush;
		string eleccion;
		cin >> eleccion;

		if (eleccion == "help"){
			cout << "\n============\nNumero del sitio\nn para nueva contrasena\nexit para salir" << endl;
		}
		if (eleccion == "exit"){
			break;
		}

		if (eleccion == "n"){
			string site;
			string user;
			string pass;
			cout << "Introduzca el sitio: " << flush;
			cin >> site;
			cout << "Introduzca el usuario: " << flush;
			cin >> user;
			cout << "Introduzca la contrasena: " << flush;
			cin >> pass;
			
			string append = encriptar(site) + ";" + encriptar(user) + ";" + encriptar(pass) + ";|";
			std::ofstream db("db.txt", std::ios::app);
			db << append;
			db.close();
		} else {
			array<string, 3> array;
			try {
				int indice = stoi(eleccion);
				array = data_vector.at(indice);
				continue;
			} catch (const std::exception&) {
				cout << "Eleccion no valida\n";
				continue;
			}

			for ( auto i : array ){
				cout << i;
			}
		}
	}
	return 0;
}
