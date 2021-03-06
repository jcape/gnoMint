//  gnoMint: a graphical interface for managing a certification authority
//  Copyright (C) 2006-2009 David Marín Carreño <davefx@gmail.com>
//
//  This file is part of gnoMint.
//
//  gnoMint is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 3 of the License, or   
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of 
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef GNOMINTCLI


#include <glib-object.h>
#include <gtk/gtk.h>

#else

#include <glib.h>

#endif

#include <glib/gi18n.h>
#include <stdlib.h>
#include <string.h>
#include <ca_file.h> 

#include "ca_policy.h"


#ifndef GNOMINTCLI

extern GtkBuilder * certificate_properties_window_gtkb;

gint __ca_policy_populate_step (void *pArg, int argc, char **argv, char **columnNames);

gint __ca_policy_populate_step (void *pArg, int argc, char **argv, char **columnNames)
{
	GHashTable * policy_table = (GHashTable *) pArg;

	g_hash_table_insert (policy_table, g_strdup (argv[1]), g_strdup(argv[2]));

	return 0;
}

void ca_policy_populate (guint64 ca_id) 
{
	GObject * widget;
	gint value;
	gchar * strvalue;
	GHashTable *policy_table = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);	

	ca_file_foreach_policy (__ca_policy_populate_step, ca_id, policy_table);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "C_INHERIT");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "country_inherited_check");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "country_same_radiobutton")), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "country_differ_radiobutton")), value);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "ST_INHERIT");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "state_inherited_check");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "state_same_radiobutton")), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "state_differ_radiobutton")), value);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "L_INHERIT");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "city_inherited_check");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "city_same_radiobutton")), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "city_differ_radiobutton")), value);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "O_INHERIT");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "organization_inherited_check");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "organization_same_radiobutton")), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "organization_differ_radiobutton")), value);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "OU_INHERIT");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "ou_inherited_check");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "ou_same_radiobutton")), value);
        gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "ou_differ_radiobutton")), value);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "C_FORCE_SAME");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "country_same_radiobutton");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "ST_FORCE_SAME");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "state_same_radiobutton");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "L_FORCE_SAME");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "city_same_radiobutton");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "O_FORCE_SAME");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "organization_same_radiobutton");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

        strvalue = (gchar *) g_hash_table_lookup (policy_table, "OU_FORCE_SAME");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "ou_same_radiobutton");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "HOURS_BETWEEN_CRL_UPDATES");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "hours_between_crl_updates_spinbutton");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), value);

	strvalue = ((gchar *) g_hash_table_lookup (policy_table, "CRL_DISTRIBUTION_POINT"));
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "crl_distribution_point_entry");
	if (strvalue)
		gtk_entry_set_text (GTK_ENTRY(widget), strvalue);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "MONTHS_TO_EXPIRE");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "months_before_expiration_spinbutton2");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "CA");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "ca_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "CRL_SIGN");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "crl_signing_check1");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "NON_REPUDIATION");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "non_repudiation_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "DIGITAL_SIGNATURE");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "digital_signature_check4");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "KEY_ENCIPHERMENT");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "key_encipherment_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "KEY_AGREEMENT");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "key_agreement_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "DATA_ENCIPHERMENT");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "data_encipherment_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "TLS_WEB_SERVER");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "webserver_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "TLS_WEB_CLIENT");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "webclient_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "TIME_STAMPING");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "time_stamping_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "CODE_SIGNING");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "code_signing_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "EMAIL_PROTECTION");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "email_protection_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);
	
	strvalue = (gchar *) g_hash_table_lookup (policy_table, "OCSP_SIGNING");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "ocsp_signing_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);

	strvalue = (gchar *) g_hash_table_lookup (policy_table, "ANY_PURPOSE");
	value = strvalue ? atoi(strvalue) : 0;
	widget = gtk_builder_get_object (certificate_properties_window_gtkb, "any_purpose_check2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget), value);
	
        g_hash_table_destroy (policy_table);
}

#endif


#ifndef GNOMINTCLI

G_MODULE_EXPORT void ca_policy_expiration_spin_button_change (gpointer spin_button, gpointer userdata)
{
	GObject * widget = gtk_builder_get_object (certificate_properties_window_gtkb, "certificate_properties_dialog");
	gchar * cert_id_str = (gchar *) g_object_get_data (G_OBJECT(widget), "cert_id");
	guint64 cert_id;
 
	if (! cert_id_str)
		return;

	if (! spin_button)
		return;

	cert_id = atoll(cert_id_str);

	ca_file_policy_set_int (cert_id, "MONTHS_TO_EXPIRE", gtk_spin_button_get_value(spin_button));

}

G_MODULE_EXPORT void ca_policy_crl_update_spin_button_change (gpointer spin_button, gpointer userdata)
{
	GObject * widget = gtk_builder_get_object (certificate_properties_window_gtkb, "certificate_properties_dialog");
	gchar * cert_id_str = (gchar *) g_object_get_data (G_OBJECT(widget), "cert_id");
	guint64 cert_id;

	if (! cert_id_str)
		return;

	if (! spin_button)
		return;

	cert_id = atoll(cert_id_str);

	ca_file_policy_set_int (cert_id, "HOURS_BETWEEN_CRL_UPDATES", gtk_spin_button_get_value(spin_button));

}

G_MODULE_EXPORT void ca_policy_crl_distribution_point_change(gpointer gtkentry, gpointer userdata)
{
	GObject * widget = gtk_builder_get_object (certificate_properties_window_gtkb, "certificate_properties_dialog");
	gchar * cert_id_str = (gchar *) g_object_get_data (G_OBJECT(widget), "cert_id");
	guint64 cert_id;

	if (! cert_id_str)
		return;

	if (! gtkentry)
		return;

	cert_id = atoll(cert_id_str);

	ca_file_policy_set (cert_id, "CRL_DISTRIBUTION_POINT", gtk_entry_get_text(gtkentry));

}

G_MODULE_EXPORT void ca_policy_toggle_button_toggled (gpointer button, gpointer userdata)
{
	GObject * widget = gtk_builder_get_object (certificate_properties_window_gtkb, "certificate_properties_dialog");
	gchar * cert_id_str = (gchar *) g_object_get_data (G_OBJECT(widget), "cert_id");
	guint64 cert_id;

	gchar *property_name = NULL;
        gboolean is_active;
	
	if (! cert_id_str)
		return;

	if (! button)
		return;

	const gchar * widget_name = gtk_buildable_get_name(GTK_BUILDABLE(button));


	cert_id = atoll(cert_id_str);
	
        is_active = gtk_toggle_button_get_active(button);

	if (! strcmp(widget_name, "country_inherited_check")) {
		property_name = "C_INHERIT";
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "country_same_radiobutton")), is_active);
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "country_differ_radiobutton")), is_active);
        }
        
	if (! strcmp(widget_name, "state_inherited_check")) {
		property_name = "ST_INHERIT";        
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "state_same_radiobutton")), is_active);
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "state_differ_radiobutton")), is_active);
        } 

	if (! strcmp(widget_name, "city_inherited_check")) {
		property_name = "L_INHERIT";        
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "city_same_radiobutton")), is_active);
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "city_differ_radiobutton")), is_active);
        }

	if (! strcmp(widget_name, "organization_inherited_check")) {
		property_name = "O_INHERIT";   
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "organization_same_radiobutton")), is_active);
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "organization_differ_radiobutton")), is_active);
        }

	if (! strcmp(widget_name, "ou_inherited_check")) {
		property_name = "OU_INHERIT";        
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "ou_same_radiobutton")), is_active);
                gtk_widget_set_sensitive (GTK_WIDGET(gtk_builder_get_object (certificate_properties_window_gtkb, "ou_differ_radiobutton")), is_active);
        }

	if (! strcmp(widget_name, "country_same_radiobutton"))
		property_name = "C_FORCE_SAME";        
        

	if (! strcmp(widget_name, "state_same_radiobutton"))
		property_name = "ST_FORCE_SAME";        

	if (! strcmp(widget_name, "city_same_radiobutton"))
		property_name = "L_FORCE_SAME";        

	if (! strcmp(widget_name, "organization_same_radiobutton"))
		property_name = "O_FORCE_SAME";        

	if (! strcmp(widget_name, "ou_same_radiobutton"))
		property_name = "OU_FORCE_SAME";        

	



	if (! strcmp(widget_name, "ca_check2"))
		property_name = "CA";

	if (! strcmp(widget_name, "crl_signing_check1"))
		property_name = "CRL_SIGN";
		
	if (! strcmp(widget_name, "non_repudiation_check2")) {
                if (! is_active) {
                        // TIME_STAMPING cannot be inactive
                        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                              "time_stamping_check2")), FALSE);
                        // We must check if EMAIL_PROTECTION can be active
                        if (! ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") &&
                            ! ca_file_policy_get (cert_id, "KEY_ENCIPHERMENT") &&
                            ! ca_file_policy_get (cert_id, "KEY_AGREEMENT")) {
                                // If none is active, we must deactivate EMAIL_PROTECTION
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb,
                                                                                                      "email_protection_check2")), FALSE);
                        }

                        // We must check if OCSP_SIGNING can be active
                        if (! ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE")) {
                                // If is not active, we must deactivate OCSP_SIGNING
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb,
                                                                                                      "ocsp_signing_check2")), FALSE);
                        }
                        
                }
		property_name = "NON_REPUDIATION";
        }
		
	if (! strcmp(widget_name, "digital_signature_check4")) {
                if (! is_active) {
                        // We must check if TLS_WEB_SERVER can be active
                        if (! ca_file_policy_get (cert_id, "KEY_ENCIPHERMENT") &&
                            ! ca_file_policy_get (cert_id, "KEY_AGREEMENT")) {
                                // If none is active, we must deactivate TLS_WEB_SERVER
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "webserver_check2")), FALSE);
                        }

                        // We must check if TLS_WEB_CLIENT can be active
                        if (! ca_file_policy_get (cert_id, "KEY_AGREEMENT")) {
                                // If none is active, we must deactivate TLS_WEB_CLIENT
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "webclient_check2")), FALSE);
                        }

                        // TIME_STAMPING and CODE_SIGNING cannot be active if digital signature is deactivated
                        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object(certificate_properties_window_gtkb,
                                                                                             "time_stamping_check2")), FALSE);

                        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object(certificate_properties_window_gtkb,
                                                                                             "code_signing_check2")), FALSE);

                        // We must check if EMAIL_PROTECTION can be active
                        if (! ca_file_policy_get (cert_id, "NON_REPUDIATION") &&
                            ! ca_file_policy_get (cert_id, "KEY_ENCIPHERMENT") &&
                            ! ca_file_policy_get (cert_id, "KEY_AGREEMENT")) {
                                // If none is active, we must deactivate EMAIL_PROTECTION
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "email_protection_check2")), FALSE);
                        }

                        // We must check if OCSP_SIGNING can be active
                        if (! ca_file_policy_get (cert_id, "NON_REPUDIATION")) {
                                // If none is active, we must deactivate OCSP_SIGNING
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "ocsp_signing_check2")), FALSE);
                        }


                }
		property_name = "DIGITAL_SIGNATURE";
        }
		
	if (! strcmp(widget_name, "key_encipherment_check2")) {
                if (! is_active) {
                        // We must check if TLS_WEB_SERVER can be active
                        if (! ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") &&
                            ! ca_file_policy_get (cert_id, "KEY_AGREEMENT")) {
                                // If none is active, we must deactivate TLS_WEB_SERVER
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "webserver_check2")), FALSE);
                        }

                        // We must check if EMAIL_PROTECTION can be active
                        if (! ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") &&
                            ! ca_file_policy_get (cert_id, "NON_REPUDIATION") &&
                            ! ca_file_policy_get (cert_id, "KEY_AGREEMENT")) {
                                // If none is active, we must deactivate EMAIL_PROTECTION
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "email_protection_check2")), FALSE);
                        }


                }
		property_name = "KEY_ENCIPHERMENT";		
        }

	if (! strcmp(widget_name, "key_agreement_check2")) {
                if (! is_active) {
                        // We must check if TLS_WEB_SERVER can be active
                        if (! ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") &&
                            ! ca_file_policy_get (cert_id, "KEY_ENCIPHERMENT")) {
                                // If none is active, we must deactivate TLS_WEB_SERVER
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "webserver_check2")), FALSE);
                        }
                        // We must check if TLS_WEB_CLIENT can be active
                        if (! ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE")) {
                                // If none is active, we must deactivate TLS_WEB_CLIENT
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "webclient_check2")), FALSE);
                        }

                        // We must check if EMAIL_PROTECTION can be active
                        if (! ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") &&
                            ! ca_file_policy_get (cert_id, "NON_REPUDIATION") &&
                            ! ca_file_policy_get (cert_id, "KEY_ENCIPHERMENT")) {
                                // If none is active, we must deactivate EMAIL_PROTECTION
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "email_protection_check2")), FALSE);
                        }
                }

		property_name = "KEY_AGREEMENT";
        }

		
	if (! strcmp(widget_name, "data_encipherment_check2"))
		property_name = "DATA_ENCIPHERMENT";





        // Purposes


	if (! strcmp(widget_name, "webserver_check2")) {
                if (is_active) {
                        // We must check digitalSignature || keyEncipherment || keyAgreement
                        if (!( ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") ||
                               ca_file_policy_get (cert_id, "KEY_ENCIPHERMENT") ||
                               ca_file_policy_get (cert_id, "KEY_AGREEMENT"))) {
                                // If none is active, we activate key encipherment
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "key_encipherment_check2")), TRUE);
                        }
                               
                }
                property_name = "TLS_WEB_SERVER";
        }

	if (! strcmp(widget_name, "webclient_check2")) {
                if (is_active) {
                        // We must check digitalSignature || keyEncipherment || keyAgreement
                        if (!( ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") ||
                               ca_file_policy_get (cert_id, "KEY_AGREEMENT"))) {
                                // If none is active, we activate digital signature
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "digital_signature_check4")), TRUE);
                        }
                        
                }
                property_name = "TLS_WEB_CLIENT";
        }

	if (! strcmp(widget_name, "time_stamping_check2")){
                if (is_active) {
                        // We must check digitalSignature && nonRepudiation
                        if (!( ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") &&
                               ca_file_policy_get (cert_id, "NON_REPUDIATION"))) {
                                // If none is active, we activate them both
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "digital_signature_check4")), TRUE);
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "non_repudiation_check2")), TRUE);
                        }
                               
                }
		property_name = "TIME_STAMPING";
        }

	if (! strcmp(widget_name, "code_signing_check2")) {
                if (is_active) {
                        // We must check digitalSignature
                        if (!( ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE"))) {
                                // If it is not active, we activate it
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "digital_signature_check4")), TRUE);
                        }
                        
                }
		property_name = "CODE_SIGNING";
        }

	if (! strcmp(widget_name, "email_protection_check2")) {
                if (is_active) {
                        // We must check digitalSignature || nonRepudiation || (keyEncipherment || keyAgreement)
                        if (!( ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") ||
                               ca_file_policy_get (cert_id, "NON_REPUDIATION") ||
                               ca_file_policy_get (cert_id, "KEY_ENCIPHERMENT") ||
                               ca_file_policy_get (cert_id, "KEY_AGREEMENT"))) {
                                // If none is active, we activate key encipherment
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "digital_signature_check4")), TRUE);
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "key_encipherment_check2")), TRUE);
                        }
                               
                }
  		property_name = "EMAIL_PROTECTION";
        }

	if (! strcmp(widget_name, "ocsp_signing_check2")) {
                if (is_active) {
                        // We must check digitalSignature || nonRepudiation
                        if (!( ca_file_policy_get (cert_id, "DIGITAL_SIGNATURE") ||
                               ca_file_policy_get (cert_id, "NON_REPUDIATION"))) {
                                // If none is active, we activate digital signature
                                gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_builder_get_object (certificate_properties_window_gtkb, 
                                                                                                      "digital_signature_check4")), TRUE);
                        }
                               
                }
		property_name = "OCSP_SIGNING";
        }

	if (! strcmp(widget_name, "any_purpose_check2"))
		property_name = "ANY_PURPOSE";

	if (property_name)
		ca_file_policy_set_int (cert_id, property_name, is_active);

}

#endif

