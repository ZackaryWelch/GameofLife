/*
 * File: termmanip.h
 * Purpose: To have fun messing with people's terminals, and making
 *          lots of colorful and interesting programs.
 *
 *          This provides a nice little interface to the ANSI escape
 *          sequence set.
 */
#ifndef TERMMANIP_H
#define TERMMANIP_H
#include <iostream>
#include <string>
#include <sstream>

/* 
 * Graphic Mode Modifiers
 */
inline std::ostream& normal(std::ostream &os) {
  return os << "\033[0m";
}


inline std::ostream& bold(std::ostream &os) {
  return os << "\033[1m";
}


inline std::ostream& underline(std::ostream &os) {
  return os << "\033[4m";
}


inline std::ostream& blink(std::ostream &os) {
  return os << "\033[5m";
}


inline std::ostream& reverseVideo(std::ostream &os) {
  return os << "\033[7m";
}



/*
 * Foreground Color Graphic Mode Modifiers
 */
inline std::ostream& black(std::ostream &os) {
  return os << "\033[30m";
}


inline std::ostream& red(std::ostream &os) {
  return os << "\033[31m";
}


inline std::ostream& green(std::ostream &os) {
  return os << "\033[32m";
}


inline std::ostream& yellow(std::ostream &os) {
  return os << "\033[33m";
}


inline std::ostream& blue(std::ostream &os) {
  return os << "\033[34m";
}


inline std::ostream& magenta(std::ostream &os) {
  return os << "\033[35m";
}


inline std::ostream& cyan(std::ostream &os) {
  return os << "\033[36m";
}


inline std::ostream& white(std::ostream &os) {
  return os << "\033[37m";
}

/*
 * Foreground Color Graphic Mode Modifiers
 */
inline std::ostream& blackBackground(std::ostream &os) {
  return os << "\033[40m";
}


inline std::ostream& redBackground(std::ostream &os) {
  return os << "\033[41m";
}


inline std::ostream& greenBackground(std::ostream &os) {
  return os << "\033[42m";
}


inline std::ostream& yellowBackground(std::ostream &os) {
  return os << "\033[43m";
}


inline std::ostream& blueBackground(std::ostream &os) {
  return os << "\033[44m";
}


inline std::ostream& magentaBackground(std::ostream &os) {
  return os << "\033[45m";
}


inline std::ostream& cyanBackground(std::ostream &os) {
  return os << "\033[46m";
}


inline std::ostream& whiteBackground(std::ostream &os) {
  return os << "\033[47m";
}


/*
 * Simple terminal commands
 */
inline std::ostream& clearScreen(std::ostream &os) {
  return os << "\033[2J";
}


inline std::ostream& clearLine(std::ostream &os) {
  return os << "\033[K";
}


inline std::ostream& saveCursor(std::ostream &os) {
  return os << "\033[s";
}


inline std::ostream& restoreCursor(std::ostream &os) {
  return os << "\033[u";
}


/*
 * This class is used by commands requiring arguments
 */
class ArgSequence {
  public:
    ArgSequence(std::string seq) {
      this->seq = seq;
    }

    std::ostream& operator()(std::ostream &os) const {
      return os << seq;
    }
  
  private:
    std::string seq;
};


//overload the << operator so ostream can use the sequence!
inline std::ostream& operator<<(std::ostream& os, const ArgSequence& aSeq) {
  return aSeq(os);
}


/*
 * Commands requiring arguments
 */
inline ArgSequence cursorUp(int value) {
  //compute the arg sequence
  std::ostringstream os;
  os << "\033[" << value << "A";

  //return the result
  return ArgSequence(os.str());
}


inline ArgSequence cursorDown(int value) {
  //compute the arg sequence
  std::ostringstream os;
  os << "\033[" << value << "B";

  //return the result
  return ArgSequence(os.str());
}


inline ArgSequence cursorForward(int value) {
  //compute the arg sequence
  std::ostringstream os;
  os << "\033[" << value << "C";

  //return the result
  return ArgSequence(os.str());
}


inline ArgSequence cursorBackward(int value) {
  //compute the arg sequence
  std::ostringstream os;
  os << "\033[" << value << "D";

  //return the result
  return ArgSequence(os.str());
}


inline ArgSequence cursorPosition(int x, int y) {
  //compute the arg sequence
  std::ostringstream os;
  os << "\033[" << y << ";" << x << "H";

  //return the result
  return ArgSequence(os.str());
}


inline std::ostream& cursorOff(std::ostream &os) {
  return os << "\033[?25l";
}


inline std::ostream& cursorOn(std::ostream &os) {
  return os << "\033[?25h";
}

#endif
