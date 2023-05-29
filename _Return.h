#pragma once
#ifndef C_LOX__RETURN_H
#define C_LOX__RETURN_H

#include <stdexcept>
#include "global.h"

using namespace std;
class _Return{
public:
    const any value;
    _Return(any value): value(value){};
};
#endif //LISP_RETURN_H
