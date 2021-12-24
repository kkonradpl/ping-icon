#ifndef PING_ICON_H
#define PING_ICON_H
#include <glibmm/ustring.h>
#include <gtkmm/statusicon.h>
#include <glibmm/dispatcher.h>

class PingIcon : public Gtk::StatusIcon
{
public:
    PingIcon(const Glib::ustring &, const Glib::ustring &, const Glib::ustring &, int, int);
    void notify(bool);

private:
    void dispatch();
    void loop();

    Glib::Dispatcher dispatcher;
    Glib::ustring icon_reachable;
    Glib::ustring icon_unreachable;
    Glib::ustring hostname;
    int interval;
    int timeout;
    int state_icon;
    bool state_thread;
};

#endif
