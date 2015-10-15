#include <QApplication>
#include <QPushButton>
#include <QString>

using namespace std;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QPushButton button;

  QObject::connect(&button, SIGNAL(clicked()), &app, SLOT(quit()));
  button.show();
  return app.exec();
}
