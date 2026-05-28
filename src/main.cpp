#include "ui/app/app.h"
#include "term/term.h"

int main(int argc, char* argv[]){
	Terminal term;
	term.disable_ctrl_c();

	App main(term);
	main.start();

}
