#include <gtk/gtk.h>     //Carrega os recursos do GTK


int main(int argc,char *argv[]){
	gtk_init(&argc,&argv);
	glade_init();
	//Inicializa o GTK
	//Inicializa o Glade – Isto geralmente é opcional
	glade_xml_new("test.glade","window1",NULL); //Lê o arquivo com a estrutura XML da sua aplicação
	glade_xml_signal_autoconnect(xml); //Conecta todos os sinais aos seus manipuladores
	gtk_main(); // O Loop de eventos do GTK
	return 0;
}
