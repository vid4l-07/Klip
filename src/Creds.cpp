#include "Creds.h"
#include <string>
#include <vector>

std::string Creds::dump() const {
	return sitio + "\n\t" + user + "\n\t" + pass;
}

bool Creds::in(const std::vector<Creds>& vector) const {
	for (auto i : vector){
		if (sitio == i.sitio && user == i.user && pass == i.pass) return true;
	}
	return false;
}

bool Creds::operator==(const Creds& otro) const {
	return sitio == otro.sitio && user == otro.user && pass == otro.pass;
}
