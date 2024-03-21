def Settings( **kwargs  ):
    return {
                'flags': [ '-x', 'c++', '-Wall', '-Wextra', '-Werror' ,'-Iinclude' , '-Ilibs/sfml/include', '-Wno-unused-parameter', '-Wno-unused-variable'  ],
    }
