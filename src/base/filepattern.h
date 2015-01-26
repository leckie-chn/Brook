// Copyright 2014 PKU-Cloud
// Author: Chao Ma (mctt90@gmail.com)
//
// Operations with file patterns
//
#ifndef BASE_FILEPATTERN_H_
#define BASE_FILEPATTERN_H_

#include <glob.h>
#include <string>

// Given a filepattern as a string, this class find mached files.
// Usage:
/*
 const string filepattern = "/usr/include/g*.h";
 FilepatternMatcher m(filepattern);
 for (int i = 0 ; i < m.NumMatched(); ++i) {
     printf("Found %s\n", m.Matched(i));
 }
*/
class FilepatternMatcher {
public:
    explicit FilepatternMatcher(const std::string& filepattern);
    ~FilepatternMatcher();

    bool NoError() const;
    int NumMatched() const;
    const char* Matched(int i) const;
private:
    static int ErrorFunc(const char* epath, int eerrno); // The error handler.
    int glob_return_;
    glob_t glob_result_;
};
#endif // BASE_FILEPATTERN_H_
