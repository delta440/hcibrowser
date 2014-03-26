#include <QApplication>
#include <stdexcept>
#include <iostream>
#include "basicbrowser.hh"
#include "imagebutton.hh"
//#include "linebutton.hh"
//#include "backicon.hh"
#include "downloadsbutton.hh"
using namespace std;


int main(int argc, char **argv) {
	try {
		QApplication app(argc, argv);
		BasicBrowser *bb = new BasicBrowser(
					"http://www.google.ca");
		DownloadsButton *btn = new DownloadsButton(35);
		bb->addBarButton(btn);
		bb->showMaximized();
		return app.exec();
	}
	catch (const exception& e) {
		cerr << "caught exception: " << e.what() << endl;
	}
	return -1;
}
