//
// Created by Srinj on 6/9/2023.
//

#ifndef LEARNOPENGL_ERROR_H
#define LEARNOPENGL_ERROR_H

#include "LearnOpenGL/callbacks/Callbacks.h"

namespace Callbacks {
    class Error: public Callback {
    public:
        Error() = default;
        ~Error();
        void create() override;
    };
}

#endif //LEARNOPENGL_ERROR_H
