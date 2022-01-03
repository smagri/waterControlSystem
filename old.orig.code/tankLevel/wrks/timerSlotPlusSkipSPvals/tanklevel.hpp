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


// for sinuplot
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>


// Concrete Tank Perameters in meters.
#define TANK_DIAMETER 8.6
#define TANK_RADIUS (TANK_DIAMETER/2)
#define TANK_HEIGHT 2.28
#define TANK_LEVEL_MAX_CM_DIGITS 3


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

    
private slots:
  // QTimer, timer, slot/callback function.
  void timerCbk(void);
  

private:
  // Private member data or fn's of THIS class can only be accessed directly
  // within member fn's of THIS class.  Outside of member fn's of THIS class
  // they can only be accessed via public member fn's defined for THIS class.
  //
  // Data is made private to avoid namespace pollution, allowing other
  // programmers to use your class without needing to worry that they have
  // called a variable in thier class/code by the same name.
  //
  // Access via member fn's is the safest as they have sanity checks in them,q
  // details that the user of your class shouldn't need to have to worry


  // Pointer for GUI widgets in this class.
  Ui::TankLevel *ui;

  // Qt periodic event timer, when it's timout() signal occurs the
  // timerCbk() slot/callback function is called.
  QTimer timer;

  // Mutator member functions, thus change class member data:
  void updatePlotLevel(void);
  void updateAbsoluteLevel(char *readStr);
  void updatePercentageLevel(char *readStr);

  // Reading the serial port contents member fn and member data.
  int readSerialPort(char *device, char *readStr);
  //
  // Character string read from the serial port.
  // char *readStr = new char[10]; 
  //
  // 'new' operator not allowed here, ie definition.  However, definition for
  // other types(ie non char*) is allowed here.
  //

  char *device; // Serial port device name.

  // Integer representation of EACH INDIVIDUAL digit read from serial port.
  int readIntS[TANK_LEVEL_MAX_CM_DIGITS];
 
  // Integer representation of ALL digits COMBINED read from serial port.
  int readInt;


  QwtPlotGrid *plotGrid;
  QwtPlotCurve *plotCurve;
  double time;
  double height;

  //QwtPlot *uiPtr2qwtPlot;


};

#endif // TANKLEVEL_H
