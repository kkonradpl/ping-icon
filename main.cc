#include <gtkmm/main.h>
#include <getopt.h>
#include "PingIcon.h"

#define DEFAULT_ICON_NAME "computer"
#define DEFAULT_INTERVAL  60
#define DEFAULT_TIMEOUT   5

struct ping_icon_conf_t
{
    const char *icon_reachable;
    const char *icon_unreachable;
    int interval;
    int timeout;
};

static void
show_usage()
{
    g_print("Usage: ping-icon [-r name] [-u name] [-i interval] [-t timeout] hostname\n");
    g_print("Options:\n");
    g_print("  -r  icon name for reachable state\n");
    g_print("  -u  icon name for unreachable state\n");
    g_print("  -i  interval (default: %d s)\n", DEFAULT_INTERVAL);
    g_print("  -t  timeout  (default: %d s)\n", DEFAULT_TIMEOUT);
    g_print("If both icons are unspecified, only reachable icon \"%s\" is used.\n", DEFAULT_ICON_NAME);
}

static void
parse_args(ping_icon_conf_t   &conf,
           int                 argc,
           char              **argv)
{
    int c;
    while((c = getopt(argc, argv, "hr:u:i:t:")) != -1)
    {
        switch(c)
        {
            case 'h':
                show_usage();
                exit(0);

            case 'r':
                conf.icon_reachable = optarg;
                break;

            case 'u':
                conf.icon_unreachable = optarg;
                break;

            case 'i':
                conf.interval = atoi(optarg);
                break;

            case 't':
                conf.timeout = atoi(optarg);
                break;

            case '?':
                if(optopt == 'r')
                    g_warning("No \"reachable\" icon name specified.");
                else if(optopt == 'u')
                    g_warning("No \"unreachable\" icon name specified.");
                else if(optopt == 'i')
                    g_warning("No interval given, using default (%d s).", DEFAULT_INTERVAL);
                else if(optopt == 't')
                    g_warning("No timeout given, using default (%d s).", DEFAULT_TIMEOUT);

                show_usage();
                break;

            default:
                break;
        }
    }
}

int
main(int    argc,
     char **argv)
{
    Gtk::Main app(argc, argv);
    ping_icon_conf_t conf;
    
    conf.icon_reachable = nullptr;
    conf.icon_unreachable = nullptr;
    conf.interval = DEFAULT_INTERVAL;
    conf.timeout = DEFAULT_TIMEOUT;
    
    parse_args(conf, argc, argv);
    gint hostname = argc - optind;

    if(hostname == 0)
    {
        show_usage();
        g_warning("No hostname specified.");
        return -1;
    }

    if(hostname > 1)
    {
        show_usage();
        g_warning("Multiple hostnames are not supported.");
        return -1;
    }

    if(conf.interval <= 1)
    {
        g_warning("Invalid interval given, using default (%d s).", DEFAULT_INTERVAL);
        conf.interval = DEFAULT_INTERVAL;
    }

    if(conf.timeout <= 0)
    {
        g_warning("Invalid timeout given, using default (%d s).", DEFAULT_TIMEOUT);
        conf.timeout = DEFAULT_TIMEOUT;
    }

    if(conf.interval < conf.timeout)
    {
        g_warning("Interval must be greater than timeout, using default values (%d/%d s)", DEFAULT_INTERVAL, DEFAULT_TIMEOUT);
        conf.interval = DEFAULT_INTERVAL;
        conf.timeout = DEFAULT_TIMEOUT;
    }

    if(!conf.icon_reachable &&
       !conf.icon_unreachable)
    {
        conf.icon_reachable = DEFAULT_ICON_NAME;
    }

    PingIcon icon(Glib::ustring(conf.icon_reachable ? conf.icon_reachable : ""),
                  Glib::ustring(conf.icon_unreachable ? conf.icon_unreachable : ""),
                  Glib::ustring(argv[optind]),
                  conf.interval,
                  conf.timeout);

    app.run();
    return 0;
}
