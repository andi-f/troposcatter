// Troposcatter.c Troposcatter calculate the whole loss over a troposcatter path

/*
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 * 
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#define PROGRAM "Troposcatter"
#define VERSION  "v 1.1a GTK"
#define COPYRIGHT "DL2FZN 2013"
#define COMMENT "Troposcatter calculate the whole loss over a troposcatter path"
#define URI "http://home.arcor.de/afischer1/afu/troposcatter.html"

typedef struct {
GtkWidget *qrg;
GtkWidget *qrb;
GtkWidget *pwr_1;
GtkWidget *pwr_2;
GtkWidget *ant_gain_1;
GtkWidget *ant_gain_2;
GtkWidget *nf_1;
GtkWidget *nf_2;
GtkWidget *rx_1_2;
GtkWidget *rx_2_1;
} example;

void calculate(GtkWidget *widget, example *data);
void about(GtkWidget *widget, gpointer data);

int main(int argc, char *argv[]) {
	example data;
	GtkWidget *window;
	GtkWidget *table;
	GtkWidget *vbox;

	GtkWidget *qrg;
	GtkWidget *qrb;
	GtkWidget *pwr_1;
	GtkWidget *pwr_2;
	GtkWidget *ant_gain_1;
	GtkWidget *ant_gain_2;
	GtkWidget *nf_1;
	GtkWidget *nf_2;
	GtkWidget *rx_1_2;
	GtkWidget *rx_2_1;

	GtkAdjustment *adj_qrg, *adj_qrb, *adj_pwr_1, *adj_pwr_2,
				*adj_gain_1, *adj_gain_2,*adj_nf_1,*adj_nf_2;

	GtkWidget *toolbar;
	GtkToolItem *quit;
	GtkToolItem *info;

	GtkWidget *label0;
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *label5;
	GtkWidget *label6;
	GtkWidget *label7;
	GtkWidget *label8;
	GtkWidget *label9;
	GtkWidget *label10;
	GtkWidget *label11;
	GtkWidget *label12_1,*label12_2;
	GtkWidget *label13_1,*label13_2,*label13_3,*label13_4,*label13_5,*label13_6;

	GtkWidget *button;

	gtk_init(&argc, &argv);

	//Main window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), "Troposcatter");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	// vertical box for toolbar
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add(GTK_CONTAINER (window), vbox);

	toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);

	quit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), quit, -1);
	info = gtk_tool_button_new_from_stock(GTK_STOCK_HELP);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), info, -1);
	
	g_signal_connect(G_OBJECT(quit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(info), "clicked", GTK_SIGNAL_FUNC(about), NULL);
	
	gtk_box_pack_start(GTK_BOX (vbox), toolbar, FALSE, FALSE, 2);

	table = gtk_table_new(12, 5, FALSE);
	gtk_box_pack_end (GTK_BOX (vbox), table, TRUE, TRUE, 20);

	label0 = gtk_label_new("Bandwidth 2200Hz/Temperature 290K");
	label1 = gtk_label_new("QRG");
	label2 = gtk_label_new("MHz");
	label3 = gtk_label_new("QRB");
	label4 = gtk_label_new("km");
	label5 = gtk_label_new("Station 1");
	label6 = gtk_label_new("Station 2");
	label7 = gtk_label_new("Power");
	label8 = gtk_label_new("Antenna gain");
	label9 = gtk_label_new("NF RX");
	label10 = gtk_label_new("Signal over Noise");
	label11 = gtk_label_new("Signal over Noise");
	label12_1 = gtk_label_new("W");
	label12_2 = gtk_label_new("W");
	label13_1 = gtk_label_new("dBD");
	label13_2 = gtk_label_new("dBD");
	label13_3 = gtk_label_new("dB");
	label13_4 = gtk_label_new("dB");
	label13_5 = gtk_label_new("dB");
	label13_6 = gtk_label_new("dB");

	adj_qrg = (GtkAdjustment *) gtk_adjustment_new(144,144,241000,1,10,0);
	qrg = gtk_spin_button_new(adj_qrg,0,0);
	
	adj_qrb = (GtkAdjustment *) gtk_adjustment_new(100,0,4000,1,10,0);
	qrb = gtk_spin_button_new(adj_qrb,0,0);
	
	adj_pwr_1 = (GtkAdjustment *) gtk_adjustment_new(100,0,1000,1,10,0);
	pwr_1 = gtk_spin_button_new(adj_pwr_1,0,0);
	adj_pwr_2 = (GtkAdjustment *) gtk_adjustment_new(100,0,1000,1,10,0);
	pwr_2 = gtk_spin_button_new(adj_pwr_2,0,0);
	
	adj_gain_1 = (GtkAdjustment *) gtk_adjustment_new(13.0,0,40,0.1,1,0);
	ant_gain_1 = gtk_spin_button_new(adj_gain_1,0,1);
	adj_gain_2 = (GtkAdjustment *) gtk_adjustment_new(13.0,0,40,0.1,1,0);
	ant_gain_2 = gtk_spin_button_new(adj_gain_2,0,1);

	adj_nf_1 = (GtkAdjustment *) gtk_adjustment_new(1.0,0,10,0.1,1,0);
	nf_1 = gtk_spin_button_new(adj_nf_1,0,1);
	adj_nf_2 = (GtkAdjustment *) gtk_adjustment_new(1.0,0,10,0.1,1,0);
	nf_2 = gtk_spin_button_new(adj_nf_2,0,1);

	rx_1_2 = gtk_label_new("");
	rx_2_1 = gtk_label_new("");

	button = gtk_button_new_with_label("Calculate");
	gtk_signal_connect(GTK_OBJECT(button), "clicked",GTK_SIGNAL_FUNC(calculate), (gpointer*) &data);

	// Header
	gtk_table_attach(GTK_TABLE(table), label0, 1, 4, 0, 1,
		GTK_EXPAND | GTK_SHRINK, GTK_EXPAND | GTK_SHRINK, 5, 5);

	// Input field QRG
	gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), qrg, 1, 2, 1, 2,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label2, 2, 3, 1, 2, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	// Input field QRB
	gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 2, 3,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), qrb, 1, 2, 2, 3,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label4, 2, 3, 2, 3, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	//Stations
	gtk_table_attach(GTK_TABLE(table), label5, 1, 2, 3, 4,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label6, 3, 4, 3, 4, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	//Power of stations
	gtk_table_attach(GTK_TABLE(table), label7, 0, 1, 5, 6,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), pwr_1, 1, 2, 5, 6,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label12_1, 2, 3, 5, 6,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), pwr_2, 3, 4, 5, 6,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label12_2, 5, 6, 5, 6,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	//Antenna gain
	gtk_table_attach(GTK_TABLE(table), label8, 0, 1, 6, 7, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), ant_gain_1, 1, 2, 6, 7, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label13_1, 2, 3, 6, 7, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), ant_gain_2, 3, 4, 6, 7, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label13_2, 4, 5, 6, 7, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	//Noise figure RX
	gtk_table_attach(GTK_TABLE(table), label9, 0, 1, 7, 8, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), nf_1, 1, 2, 7, 8, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label13_3, 2, 3, 7, 8, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), nf_2, 3, 4, 7, 8, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label13_4, 4, 5, 7, 8, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	// Signal TX 2 at RX 1
	gtk_table_attach(GTK_TABLE(table), label10, 1, 2, 8, 9,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), rx_1_2, 1, 2, 9, 10,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label13_5, 2, 3, 9, 10,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	// Signal TX 1 at RX 2
	gtk_table_attach(GTK_TABLE(table), label11, 3, 4, 8, 9, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), rx_2_1, 3, 4, 9, 10,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label13_6, 4, 5, 9, 10,
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
		
	gtk_table_attach(GTK_TABLE(table), button, 1, 2, 11, 12, 
		GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	data.qrg = qrg;
	data.qrb = qrb;
	data.pwr_1 = pwr_1;
	data.pwr_2 = pwr_2;
	data.ant_gain_1 = ant_gain_1;
	data.ant_gain_2 = ant_gain_2;
	data.nf_1 = nf_1;
	data.nf_2 = nf_2;
	data.rx_1_2 = rx_1_2;
	data.rx_2_1 = rx_2_1;
	
	gtk_widget_show_all(window);

	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();

	return 0;
}

void calculate(GtkWidget *widget, example *data)	{
	double	S_12;
	double	S_21;
	double	ts_loss;
	double	fr_loss;
	char buf[10];

	gdouble f = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->qrg));
	gdouble d = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->qrb));
	gdouble tx_pwr1 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->pwr_1));
	gdouble tx_pwr2 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->pwr_2));
	gdouble ant_gain1 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->ant_gain_1));
	gdouble ant_gain2 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->ant_gain_2));
	gdouble rx_nf1 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->nf_1));
	gdouble rx_nf2 = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->nf_2)); 

	fr_loss = 32.45 + 20*log10(f) + 20*log10(d);

	tx_pwr1 = 10 * log10(tx_pwr1/0.001);
	tx_pwr2 = 10 * log10(tx_pwr2/0.001);

	ts_loss = 24.44 + 4.283 * log(f) + 0.06656 * d;

	S_21 = ant_gain1 + ant_gain2 + tx_pwr1 + 140 - fr_loss - rx_nf2 - ts_loss;
	S_12 = ant_gain1 + ant_gain2 + tx_pwr2 + 140 - fr_loss - rx_nf1 - ts_loss;

	sprintf(buf,"%3.0f",S_12);
	gtk_label_set_text(GTK_LABEL(data->rx_1_2),buf);
	sprintf(buf,"%3.0f",S_21);
	gtk_label_set_text(GTK_LABEL(data->rx_2_1),buf);
}

// Callback for about
void about(GtkWidget *widget, gpointer data) {
  GtkWidget *dialog = gtk_about_dialog_new();
  gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), PROGRAM);
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), VERSION); 
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), COPYRIGHT);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), COMMENT);
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), URI);
  gtk_dialog_run(GTK_DIALOG (dialog));
  gtk_widget_destroy(dialog);
 }  
