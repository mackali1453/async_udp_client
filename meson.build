project('async_udp_client', 'cpp', default_options : ['cpp_std=c++20'])

compiler = meson.get_compiler('cpp')

boost_dep = dependency('boost', modules : ['system'])
ws2Dep = compiler.find_library('ws2_32', required: true)
wsock32Dep = compiler.find_library('wsock32', required: true)

executable('async_udp_client', 'async_udp_client.cpp', dependencies : [boost_dep, ws2Dep, wsock32Dep])
#library('Muscle', 'src/Muscle.cpp', dependencies : [boost_dep, ws2Dep, wsock32Dep])
