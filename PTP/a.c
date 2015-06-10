#include <gtk/gtk.h>

void ao(GtkWodget *w,gpointer *p,gpointer *q){
	printf("%d",(int)p);
	printf("%d",(int)q);
}

int main( int argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *table;

  GtkWidget *warn;

  gtk_init(&argc, &argv);

  GtkBuilder *builder;
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "test.glade",NULL);
	
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"MenuP"));
	GtkWidget *buttonC = GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
	GtkWidget *buttonS = GTK_WIDGET(gtk_builder_get_object(builder,"button7"));
	GtkWidget *buttonA = GTK_WIDGET(gtk_builder_get_object(builder,"button5"));
	GtkWidget *buttonI = GTK_WIDGET(gtk_builder_get_object(builder,"Sair1"));
	
	/* Conectando os sinais */
	
	g_signal_connect (G_OBJECT (buttonA), "clicked", G_CALLBACK (a), (gpointer)12,(gpointer)14);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
