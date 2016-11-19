#include "gtk/gtk.h"
#include "Graphics.h"
#include "stdio.h"
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
	if(s != "void"){
		FILE *INFILE = fopen(s,"r");
		if(INFILE==NULL){
			printf("error can't open the file");
		}
		else{
			char s[83] ;
			char final[83*5];
			int ch ;
			int compt = 0;
			while((ch = getc(INFILE)) != EOF && compt <80){
				s[compt] = ch;
				compt++;

			}
			gtk_label_set_text(GTK_LABEL(label),s);
			
		}
	}
}


int Init(int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    GtkWidget *window,*label,*button,*button2,*table,*image;
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
    image = gtk_image_new_from_file("/home/lucas/Work/ThirdEye/ThirdEyeLogoB2.png");
    button = gtk_button_new_with_mnemonic("_Start");

    button2 = gtk_button_new_with_mnemonic("_ChoseImage");
    label = gtk_label_new("HIHI");
    struct mymultiple k;
    k.Pobject= window;
    k.one = label;
    g_signal_connect(button2,"clicked",G_CALLBACK(openDialog),&k);
    gtk_table_attach(GTK_TABLE(table),label,0,2,1,2,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
    //gtk_table_attach(GTK_TABLE(table),image,1,2,0,1,GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
    gtk_table_attach(GTK_TABLE(table),button,1,2,0,1,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
    gtk_table_attach(GTK_TABLE(table),button2,0,1,0,1,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
    gtk_container_add(GTK_CONTAINER(window),table);

    

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}