#include <QApplication>
#include <stdexcept>
#include <iostream>
#include "basicbrowser.hh"
#include "bubblesbrowser.hh"
using namespace std;

// This is dirty, but makes things much easier.
QApplication *app;


int main(int argc, char **argv) {
	try {
		app = new QApplication(argc, argv);
		//BasicBrowser *bb = new BasicBrowser("http://www.thinkbroadband.com/download.html");
		BubblesBrowser *bb = new BubblesBrowser("http://www.thinkbroadband.com/download.html");
		cout<<bb->height()<<endl;
		bb->showMaximized();
		return app->exec();
	}
	catch (const exception& e) {
		cerr << "caught exception: " << e.what() << endl;
	}
	return -1;
}
