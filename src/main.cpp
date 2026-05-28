#include "ui/app/app.h"
#include "term/term.h"

int main(int argc, char* argv[]){
	Terminal term;

	App main(term);
	main.start();

}
