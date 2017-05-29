#include "MateLib/RefCount.hpp"
#include "MateLib/Scope.hpp"

namespace Mate {

    RefCount::RefCount() : cnt(1) { }

    RefCount::~RefCount() { }

    void RefCount::add_ref() {
        Scope<Mutex> lock(mtx);
        cnt++;
    }

    void RefCount::release() {
        Scope<Mutex> lock(mtx);
        cnt--;
        if (!cnt) {
            on_destroy();
        }
    }

    void RefCount::on_destroy() {
        delete this;
    }

}
