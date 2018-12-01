// Image demo
#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xmd.h>
#include <X11/Xatom.h>

#include <FL/x.H>

// Global pointers for the GUI objects
Fl_Window *mywindow;
Fl_Button *button;
// Fl_Button *dogbutton;
Fl_Box *mypicturebox;
Fl_JPEG_Image *startimg;
Fl_PNG_Image *dog_1;
Fl_PNG_Image *dog_2;

extern Display *fl_display;
extern Window fl_window;
extern GC fl_gc;
extern int fl_screen;
extern XVisualInfo *fl_visual;
extern Colormap fl_colormap;

Display* fl_display;
bool is_transparent = 1;

double alpha = 0.8;

bool pic = 0;



void mybutton_cb(Fl_Widget * w)
{
	
	Atom atom = XInternAtom(fl_display, "_NET_WM_WINDOW_OPACITY", False); 
	uint32_t opacity = (is_transparent) ? (uint32_t)(0xFFFFFFFF * alpha) : (uint32_t)(0xC0000000 * alpha);
	is_transparent = (is_transparent) ? 0 : 1;

	XChangeProperty(fl_display, fl_xid(mywindow), 
                atom, XA_CARDINAL, 32, PropModeReplace, 
                (unsigned char*)&opacity, 1L); 

	printf("x: %d\ty: %d\n", Fl::event_x(), Fl::event_y());

	mywindow->end();
	mywindow->show();

	mypicturebox->hide();
	mypicturebox->redraw();

	mypicturebox->image(pic ? dog_1 : dog_2);
	pic = (pic) ? 0 : 1;


	mypicturebox->set_visible();
	mypicturebox->redraw();
}



int main()
{
	int height = Fl::h();
	int width = Fl::w();

	// The main window
	mywindow = new Fl_Window(0, height - 200, width, 200);
	mywindow->border(0);

	button = new Fl_Button(0, 0, width, 50);
	button->callback(mybutton_cb);

	// Fl::handle(Fl::event_y(), mywindow);

	printf("%d height; %d width\n", Fl::h(), Fl::w());

	// Load some images to use later
	startimg = new Fl_JPEG_Image("startimg.jpg");
	dog_1 = new Fl_PNG_Image("die_1.png");
	dog_2 = new Fl_PNG_Image("love_1.png");

	// A box for the image
	mypicturebox = new Fl_Box(width/2 - 50, 50, 100, 100);

	// Give it some initial contents
	mypicturebox->image(startimg);

	// Make the window visible and start processing events
	mywindow->end();
	mywindow->show();
	return Fl::run();
}