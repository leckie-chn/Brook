// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/consistency.h"

namespace brook {

//-----------------------------------------------------------
// Implementation of Consistency
//-----------------------------------------------------------
void Consistency::Wait() {
    
}

void Consistency::Increase() {

}

//-----------------------------------------------------------
// Implementation of BSP
//-----------------------------------------------------------
bool BSP::Judge() {

    return true;
}

//-----------------------------------------------------------
// Implementation of Asychronous.
//-----------------------------------------------------------
bool Asychronous::Judge() {

    return true;
}

//-----------------------------------------------------------
// Implementation of SSP.
//-----------------------------------------------------------
bool SSP::Judge() {
    
    return true;
}


} // namespace brook
