// Image demo

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>

// Global pointers for the GUI objects
Fl_Window *mywindow;
Fl_Button *spiderbutton;
Fl_Button *dogbutton;
Fl_Box *mypicturebox;
Fl_JPEG_Image *startimg;
Fl_PNG_Image *dog_1;
Fl_PNG_Image *dog_2;


void mybutton_cb(Fl_Widget * w, long int data)
{
	mypicturebox->hide();
	mypicturebox->redraw();


	if (data == 8) {
		mypicturebox->image(dog_1);
	}
	if (data == 4) {
		mypicturebox->image(dog_2);
	}

	mypicturebox->redraw();

	mypicturebox->set_visible();
	mypicturebox->redraw();
}


int main()
{
	// The main window
	mywindow = new Fl_Window(300, 220, "FLTK image demo");

	// Two buttons, sharing one callback
	spiderbutton = new Fl_Button(50, 50, 50, 30, "Spider");
	dogbutton = new Fl_Button(200, 50, 50, 30, "Dog");

	 
	spiderbutton->callback(mybutton_cb, 8);
	dogbutton->callback(mybutton_cb, 4);

	// Load some images to use later
	startimg = new Fl_JPEG_Image("startimg.jpg");
	dog_1 = new Fl_PNG_Image("die_1.png");
	dog_2 = new Fl_PNG_Image("love_1.png");

	// A box for the image
	mypicturebox = new Fl_Box(100, 100, 100, 100);

	// Give it some initial contents
	mypicturebox->image(startimg);

	// Make the window visible and start processing events
	mywindow->end();
	mywindow->show();
	return Fl::run();
}