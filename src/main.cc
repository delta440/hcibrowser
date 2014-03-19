#include <QApplication>
#include <stdexcept>
#include <iostream>
#include "basicbrowser.hh"
#include "imagebutton.hh"
using namespace std;


int main(int argc, char **argv) {
	try {
		QApplication app(argc, argv);
		BasicBrowser *bb = new BasicBrowser(
					"http://www.uleth.ca/artsci/math-computer-science");
		bb->showMaximized();
		return app.exec();
	}
	catch (const exception& e) {
		cerr << "caught exception: " << e.what() << endl;
	}
	return -1;
}
