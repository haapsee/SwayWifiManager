#ifndef GTK_H
#define GTK_H

#include <gtkmm.h>
#include <vector>
#include <string>
#include "../networking/networking_interface.h"


class MainWindow : public Gtk::Window
{
public:
    MainWindow(std::vector<WifiNetwork> wifi_networks);
    virtual ~MainWindow();
private:
    void on_button_close();
    void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item);
    Glib::RefPtr<Gtk::StringList> string_list;
};


class GtkManager
{
public:
    GtkManager();
    virtual ~GtkManager();
    int createWindow(std::vector<WifiNetwork> wifi_networks);
private:
    Glib::RefPtr<Gtk::Application> app;
};

#endif // GTK_H