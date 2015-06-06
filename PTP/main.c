#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "interface.c"
#include "apoio_interface.c"
#include "Without.c"

float saldo=0;
Produto produtos[300];

int main (int argc, char *argv[]){

	MyApp *app;

	gtk_init (&argc, &argv);
	app = g_slice_new (MyApp);
	app->windows = NULL;
	
	/* create first window */
	MenuP(NULL, app);
	
	gtk_main ();
	g_slice_free (MyApp, app);
	printf("%f",saldo);
	return 0;               
}
