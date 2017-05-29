#ifndef _MATELIB_SCOPE_HPP_
#define _MATELIB_SCOPE_HPP_

namespace Mate {

    template<class T> class Scope {
    public:
        Scope(T& obj) : obj(obj) {
            obj.scope_enter();
        }

        ~Scope() {
            obj.scope_leave();
        }

    private:
        T& obj;
    };

}

#endif