// Class  TankLevel  is  declared(type)  in tanklevel.hpp.   Its  member  fn
// definitions are placed in tanklevel.cpp, the class implementation.

#ifndef TANKLEVEL_H
#define TANKLEVEL_H

// Qwt headers are in ui_tanklevel.h

// Qt headers
#include <QString>
#include <QLabel>
#include <QTimer>
#include <QWidget>

// #include <qwt_plot.h>
// #include <qwt_plot_grid.h>
// #include <qwt_plot_curve.h>

// for sinuplot
#include <qapplication.h>
#include <qlayout.h>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_series_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include <math.h>

// for sinuplot
// compiler error: 'QwtPlotGrid' does not name a type' occurrs otherwise.
class QwtPlotGrid;
class QwtPlotCurve;


// The 'using' directive  allows us to refer to  the Standard Template
// Library(STL)  members without the  std prefix,  or qualifed  by the
// namespace they belong to, as in std::cout becomes cout.
//
// The directive  lifts the namespace  members into the  nearest scope
// that  contains  both  the  namespace  and  the  'using'  directive.
// However, there  are other ways to  achive this, see  Lippman, but I
// suspect this is the most commonly used way.
using namespace std;


// Our class name, TankLevel, is defined within the Ui namespace.  Thus
// avoiding namespace pollution, so other programs can call a class by
// TankLevel name???
//
// I think this is here so  compiler wont barff at pointer ui in class
// declaration.  As  Ui is redefined  in ui_tanklevel.h to  have class
// TankLevel also derive publicly  from class Ui_TankLevel, the Qt GUI
// declaration.
namespace Ui{
  class TankLevel;
}


class TankLevel : public QWidget{

  Q_OBJECT
  // This class is subclassed(derived) from QObject and QWidget
  // parent classes.

    
public:
  // Public member fn's & data here may be accessed outside of member
  // fn's of this class.


  // Class DEFAULT  constructor, thus has no parameters  and no return
  // value.  However,  parent class constructor parameters  need to be
  // provided.   Note, default values  can only  be supplied  in class
  // declaration.
  explicit TankLevel(QWidget *parent = 0);

  // Class constructors,  have parameters but no  return value.  These
  // are examples of fn overloading; where fn name is the same but the
  // signatures  are  different,  that  is,  the type  and  number  of
  // parameters  are  different.    Again,  parent  class  constructor
  // parameters need to be provided.

  // Class DEFAULT destructor, thus has no parameters or return value.
  // There  can  only  be one  class  destructor  so  there is  no  fn
  // overloading.
  ~TankLevel();
    

private:
  // Private member data or fn's of THIS class can only be accessed directly
  // within member fn's of THIS class.  Outside of member fn's of THIS class
  // they can only be accessed via public member fn's defined for THIS class.
  //
  // Data is made private to avoid namespace pollution, allowing other
  // programmers to use your class without needing to worry that they have
  // called a variable in thier class/code by the same name.
  //
  // Access via member fn's is the safest as they have sanity checks in them,
  // details that the user of your class shouldn't need to have to worry


  // Pointer for GUI widgets in this class.
  Ui::TankLevel *ui;

  // Qt periodic event timer, for timout() signal & readSerialPort() slot.
  QTimer timer;

  // Mutator member functions, thus change class member data:
  void updatePlotLevel(void);
  void updateAbsoluteLevel(void);
  void updatePercentageLevel(void);

  // Reading the serial port contents member fn and member data.
  int readSerialPort(char *device);
  char *device; // Serial port device name.
  unsigned char charRead;  // Character read from the serial port.

  QwtPlotGrid *plotGrid;
  QwtPlotCurve *plotCurve;
  double time;
  double height;

};

#endif // TANKLEVEL_H
