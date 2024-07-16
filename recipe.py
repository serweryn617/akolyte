# Cooking recipe, checkout Cook at https://github.com/serweryn617/cook

from cook.build import BuildStep, LocalBuildServer, local_build_from_list
import os
from pathlib import Path


def docker_command(command):
    return ' '.join(f'''
        docker run --rm -it
        -u {os.getuid()}:{os.getgid()}
        -v {Path.cwd() / 'firmware'}:/workspace/firmware
        -v {Path.cwd() / 'sdk'}:/workspace/sdk
        -v {Path.cwd() / 'build'}:/workspace/build
        -e PICO_SDK_PATH=/workspace/sdk/pico-sdk
        pico-builder
        /bin/bash -c "{command}"
    '''.split())


default_build_server = 'local'
default_project = 'build_all'


build_servers = [
    'local',
]


projects = {}


projects['setup'] = {
    'components': [
        'init_submodules',
        'build_docker',
    ],
}


projects['build_all'] = {
    'components': [
        'firmware',
        'copy_compile_commands',
    ],
}


projects['build_firmware'] = {
    'build_servers': [
        LocalBuildServer(),
    ],

    'build_steps': [
        BuildStep(command='mkdir -p build/generated/pio'),
        BuildStep(command=docker_command("cd /workspace/build && cmake ../firmware -DSIDE=0 && cmake --build . -j")),
    ],
}


projects['docker_interactive'] = local_build_from_list([
    docker_command('')[:-6]
])


projects['firmware'] = local_build_from_list([
    'mkdir -p build',
    ('build', 'mkdir -p generated/pio'),

    ('build', 'cmake ../firmware -DSIDE=0'),
    ('build', 'cmake --build . -j'),
    'cp build/keypad.uf2 keypad_left.uf2',

    ('build', 'cmake ../firmware -DSIDE=1'),
    ('build', 'cmake --build . -j'),
    'cp build/keypad.uf2 keypad_right.uf2',
])


projects['copy_compile_commands'] = local_build_from_list([
    'cp build/compile_commands.json .vscode/compile_commands.json'
])


projects['init_submodules'] = local_build_from_list([
    ('sdk', 'git submodule update --init --depth 1 pico-sdk'),
    'git submodule status',

    ('sdk/pico-sdk/lib', 'git submodule update --init --depth 1 tinyusb'),
    'git submodule status',
])


projects['build_docker'] = local_build_from_list([
    'docker build -t pico-builder .'
])


