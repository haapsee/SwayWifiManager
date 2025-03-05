/**
 * MIT License
 * 
 * Copyright (c) 2025 Eemil Haapsaari
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "gtk.h"

MainWindow::MainWindow(std::vector<WifiNetwork> wifi_networks)
{
    set_title("Sway Network Manager");
    set_default_size(400, 200);
    
    Gtk::Button button("Quit");
    button.set_hexpand(true);
    button.set_halign(Gtk::Align::END);
    button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_close));

    list_store = Gio::ListStore<WifiNetworkColumns>::create();

    for (int i = 0; i < wifi_networks.size(); i++) {
        WifiNetwork wifi_network = wifi_networks[i];
        list_store->append(WifiNetworkColumns::create(
            wifi_network.ssid,
            wifi_network.mode,
            wifi_network.channel,
            wifi_network.signal,
            wifi_network.security
        ));
    }

    auto selection_model = Gtk::SingleSelection::create(list_store);
    
    auto factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
        &MainWindow::on_setup_label), Gtk::Align::END));
    factory->signal_bind().connect(
        sigc::mem_fun(*this, &MainWindow::on_bind_ssid));
    auto column_ssid = Gtk::ColumnViewColumn::create("SSID", factory);
    column_ssid->set_expand(true);

    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
        &MainWindow::on_setup_label), Gtk::Align::END));
    factory->signal_bind().connect(
        sigc::mem_fun(*this, &MainWindow::on_bind_mode));
    auto column_mode = Gtk::ColumnViewColumn::create("Mode", factory);
    column_mode->set_expand(true);

    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
        &MainWindow::on_setup_label), Gtk::Align::END));
    factory->signal_bind().connect(
        sigc::mem_fun(*this, &MainWindow::on_bind_channel));
    auto column_channel = Gtk::ColumnViewColumn::create("Channel", factory);
    column_channel->set_expand(true);

    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
        &MainWindow::on_setup_label), Gtk::Align::END));
    factory->signal_bind().connect(
        sigc::mem_fun(*this, &MainWindow::on_bind_signal));
    auto column_signal = Gtk::ColumnViewColumn::create("Signal", factory);
    column_signal->set_expand(true);

    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
        &MainWindow::on_setup_label), Gtk::Align::END));
    factory->signal_bind().connect(
        sigc::mem_fun(*this, &MainWindow::on_bind_security));
    auto column_security = Gtk::ColumnViewColumn::create("Security", factory);
    column_security->set_expand(true);

    Gtk::ColumnView columnView;
    columnView.add_css_class("data-table");
    columnView.set_model(selection_model);
    columnView.append_column(column_ssid);
    columnView.append_column(column_mode);
    columnView.append_column(column_channel);
    columnView.append_column(column_signal);
    columnView.append_column(column_security);


    Gtk::ScrolledWindow scrolledWindow;
    scrolledWindow.set_expand(true);
    scrolledWindow.set_child(columnView);

    Gtk::Box vbox(Gtk::Orientation::VERTICAL);
    vbox.append(scrolledWindow);
    vbox.append(button);
    vbox.set_margin(5);

    set_child(vbox);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item, Gtk::Align halign)
{
    list_item->set_child(*Gtk::make_managed<Gtk::Label>("", halign));
}

void MainWindow::on_bind_ssid(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto col = std::dynamic_pointer_cast<WifiNetworkColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if (!label)
        return;
    label->set_halign(Gtk::Align::START);
    label->set_text(col->ssid);
}

void MainWindow::on_bind_mode(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto col = std::dynamic_pointer_cast<WifiNetworkColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if (!label)
        return;
    label->set_halign(Gtk::Align::START);
    label->set_text(col->mode);
}

void MainWindow::on_bind_channel(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto col = std::dynamic_pointer_cast<WifiNetworkColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if (!label)
        return;
    label->set_halign(Gtk::Align::START);
    label->set_text(col->channel);
}

void MainWindow::on_bind_signal(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto col = std::dynamic_pointer_cast<WifiNetworkColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if (!label)
        return;
    label->set_halign(Gtk::Align::START);
    label->set_text(col->signal);
}

void MainWindow::on_bind_security(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto col = std::dynamic_pointer_cast<WifiNetworkColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if (!label)
        return;
    label->set_text(col->security);
}


void MainWindow::on_button_close()
{
    set_visible(false);
}


GtkManager::GtkManager()
{
    this->app = Gtk::Application::create("com.example.swaynetworkmanager");
}

GtkManager::~GtkManager()
{
}

int GtkManager::createWindow(std::vector<WifiNetwork> wifi_networks)
{   
    return this->app->make_window_and_run<MainWindow>(0, nullptr, wifi_networks);
}