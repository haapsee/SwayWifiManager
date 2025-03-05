#ifndef GTK_H
#define GTK_H

#include <gtkmm.h>
#include <vector>
#include <string>
#include "../networking/networking_interface.h"


class WifiNetworkColumns : public Glib::Object
{
public:
    Glib::ustring ssid;
    Glib::ustring mode;
    Glib::ustring channel;
    Glib::ustring signal;
    Glib::ustring security;

    static Glib::RefPtr<WifiNetworkColumns> create(
        const Glib::ustring& ssid,
        const Glib::ustring& mode,
        const Glib::ustring& channel,
        const Glib::ustring& signal,
        const Glib::ustring& security
    )
      {
        return Glib::make_refptr_for_instance<WifiNetworkColumns>(
            new WifiNetworkColumns(ssid, mode, channel, signal, security));
      }
protected:
    WifiNetworkColumns(
        const Glib::ustring& ssid,
        const Glib::ustring& mode,
        const Glib::ustring& channel,
        const Glib::ustring& signal,
        const Glib::ustring& security
    )
      : ssid(ssid),
        mode(mode),
        channel(channel),
        signal(signal),
        security(security)
    {
    }
};

class MainWindow : public Gtk::Window
{
public:
    MainWindow(std::vector<WifiNetwork> wifi_networks);
    virtual ~MainWindow();
private:
    void on_button_close();
    void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item, Gtk::Align halign);
    void on_bind_ssid(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_mode(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_channel(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_signal(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_security(const Glib::RefPtr<Gtk::ListItem>& list_item);

    Glib::RefPtr<Gio::ListStore<WifiNetworkColumns>> list_store;
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