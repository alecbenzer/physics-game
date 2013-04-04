#ifndef _HELP_H
#define _HELP_H

// from http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml#Copy_Constructors
//
// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#endif  // _HELP_H
