#include "ui/main/main_menu.h"
#include "term/term.h"

int main(int argc, char* argv[]){
	Terminal term;

	MainMenu main(term);
	main.start();

}
