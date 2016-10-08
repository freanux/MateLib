#ifndef _MATELIB_ERASER_HPP_
#define _MATELIB_ERASER_HPP_

#include <algorithm>

namespace Mate {

    template<class T> static bool erase_ptr_element(T *elem) {
        if (elem->delete_me) {
            delete elem;
            return true;
        }

        return false;
    }

    template<class T> static bool erase_ref_element(T& elem) {
        if (elem.delete_me) {
            return true;
        }

        return false;
    }

    template<class T1, class T2> void erase_ptr_elements(T1& elements) {
        elements.erase(std::remove_if(elements.begin(),
        elements.end(), erase_ptr_element<T2>),
        elements.end());
    }

    template<class T1, class T2> void erase_ref_elements(T1& elements) {
        elements.erase(std::remove_if(elements.begin(),
        elements.end(), erase_ref_element<T2>),
        elements.end());
    }

}

#endif