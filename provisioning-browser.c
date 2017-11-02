#include <stdio.h>
#include <signal.h>
#include <string.h>

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

void maximize();

static WebKitWebView* web_view;
static GtkWidget *window;
gchar* default_url = "https://github.com/pschultz/kiosk-browser/blob/master/README.md";

static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);
static void shutdown_uri_scheme_request_cb (WebKitURISchemeRequest *request, gpointer user_data);

int main(int argc, char** argv) {
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_signal_connect(window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
  g_signal_connect(web_view, "close", G_CALLBACK(closeWebViewCb), window);

  web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());

  WebKitWebContext* context = webkit_web_view_get_context(web_view);
  webkit_web_context_register_uri_scheme(context, "shutdown", shutdown_uri_scheme_request_cb, NULL, NULL);

  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));

  if(argc > 1) {
    webkit_web_view_load_uri(web_view, argv[1]);
  }
  else {
    webkit_web_view_load_uri(web_view, default_url);
  }

  maximize();

  gtk_widget_grab_focus(GTK_WIDGET(web_view));
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

void maximize() {
  //gtk_window_maximize(GTK_WINDOW(window));
  gtk_window_fullscreen(GTK_WINDOW(window));
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

  GdkDisplay *display = gtk_widget_get_display(GTK_WIDGET(web_view));
  GdkWindow *win = gtk_widget_get_window(GTK_WIDGET(web_view));
  GdkMonitor *monitor = gdk_display_get_monitor_at_window(display, win);
  GdkRectangle geometry;

  gdk_monitor_get_geometry(monitor, &geometry);
  gtk_window_set_default_size(GTK_WINDOW(window), geometry.width, geometry.height);
}

static void destroyWindowCb(GtkWidget* widget, GtkWidget* window) {
    gtk_main_quit();
}

static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window) {
    gtk_widget_destroy(window);
    return TRUE;
}

static void
shutdown_uri_scheme_request_cb (WebKitURISchemeRequest *request,
                             gpointer                user_data) {
  gtk_main_quit();
}
