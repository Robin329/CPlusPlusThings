// -----------------------------------------------------------------------------
#include "GUI.h" // for Simple_window only (doesn't really belong in Window.h)

namespace Graph_lib {
// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation
class Window;
struct Simple_window : Window {
    Simple_window(Point xy, int w, int h, const string& title);

    bool wait_for_button();

    void wait_for_button_modified()
    // modified event loop
    // handle all events (as per default), but quit when button_pushed becomes true
    // this allows graphics without control inversion
    {
        while (!button_pushed) Fl::wait();
        button_pushed = false;
        Fl::redraw();
    }

    Button next_button;

private:
    bool button_pushed;

    static void cb_next(Address, Address addr) // callback for next_button
    //	{ reference_to<Simple_window>(addr).next(); }
    {
        static_cast<Simple_window*>(addr)->next();
    }

    void next();
};

} // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
