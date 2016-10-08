#ifndef _MATELIB_SCOPE_HPP_
#define _MATELIB_SCOPE_HPP_

namespace Mate {

    template<class T> class Scope {
    public:
        Scope(T& obj) : obj(obj) {
            obj.enter_scope();
        }

        ~Scope() {
            obj.leave_scope();
        }

    private:
        T& obj;
    };

}

#endif