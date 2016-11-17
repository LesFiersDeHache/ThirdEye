#include "gtk/gtk.h"
#include "Graphics.h"

static void HELLO(GtkWidget *widget,gpointer data)
{
    gtk_label_set_text(GTK_LABEL(data),"you clicked it hihi");
    g_print("clicked \n");
}


int Init(int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    GtkWidget *window,*label,*button,*button2,*table;
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

    table = gtk_table_new(2,2,0);
    button = gtk_button_new_with_mnemonic("_Start");
    button2 = gtk_button_new_with_mnemonic("_ChoseImage");
    label = gtk_label_new("HIHI");
    g_signal_connect(button2,"clicked",G_CALLBACK(HELLO),label);
    //gtk_table_attach(GTK_TABLE(table),label,1,1,1,1,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
    gtk_table_attach(GTK_TABLE(table),button,1,2,1,2,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
    gtk_table_attach(GTK_TABLE(table),button2,0,1,0,1,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);

    gtk_container_add(GTK_CONTAINER(window),table);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}