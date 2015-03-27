// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef SYSTEM_FILEPATTERN_H_
#define SYSTEM_FILEPATTERN_H_

#include <glob.h>
#include <string>

// Given a filepattern as a string, this class find named mached files.
// Usage:
/*
 const string filepattern "/usr/include/g*.h"
 FilepatternMatcher m(filepattern);
 for (int i = 0 ; i < m.NumMatched(); ++i) {
     printf("Found %s\n", m.Matched());
 }
 */
class FilepatternMatcher {

};

#endif // SYSTEM_FILEPATTERN_H_
