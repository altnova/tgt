//<	img tests
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>

#include <unistd.h>

#include <stdio.h>

// #include "../cfg/___.h"


Fl_Window *win;
Fl_Button *dog_1_button;
Fl_Button *dog_2_button;
Fl_Box 	*picbox;

Fl_JPEG_Image *startimg;
Fl_PNG_Image *dog_1_img;
Fl_PNG_Image *dog_2_img;



///////////////////////////////////////////////////////////////
//<							TASKS							>//
///////////////////////////////////////////////////////////////
//<															>//
//<		* 			V set_img(S png_name ); 				>//
//< 		draws png_name at staic coors in static 		>//
//<			picture box in static window only if called		>//
//<															>//
//<		* 				V set_win();						>//
//<			set main window, transparensy, click-through	>//
//<					size and static img_box;				>//
//<															>//
//<		*		V height_(); && V width_();					>//
//<			gets w/h into global width && height 			>//
//<															>//
//<	  	* 			C click_in(I x, I y);					>//
//<			returns 1 if last click-event had coordinates	>//
//<					IN_RAD(x, y);							>//
//<															>//
//<		* 		S dragged_file(I x, I y);					>//
//<			strange function for tracking user's file 		>//
//<			movements on desktop. If file dragged to 		>//
//<			IN_RAD(x, y) of kennel dog should eat it, so 	>//
//<				filename is returned						>//
//<															>//
//<			**************************************			>//
///////////////////////////////////////////////////////////////
	



void mybutton_cb(Fl_Widget* w, long int data)
{
	picbox->hide();
	picbox->redraw();


	if (data == 8) 
		picbox->image(dog_1_img);

	if (data == 4) 
		picbox->image(dog_2_img);

	picbox->set_visible();
	picbox->redraw();

}


void iter(Fl_box box)
{
	int i; 

	for (i = 0; ; i++) {
		usleep(1000000);

		box->hide();
		box->redraw();

		if (i%2)
			box->image(dog_1_img);
		else 
			box->image(dog_2_img);

		box->set_visible();
		box->redraw();
	}
}



/*class Mywin : public Fl_Window {
    void resize(int X, int Y, int W, int H) {
        Fl_Window::resize(X,Y,W,H);
        redraw();
        Fl::check();
    }

public:
    Mywin(int x,int y,int w, int h) : Fl_Window(x,y,w,h) {
    }
};
*/


class 

int main()
{

	win = new Fl_Window(100, 100, 500, 220, "FLTK image demo");		//<	set main window

	dog_1_button = 	new Fl_Button(50, 50, 80, 30, "dog_die");		//< two buttons, one callback ^_^
	dog_2_button = 	new Fl_Button(200, 50, 80, 30, "dog_read");

	dog_1_button->callback(mybutton_cb, 8);
	dog_2_button->callback(mybutton_cb, 4);

	startimg = new Fl_JPEG_Image("startimg.jpg");					//<	testing images
	dog_1_img = new Fl_PNG_Image("image_2.png");
	dog_2_img = new Fl_PNG_Image("myfile.png");

	picbox = new Fl_Box(100, 100, 100, 100);						//< image box

	picbox->image(startimg);										//<	just for start 

	win->end();
	win->show();													//<	make it visible and start 
	picbox->show();

	// printf("before run\n");

	int ftl = Fl::run();

	// printf("before iter\n");

	// iter();

	// printf("after iter\n");

	return ftl;
}