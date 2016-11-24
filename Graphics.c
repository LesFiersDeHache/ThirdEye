#include "gtk/gtk.h"
#include "Graphics.h"
#include "stdio.h"

GtkWidget *textview ;

struct mymultiple {
	GtkWidget *Pobject;
	gpointer *one;
	gpointer *two;
};


static void HELLO(GtkWidget *widget,gpointer data)
{
    gtk_label_set_text(GTK_LABEL(data),"you clicked it hihi");
    g_print("clicked \n");
}

static void openDialog(GtkWidget *button,struct mymultiple *data){
	gpointer *window = data->Pobject;
	gpointer *label = data->one;
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new("Choose a file",GTK_WINDOW(window),
		GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,
		GTK_RESPONSE_CANCEL,NULL);
	gtk_widget_show_all(dialog);
	gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
	char *s = "void";
	if(resp == GTK_RESPONSE_OK){

		s = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		g_print("%s\n",s);

	}
	else{
		g_print("YOU PRESSED CANCEL IDIOT\n");
	}
	gtk_widget_destroy(dialog);
	
}
void ChangeTxt(char *s){
	GtkTextBuffer *buffer = gtk_text_buffer_new (NULL);
    const gchar *t = s;
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer,&iter,0);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&iter,t,-1);
	gtk_text_view_set_buffer(textview,buffer);
}

// CALLED ON CLICK
void LoadNeuralNetwork(){
	g_print("Give me a NeauralNet Func\n");

}
void Read(){
	g_print("Give me a Read Func\n");

}
void SaveText(){
	g_print("Give me a Save Text Func\n");

}
// END CALLED ON CLICK


int Init(int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    GtkWidget *window,*button,*button2,*table,*button3,*button4;
    //gtk_window_set_default_size (GTK_WINDOW (window), 640, 480);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size (GTK_WINDOW (window), 640, 480);
    g_signal_connect(window,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    /*

    label = gtk_label_new("HelloWorld");
    button = gtk_button_new_with_label("Click me");
    g_signal_connect(button,"clicked",G_CALLBACK(HELLO),label);
    hbox = gtk_hbox_new(0,0);
    gtk_box_pack_start(GTK_BOX(hbox),label,1,1,0);
    gtk_box_pack_start(GTK_BOX(hbox),button,1,1,0);
    gtk_container_add(GTK_CONTAINER(window),hbox);*/

    table = gtk_table_new(4,4,0);
    button = gtk_button_new_with_mnemonic("_Load Text");
    button2 = gtk_button_new_with_mnemonic("_Load Neural Network");
    button3 = gtk_button_new_with_mnemonic("_Read");
    button4 = gtk_button_new_with_mnemonic("_Save Text");

    gtk_widget_set_sensitive(button3,FALSE);

    gtk_widget_set_sensitive(button4,FALSE);

    gtk_widget_set_sensitive(button2,FALSE);

    

    GtkTextBuffer *buffer = gtk_text_buffer_new (NULL);
    const gchar *t = "LUKA ET OUAIS";
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer,&iter,0);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&iter,t,-1);
    textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview), GTK_WRAP_WORD);

    struct mymultiple k;
    k.Pobject= window;
    g_signal_connect(button,"clicked",G_CALLBACK(openDialog),&k);

    g_signal_connect(button2,"clicked",G_CALLBACK(LoadNeuralNetwork),NULL);

    g_signal_connect(button3,"clicked",G_CALLBACK(Read),NULL);

    g_signal_connect(button4,"clicked",G_CALLBACK(SaveText),NULL);


    gtk_table_attach(GTK_TABLE(table),button,0,1,0,1,GTK_FILL,GTK_EXPAND|GTK_FILL,10,10);
    gtk_table_attach(GTK_TABLE(table),button2, 0,1,1,2,GTK_FILL,GTK_EXPAND|GTK_FILL,10,10);
    gtk_table_attach(GTK_TABLE(table),button3,3,4,3,4,GTK_FILL,GTK_FILL|GTK_EXPAND,10,10);
    gtk_table_attach(GTK_TABLE(table),button4,0,1,2,3,GTK_FILL,GTK_EXPAND|GTK_FILL,10,10);

    gtk_table_attach(GTK_TABLE(table),textview,1,4,0,3,GTK_EXPAND|GTK_FILL,GTK_FILL,2,2);


    /*gtk_table_attach(GTK_TABLE(table),label,0,2,1,2,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
    //gtk_table_attach(GTK_TABLE(table),image,1,2,0,1,GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
    gtk_table_attach(GTK_TABLE(table),button,1,2,0,1,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
    gtk_table_attach(GTK_TABLE(table),button2,0,1,0,1,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
    */
    gtk_container_add(GTK_CONTAINER(window),table);

    

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}