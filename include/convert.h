
/*
*
*
*
*	Convert Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.15
*
*	Updated by Bonbon	2015.01.15
*
*/


#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <iostream>


namespace Matrix
{
    class Convert
    {
    public:
        // convert object to string
        template <class T>
        static std::string ToStr(T value);

        // convert int to string
        static std::string Int2Str(int value);

        // convert string to int
        static int Str2Int(std::string value);
    };

}

#endif
