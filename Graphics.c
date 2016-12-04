#include "gtk/gtk.h"
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <assert.h>
#include "NeuralNet.h"
#include "Sigmoid.h"
#include <time.h>
#include "list.h"
#include "CutBitmap.h"
#include "SDLstuff.h"
#include "Bitmap.h"
#include "Matrix.h"
#include "resize.h"
#include "save.h"
#include "Graphics.h"
#include "listB.h"



GtkWidget *textview,*button,*button2,*button3,*button4 ;
	char *s;

struct mymultiple {
	GtkWidget *Pobject;
	gpointer *one;
	gpointer *two;
};



static void openDialog(GtkWidget *button,gpointer *window){
	GtkWidget *dialog;
    (void)(button);
	dialog = gtk_file_chooser_dialog_new("Choose a file",GTK_WINDOW(window),
		GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,
		GTK_RESPONSE_CANCEL,NULL);
	gtk_widget_show_all(dialog);
	gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
	if(resp == GTK_RESPONSE_OK){

		s = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		g_print("%s\n",s);

	}
	else{
		g_print("YOU PRESSED CANCEL\n");
	}
	gtk_widget_destroy(dialog);
    if(s!= NULL){
        // HERE YOU DO WHAT YOU WANT AFTER THE FILE EXPLORER CLOSE
        // YOU SHOULD LOAD THE IMAGE 
        //SHOWING RAW IMAGE
        //display_image(load_image(s));
        //display Binarize Image
        Bitmap B =  LoadToBitmap(s);
        display_image(BitmapToSurface(&B));
        //display_image(BitmapToSurface(&B));
        //DoAll(&B);
        List * K = CutAll(&B);
	Bitmap Kline = DrawLines(&B,K);
	display_image(BitmapToSurface(&Kline));
        gtk_widget_set_sensitive(button2,TRUE);
        gtk_widget_set_sensitive(button3,TRUE);
        gtk_widget_set_sensitive(button4,FALSE);
        SDL_Quit();
	//struct listB *res = sendList(L,&B);
    }

	
}


void ChangeTxt(char *s){
    // Call This func to Change the Text in THe texview.
	GtkTextBuffer *buffer = gtk_text_buffer_new (NULL);
    const gchar *t = s;
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer,&iter,0);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&iter,t,-1);
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(textview),buffer);
}

// CALLED ON CLICK
void LoadNeuralNetwork(){
	g_print("Weight and bias Loaded\n");
    g_print("Neural Network Init\n");

    //if success
    gtk_widget_set_sensitive(button4,TRUE);
}
void Read(){
    g_print("ReadBut LOL\n");

}
void SaveText(){
	g_print("Give me a Save Text Func\n");

}
// END CALLED ON CLICK

int Init(int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    GtkWidget *window,*table;
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
    g_signal_connect(button,"clicked",G_CALLBACK(openDialog),window);

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
