// TODO generar contrasenas, editar, buscar contrasena
#include <array>
#include <cstdlib>
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

void cls(){
	#ifdef _WIN32
	system("cls");
	#else
	system("clear");
	#endif
}

bool log_in(){
	ifstream archivo_pass("password.txt");
	string password;
	getline(archivo_pass, password);
	if (!archivo_pass || password == ""){
		string pass;
		ofstream archivo_nuevo("password.txt");
		cout << "No se ha encontrado ninguna contrasena, ingrese una: " << flush;

		getline(cin, pass);
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

			if (encriptar(trypass) == password){
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
	archivo_pass.close();
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


struct Creds{
	string sitio;
	string user;
	string pass;

	string dump() const {
		return sitio + "\n\t" + user + "\n\t" + pass;
	}

	bool operator==(const Creds otro) const {
		return sitio == otro.sitio && user == otro.user && pass == otro.pass;
	}
};

bool in(Creds cred, vector<Creds> vector){
	bool esta = false;
	for (auto i : vector){
		if (cred == i){
			esta = true;
		}
	}

	return esta;
}

vector<Creds> dump_passwords(){
	vector<Creds> data_vector;
	string format;
	format += "\nContrsenas:\n";

	ifstream db("db.txt");
	string file_content;

	while (getline(db, file_content, '|')){
		array<string, 3> content = split(file_content, ';');
		Creds c = {desencriptar(content.at(0)), desencriptar(content.at(1)), desencriptar(content.at(2))};
		data_vector.push_back(c);
	}
	return data_vector;
}

vector<Creds> find_pass(string sitio, vector<Creds> data_vector){
	vector<Creds> creds_vec;
	if (sitio == ""){
		return data_vector;
	}
	for (Creds i : data_vector){
		if (i.sitio == sitio){
			creds_vec.push_back(i);
		}
	}
	return creds_vec;
}

Creds new_pass(){
	string site;
	string user;
	string pass;
	cout << "Introduzca el sitio: " << flush;
	getline(cin, site);
	cout << "Introduzca el usuario: " << flush;
	getline(cin, user);
	cout << "Introduzca la contrasena: " << flush;
	getline(cin, pass);
	Creds c = {site, user, pass};
	return c;
}

void update_db(vector<Creds> data_vector){
	string append = "";
	for (Creds i:data_vector){
		append += encriptar(i.sitio) + ";" + encriptar(i.user) + ";" + encriptar(i.pass) + ";|";
	}
	ofstream db("db.txt");
	db << append;
	db.close();
}

int elegir(){
		cout << "> " << flush;
		string eleccion_str;
		getline(cin, eleccion_str);
		int eleccion;
		// try {
			eleccion = stoi(eleccion_str);
		// } catch (...) {
		// 	continue;
		// }
		return eleccion;
}

int main(){
	bool login_check = log_in();
	if (!login_check) {
		return 1;
	}

	string eleccion;
	while(true){
		string banner0 ="┌──────────────────────────┐\n"
						"│     PASSWORD MANAGER     │\n"
						"├──────────────────────────┤\n"
						"│ 1. Ver contraseñas       │\n"
						"│ 2. Añadir nueva          │\n"
						"│ 3. Ayuda                 │\n"
						"│ 99. Salir                │\n"
						"└──────────────────────────┘\n";
		string banner1 ="┌──────────────────────────┐\n"
						"│     PASSWORD MANAGER     │\n"
						"├──────────────────────────┤\n"
						"│ 1. Filtrar por sitio     │\n"
						"│ 2. Editar                │\n"
						"│ 99. Volver               │\n"
						"└──────────────────────────┘\n";
		cout << banner0 << endl;

		int eleccion = elegir();
		vector<Creds> data_vector = dump_passwords();

		switch (eleccion) {
			case 1: {  // ver contrasenas
				int eleccion = 0;
				vector<Creds> result_vector = data_vector;
				while (eleccion != 99) {
					cls();
					cout << banner1 << endl;
					string format;
					for (int i = 0; i < data_vector.size(); i++){
						if (in(data_vector.at(i), result_vector)){
							format += to_string(i) + ". " + data_vector.at(i).dump() + "\n";
						}
					}
					cout << format << endl;

					eleccion = elegir();
					switch (eleccion){
						case 1: { // filtrar
							string sitio;
							cout << "Introduce el sitio: " << flush;
							getline(cin, sitio);
							result_vector = find_pass(sitio, data_vector);
							break;
						}
						case 2: { // editar
							cout << "\nIntroduce el indice" << endl;
							int indice = elegir();
							if (indice > data_vector.size()){
								cout << "No existe" << endl;
								break;
							}
							string new_user;
							string new_pass;
							cout << "Introduce nuevo usuario (vacio para no modificar): ";
							getline(cin, new_user);
							cout << "Introduce nueva contrasena (vacio para no modificar): ";
							getline(cin, new_pass);
							cout << "\nUsuario: " << new_user << "\nContrasena: " << new_pass;
							cout << "\nContinuar? (y/N)";
							string continuar;
							getline(cin, continuar);
							if (continuar == "y"){
								if (new_user != ""){
									data_vector.at(indice).user = new_user;
								}
								if (new_pass != ""){
									data_vector.at(indice).pass = new_pass;
								}
								update_db(data_vector);
							}
							result_vector = data_vector;
							break;
						}
					}
				}
				cls();
				break;
			}
			case 2:  // nueva contrasena
				cls();
				data_vector.push_back(new_pass());
				update_db(data_vector);
				break;
			case 3:  // editar
				cls();
				break;
			case 99:  // exit
				return 0;
				break;
		}
	}
	return 1;
}
