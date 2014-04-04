#include <QApplication>
#include <stdexcept>
#include <iostream>
#include "basicbrowser.hh"
#include "bubblesbrowser.hh"
using namespace std;


int main(int argc, char **argv) {
	try {
		QApplication app(argc, argv);
        //BasicBrowser *bb = new BasicBrowser("http://www.thinkbroadband.com/download.html");
        BubblesBrowser *bb = new BubblesBrowser("http://www.thinkbroadband.com/download.html");
		bb->showMaximized();
		return app.exec();
	}
	catch (const exception& e) {
		cerr << "caught exception: " << e.what() << endl;
	}
	return -1;
}
